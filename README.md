# LiquidDuo
Liquid crystal display, DUO

## Info about the project:

Displays we are using are ***QAPASS 1602a***, they are 2x16 lcd displays (Meaning 2 rows x 16 cols)
For communication we have two slave ***arduinos*** that get informations from master mainboard
For programming the arduinos we used ***Arduino IDE***, but since we need to communicate with **AVR** mainboard, we used atom for whole project as well
For communication between mainboard and arduinos we used ***UART*** communcation, and between arduinos and lcds we use ***I2C*** communication
The library for lcds needs to be downloaded, you can find it here: ***http://www.arduinolibraries.info/libraries/liquid-crystal-i2-c***

Since the robot will be quite large, we need mainboard to keep track of our score, then, mainboard sends informations about the score to the arduinos, not whole number, but each digit on it's own, then arduinos read the informations and send it to lcds that are defined by their own addresses
