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
 *  f: The specification function to determine which properties
 *     will be reported on for this benchmark
 *      
 */
EXTC benchctx_t *get_benchctx(benchprops_f all_props, benchprops_f unique_props);

EXTC void bench_setval(benchctx_t *ctx, benchprop_name_t name, benchprop_val_t val);

/*
 * write the report of the benchmark results
 */
EXTC void bench_report(benchctx_t *ctx);


#undef EXTC

#endif
