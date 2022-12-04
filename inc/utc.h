#ifndef __UTC_H_
#define __UTC_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/time.h>
#include <time.h>

typedef struct __utc_TypeDef{

	struct timeval tv;

	int year;

	int mon;

	int day;

	int hour;

	int min;

	double sec;

}utc_TypeDef;



int utc_Report(utc_TypeDef );
int utc_Update(utc_TypeDef* );

#ifdef __cplusplus
}
#endif
#endif // !__UTC_H_