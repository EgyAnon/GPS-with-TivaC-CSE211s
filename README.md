# GPS-with-TivaC-CSE211s
A project for the "CSE211s: Introduction to Embedded Systems" course


Team Members: 
Marten Ehab Fouad Askander 2101642.
Mohamed Gamal El-Din Abduljalil 2001078.
Ahmed Gamal Sdeek Ahmed 2002048.
Ahmed Ibrahim Ali Aboshanab 2000267.
Ahmed Haitham Ismael El-Ebidy 2101629.
Mahmoud Hassan Abdelwahab Amin 2001246.

*brief description*
In this this project, we've used the NEO6M GPS module and interfaced it with the Tiva C launchpad
to create a simple embedded system capable of extracting the longitude and latitude of user,
and making simple decisions based on these data.

We have deployed the UART synchronization protocol in making the launchpad communicate with the GPS module, and have wrote functions to calculate distance and toggle LEDs both built in the board and external (on a breadboard, via GPIO).

**NOTES**
1.In building this project, we've used **CODE COMPOSER STUDIO (CCS)** as our preferred compiler.
2.We have left out the startup code of the TM4C123GH6PM microcontroller as it is not the same across compilers, so please make sure you include it before building the project.


