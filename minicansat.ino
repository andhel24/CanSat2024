/*
Mini-cansat (grunnprogram)

SD-kort-leser kobles slik:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 ** GND - GND
 ** 3,3 V - 5V  (3,3V-porten på nano klarer ikke levere nok effekt)

*/

#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

const int chipSelect = 4;
Adafruit_BMP280 bmp; // I2C
unsigned long logtid = millis();   // variabel for å holde orden på når sist log ble gjort

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // Initialiserer SD-kort-leser
  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  // Initialiserer BMP280
  unsigned status;
  status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  if (!status) {
    Serial.println("Failed to initialize BMP280");
    while(1);
  }
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

float analogtemp() {
  int x = analogRead(A0);
  return (0.015*x + 27);  // funksjonen som følger av kalibrering av analog temp sensor
}

void log() {
  String dataString = "";
  // leser sensorverdier og legger til tekststreng
  dataString += String(millis()/1000.0) + "   ";
  dataString += String(bmp.readTemperature()) + "   ";
  dataString += String(bmp.readPressure()) + "   ";
  dataString += String(bmp.readAltitude(1013.25)) + "   ";
  dataString += String(analogtemp());

  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  delay(10);
  
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}

void loop() {
  if ((millis()-logtid) > 1000) {
    logtid = millis();
    log();
  }
}









