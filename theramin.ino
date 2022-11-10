
/*
   Arduino Theremin with A minor pentatonic scale
   pollux labs, 2020
   All rights reserved.
*/

const int trigger = 5;
const int echo = 4;

const int piezo = 6;

int distance = 0; // current distance of item to sensor
int distanceHigh = 0; // max distance from theramin, defined through calibration

int lengthOfScale = 0; // number of notes in scale played by theramin

int note = 0; // note detected

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

// calibration
void setup() {
  Serial.begin(9600);
  pinMode(trigger, OUTPUT); // command to emit wave
  pinMode(echo, INPUT); // signal returned to ultrasonic sensor

  while (millis() < 5000) { // for 5 seconds
    digitalWrite(trigger, HIGH); // send out ultrasonic wave
    digitalWrite(trigger, LOW); // immediately turn trigger off
    distance = pulseIn(echo, HIGH); // measure time in ms taken for wave to reach sensor again 

    if (distance > distanceHigh) {
      distanceHigh = distance; // set maximum distance away from sensor
    }
  }

  lengthOfScale = sizeof(scale) / sizeof(scale[0]); // number of notes in scale
}

void loop() {
  digitalWrite(trigger, HIGH);
  digitalWrite(trigger, LOW);

  distance = pulseIn(echo, HIGH);

  // calculate note to be played
  // distance - current distance from sensor
  // 250 - min distance from sensor
  // distanceHigh - max distance from sensor
  // scale[0] - lowest note in scale
  // scale[lengthOfScale-1] - highest note in scale
  note = map(distance, 250, distanceHigh, scale[0], scale[lengthOfScale - 1]);
  
  Serial.println(note);
    
  for (byte j = 0; j < (lengthOfScale); j++) {

    // if note matches exactly one of the notes in the scale, play it
    if (note == scale[j]) {
      tone(piezo, note);
      break;
    }
    // if note is between two notes in the scale, play the lower note
    else if (note > scale[j] && note < scale[j + 1]) {
      note = scale[j];
      tone(piezo, note);
      break;
    }
  }
  delay(30);
}
