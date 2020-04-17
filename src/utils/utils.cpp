#include "utils.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

const char *get_env_charp_or_default(const char *envVarName, const char *dflt) {
  const char *val;
  val = getenv(envVarName);
  cout << "getting env var " << envVarName << " as " << val << "\n";
  if(val == NULL) val = dflt;
  cout << "val is now " <<  val << "\n";
  return val;
}
