// Define the number of samples to keep track of.  The higher the number,
// the more the readings will be smoothed, but the slower the output will
// respond to the input.  Using a constant rather than a normal variable lets
// use this value to determine the size of the readings array.
const int numReadings = 20;

int readings[numReadings];     
int readIndex = 0;              
int total = 0;                 
int average = 0; 
float tempNormal;  
int previousTemp;             
int checkTemp = 0;
int tempPin = A1;
int currentTemp;
bool firstRun = true;

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
}

void loop() {
  if (firstRun) {
    checkTemp = 0;
        previousTemp = analogRead(tempPin);
       while (checkTemp < 5 ) {
        currentTemp = analogRead(tempPin);
       if (currentTemp == previousTemp){
          checkTemp = checkTemp + 1;
       } else if (checkTemp = 5) {
        tempNormal = currentTemp;
        Serial.println ("Gecralibeert op:" + (String)tempNormal);
        tempNormal = tempNormal/10.000;
        break;
       } else {
        checkTemp = 0;
      }
      previousTemp = currentTemp;
      delay(500);
    }
  }
firstRun = false;

  float cel = average/10.000;
  if (cel > tempNormal)
{
  digitalWrite(13, HIGH);   
}
else
{
  digitalWrite(13, LOW);    
}
  
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(tempPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.print("TEMPERATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  Serial.print("CHECKTEMP = ");
  Serial.print(checkTemp);
  Serial.println();
  Serial.print("TEMPNORMAL = ");
  Serial.print(tempNormal);
  Serial.println();
  delay(300);        // delay in between reads for stability
}
