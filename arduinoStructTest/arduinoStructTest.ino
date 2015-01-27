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

// Pointer arrays to hold station structs
struct weatherStation* stationList = (struct weatherStation*) malloc(sizeof(struct weatherStation));
struct weatherStation* tmpStationList;
// The number of stations currently in the main list
int stationCount = 1;
// Function declarations
void printStation(struct weatherStation* station);

void setup()
{
  // Serial init
  Serial.begin(9600);
  Serial.println("Setup start");
  // Setup first station
  stationList[0].temperature = 98.6;
  stationList[0].humidity = 34;
  stationList[0].pressure = 56;
  strcpy(stationList[0].name, "Inside");
  Serial.println("Setup done");
  printStation(&stationList[0]);
  Serial.println("=================");
  // Increment station count and reallocate memory to prepare for the addition
  // of the second station
  stationCount++;
  tmpStationList = (struct weatherStation*) realloc(stationList, stationCount * sizeof(struct weatherStation));
  // If the temporary pointer array is not NULL, then reallocation is successful and the main array
  // needs to be repointed to the temp pointer array.
  if (tmpStationList != NULL)
  {
    Serial.println(" Resized array successfully");
    stationList = tmpStationList;
  }
  // If tmpStationList is NULL, then memory was not successfully allocated and we have an issue.
  else
  {
    Serial.println(" Did not resize array successfully");
    // Problem!
  }
  // Setup second station record.
  stationList[1].temperature = 68;
  stationList[1].humidity = 45;
  stationList[1].pressure = 67;
  strcpy(stationList[1].name, "Outside");
  printStation(&stationList[1]);
}

void loop() 
{
 // Do nothing here. This space left intentionally blank.
}

// Print station struct's data members.
void printStation(struct weatherStation* station)
{
 Serial.println(station->name);
 Serial.println(station->temperature);
 Serial.println(station->humidity);
 Serial.println(station->pressure); 
}
