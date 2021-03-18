//trill craft x adalogger
//why is the sd card section of the code not working
#include <SPI.h>
#include <SD.h>
#include <Trill.h>

const int chipSelect = 4; //make sure this is the right pin for adalogger

Trill trillSensor;
int data = 0;

void setup() {
  Serial.begin(115200);

  while (!Serial) {// wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");

  int ret = trillSensor.setup(Trill::TRILL_CRAFT);
  if (ret != 0) {
    Serial.println("failed to initialise trillSensor");
    Serial.print("Error code: ");
    Serial.println(ret);
  }
}

void loop() {
  delay(100);
  trillSensor.requestRawData();

  while (trillSensor.rawDataAvailable() > 0) {
    data = trillSensor.rawDataRead();
    if (data < 1000)
      Serial.print(0);
    if (data < 100)
      Serial.print(0);
    if (data < 10)
      Serial.print(0); //FOR LATER
    Serial.print(data);
    Serial.print(" ");
  }
 
// File dataFile = SD.open("trillData.txt", FILE_WRITE);
File dataFile = SD.open("datalog.txt", FILE_WRITE);
  //int data = trillSensor.rawDataRead();
  if (dataFile) {
    //IF DATA >10 = SAVE DATA (leave 0)
   dataFile.print(data);  //only one line of data being printed to file
   dataFile.println(",");
    dataFile.close();
  Serial.println(data);  
  } else {
    Serial.println("error opening file"); //error fixed by changing name back to datalog idk why
  }
  delay(50);

}
