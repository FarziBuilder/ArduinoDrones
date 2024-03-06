byte channel1, channel2, channel3, channel4;
int receiver_input1, receiver_input2, receiver_input3, receiver_input4, esc_counter, start;
unsigned long int timer1, timer2, timer3, timer4, currentTime, timerTracker, zero_timer, esc_timer;
unsigned long int testTime;
unsigned long int futureTime1, futureTime2, futureTime3, futureTime4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  DDRD |= B11110000;
  DDRB |= B00010000; //Set Pin 12 as output
  PCICR |= (1 << PCIE0);

  PCMSK0 |= (1 << PCINT0);
  PCMSK0 |= (1 << PCINT1);
  PCMSK0 |= (1 << PCINT2);
  PCMSK0 |= (1 << PCINT3);

  //setup the hardware timer
  // TCCR2A = 0;
  // TCCR2B = 0;
  // TCCR2A |= (1<<WGM1);
  // TCCR2B |= (1<<CS20);
  // TIMSK2 |= (1<<OCIE2A);
  // OCR2A = 63;
  start = 0;
  zero_timer = micros();
  //check if the throttle is at lowest
  while (receiver_input3 > 990 || receiver_input3 < 1020  || receiver_input4 < 1400){
    start++;
    PORTD |= 0b11110000;
    delayMicroseconds(1000);
    PORTD &= 0b00001111;

    if(start == 125){
      PINB |= 0b00010000;
      start = 0;
    }
  }

}

void loop() {
  delay(500);
  // PORTB |= B00010000;
  // delayMicroseconds(2000);
  // PORTB &= B11101111;
  // timerTracker = micros() + 1500;
  // PORTB |= B00010000;
  // while (micros < timerTracker);
  // PORTB &= B11101111;

  //give me a delay of 4000 ms using while
  zero_timer = micros();
  while(micros() < zero_timer + 4000);

  //send a pulse of 1500 ms to each of the D pins. (Why D?)
  //first create vars to store future time
  futureTime1 = zero_timer + receiver_input_channel_3;
  futureTime2 = zero_timer + receiver_input_channel_3;
  futureTime3 = zero_timer + receiver_input_channel_3;
  futureTime4 = zero_timer + receiver_input_channel_3;
  //set D pin on
  PORTD |= 0b11110000;
  //use if find out whether that future time has come or not
  if (PORTD < 16){
    //if time has exceeded then shut down that Pin
    esc_timer = micros();
    if (esc_timer > futureTime1) PORTD &= 0b11101111;
    if (esc_timer > futureTime2) PORTD &= 0b11011111;
    if (esc_timer > futureTime3) PORTD &= 0b10111111;
    if (esc_timer > futureTime4) PORTD &= 0b01111111;
  }

  //print_signals();
}


// ISR(TIMER2_COMPA_vect){
//   //what shud this code do?
//   esc_counter++;
//   if (esc_counter > 625 && esc_counter <= 1000){
//     PORTB |= B00010000;
//   }
//   if (esc_counter > 1000){
//     PORTB &= B11101111;
//     esc_counter = 0;
//   }
// }


ISR(PCINT0_vect) {
  //what now?
  //currentTime = micros();

  if (channel1 == 0 && (PINB & 0b00000001)) {
    timer1 = currentTime;
    channel1 = 1;
  } else if (channel1 == 1 && !(PINB & 0b00000001)) {
    receiver_input1 = micros() - timer1;
    channel1 = 0;
  }

  if (channel2 == 0 && (PINB & 0b00000010)) {
    timer2 = currentTime; // Added missing semicolon
    channel2 = 1;
  } else if (channel2 == 1 && !(PINB & 0b00000010)) {
    receiver_input2 = micros() - timer2;
    channel2 = 0;
  }

  if (channel3 == 0 && (PINB & 0b00000100)) {
    timer3 = currentTime;
    channel3 = 1;
  } else if (channel3 == 1 && !(PINB & 0b00000100)) {
    receiver_input3 = micros() - timer3;
    channel3 = 0;
  }

  if (channel4 == 0 && (PINB & 0b00001000)) { // Corrected the binary representation
    timer4 = currentTime;
    channel4 = 1;
  } else if (channel4 == 1 && !(PINB & 0b00001000)) { // Corrected the binary representation
    receiver_input4 = micros() - timer4;
    channel4 = 0;
  }
}

void print_signals() {
//what happens to the signals?

  if (receiver_input1 <1400 && receiver_input1 >1000) {
  Serial.print("RollLeft: ");
  Serial.println(receiver_input1);

  } else if(receiver_input1>1600&&receiver_input1<2000){
  Serial.print("RollRight: ");
  Serial.println(receiver_input1);
  }

  if(receiver_input2<1400&&receiver_input2>1000){
  Serial.print("PitchUp: ");
  Serial.println(receiver_input2);
  }else if(receiver_input2>1600&&receiver_input2<2000){
  Serial.print("PitchDown: ");
  Serial.println(receiver_input2);
  }

  if(receiver_input3<1400&&receiver_input3>1000){
    Serial.print("ThrottleDown: ");
    Serial.println(receiver_input3);
  }else if(receiver_input3>1600&&receiver_input3<2000){
    Serial.print("ThrottleUp: ");
    Serial.println(receiver_input3);
  }

  if(receiver_input4<1400&&receiver_input4>1000){
    Serial.print("YawLeft: ");
    Serial.println(receiver_input4);
  }else if(receiver_input4>1600&&receiver_input4<2000){
    Serial.print("YawRight: ");
    Serial.println(receiver_input4);
  }
}