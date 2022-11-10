
const int ledPin = 12;
const int buttonPin = 2;

int ledState = LOW;
  
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH){
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
  }

  delay(200);
}
