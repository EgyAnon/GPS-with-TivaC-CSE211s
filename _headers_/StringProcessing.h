#ifndef  _STRINGPROCESS_H_
#define _STRINGPROCESS_H_

/*0.Documentation Section*/
/* Description: this header file contains all the functions required to read extract useful data from the GPS module
 * Authors: Ahmed Haitham Ismael El-Ebidy 2101629
 *	    Ahmed Gamal Sdeek Ahmed 2002048
 */


#include <string.h>
#include <stdio.h>
#include <stdbool.h>

extern char gps_dump[100];
extern char GPGGA[75];
extern bool GPGGA_Fix;


//fills the character fields with zeros for initialization and debugging purposes
void Reset_Fields(void)
{
    memset(gps_dump,0,100);
	memset(GPGGA,0,75);
}

//filters the GPGGA messages from all other NMEA sequences
void Message_Classifier(char* gps_dump)
{
	if (strncmp(gps_dump,"$GPGGA",6)==0)
	{
		strcpy(GPGGA,gps_dump);
		if(GPGGA[44]=='1') GPGGA_Fix = true;
	}
	else return;
}

//extracts the latitude from a standard GPGGA sequence in degrees and fractions of a degree format.
float Extract_Latitude(char *GPGGA_Sequence)
{
	float latitude  = 0;
	int i;
	for(i = 0; i<10;i++)
	{
		if(i==4) continue;
		
		latitude*=10;
		latitude+=(GPGGA[17+i]-48);
	}
	
	latitude/=10000000;
	latitude = (int)latitude + (latitude-(int)latitude)*10/6;
	return latitude;
}

//extracts the longitude from a standard GPGGA sequence in degrees and fractions of a degree format.
float Extract_Longitude(char *GPGGA_Sequence)
{
    float longitude  = 0;
    int i;
    for(i = 0; i<11;i++)
    {
        if(i==5) continue;

        longitude*=10;
        longitude+=(GPGGA[30+i]-48);
    }

    longitude/=10000000;
    longitude = (int)longitude+(longitude-(int)longitude)*10/6;
    return longitude;
}

unsigned char Extract_Satellite_Count(char *GPGGA_Sequence)
{
    return ((GPGGA_Sequence[46]-48)*10+(GPGGA_Sequence[47]-48));
}

#endif
