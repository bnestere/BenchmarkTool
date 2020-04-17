#ifndef __BENCHTOOL_TYPES_H__
#define __BENCHTOOL_TYPES_H__

#ifdef __cplusplus
#define EXTC extern "C"
#else
#define EXTC
#endif

typedef const char* benchprop_name_t;
typedef double benchprop_val_t;
typedef benchprop_name_t* benchprops_t;
typedef benchprops_t (*benchprops_f)();

typedef struct _benchprop_inst_t {
  benchprop_name_t propname;
  benchprop_val_t val;
  int isset;
} benchprop_inst_t;


typedef struct _benchctx_t {
  benchprops_t props; // all property names supported by a benchmark
  benchprops_t unique_keys; //  list of property names with values that uniquely identify a record
  benchprop_inst_t *pinstlist; // instantiation list of all properties
} benchctx_t;

#define BP_DECL(x) BP_VAR(x)
#define ITER_VAR   BP_DECL(__LINE__)
#define BP_UNIQUE_VAR(x) bpunique##x##var
#define BP_UNIQUE_DECL(z) BP_UNIQUE_VAR(z) 
#define BP_UNIQUE BP_UNIQUE_DECL(__LINE__)

#define BP_INIT_ITER(i, iter, props) i=0, iter = props[i]
#define BENCHPROP_CONTINUE(nameiter) (nameiter != NULL && nameiter != 0 && *nameiter !=  '\0')
#define BENCHPROP_NEXT(i, iter, props) iter = props[++i]

#define BENCHPROPS_ITERATE_AND_COUNT(props, iter, i) for( \
    BP_INIT_ITER(i, iter, props); \
    BENCHPROP_CONTINUE(iter); \
    BENCHPROP_NEXT(i, iter, props))

#define BENCHPROPS_ITERATE_AND_COUNT_INTERNAL(props, iter, i) int i; BENCHPROPS_ITERATE_AND_COUNT(props,iter,i)

#define BENCHPROPS_ITERATE(props, iter) BENCHPROPS_ITERATE_AND_COUNT_INTERNAL(props, iter, BP_UNIQUE)

#undef EXTC

#endif
