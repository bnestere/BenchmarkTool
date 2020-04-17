#include <iostream>
#include <fstream>
#include "benchtool.h"
#include "writer/common.hpp"

int nProps;

void init_propvals(benchctx_t *ctx) {
  benchprop_name_t propname;

  BENCHPROPS_ITERATE_AND_COUNT(ctx->props, propname, nProps) {
    printf("Prop[%d]=%s\n", nProps, propname);
  }

  ctx->pinstlist = (benchprop_inst_t*) malloc(sizeof(benchprop_inst_t) * nProps);

  int i;
  BENCHPROPS_ITERATE_AND_COUNT(ctx->props, propname, i) {
    benchprop_inst_t *pinst = &ctx->pinstlist[i];
    pinst->propname = propname;
    pinst->val = 0.f;
    pinst->isset = 0;
  }
}

benchprop_inst_t *get_pinst(benchctx_t *ctx, benchprop_name_t name) {
  benchprop_name_t propname;
  int i;
  BENCHPROPS_ITERATE_AND_COUNT(ctx->props, propname, i) {
    printf("Testing %d\n", i);
    if(propname == name) {
      printf("Found %s\n", propname);

      return &ctx->pinstlist[i];
    }
  }
  return NULL;
}


void bench_setval(benchctx_t *ctx, benchprop_name_t name, benchprop_val_t val) {
  benchprop_inst_t *pinst = get_pinst(ctx, name);
  if(pinst == NULL) {
    printf("pinst is null\n");
    return;
  }
  pinst->val = val;
  pinst->isset = 1;
}

benchctx_t *get_benchctx(benchprops_f all_props, benchprops_f unique_props) {
  //benchprops_t bp = f();
  static benchctx_t ctx;
  ctx.props = all_props();
  ctx.unique_keys = unique_props();

  init_propvals(&ctx);
  

  return &ctx;
}


void bench_report(benchctx_t *ctx) {
  report_csv(ctx);
}
