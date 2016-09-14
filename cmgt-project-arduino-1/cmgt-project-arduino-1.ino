const int motorPin = 3;
const int lightSensorPin = A0;
const int maxAmountOfLightSamples = 5;
int lightSamplerCounter;
int lightSamples[4];
int amountOfLightAverage;
bool samplingIsDone;
bool motorIsRunning;

void setup () {
  pinMode(motorPin, OUTPUT);
  pinMode(lightSensorPin, OUTPUT);
  Serial.begin(9600);
}


void loop () {
  
  int amountOfLight = analogRead(lightSensorPin);

  Serial.println("Amount of light: " + (String)amountOfLight);
  
  // When we need more samples add value to array.
  if (lightSamplerCounter < maxAmountOfLightSamples) {
    lightSamples[lightSamplerCounter] = amountOfLight;
    lightSamplerCounter++;
    
    // Wait 50ms for our next sample to get a better average.
    delay(50);
  }
  
  // When sampling is done calculate the average of all values in our array.
  else if (!samplingIsDone) {
    for (int i = 0; i < maxAmountOfLightSamples; i++) {
      amountOfLightAverage += lightSamples[i];

      if (i == maxAmountOfLightSamples - 1) {
        samplingIsDone = true;
        amountOfLightAverage /= maxAmountOfLightSamples;
        Serial.println("AVERAGE: " + (String)amountOfLightAverage);
      }
    }
  }

//  Serial.println("=== BEGIN SAMPLES ===");
//  
//  for (int i = 0; i < maxAmountOfLightSamples; i++) {
//    Serial.println(lightSamples[i]); 
//  }
//  
//  Serial.println("=== END SAMPLES ===");

  if (samplingIsDone) {

    // When amount of light exceeds average plus 4, start motor after 3 seconds.
    if (amountOfLight > amountOfLightAverage + 4 && !motorIsRunning) {
      Serial.println("motor is running");

      if (!motorIsRunning) {
        delay(3000);
        motorIsRunning = true;
        analogWrite(motorPin, 255);
      }
    } 

    // When amount of light is less than average, stop motor.
    else if (amountOfLight <= amountOfLightAverage + 4) {
      Serial.println("motor stopped");
      motorIsRunning = false;
      analogWrite(motorPin, LOW);
    }  
  }
}
