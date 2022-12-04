#ifndef __CATALOG_H_
#define __CATALOG_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "sofa.h"
#include "utc.h"

typedef struct __eoparameter_TypeDef{
	
	double xp;			//Earth Orientation Parameters in [radians] (IERS bulletins)
	
	double yp;			//Earth Orientation Parameters in [radians] (IERS bulletins)

}eoparameter_TypeDef;

typedef struct __siData_TypeDef{
	
	double latitude;		//[radians]
	
	double longitude;		//[radians]

	double pressure;		//Ambient pressure (HPa)

	double temperature;	//Temperature (C)

	double humidity;		//Relative humidity (frac)

	double height;		//Height above the reference ellipsoid (m)

	double wavelength;	//Effective color (microns)

	eoparameter_TypeDef eoparameter;

	double dut1;			//UT1-UTC in [seconds] (IERS bulletins)

}siData_TypeDef;

typedef struct __sdData_TypeDef{

	double alpha;			//Right ascension (alpha) in [radians] (ICRS, Epoch=J1991.25)

	double delta;			//Declination (delta) in [radians] (ICRS, Epoch=J1991.25)

	double mu_alpha;		//Proper motion mu_alpha (derivative of alpha) in [radians/yr]

	double mu_delta;		//Proper motion mu_delta (derivative of alpha) in [radians/yr]

	double parallax;		//Trigonometric parallax in arcsecond

	double radial_vel;	//Radial velocity in km/s

}sdData_TypeDef;

typedef struct __rdvector_TypeDef{

	double az;

	double zd;

}rdvector_Typedef;

int catalog_preCal(utc_TypeDef , siData_TypeDef , iauASTROM* );
int catalog_epochConvert(sdData_TypeDef* );
int catalog_Update(utc_TypeDef , double , sdData_TypeDef , iauASTROM* , rdvector_Typedef* );
void reprd(const char* , double );

#ifdef __cplusplus
}
#endif
#endif // !__CATALOG_H_
