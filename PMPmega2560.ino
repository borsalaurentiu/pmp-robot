#include<Wire.h>
#include <math.h>


const int MPU = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
double yaw, pitch, roll;

#include <IRremote.h>     //biblioteca pentru controlul IR
#include <Servo.h>        //biblioteca pentru controlul servo

#define mpin00 11         //pin motor1 -> in2 punteH; 7BBa
#define mpin01 12         //pin motor1 -> in1 punteH; 3BBa
#define mpin10 6          //pin motor2 -> in3 punteH; 1BBa
#define mpin11 7          //pin motor2 -> in4 punteH; 5BBa

#define trigPin 25        //pin trig -> jumper portocaliu sonar; 29BBb 
#define echoPin 24        //pin echo -> jumper galben sonar; 30BBb

#define stopuri 26        //pin stopuri -> jumper galben; direct 
#define intrerupere 2     //pin intrerupere IR -> jumper albastru; 28BBb

//pin VIN -> jumper albastru; 25BBa
//pin 3 control servo -> jumper portocaliu; 11BBa

volatile int enable = 0;  //activeaza intrerupere
Servo srv;                //activeaza servo
Servo viraj;              //vireaza rotile
IRrecv irrecv(2);         //legatura la IR pe pin 2
decode_results results;   //rezultatele receptionate de IR
int stanga, dreapta;      //distantele spre stanga si dreapta

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  //definire IR si intrerupere
  irrecv.enableIRIn();
  irrecv.blink13(true);
  pinMode(intrerupere, INPUT);
  attachInterrupt(digitalPinToInterrupt(intrerupere), infra, CHANGE);

  //definire intrare si iesire de la sonar
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //configurarea pinilor motor ca iesire, initial valoare 0
  digitalWrite(mpin00, 0);
  digitalWrite(mpin01, 0);
  digitalWrite(mpin10, 0);
  digitalWrite(mpin11, 0);
  pinMode (mpin00, OUTPUT);
  pinMode (mpin01, OUTPUT);
  pinMode (mpin10, OUTPUT);
  pinMode (mpin11, OUTPUT);

  //pin leduri stop si semnalizari
  pinMode(stopuri, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(29, OUTPUT);
}

void loop() {
  
  if (enable != 0) {
    verifica(3, 0);
    vireaza(5, 0);
    while (distanta() > 22 && enable != 0) {
      mergeInainte();
    }
    opreste();

    verifica(3, -1);
    delay(500);
    stanga = distanta();
    delay(500);
    verifica(3, 1);
    delay(500);
    dreapta = distanta();
    delay(500);
    Serial.print("stanga ");
  Serial.println(stanga);
    Serial.print("dreapta ");
  Serial.println(dreapta);
    if (stanga >= dreapta && stanga > 40) {
      ocolesteStanga();
    } else {
      ocolesteDreapta();
    }
  } else {
    avarii(3);
    
    while (distanta() > 15 && enable == 0) {
      
      manevra();
      if (pitch > 40) {
        mergeInainte();
      } else if (pitch < -40) {
        mergeInapoi();
      } else {
        opresteF();
      }

      
      if (roll < -20) {
        vireaza(5, 1);
      } else if ( roll > 20) {
        vireaza(5, -1);
      } else {
        vireaza(5, 0);
      }
    }
    opreste();

  } 
}
