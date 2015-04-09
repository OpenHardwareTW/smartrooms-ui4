/* 
Arduino 7-Segment LED Display for Common Anode Displays
Arduino Pins: 2,3,4,5,6,7,8
Display Pins: 7,6,4,2,1,9,10
Display Pins 3 should go to VCC
Switch Input is at Pin 9
References: http://www.electroschematics.com/9636/arduino-segment-display-counter/
*/
byte numbers[10] = { 
                    B11111100, B01100000, B11011010, B11110010, B01100110, 
                    B10110110, B10111110, B11100000, B11111110, B11100110 
                    };
void setup() { 
    for(int i = 2; i <= 8; i++) {
        pinMode(i, OUTPUT); 
    }
    pinMode(9, INPUT);
}
 
int counter = 0;
bool go_by_switch = true;
int last_input_value = LOW;
 
void loop() {
    if(go_by_switch) {
        int switch_input_value = digitalRead(9);
        if(last_input_value == LOW && switch_input_value == HIGH) {
            counter = (counter + 1) % 10;
        }
        last_input_value = switch_input_value;
    } else {
        delay(500); 
        counter = (counter + 1) % 10;
    }
    writeNumber(counter);
}
 
void writeNumber(int number) {
    if(number < 0 || number > 9) {
        return;
    }
    byte mask = numbers[number];
    byte currentPinMask = B10000000;
    for(int i = 2; i <= 8; i++) {
        if(mask & currentPinMask) digitalWrite(i,LOW); 
        else digitalWrite(i,HIGH);
    currentPinMask = currentPinMask >> 1;
    }
}
