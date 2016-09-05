int thermistorPin = A0;
int motorPin = 3;
int temperatureThreshold = 220;

void setup () {
  Serial.begin(9600);
  pinMode(thermistorPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
}

void loop () { 
  int temperature = analogRead(thermistorPin);

  Serial.println(temperature);

  // When temperature is above threshold -> start motor.
  if (temperature > temperatureThreshold) {
    analogWrite(motorPin, 255);
  } 
  
  // When temperature is below threshold -> stop motor.
  else {
    analogWrite(motorPin, 0);
  }
}
