#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

#include <Wire.h>
#include <Adafruit_Sensor.h>
//#include "Adafruit_BMP280.h"
#include <Adafruit_BMP085.h>
#include "DHT.h"                                    //Library for the DHT11 Sensor
#include <SD.h> //Load SD library 
int chipSelect = 10; //chip select pin for the MicroSD Card Adapter
File file; // file object that is used to read and write data

//-----------------------------------------------------------------------------------------------------
//                                               DEFINES
//-----------------------------------------------------------------------------------------------------

#define DHTPIN  2                                   //DHT Output on D2
#define DHTTYPE DHT11                               //DHT Type (11,21,22)
//Adafruit_BMP280 bmp; // I2C
 Adafruit_BMP085 bmp;
  

RH_ASK driver(2000,8,7);

struct package                                      //Struct Type Name
{
  float temperature ;                               //Struct Member
  float pressure ;                               //Struct Member
  float alt ;                               //Struct Member
  float humidity ;                                  //Struct Member
};


typedef struct package Package;                     //Define name of
Package data;                                       //Object name
byte tx_buf[sizeof(data)] = {0};

//-----------------------------------------------------------------------------------------------------
//                                            LIBRARY CALLS
//-----------------------------------------------------------------------------------------------------
DHT dht(DHTPIN, DHTTYPE);                           //Create instance of DHT called dht

void setup()
{
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
  readSensor();
    memcpy(tx_buf, &data, sizeof(data) );
  byte zize=sizeof(data);

driver.send((uint8_t *)tx_buf, zize); driver.waitPacketSent();
   Serial.println(data.alt );
  Serial.println(data.humidity );
  Serial.println(data.temperature );
  Serial.println(data.pressure );
file = SD.open("recvdata.csv", FILE_WRITE); // open file to write data
  if (file) {

    file.print(data.alt ); // write number to file
    file.print(","); // write number to file
    file.print(data.humidity); // write number to file
    file.print(","); // write number to file
    file.print(data.temperature); // write number to file
    file.print(","); // write number to file
    file.println(data.pressure); // write number to file
    file.close(); // close file
    Serial.println("1"); // debug output: show written number in serial monitor
  } else {
    Serial.println("0");
  }
   delay(1000);
}

void readSensor()                                   //readSensor function
{
 delay(500);                                       //wait 1 second
 dht.begin();
 bmp.begin();    //Begin the sensor
 data.humidity = dht.readHumidity();                //get humidity & store in Struct variable data.humidity
 data.temperature = bmp.readTemperature();         //get temperature & store in Struct variable data.temperature
 data.pressure = bmp.readPressure();               //get temperature & store in Struct variable data.temperature
 data.alt =  bmp.readAltitude ();  //Change the "1050.35" to your city current barrometric pressure (https://www.wunderground.com)
}
