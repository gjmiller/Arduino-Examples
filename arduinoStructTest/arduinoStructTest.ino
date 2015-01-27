#include <stdlib.h>
#include <string.h>

struct weatherStation
{
 float temperature;
 float humidity;
 float pressure;
 char name[20];
 double lastUpdateMillis;
};

struct weatherStation* stationList = (struct weatherStation*) malloc(sizeof(struct weatherStation));
struct weatherStation* tmpStationList;
int stationCount = 1;
void printStation(struct weatherStation* station);

void setup()
{
  // Serial init
  Serial.begin(9600);
  Serial.println("Setup start");
  stationList[0].temperature = 98.6;
  stationList[0].humidity = 34;
  stationList[0].pressure = 56;
  strcpy(stationList[0].name, "Inside");
  Serial.println("Setup done");
  printStation(&stationList[0]);
  Serial.println("=================");
  stationCount++;
  tmpStationList = (struct weatherStation*) realloc(stationList, stationCount * sizeof(struct weatherStation));
  if (tmpStationList != NULL)
  {
    Serial.println(" Resized array successfully");
    stationList = tmpStationList;
  }
  else
  {
    Serial.println(" Did not resize array successfully");
    // Problem!
  }
  stationList[1].temperature = 68;
  stationList[1].humidity = 45;
  stationList[1].pressure = 67;
  strcpy(stationList[1].name, "Outside");
  printStation(&stationList[1]);
}

void loop() 
{

}

void printStation(struct weatherStation* station)
{
 Serial.println(station->name);
 Serial.println(station->temperature);
 Serial.println(station->humidity);
 Serial.println(station->pressure); 
}
