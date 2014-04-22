#include <MIDI.h>

const int BUTTON_MIN = 2;
const int BUTTON_MAX = 12;
const int BASE_PITCH = 53;

int playing = -1;
char* notes[] = {
  "01111110011",
  "01111110110",
  "01111110010",
  "01111111000",
  "01111110000",
  "01111100000",
  "01111010010",
  "01111000000",
  "01110111000",
  "01110000000",
  "01101100000",
  "01100000000",
  "01010000000",
  "00110000000",
  "00010000000",
  "00111110010",
  "10111110000",
  "10111100000",
  "10111010000",
  "10111000000",
  "10110100000",
  "10110000000",
  "10110010010",
  "10110110000",
  "10100110000",
  "10101100011",
  "10101100010",
};
int noteCount = sizeof(notes) / sizeof(notes[0]);

void setup() {
  for (int i = BUTTON_MIN; i <= BUTTON_MAX; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  MIDI.begin();
}

void loop() {
  char currentValue[] = "00000000000";
  int exist = 0;
  for (int i = BUTTON_MIN; i <= BUTTON_MAX; i++) {
    if (digitalRead(i) == LOW) {
      currentValue[i - BUTTON_MIN] = '1';
      exist = 1;
    } else {
      currentValue[i - BUTTON_MIN] = '0';
    }
  }
  
  if (exist == 1) {
    for (int i = 0; i < noteCount; i++) {
      if (strcmp(currentValue, notes[i]) == 0) {
        if (i != playing) {
          if (playing > -1) {
            MIDI.sendNoteOff(BASE_PITCH + playing, 0, 1);
          }
          playing = i;
          MIDI.sendNoteOn(BASE_PITCH + playing, 127, 1);
        }
        break;
      }
    }
  } else {
    if (playing > -1) {
      MIDI.sendNoteOff(BASE_PITCH + playing, 0, 1);
      playing = -1;
    }
  }
}
