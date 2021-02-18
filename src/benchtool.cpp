#include <iostream>
#include <fstream>
#include "benchtool.h"
#include "writer/common.hpp"

int nProps;

void init_propvals(bench_ctx_t *ctx) {
  benchprop_name_t propname;

  // Save the number of total properties
  BENCHPROPS_ITERATE_AND_COUNT(ctx->props, propname, nProps); 

  ctx->pinstlist = (benchprop_inst_t*) malloc(sizeof(benchprop_inst_t) * nProps);

  int i;
  BENCHPROPS_ITERATE_AND_COUNT(ctx->props, propname, i) {
    benchprop_inst_t *pinst = &ctx->pinstlist[i];
    pinst->propname = propname;
    pinst->val = 0.f;
    pinst->isset = 0;
  }
}

benchprop_inst_t *get_pinst(bench_ctx_t *ctx, benchprop_name_t name) {
  benchprop_name_t propname;
  int i;
  BENCHPROPS_ITERATE_AND_COUNT(ctx->props, propname, i) {
    if(propname == name) {
      return &ctx->pinstlist[i];
    }
  }
  return NULL;
}


void bench_setval(bench_ctx_t *ctx, benchprop_name_t name, benchprop_val_t val) {
  benchprop_inst_t *pinst = get_pinst(ctx, name);
  if(pinst == NULL) {
    printf("pinst is null\n");
    return;
  }
  pinst->val = val;
  pinst->isset = 1;
}

bench_ctx_t *get_bench_ctx(benchprops_f all_props, benchprops_f unique_props) {
  static bench_ctx_t ctx;
  ctx.props = all_props();
  ctx.unique_keys = unique_props();

  init_propvals(&ctx);
  

  return &ctx;
}


void bench_report(bench_ctx_t *ctx) {
  report_csv(ctx);
}
