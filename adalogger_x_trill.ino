//trill craft x adalogger
//why is the sd card section of the code not working
#include <SPI.h>
#include <SD.h>
#include <Trill.h>

const int chipSelect = 4; //make sure this is the right pin for adalogger

Trill trillSensor;

void setup() {

//  Serial.begin(115200);
Serial.begin(9600);
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
    int data = trillSensor.rawDataRead();
    if (data < 1000)
      Serial.print(0);
    if (data < 100)
      Serial.print(0);
    if (data < 10)
      Serial.print(0);
    Serial.print(data);
    Serial.print(" ");
  }
 Serial.print(" ");
  String dataString = "";
  for (int analogPin = 0; analogPin < 3; analogPin++) {
    int sensor = analogRead(analogPin); //what is this doing
    dataString += String(sensor);
    if (analogPin < 2) {
      dataString += ",";
    }
  }
  File dataFile = SD.open("trillData.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.println(",");
    dataFile.close();
    Serial.println(dataString);
  } else {
    Serial.println("error opening trillData.txt");
  }
  delay(50);
}
