#ifndef CALCULATIONS_H_
#define CALCULATIONS_H_

/*0.Documentation Section
 *Description: this header file contains functions used to do calculations and act upon data extracted from the GPS module
 *Authors: Mahmoud Hassan Abdelwahab Amin 2001246 &
	Marten Ehab Fouad Askander 2101642 
 */

#include <math.h>
#include "PortF.h"

extern bool reached_target;

/*
 Input: latitudes and longitudes of two points in degrees and fractions of a degree
 Output: as-the-crow-flies distance between the two points in meters
 */
 double distance(double latitude1, double longitude1,double latitude2, double longitude2)
 {
		latitude1 = (latitude1) * (M_PI / 180);
		latitude2 = (latitude2) * (M_PI / 180);
		double latDeltaRad = (latitude2 - latitude1) *	(M_PI / 180);
		double longDeltaRad = (longitude2 - longitude1) * (M_PI / 180);		
		
		double hs_of_distance_over_radius = pow(sin(latDeltaRad / 2), 2) +pow(sin(longDeltaRad / 2), 2) *cos(latitude1) * cos(latitude2);
		double distance_over_radius = 2 * asin(sqrt(hs_of_distance_over_radius));
		return 6371 * distance_over_radius * 1000; // radius of earth is 6371 KM nearly
}

 /*Input: the distance between current point and target point
  *Output: NONE
  *Functionality: modifies the LEDs accoeding to the distance between the current point and target point
  */

void Control_Action(float dist)
{
    if (dist <3)    //target reached - GREEN
    {
        GPIO_PORTD_DATA_R &= ~(0x07);
        GPIO_PORTD_DATA_R |= 0x04;
        reached_target = true;
        ClearLEDs();
        SetGreen();
    }

    else if (dist<10)   //target close - YELLOW
    {
          GPIO_PORTD_DATA_R &= ~(0x07);
          GPIO_PORTD_DATA_R |= 0x02;
          reached_target = false;
          ClearLEDs();
          SetGreen();
          SetRed();
    }
    else    //target far - RED
    {
        GPIO_PORTD_DATA_R &= ~(0x07);
        GPIO_PORTD_DATA_R |= 0x01;
        reached_target = false;
        ClearLEDs();
        SetRed();
    }
}

#endif
