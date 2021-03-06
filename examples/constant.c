#include <stdio.h>
#include <benchtool.h>
#include <benchtool_datatypes.h>

benchprop_name_t props[] = {
  "ukey1", "ukey2", "ukey3", "dval",
  NULL
};
benchprop_name_t unique_props[] = {
  "ukey1", "ukey2", "ukey3",
  NULL
};
benchprops_t all_props_f() {
  return props;
}
benchprops_t unique_props_f() {
  return unique_props;
}


int main(int argc, char *argv[]) {
  bench_ctx_t *ctx = get_bench_ctx(all_props_f, unique_props_f);
  bench_setval(ctx, "ukey1", 15);
  bench_setval(ctx, "ukey2", 22);
  bench_setval(ctx, "ukey3", 38);
  bench_setval(ctx, "dval", 9);
  bench_report(ctx);
}
