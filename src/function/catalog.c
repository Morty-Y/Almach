#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "sofa.h"
#include "catalog.h"

int catalog_preCal(utc_TypeDef utc,siData_TypeDef siData,iauASTROM *p_astrom)
{
	double utc1, utc2, eo;
	
	if (iauDtf2d("UTC", utc.year, utc.mon, utc.day, utc.hour, utc.min, utc.sec, 
			&utc1, &utc2)) return -1;
	
	if (iauApco13(utc1, utc2, siData.dut1, siData.longitude, siData.latitude, siData.height, siData.eoparameter.xp, 
		            siData.eoparameter.yp, siData.pressure, siData.temperature, siData.humidity, 
	              siData.wavelength, p_astrom, &eo)) return -1;
	
	return 0;
}

int catalog_epochConvert(sdData_TypeDef* p_sdData)
{
	double ep1a, ep1b, ep2a, ep2b;
	
	/* Convert ICRS epoch J1991.25 to ICRS epoch J2000.0*/
	ep1a = 2448349.0625;	//Julian Day of epoch J1991.25
	ep1b = 0.0;
	ep2a = 2451545.0;		//Julian Day of epoch J2000.0
	ep2b = 0.0;

	if(iauPmsafe(p_sdData->alpha, p_sdData->delta, p_sdData->mu_alpha, p_sdData->mu_delta, 
		 p_sdData->parallax, p_sdData->radial_vel, ep1a, ep1b, ep2a, ep2b, &(p_sdData->alpha), 
	   &(p_sdData->delta), &(p_sdData->mu_alpha), &(p_sdData->mu_delta), &(p_sdData->parallax), 
	   &(p_sdData->radial_vel))) return -1;
	
	return 0;
}

int catalog_Update(utc_TypeDef utc, double dut1, sdData_TypeDef sdData, iauASTROM* p_astrom, rdvector_Typedef* p_rdvector)
{
	double utc1, utc2, ut11, ut12, ri, di, aob, zob, hob, dob, rob;
	
	if (iauDtf2d("UTC", utc.year, utc.mon, utc.day, utc.hour, utc.min, utc.sec,
				&utc1, &utc2)) return -1;
	if (iauUtcut1(utc1, utc2, dut1, 
				&ut11, &ut12)) return -1;
	iauAper13(ut11, ut12, p_astrom);
	iauAtciq(sdData.alpha, sdData.delta, sdData.mu_alpha, sdData.mu_delta, sdData.parallax, sdData.radial_vel, p_astrom, &ri, &di);
	iauAtioq(ri, di, p_astrom, &aob, &aob, &hob, &dob, &rob);
	p_rdvector->az = aob;
	p_rdvector->zd = zob;
	
	return 0;
}

void reprd(const char* s, double a)
{
	char pm;
	int i[4];
	printf("%15s", s);
	iauA2af(6, a, &pm, i);
	printf(" %c%2.2d %2.2d %2.2d.%6.6d", pm, i[0], i[1], i[2], i[3]);
}
