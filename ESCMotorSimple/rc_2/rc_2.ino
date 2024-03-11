#include <Servo.h>

Servo esc; // Create a servo object to control the ESC
volatile int receiverInput; // To store the receiver input
volatile unsigned long timerStart; // To mark the start of the pulse
int escSignal;

void isr() {
  if (digitalRead(2) == HIGH) {
    timerStart = micros(); // Mark the time when signal goes HIGH
  } else {
    receiverInput = micros() - timerStart; // Calculate pulse width
  }
}

void setup() {
  Serial.begin(9600);
  esc.attach(9); // Attach the ESC to pin 9
//   pinMode(2, INPUT); // Set receiver input pin as input
//   attachInterrupt(digitalPinToInterrupt(2), isr, CHANGE); // Attach interrupt
 }

void loop() {
  // int escSignal = receiverInput; // Direct mapping; adjust based on your setup
  // escSignal = constrain(escSignal, 1000, 2000); // Ensure the signal is within the valid range
  
  for (int i =1000;i<2000;i++){
    escSignal = i;
    esc.writeMicroseconds(escSignal);
    delay(20);
  }
   // Write the signal to the ESC
  
  //Serial.println(receiverInput); // Optional: output the receiver input for debugging

  //delay(20); // Small delay to reduce noise and serial output rate
}
