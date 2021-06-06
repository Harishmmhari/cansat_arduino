#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;
char temperatureChar[10];
char pressureChar[10];
char altChar[10];
char humidityChar[10];

struct package                                      //Struct Type Name
{
  float temperature = 0.0;                          //Struct Member                        
  float humidity = 0.0;                             //Struct Member
  float pressure = 0.0;                               //Struct Member
  float alt = 0.0 ;                               //Struct Member
};

typedef struct package Package;                     //Define name of
Package data;                                       //Object name

void setup()
{
    Serial.begin(9600);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[sizeof(data)];                      //unsigned int 8 bit called buf with size specified in Struct member data
    uint8_t buflen = sizeof(data);                  //unsigned int 8 bit called buflen with size specified in Struct member data
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
    memcpy(&data,&buf,buflen);                      //memcpy ( void * destination, const void * source, size_t num );
    Serial.print(data.temperature);                  //print temperature in C to serial port
  Serial.print(",");                  
 Serial.print(data.humidity);                    //print humidity to serial port
  Serial.print(",");                  
 Serial.print(data.alt);                    //print alt to serial port
Serial.print(",");                  
Serial.print(data.pressure);                    //print pressure to serial port
   Serial.println();                  
    }
}
