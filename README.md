# MilageMeterForBLDC
That program reads impulses from hall sensor in BLDC motor and convert that for distance. Informations are stored in EEPROM. I used Arduino nano and hall sensor connected to D8 pin. As display I used SSD1306 adafruit display using I2C.

If you want use that in your project you should change number in if in line 66.

That number equal = (distance traveled for 30hall impulses) / 100
