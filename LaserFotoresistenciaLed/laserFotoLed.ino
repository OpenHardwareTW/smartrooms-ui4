
int analogInputNumber = 0;
int analogThresholdForLaserCut = 100;
int analogValue;
boolean firstTimeObstaclePasses = true;
int ledPin = 7;
boolean ledState = false;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (isLaserCut()) {
    Serial.println("Obstaculo en el medio");
    changeLedState();
    delay(1000);
  }
}

boolean isLaserCut(){
  if (isObstaclePresent() && isFirstTimeObstaclePasses())
    return true;
  else if (!isObstaclePresent())
    firstTimeObstaclePasses = true;  
  return false;
}

boolean isFirstTimeObstaclePasses() {
  if (firstTimeObstaclePasses) {
      firstTimeObstaclePasses = false;
      return true;
  }
  return false;
}

boolean isObstaclePresent() {
  return analogRead(analogInputNumber) >= analogThresholdForLaserCut;
}

void changeLedState() {
  digitalWrite(ledPin, ledState);
  ledState = !ledState;
}
