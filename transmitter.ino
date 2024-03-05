// Declaring Variables
byte last_channel_1, last_channel_2, last_channel_3, last_channel_4;
int receive_input_channel_1, receive_input_channel_2, receive_input_channel_3, receive_input_channel_4;
unsigned long timer_1, timer_2, timer_3, timer_4;

// Setup routine
void setup() {
  // Arduino (ATmega) pins default to inputs, so they don't need to be explicitly declared as inputs
  PCICR |= (1 << PCIE0);    // set PCIE0 to enable PCMSK0 scan
  PCMSK0 |= (1 << PCINT0);   // set PCINT0 (digital input 8) to trigger an interrupt on state change
  PCMSK0 |= (1 << PCINT1);   // set PCINT1 (digital input 9) to trigger an interrupt on state change
  PCMSK0 |= (1 << PCINT2);   // set PCINT2 (digital input 10) to trigger an interrupt on state change
  PCMSK0 |= (1 << PCINT3);   // set PCINT3 (digital input 11) to trigger an interrupt on state change
  Serial.begin(9600);
}

// Main program loop
void loop() {
  delay(250);
  print_signals();
}

// This routine is called every time input 8, 9, 10 or 11 changed state
ISR(PCINT0_vect) {
  // Channel ----------------------------------------------------
  if((last_channel_1 == 0) && (PINB & B00000001)) { // Input 8 changed from 0 to 1
    last_channel_1 = 1;                             // Remember current input state
    timer_1 = micros();                             // Set timer_1 to micros()
  } else if ((last_channel_1 == 1) && !(PINB & B00000001)) { // Input 8 changed from 1 to 0
    last_channel_1 = 0;                             // Remember current input state
    receive_input_channel_1 = micros() - timer_1;   // Channel 1 is micros() - timer_1
  }
  // Channel ----------------------------------------------------
  if((last_channel_2 == 0) && (PINB & B00000010)) { // Input 9 changed from 0 to 1
    last_channel_2 = 1;                             // Remember current input state
    timer_2 = micros();                             // Set timer_2 to micros()
  } else if ((last_channel_2 == 1) && !(PINB & B00000010)) { // Input 9 changed from 1 to 0
    last_channel_2 = 0;                             // Remember current input state
    receive_input_channel_2 = micros() - timer_2;   // Channel 2 is micros() - timer_2
  }
  // Channel ----------------------------------------------------
  if((last_channel_3 == 0) && (PINB & B00000100)) { // Input 10 changed from 0 to 1
    last_channel_3 = 1;                             // Remember current input state
    timer_3 = micros();                             // Set timer_3 to micros()
  } else if ((last_channel_3 == 1) && !(PINB & B00000100)) { // Input 10 changed from 1 to 0
    last_channel_3 = 0;                             // Remember current input state
    receive_input_channel_3 = micros() - timer_3;   // Channel 3 is micros() - timer_3
  }
  // Channel ----------------------------------------------------
  if((last_channel_4 == 0) && (PINB & B00001000)) { // Input 11 changed from 0 to 1
    last_channel_4 = 1;                             // Remember current input state
    timer_4 = micros();                             // Set timer_4 to micros()
  } else if ((last_channel_4 == 1) && !(PINB & B00001000)) { // Input 11 changed from 1 to 0
    last_channel_4 = 0;                             // Remember current input state
    receive_input_channel_4 = micros() - timer_4;   // Channel 4 is micros() - timer_4
  }
}

// Subroutine for displaying the receiver signals
void print_signals() {
    //Serial.print("Roll:");
    if(receive_input_channel_1 - 1480 < 0 && receive_input_channel_1 - 1000 > 0){
      Serial.print("PitchDown");
      Serial.println(receive_input_channel_1);
    }
    else if(receive_input_channel_1 - 1520 > 0 && receive_input_channel_1 - 2000 < 0){
      Serial.print("PitchUp");
      Serial.println(receive_input_channel_1);
    }
    //else Serial.print("--");
    
    //Serial.print("Pitch:");
    if(receive_input_channel_2 - 1480 < 0 && receive_input_channel_2 - 1000 > 0){
      Serial.print("GasDown:");
      Serial.println(receive_input_channel_2);
    }
    else if(receive_input_channel_2 - 1520 > 0 && receive_input_channel_2 - 2000 < 0){
      Serial.print("GasUp:");
      Serial.println(receive_input_channel_2);
    }
    //else Serial.print("--");

    //Serial.print("Gas:");
    if(receive_input_channel_3 - 1480 < 0 && receive_input_channel_3 - 1000 > 0){
      Serial.print("YawLeft");
      Serial.println(receive_input_channel_3);
    }
    else if(receive_input_channel_3 - 1520 > 0 && receive_input_channel_3 - 2000 < 0){
      Serial.print("YawRight");
      Serial.println(receive_input_channel_3);
    }
    //else Serial.print("--");

    //Serial.print("Yaw:");
    if(receive_input_channel_4 - 1480 < 0 && receive_input_channel_4 - 1000 > 0){
      Serial.print("Rollleft");
      Serial.println(receive_input_channel_4);
    }
    else if(receive_input_channel_4 - 1520 > 0 && receive_input_channel_4 - 2000 < 0){
      Serial.print("RollRight");
      Serial.println(receive_input_channel_4);
    }
    //else Serial.print("--");
    
};
