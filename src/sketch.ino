/*
  chording keyboard code (c) Daniel Bergey 2014
*/

// anything below `threshold` indicates a pressed sensor
// Life is good if they can all be the same, but hand-sewing isn't that precise
// Easier to fine-tune here than switching resistors
const int threshold[] = {480, 256, 256, 256, 256 };

/* keymap in binary order, with thumb as least-significant bit, pinkie on 0x10 */
const char keymap[] = { ' ', // no keys pressed, do not print
                       ' ' , 'u' , 's' , 'e' , 'n' , 'i' , 't', // 0x01-0x07 
                       'o' , 'h' , 'r' , 'd' , 'l' , 'c' , 'm' , 'w', // 0x08-0x0F
                       'a' , 'b' , 'v' , 'k' , 'q' , 'j' , 'x' , 'z', // 0x10-0x17
                       0x80 /* ctrl */ , 'f' , 'g' , 'y' , 0xB1 /* 0xB1 esc*/ , 'p', 0xC1 , 0x81 /* shift */
                       // 0x1A-0x1F
};
// Modifier Keys: http://arduino.cc/en/Reference/KeyboardModifiers

int fingertip_state = 0;

void setup() {
     // Do not need to set input mode for analog pins
     /* int thumbState, firstState, middleState, ringState, pinkiState; */
     Keyboard.begin();
}

void loop() {
     fingertip_state = 0;

// wire fingertip sensors to analog inputs A0 through A4
     // thumb on A0
     if (digitalRead(12)) {
          for(int i=0; i<5; i++) {
               fingertip_state |= ((analogRead(i) < threshold[i] ? 1 : 0) << i);
               // debugging
               Keyboard.print(analogRead(i));
               Keyboard.print(' ');
          }

          // debugging
          Keyboard.print("0x");
          Keyboard.println(String(fingertip_state, HEX));

          if (fingertip_state != 0x00) {
               // only lowercase for now
               Keyboard.write(keymap[fingertip_state]);
          }

          delay(1000);
     }
}
