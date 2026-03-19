## Hallway Light System - 1.1P



&#x20;                                                     



##### Lights.cpp



Contains the lightsOn and lightOff methods. Takes the 

appropriate light pin as an argument, and writes power as

either HIGH or LOW depending on method called. 



&#x20;                                                       



##### Lights.h



Interface for light methods, and can be refactored if 

required for scalability. 



Included in main program with #include "Lights.h"







&#x20;                                                       

##### Task1.1Lights\_ON.ino



Contains the main program logic. Imports modular on/off methods from

Lights.cpp. Initialises necessary lights and button. On button press

calls lightON method for both lights, then after 30 seconds will 

call lightOff for Door, then for Hallway 30 seconds later. 









&#x20;



