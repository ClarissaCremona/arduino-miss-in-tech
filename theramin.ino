
/*
   Arduino Theremin with A minor pentatonic scale
   pollux labs, 2020
   All rights reserved.
*/

const int trigger = 5;
const int echo = 4;

const int piezo = 6;

int distance = 0;
int distanceHigh = 0;

int lengthOfScale = 0;

int note = 0;

//A Minor pentatonic scale
//int scale[] = {
//  147, 165, 196, 220, 262, 294, 330, 392, 440,
//  523, 587, 659, 784, 880, 1047, 1175, 1319, 1568,
//  1760, 2093, 2349
//};

//C Major scale
int scale[] = {
  131, 147, 165, 175, 196, 220, 247, 262, 294,
  330, 349, 392, 440, 494, 523, 587, 659, 698,
  784, 880, 988, 1047
};


void setup() {
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  while (millis() < 5000) {
    digitalWrite(trigger, HIGH);
    digitalWrite(trigger, LOW);
    distance = pulseIn(echo, HIGH);

    if (distance > distanceHigh) {
      distanceHigh = distance;
    }
  }

  for (byte i = 0; i < (sizeof(scale) / sizeof(scale[0])); i++) {
    lengthOfScale += 1;
  }
}

void loop() {
  digitalWrite(trigger, HIGH);
  digitalWrite(trigger, LOW);

  distance = pulseIn(echo, HIGH);

  note = map(distance, 250, distanceHigh, scale[0], scale[lengthOfScale - 1]);
  
  Serial.println(note);
    
  for (byte j = 0; j < (lengthOfScale); j++) {

    if (note == scale[j]) {
      tone(piezo, note);
      break;
    }
    else if (note > scale[j] && note < scale[j + 1]) {
      note = scale[j];
      tone(piezo, note);
      break;
    }
  }
  delay(30);
}
