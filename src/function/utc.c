#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "utc.h"


int utc_Report(utc_TypeDef utc)
{
    printf("UTC: %4d-%2d-%2d %2d:%2d:%2.6f\n", 
    utc.year, utc.mon, utc.day, utc.hour, utc.min, utc.sec);

    return 0;
}

int utc_Update(utc_TypeDef* p_utc)
{
    struct tm* temp;

    gettimeofday(&(p_utc->tv), NULL);
    temp = gmtime(&(p_utc->tv.tv_sec));
    p_utc->year = temp->tm_year + 1900;
    p_utc->mon = temp->tm_mon;
    p_utc->day = temp->tm_mday;
    p_utc->hour = temp->tm_hour;
    p_utc->min = temp->tm_min;
    p_utc->sec = (double) temp->tm_sec + (p_utc->tv.tv_usec / 1000000.0);
    
    return 0;
}