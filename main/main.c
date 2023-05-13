                /*0.Documentation Section: main.c*/
//Authors: Ahmed Haitham Ismael El-Ebidy 2101629
//Description: the main C file for our GPS/Tiva C project.


                    /*1.Includes and defines*/
#include "../_headers_/tm4c123gh6pm.h"
#include "../_headers_/UART_Functions.h"
#include "../_headers_/StringProcessing.h"
#include "../_headers_/SysTick.h"
#include "../_headers_/calculations.h"
#include "../_headers_/PortF.h"
#include "../_headers_/PortD.h"
#include <stdbool.h>

#define target1_lat 00.00000000             //hard-coded latitude of target point
#define target1_long 00.00000000            //hard-coded longitude of target point

                    /*2.Global Variables*/
char gps_dump[100];                            //a character array to temporarily hold read NMEA sequences from the GPS module
char GPGGA[75];                                //a character array to hold the last read GPGGA sequence (valid or not)
bool GPGGA_Fix;                                //is true if a valid fix is obtained, false otherwise
float longitude;                               //latest longitude from GPS module
float latitude;                                //latest latitude from GPS module
unsigned char satellite_count;                 //if a valid fix is obtained, this variable holds the number of satellites used in the fix
float distance_to_target;                     //holds the latest calculated distance between current point
                                               //and the hardcoded target point
float Start_Latitude;                          //Latitude of starting point
float Start_Longitude;                         //Longitude of starting point
float Final_Distance;                          //distance between starting point and target point
bool reached_target;


                    /*3.main function*/
int main(void)
{
    /*One-time initialization of services and parameters*/
    PLL_init(); //Using PLL to switch to 80MHz operating frequence (HIGH PERFORMANCE MODE)
    UART1_Init(80000000,9600); //Initializing UART Protocol on PORT B with a Baud Rate of 9600
    PortF_Init();           //Initializing PortF
    PortD_Init();           //Initializing PortD

    GPGGA_Fix = false;  //assume no fix is obtained on start
    distance_to_target = 0x0FFFFF;
    satellite_count = 0;
    Reset_Fields();     //clearing arrays

            /*main execution loop*/
    while(1)
    {
        UART1_InString(gps_dump,100);   //read a NMEA sequence from GPS module
        Message_Classifier(gps_dump);   //if the sequence is a GPGGA sequence, keep it in GPGGA array

        if(GPGGA_Fix)   //if a valid fix is obtained, extract useful data, and take action.
        {
            longitude = Extract_Longitude(GPGGA);
            latitude = Extract_Latitude(GPGGA);
            satellite_count = Extract_Satellite_Count(GPGGA);
            distance_to_target = distance(latitude,longitude,target1_lat,target1_long); //calculate the distance to a pre-specified target
            Control_Action(distance_to_target);

            if(Read_SW1())  //if switch 1 is pressed, store the current longitude and latitude (STARTING POINT)
            {
                Start_Latitude = latitude;
                Start_Longitude = longitude;
            }
        }

        else    //if no valid fix is obtained, turn off LEDs
        {
            GPIO_PORTD_DATA_R &=~(0x07);
            ClearLEDs();
        }
    }
}
