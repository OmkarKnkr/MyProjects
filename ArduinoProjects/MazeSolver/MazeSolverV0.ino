#include <NewPing.h>
//MOTOR A 
int enA = 3;
int in1 = 12;
int in2 = 13;

// Motor B

int enB = 5;
int in3 = 2;
int in4 = 7;

//FRONT
#define trig_pin A0 
#define echo_pin A1 

//RIGHT
#define trig_pin2 A2 
#define echo_pin2 A3 

//LEFT
#define trig_pin3 A4 
#define echo_pin3 A5 

long distanceFront, distanceRight,distanceLeft,max_dist=500 ;


NewPing sonar1(trig_pin, echo_pin, max_dist);
NewPing sonar2(trig_pin2, echo_pin2, max_dist);
NewPing sonar3(trig_pin3, echo_pin3, max_dist);

void setup() {
// TCCR0B = TCCR0B & B11111000 | B00000010 ;
  pinMode(in3, OUTPUT);  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(trig_pin, OUTPUT);  
  pinMode(echo_pin, INPUT);
  pinMode(trig_pin2, OUTPUT);
  pinMode(echo_pin2, INPUT);
  pinMode(trig_pin3, OUTPUT);
  pinMode(echo_pin3, INPUT);

  distanceFront=sonar1.ping_cm();
  distanceRight=sonar2.ping_cm();
  distanceLeft=sonar3.ping_cm();
 
  Serial.begin(9600);
  analogWrite(enA,110);
  analogWrite(enB,140);
  forward();
  delay(300);

}
void loop(){
  distanceFront=sonar1.ping_cm();
  distanceRight=sonar2.ping_cm();
  distanceLeft=sonar3.ping_cm(); 
  Serial.print("Right Distance: ");
  Serial.print(distanceRight);
  Serial.print(" cm, Left Distance: ");
  Serial.print(distanceLeft);
  Serial.print(" cm, Front Distance: ");
  Serial.println(distanceFront);
  
  if (distanceFront>10 && distanceFront!=0 ) {
    forward();
    distanceFront=sonar1.ping_cm();
    distanceRight=sonar2.ping_cm();
    distanceLeft=sonar3.ping_cm(); 
  }

  //LEFT
  else if (distanceLeft > distanceRight && distanceFront<=45 && distanceFront!=0 ) {
    Serial.println("LEFT");
    // stop();
    if(distanceFront<5 && distanceFront!=0){
    reverse();
    }
    turnLeft();
    distanceFront=sonar1.ping_cm();
    distanceRight=sonar2.ping_cm();
    distanceLeft=sonar3.ping_cm(); 
    delay(150);
  }

  //RIGHT
  else if (distanceRight > distanceLeft && distanceFront<45 && distanceFront!=0 ){
    Serial.println("RIGHT");
    // stop();
    if(distanceFront<5 && distanceFront!=0){
      reverse();
    }
    turnRight();
    distanceFront=sonar1.ping_cm();
    distanceRight=sonar2.ping_cm();
    distanceLeft=sonar3.ping_cm(); 
    delay(150);
  }

  //U-TURN
  else if ((distanceFront && distanceRight && distanceLeft)<45 && distanceFront!=0 ){
    Serial.println("U-TURN");
    // stop();
    if(distanceFront<5 && distanceFront!=0){
      reverse();
    }
    // delay(150);
    uturn();
    distanceFront=sonar1.ping_cm();
    distanceRight=sonar2.ping_cm();
    distanceLeft=sonar3.ping_cm(); 
    delay(150);
  }
  //T-TURN CHANGE AS PER TRACK
  else if (distanceRight >15 && distanceLeft>15  && distanceFront<15  && distanceFront!=0 ){
    Serial.println("RIGHT");
    // stop();
    if(distanceFront<5){
      reverse();
    }    
    turnRight();
    distanceFront=sonar1.ping_cm();
    distanceRight=sonar2.ping_cm();
    distanceLeft=sonar3.ping_cm(); 
    delay(150);
  }

}


void forward () {
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}
void reverse (){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(120);
  stop();
}
void turnLeft() {
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(275);
  stop();
}
void turnRight() {
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(200);
  stop();
}
void uturn() {
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(1000);
  stop();
}
void stop() {
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(350);
}