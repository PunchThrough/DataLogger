/* 
 This example shows how to get the ambient temperature
 in degrees Celsius from the Bean's built-in temperature sensor 
 and log it on an SD card using the SD library.
 
 Please note that you have to modify the SD library to use 
 it with the Bean.
 
 In Sd2PinMap.h, line 278-281, change the pins to the following:
 SS_PIN = 2;
 MOSI_PIN = 3;
 MISO_PIN = 4;
 SCK_PIN= 5;
 
 This example code is in the public domain. 
 */

#include <SD.h>

const int chipSelect = 2;
uint8_t temp;

void setup()
{
  Serial.begin();
 // Check if the card is present and can be initialized
 if (!SD.begin(chipSelect)) {
    Serial.println("SD fail");
    return;
  }
}

void loop()
{
  // Get the ambient temperature with a range of -40C to 87.5C
  temp = Bean.getTemperature();

  // Open the data file
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
  // If the file is available, write to it:
  if (dataFile) {
    dataFile.println(String(temp));
    dataFile.close();
  }
  
  // If the file isn't open, send an error message over serial
  else {
    Serial.println("error opening datalog.txt");
  }
  
  // Sleep for a minute before we read the temperature again
  Bean.sleep(60000);
}
