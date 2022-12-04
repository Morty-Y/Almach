#include <stdio.h>
#include <string.h>
#include "track.h"
#include "calibrate.h"
#include "manual.h"

#define TRACK 		"-t"
#define CALIBRATE	"-c"
#define MANUAL		"-m"

/**
 * @brief The entrance of Almach.
 * @param argc 
 * 		  Count of arguments. For example, if do "./Almach 1 2 3 4", argc = 5.
 * @param argv 
 * 		  Array of string of the arguments. For example, if do "./Almach 1 2 3 4",
 * 		  argv[0] = "./Almach"
 * 		  argv[1] = "1"
 * 		  argv[2] = "2"
 * 		  argv[3] = "3"
 * 		  argv[4] = "4"
 * @return =0 if goes well.
 */
int main(int argc, char* argv[])
{	
	int i = 0;

	if (argc == 2)
	{
		if (strcmp(argv[1], TRACK) == 0)
		{
			printf("track start...\n");
			track();
		}
		else if (strcmp(argv[1], CALIBRATE) == 0)
		{
			printf("calibration start...\n");
			calibrate();
		}
		else if (strcmp(argv[1], MANUAL) == 0)
		{
			printf("manual control...\n");
			manual();
		}
		else
		{
			printf("Almach: incorrect arguments: ");
			for (i = 1; i < argc; i++)
			{
				printf("%s ", argv[i]);
			}
			printf("\n");
		}
	}
	else
	{
		printf("Almach: incorrect arguments: ");
		for (i = 1; i < argc; i++)
		{
			printf("%s ", argv[i]);
		}
		printf("\n");
		
	}

	return 0;
}