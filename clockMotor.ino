//CLOCK MOTOR

/*
using Easydriver & Arduino Uno
Arduino is powering both the Easydriver and the motor - GND goes into the easydriver twice, on each side of the board

Easydriver DIR goes to pin 8
Easydriver STEP goes to pin 9

*/

int d = 10; //delay
int stps = 0;

int rotations = 0;


void setup() {
  Serial.begin(9600);
  
  pinMode(8, OUTPUT);  //using this as direction pin
  pinMode(9, OUTPUT); //this is the step control
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

void loop() {
  takeAStep();
    //enclose this in a function
//  digitalWrite(9, HIGH); //everytime this is called, the stepper motor will move 1/8th of a full step
//                         //1.8 degrees per step, there will be 200 full steps per revolution, or 1600 microsteps per revolution. 
//  delay(d); //this is how long in milliseconds before it flips the motor         
//  digitalWrite(9, LOW); 
//  delay(d);          
  
  //  If you use delay(10); for both, the you'll move at 50 microsteps/second.
  
  //for adjusting speed
  char c;
  if(Serial.available()) {
    c = Serial.read();
    
    if (c == 'a') {//SET TO ZERO
      stps = 0;
//      Serial.println(stps);
    }
    
    if (c == 'f') {  // forward
      d = 5;
    }
    if (c == 's') {  // stop
      d = 0;
    }
    if (c == '1') {  // super slow
      d = 100;
    }
    if (c == '2') {  // medium 
      d = 10;
    }
    if (c == '3') {  // fast
      d = 1;
    }
  }
  
}


void takeAStep() {
  digitalWrite(9, HIGH); //everytime this is called, the stepper motor will move 1/8th of a full step
                         //1.8 degrees per step, there will be 200 full steps per revolution, or 1600 microsteps per revolution. 
  delay(d); //this is how long in milliseconds before it flips the motor         
  digitalWrite(9, LOW); 
  delay(d); 
  
  stps = stps + 1;
  
  if (stps > 380){
    stps = 0;
    rotations = rotations + 1;
    Serial.println(rotations);
  }
//Serial.println(stps); 
}
  
