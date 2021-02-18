#include "benchtool_datatypes.h"

#ifndef __BENCHMARKTOOL_H__
#define __BENCHMARKTOOL_H__

#ifdef __cplusplus
#define EXTC extern "C"
#else
#define EXTC
#endif


/*
 * Factory method to retrieve a benchmark tool context.
 * The properties of the context are set through the
 * function pointer parameter
 * 
 * Arguments
 *  all_props: All properties to save for the particular benchmark
 *  unique_props: Properties that uniquely identify a run
 *      
 */
EXTC bench_ctx_t *get_bench_ctx(benchprops_f all_props, benchprops_f unique_props);

/*
 * Set a value for a given benchmark run
 *
 * Arguments
 *  ctx: The benchmark context to save the value in
 *  name: The name of the property to set a value for
 *  val: The value of the property
 */
EXTC void bench_setval(bench_ctx_t *ctx, benchprop_name_t name, benchprop_val_t val);

/*
 * Write the report of the benchmark results
 *
 * Arguments
 *  ctx: The benchmark context to write all property names/values for
 */
EXTC void bench_report(bench_ctx_t *ctx);


#undef EXTC

#endif
