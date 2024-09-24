/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/

// the setup routine runs once when you press reset:
float AtilC(int x) {
  return (0.1092 * x - 30.4);
}
int tid = millis();
int tid_2 = millis();
int lys = 0;
int i = 0;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  lys = lys + sensorValue;
  i = i + 1;
  // print out the value you read:
  if (millis() - tid > 1000) {
    Serial.println(lys / i);
    tid = millis();
    lys = 0;
    i = 0;
  }
  if (millis() - tid_2 > 1000 * 60) {
    Serial.println("Nå har det gått nok et minutt");
    tid_2 = millis();
  }
  //Serial.print(AtilC(sensorValue)); Serial.println("*C");
}
