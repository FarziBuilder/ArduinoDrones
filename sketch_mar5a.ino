byte channel1, channel2, channel3, channel4;
int receiver_input1, receiver_input2, receiver_input3, receiver_input4;
unsigned long int timer1, timer2, timer3, timer4;
unsigned long int testTime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.print("check2");
  PCICR |= (1 << PCIE0);

  PCMSK0 |= (1 << PCINT0);
  PCMSK0 |= (1 << PCINT1);
  PCMSK0 |= (1 << PCINT2);
  PCMSK0 |= (1 << PCINT3);
}

ISR(PCINT0_vect) {
  //what now?
  if (channel1 == 0 && (PINB & 0b00000001)) {
    timer1 = micros();
    channel1 = 1;
  } else if (channel1 == 1 && !(PINB & 0b00000001)) {
    receiver_input1 = micros() - timer1;
    channel1 = 0;
  }

  if (channel2 == 0 && (PINB & 0b00000010)) {
    timer2 = micros(); // Added missing semicolon
    channel2 = 1;
  } else if (channel2 == 1 && !(PINB & 0b00000010)) {
    receiver_input2 = micros() - timer2;
    channel2 = 0;
  }

  if (channel3 == 0 && (PINB & 0b00000100)) {
    timer3 = micros();
    channel3 = 1;
  } else if (channel3 == 1 && !(PINB & 0b00000100)) {
    receiver_input3 = micros() - timer3;
    channel3 = 0;
  }

  if (channel4 == 0 && (PINB & 0b00001000)) { // Corrected the binary representation
    timer4 = micros();
    channel4 = 1;
} else if (channel4 == 1 && !(PINB & 0b00001000)) { // Corrected the binary representation
    receiver_input4 = micros() - timer4;
    channel4 = 0;
}
}

void loop() {
// put your main code here, to run repeatedly:
// testTime = micros() + 2000;
// //Serial.print("check");
// while(micros() < testTime);
delay(500);
//Serial.print("check");
print_signals();
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