#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <iomanip>

#include "../benchtool_datatypes.h"
#include "../utils/utils.hpp"

using namespace std;

void bench_write_line_csv_stream(bench_ctx_t *ctx, std::ostream& out) {
  benchprops_t props = ctx->props; 
  int i;
  const char *nameiter;
  for(i=0, nameiter = props[i]; nameiter != NULL; nameiter = props[++i]) {
    if(i > 0) out << ",";
    out << nameiter;
  }
  out << "\n";
}

void bench_write_vals_stream(bench_ctx_t *ctx, std::ostream& out,
    std::vector<int> *file2appidx) {
  int filei = 0;
  for(int appi : *file2appidx) {
    if(filei > 0) out << ",";
    if(ctx->pinstlist[appi].isset) out << std::setprecision(4) << ctx->pinstlist[appi].val;
    filei++;
  }

  out << std::endl;

}

const std::string _filename = "report.csv";
const char* ENV_FILENAME = "BENCHTOOL_FILE";


void bench_get_filename(bench_ctx_t *ctx, string *str) {
  str->append(string(get_env_charp_or_default(ENV_FILENAME, _filename.c_str())));
}

void bench_get_tmp_filename(bench_ctx_t *ctx, string *str) {
  bench_get_filename(ctx,str);
  str->append(".tmp");
  //str.append(bench_get_filename(ctx, str) + ".tmp";
  //return bench_get_filename
  //return _tmpfilename;
}

void overwrite_report(bench_ctx_t *ctx) {

  
  std::string filename;
  bench_get_filename(ctx, &filename);

  std::string tmpfilename;
  bench_get_tmp_filename(ctx, &tmpfilename);

  //std::cout << "fn " << filename << " :: tfn " << tmpfilename << "\n";

  std::ifstream ifs(tmpfilename.c_str(), std::ios::binary);
  std::ofstream ofs(filename.c_str(), std::ios::binary);

  ofs << ifs.rdbuf();
}



void process_first_line(bench_ctx_t *ctx, std::string propname_line, vector<int> *file2appidx) {
  std::istringstream propstream(propname_line);

  while(propstream) {
    std::string propname;
    if(!std::getline(propstream, propname, ',')) break;

    int appi;
    benchprop_name_t iter;
    BENCHPROPS_ITERATE_AND_COUNT(ctx->props, iter, appi) {
      if(strcmp(propname.c_str(), iter) == 0) {
        file2appidx->push_back(appi); 
        break;
      }
    }
  }
}

int record_matches_ctx(bench_ctx_t *ctx, std::string line, vector<int> *file2appidx) {

  std::istringstream valstream(line);

  //benchprop_val_t fileVal;
  int matchingValues = 0;
 // while(propstream) {
  int filei = 0;
  for(benchprop_val_t fileVal; valstream >> fileVal;) {

// first check if the property is unique to the record
    int appi = file2appidx->at(filei);
    benchprop_name_t propname = ctx->props[appi];


    int ci;
    benchprop_name_t uniquekey;
    BENCHPROPS_ITERATE_AND_COUNT(ctx->unique_keys, uniquekey, ci) {
      // is the property unique?
      if(strcmp(uniquekey,propname) == 0) {
        // yes

        // does the key match?
        if(fileVal == ctx->pinstlist[ci].val) {
          matchingValues++;
          continue;
        }
      }
    }
    filei++;
    if(valstream.peek() == ',' || valstream.peek() == ' ') {
      valstream.ignore();
    }
  }

  int nUniques;
  benchprop_name_t pname;
  BENCHPROPS_ITERATE_AND_COUNT(ctx->unique_keys, pname, nUniques);
  // Does the amount of values that matched equal the amount of unique keys?
  return matchingValues == nUniques;
}

void report_csv(bench_ctx_t *ctx) {
  ostringstream csv;
  
  std::string filename;
  bench_get_filename(ctx, &filename);
  std::string tmpfilename;
  bench_get_tmp_filename(ctx,&tmpfilename);

  std::ofstream ofs(tmpfilename.c_str(), std::ofstream::out);
  std::ifstream ifs(filename.c_str());

 bench_write_line_csv_stream(ctx, ofs);

  std::vector<int> file2appidx;

  ifstream in_file(filename.c_str());
  if(in_file.good()) {
    // Existing file exist to merge with
    vector<benchprop_name_t> props;
    
    std::string line;
    int firstLine = 1;
    while(std::getline(in_file, line)) {
      // process property names in order
      if(firstLine) {
        process_first_line(ctx, line, &file2appidx);       
        firstLine = 0;
        continue;
      } 

      if(record_matches_ctx(ctx,line,&file2appidx)) {
        cout << "Found matching record!" << "\n";
        continue;
      } 

      ofs << line << std::endl;
    }
  } else {
    int appi;
    benchprop_name_t name;
    BENCHPROPS_ITERATE_AND_COUNT(ctx->props, name, appi) {
      file2appidx.push_back(appi); 
    }
  }

 bench_write_vals_stream(ctx, ofs, &file2appidx); 
 ofs.close();
 
 overwrite_report(ctx);
}
