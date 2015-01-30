// This sketch will cause an XBee radio attached to the Arduino to
// listen for requests from another XBee radio. It will take the
// payload received by the XBee and add it to a dynamically allocated
// array of strings (character arrays). It will attempt to grow the 
// array holding the strings as it adds them.

// In order to use this sketch, the XBee radio (Series 1 used here)
// must be setup to use API mode (AP=2 in X-CTU).
// I use pins 2 and 3 here, but those can be changed in the defines
// below.

#include <XBee.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
#include <string.h>

#define ssRxPin 2
#define ssTxPin 3

// Setup XBee variables
SoftwareSerial nss(ssRxPin, ssTxPin);
XBee xbee = XBee();
Rx16Response rx16 = Rx16Response();
uint16_t addr16;
// Setup string storage
unsigned int stringCount = 0;
char **stringArray = (char **) malloc(stringCount * sizeof(char *));
char **tmpStringArray;


void setup()
{
 Serial.begin(9600);
 nss.begin(9600);
 xbee.setSerial(nss);
 Serial.println("Done with setup"); 
}

void loop()
{
 // Read data from the XBee
 xbee.readPacket();
 if(xbee.getResponse().isAvailable())
 {
  Serial.println("Received data");
  if (xbee.getResponse().getApiId() == RX_16_RESPONSE)
  {
   xbee.getResponse().getRx16Response(rx16);
   // When data is received, try to add it to the array holding strings.
   stringCount++;
   Serial.print("String count is ");
   Serial.println(stringCount);
   // Reallocate the string holder to hold the incoming string.
   tmpStringArray = (char **) realloc(stringArray, stringCount * sizeof(char *));
   if (tmpStringArray != NULL)
   {
    // If the reallocation was successful, store the new string.
    stringArray = tmpStringArray;
    // Make space at the end of the string holder.
    stringArray[stringCount - 1] = (char *) malloc(21);
    // Get data out of the XBee response and store it in the last space of the
    // string holder.
    memcpy(stringArray[stringCount - 1], rx16.getData(), 20);
    // Print the new data from the array to make sure it was stored correctly
    // and that it can be retrieved successfully.
    Serial.println(stringArray[stringCount - 1]);
    Serial.println();
   }
   else
   {
    // If there's a problem reallocating memory for the string holder,
    // we have a problem and need to stop here.
    Serial.println("Error reallocating memory!");
    delay(999999999);
   }
  }
  else if (xbee.getResponse().isError())
  {
   Serial.print("Error reading packet. Error code is ");
   Serial.println(xbee.getResponse().getErrorCode());
  }
 }
}
