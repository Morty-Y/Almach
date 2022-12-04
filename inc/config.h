#ifndef __CONFIG_H_
#define __CONFIG_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "catalog.h"

#define BUFSIZE 30
#define DEVAL '\0'
#define DAS2R (4.848136811095359935899141e-6)	/* arcsec to radians */

void config_Get(siData_TypeDef* siData, sdData_TypeDef* trace, sdData_TypeDef* clbrt, const char* file_path);
void config_keyGet(const char* file_path, const char* section_name, const char* key_name, char* buf);
void config_dhmsStand(char* buf, int* p_dh, int* p_min, double* p_sec);

#ifdef __cplusplus
}
#endif
#endif // !__CONFIG_H_