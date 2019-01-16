
int pins[5] = {2, 3, 4, 5};

bool states[5], lastStates[5];

int pitchOffset = 0x3c;

void setup() {
    Serial.begin(38400);
    for(int i = 0; i < 4; i++) {
      pinMode(pins[i], INPUT);
      states[i] = false;
      lastStates[i] = false;
    }
}

void loop() {
  for(int i = 0; i < 4; i++) {
    states[i] = digitalRead(pins[i]);

    if(states[i] != lastStates[i]) {
      if(!states[i]) {
        noteOn(0x80 + i, pitchOffset + i, 0x00);
      }
      else {
        noteOn(0x90 + i, pitchOffset + i, 0x45);
      }
    }



    lastStates[i] = states[i];
  }
}

// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
//cmd: 0xCc C = Command c = channel 
//pitch: middle c is 3C
//Velocity: is just 0-126 halfway point is 0x45
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
  Serial.flush();
}