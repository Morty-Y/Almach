#include <stdio.h>
#include <stdlib.h>
#include "minIni.h"
#include "config.h"

int missing_count = 0;

void config_keyGet(const char* file_path, const char* sec, const char* key, char* buf)
{
    char deval[1] = { DEVAL };

    ini_gets(sec, key, deval, buf, BUFSIZ, file_path);
    if(*(buf) == DEVAL){
        printf("%15s: load failed!\n", key);
        missing_count++;
        return;
    }
    else
        printf("%15s: %s\n", key, buf);
        
}


void config_dhmsStand(char* buf, int* p_dh, int* p_min, double* p_sec)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char temp[3][10] = { 0 };

    for ( i = 0; i < BUFSIZE; i++)
    {   
        if((',' <= buf[i]) && (buf[i] <= '9'))
        {
            if(('0' <= buf[i]) || (buf[i] == '.') || (buf[i] == '-'))
            {
                temp[j][k] = buf[i];
                k++;
            }
            else
            {
                j++;
                k = 0;
                if (j > 2){
                    printf("format error\n");
                    return;
                }
            }
        }
    }
    *(p_dh) = atoi(temp[0]);
    *(p_min) = atoi(temp[1]);
    *(p_sec) = atof(temp[2]);
}

/**
 * @brief Read data from config.ini
 * @param siData
 *        Return: Star-Independent Data
 * @param track 
 *        Return: Track Star Data
 * @param clbrt 
 *        Return: Calibration Star Data
 * @param file_path 
 *        Give: config.ini file path.
 */
void config_Get(siData_TypeDef* siData, sdData_TypeDef* track, sdData_TypeDef* clbrt, const char* file_path)
{
    char buf[BUFSIZE] = { 0 };
    int deg, hour, min;
    double sec;

/*     if(config_intCheck(file_path))
            return; */

    printf("[Star-Independent Parameters]\n");
    config_keyGet(file_path, "Star-Independent Parameters", "latitude", buf);
    config_dhmsStand(buf, &deg, &min, &sec);
    if(deg > 0)
        iauAf2a(' ', deg, min, sec, &(siData->latitude));
    else
        iauAf2a('-', deg, min, sec, &(siData->latitude));
    

    config_keyGet(file_path, "Star-Independent Parameters", "longitude", buf);
    config_dhmsStand(buf, &deg, &min, &sec);
    if(deg > 0)
        iauAf2a(' ', deg, min, sec, &(siData->longitude));
    else
        iauAf2a('-', deg, min, sec, &(siData->longitude));

    config_keyGet(file_path, "Star-Independent Parameters", "pressure", buf);
    siData->pressure = atof(buf);

    config_keyGet(file_path, "Star-Independent Parameters", "temperature", buf);
    siData->temperature = atof(buf);

    config_keyGet(file_path, "Star-Independent Parameters", "humidity", buf);
    siData->humidity = atof(buf);

    config_keyGet(file_path, "Star-Independent Parameters", "height", buf);
    siData->height = atof(buf);

    config_keyGet(file_path, "Star-Independent Parameters", "wavelength", buf);
    siData->wavelength = atof(buf);

    config_keyGet(file_path, "Star-Independent Parameters", "eoparameter_xp", buf);
    siData->eoparameter.xp = atof(buf) * DAS2R;

    config_keyGet(file_path, "Star-Independent Parameters", "eoparameter_yp", buf);
    siData->eoparameter.yp = atof(buf) * DAS2R;

    config_keyGet(file_path, "Star-Independent Parameters", "dut1", buf);
    siData->dut1 = atof(buf);


    printf("[Track Star]\n");
    config_keyGet(file_path, "Track Star", "alpha", buf);
    config_dhmsStand(buf, &hour, &min, &sec);
    if (hour > 0)
        iauTf2a(' ', hour, min, sec, &(track->alpha));
    else
        iauTf2a('-', hour, min, sec, &(track->alpha));


    config_keyGet(file_path, "Track Star", "delta", buf);
    config_dhmsStand(buf, &deg, &min, &sec);
    if(deg > 0)
        iauAf2a(' ', deg, min, sec, &(track->delta));
    else
        iauAf2a('-', deg, min, sec, &(track->delta));
    

    config_keyGet(file_path, "Track Star", "mu_alpha", buf);
    track->mu_alpha = (atof(buf) / 1000.0) * DAS2R / cos(track->delta);

    config_keyGet(file_path, "Track Star", "mu_delta", buf);
    track->mu_delta = (atof(buf) / 1000.0) * DAS2R;

    config_keyGet(file_path, "Track Star", "parallax", buf);
    track->parallax = atof(buf) / 1000.0;

    config_keyGet(file_path, "Track Star", "radial_vel", buf);
    track->radial_vel = atof(buf);

    printf("[Calibration Star]\n");
    config_keyGet(file_path, "Calibration Star", "alpha", buf);
    config_dhmsStand(buf, &hour, &min, &sec);
    if (hour > 0)
        iauTf2a(' ', hour, min, sec, &(clbrt->alpha));
    else
        iauTf2a('-', hour, min, sec, &(clbrt->alpha));


    config_keyGet(file_path, "Calibration Star", "delta", buf);
    config_dhmsStand(buf, &deg, &min, &sec);
    if(deg > 0)
        iauAf2a(' ', deg, min, sec, &(clbrt->delta));
    else
        iauAf2a('-', deg, min, sec, &(clbrt->delta));
    

    config_keyGet(file_path, "Calibration Star", "mu_alpha", buf);
    clbrt->mu_alpha = (atof(buf) / 1000.0) * DAS2R / cos(clbrt->delta);

    config_keyGet(file_path, "Calibration Star", "mu_delta", buf);
    clbrt->mu_delta = (atof(buf) / 1000.0) * DAS2R;

    config_keyGet(file_path, "Calibration Star", "parallax", buf);
    clbrt->parallax = atof(buf) / 1000.0;

    config_keyGet(file_path, "Calibration Star", "radial_vel", buf);
    clbrt->radial_vel = atof(buf);

    if (missing_count > 0)
    {
        printf("\nWarning: %d missing parameter\n\n", missing_count);
    }
}
