int motorPin = 3;
int lightSensorPin = A0;
int maxAmountOfLightSamples = 5;
int lightSamplerCounter;
int lightSamples[4];
int amountOfLightAverage;
bool samplingIsDone;

void setup () {
  pinMode(motorPin, OUTPUT);
  pinMode(lightSensorPin, OUTPUT);
  Serial.begin(9600);
  while (! Serial);
}


void loop () {

  if (!samplingIsDone) {
    delay(50);
  }
  
  int amountOfLight = analogRead(lightSensorPin);

  // When we need more samples add value to array.
  if (lightSamplerCounter < maxAmountOfLightSamples) {
    lightSamples[lightSamplerCounter] = amountOfLight;
    lightSamplerCounter++;
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
    if (amountOfLight > 8) {
      analogWrite(motorPin, 255);
    } 
    
    else {
      analogWrite(motorPin, LOW);
    }  
  }

  delay(50);
}
