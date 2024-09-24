/*
Temperatursensor
Fast motstand og NTC bør ha omtrent samme verdi ved romtemperatur.
NTC -> GND + A0
Motstand -> 5V + A0

Temperaturberegningen som gjøres i rutninen temperatur finner man ved kalibrering mot kjent
temperatur. Mål A0 for ulike temperaturverdier med et termometer
og finn f.eks. ved regresjon sammenhengen mellom målt temperatur og verdi på A0.
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

float temperatur(int x) {
  return(0.015*x+20);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.print("A0: "); Serial.print(sensorValue);
  Serial.print("Temperatur: "); Serial.print(temperatur(sensorValue)); Serial.println("*C");
  delay(1000);  // delay in between reads for stability
}
