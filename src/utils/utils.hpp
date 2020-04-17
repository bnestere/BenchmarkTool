#include "../benchtool_datatypes.h"
#ifndef __BENCHTOOL_UTILS_H__
#define __BENCHTOOL_UTILS_H__

/*
 * Get a value from the env
 */
const char *get_env_charp_or_default(const char *envVarName, const char *dflt);

#undef EXTC
#endif
