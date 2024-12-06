#include <Servo.h>
#include<String.h>
//#define EN 8
#define X_DIR 5
#define Y_DIR 6
#define X_STP 2
#define Y_STP 3
#define IN3 8
#define IN4 11

const byte enablePin = 8;  // for CNC shield
const byte servoPin1 = 13; // Spindle enable pin (SpinDir) .  // tay gap
const byte servoPin2 = 12; //--- port12-SpinEn // khop 4
const byte servoPin3 = A3; //--- PinA3-CoolEn // khop 3
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

#define CB  4// Chan tin hieu Cam bien -> Chân số 10 Arduino (digital)
int gap = 60;
/////
int angle[4];

char* result1;
/////
void servo(Servo myservo,int angle)
{
  myservo.write(angle);
}

void step(boolean dir, byte dirPin, byte stepperPin, int steps)
{
  digitalWrite(dirPin, dir);
  delay(50);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(2000);  
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(2000);  
  }
}

void setup(){
  Serial.begin(9600);
  pinMode(X_DIR, OUTPUT);
  pinMode(X_STP, OUTPUT);
  pinMode(Y_DIR, OUTPUT); 
  pinMode(Y_STP, OUTPUT);
  //pinMode(EN, OUTPUT);
  //digitalWrite(EN, LOW);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);
  pinMode(A3,OUTPUT);
  myservo1.attach(servoPin1); // servo tay gap
  myservo2.attach(servoPin2); // servo khop 4
  myservo3.attach(A3); // chan servo khop 3 --- CoolEn
   servo(myservo1,0); //gap
   servo(myservo2,0); // khop 4 //day vat
   servo(myservo3,0); // khop 3

  // bang chuyen
 pinMode(CB,INPUT); //Setup ngõ vào
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 myservo4.attach(7);// servo bang chuyen
 servo(myservo4,0);
}

void ban_dau() {
  angle[0]=0;
  angle[1]=0;
  angle[2]=0;
  //angle[3]=0;
  int alpha1 = angle[0];
  int alpha2 = angle[1];
  int alpha3 = angle[2]+90;
  //int alpha4 = angle[3]+90; // khop 4 / 
  /*volatile long int  pulse1 = alpha1*200/360*3; // dem xung khop 1
  volatile long int  pulse2 = alpha2*200/360*3; // dem xung khop 2*/
  if(alpha1>=0)
  {
    volatile long int  pulse1 = alpha1*200/360*3; // dem xung khop 1
    step(false, X_DIR, X_STP, pulse1);
  }
  else
  {
    volatile long int  pulse1 = -alpha1*200/360*3; // dem xung khop 1
    step(true, X_DIR, X_STP, pulse1); // khop 1
  }
   if(alpha2>=0)
  {
    volatile long int  pulse2 = alpha2*200/360*3; // dem xung khop 2
    step(false, Y_DIR, Y_STP, pulse2);
  }
  else
  {
    volatile long int  pulse2 = -alpha2*200/360*3; // dem xung khop 2
    step(true, Y_DIR, Y_STP, pulse2); // khop 2
  }
  //myservo3.write(60); // khop 3
  servo(myservo3,alpha3);
  //myservo2.write(alpha4);// khop 4
  //servo(myservo2,alpha4); 
  delay(500); 
}
void gap_vat()
{
  angle[0]=0;
  angle[1]=0;
  angle[2]=50;
  //angle[3]=0;
  int alpha1 = angle[0];
  int alpha2 = angle[1];
  int alpha3 = angle[2]+90;
  //int alpha4 = angle[3]+90; // khop 4 / 
  /*volatile long int  pulse1 = alpha1*200/360*3; // dem xung khop 1
  volatile long int  pulse2 = alpha2*200/360*3; // dem xung khop 2*/
  if(alpha1>=0)
  {
    volatile long int  pulse1 = alpha1*200/360*3; // dem xung khop 1
    step(false, X_DIR, X_STP, pulse1);
  }
  else
  {
    volatile long int  pulse1 = -alpha1*200/360*3; // dem xung khop 1
    step(true, X_DIR, X_STP, pulse1); // khop 1
  }
   if(alpha2>=0)
  {
    volatile long int  pulse2 = alpha2*200/360*3; // dem xung khop 2
    step(false, Y_DIR, Y_STP, pulse2);
  }
  else
  {
    volatile long int  pulse2 = -alpha2*200/360*3; // dem xung khop 2
    step(true, Y_DIR, Y_STP, pulse2); // khop 2
  }
  //myservo3.write(60); // khop 3
  servo(myservo3,alpha3);
  //myservo2.write(alpha4);// khop 4
  //servo(myservo2,alpha4);
  delay(2000); 
  servo(myservo1,gap);
  delay(500);
}
void di_chuyen()
{
  angle[0]=-60;
  angle[1]=0;
  angle[2]=20;
  //angle[3]=0;
  int alpha1 = angle[0];
  int alpha2 = angle[1];
  int alpha3 = angle[2]+90;
  //int alpha4 = angle[3]+90; // khop 4 / 
  /*volatile long int  pulse1 = alpha1*200/360*3; // dem xung khop 1
  volatile long int  pulse2 = alpha2*200/360*3; // dem xung khop 2*/
 servo(myservo3,alpha3);
 delay(1000);
  if(alpha1>=0)
  {
    volatile long int  pulse1 = alpha1*200/360*3; // dem xung khop 1
    step(false, X_DIR, X_STP, pulse1);
  }
  else
  {
    volatile long int  pulse1 = -alpha1*200/360*3; // dem xung khop 1
    step(true, X_DIR, X_STP, pulse1); // khop 1
  }
   if(alpha2>=0)
  {
    volatile long int  pulse2 = alpha2*200/360*3; // dem xung khop 2
    step(false, Y_DIR, Y_STP, pulse2);
  }
  else
  {
    volatile long int  pulse2 = -alpha2*200/360*3; // dem xung khop 2
    step(true, Y_DIR, Y_STP, pulse2); // khop 2
  }
  //servo(myservo2,alpha4); 
  //delay(500);
  servo(myservo1,0);
  delay(500);
}
void di_chuyen1()
{
   /////  -------------------------- /////////////////
  angle[0]=60;
  angle[1]=0;
  angle[2]=20;
  //angle[3]=0;
  int alpha1 = angle[0];
  int alpha2 = angle[1];
  int alpha3 = angle[2]+90;
  //int alpha4 = angle[3]+90; // khop 4 / 
  /*volatile long int  pulse1 = alpha1*200/360*3; // dem xung khop 1
  volatile long int  pulse2 = alpha2*200/360*3; // dem xung khop 2*/
 servo(myservo3,alpha3);
 delay(1000);
  if(alpha1>=0)
  {
    volatile long int  pulse1 = alpha1*200/360*3; // dem xung khop 1
    step(false, X_DIR, X_STP, pulse1);
  }
  else
  {
    volatile long int  pulse1 = -alpha1*200/360*3; // dem xung khop 1
    step(true, X_DIR, X_STP, pulse1); // khop 1
  }
   if(alpha2>=0)
  {
    volatile long int  pulse2 = alpha2*200/360*3; // dem xung khop 2
    step(false, Y_DIR, Y_STP, pulse2);
  }
  else
  {
    volatile long int  pulse2 = -alpha2*200/360*3; // dem xung khop 2
    step(true, Y_DIR, Y_STP, pulse2); // khop 2
  }
  
  //servo(myservo2,alpha4); 
  //delay(500);
  servo(myservo1,0);
  delay(500);
}

void quay_ve()
{
  angle[0]=50;
  angle[1]=0;
  angle[2]=0;
  //angle[3]=0;
  int alpha1 = angle[0];
  int alpha2 = angle[1];
  int alpha3 = angle[2]+90;
  //int alpha4 = angle[3]+90; // khop 4 / 
  /*volatile long int  pulse1 = alpha1*200/360*3; // dem xung khop 1
  volatile long int  pulse2 = alpha2*200/360*3; // dem xung khop 2*/

  if(alpha1>=0)
  {
    volatile long int  pulse1 = alpha1*200/360*3; // dem xung khop 1
    step(false, X_DIR, X_STP, pulse1);
  }
  else
  {
    volatile long int  pulse1 = -alpha1*200/360*3; // dem xung khop 1
    step(true, X_DIR, X_STP, pulse1); // khop 1
  }
   if(alpha2>=0)
  {
    volatile long int  pulse2 = alpha2*200/360*3; // dem xung khop 2
    step(false, Y_DIR, Y_STP, pulse2);
  }
  else
  {
    volatile long int  pulse2 = -alpha2*200/360*3; // dem xung khop 2
    step(true, Y_DIR, Y_STP, pulse2); // khop 2
  }
  //myservo3.write(60); // khop 3
  servo(myservo3,alpha3);
  //myservo2.write(alpha4);// khop 4
  //servo(myservo2,alpha4); 
  
  delay(1000);
}
void quay_ve1()
{
   /////  -------------------------- /////////////////
  angle[0]=-50;
  angle[1]=0;
  angle[2]=0;
  //angle[3]=0;
  int alpha1 = angle[0];
  int alpha2 = angle[1];
  int alpha3 = angle[2]+90;
  //int alpha4 = angle[3]+90; // khop 4 / 
  /*volatile long int  pulse1 = alpha1*200/360*3; // dem xung khop 1
  volatile long int  pulse2 = alpha2*200/360*3; // dem xung khop 2*/

  if(alpha1>=0)
  {
    volatile long int  pulse1 = alpha1*200/360*3; // dem xung khop 1
    step(false, X_DIR, X_STP, pulse1);
  }
  else
  {
    volatile long int  pulse1 = -alpha1*200/360*3; // dem xung khop 1
    step(true, X_DIR, X_STP, pulse1); // khop 1
  }
   if(alpha2>=0)
  {
    volatile long int  pulse2 = alpha2*200/360*3; // dem xung khop 2
    step(false, Y_DIR, Y_STP, pulse2);
  }
  else
  {
    volatile long int  pulse2 = -alpha2*200/360*3; // dem xung khop 2
    step(true, Y_DIR, Y_STP, pulse2); // khop 2
  }
  //myservo3.write(60); // khop 3
  servo(myservo3,alpha3);
  //myservo2.write(alpha4);// khop 4
  //servo(myservo2,alpha4); 
  
  delay(1000);
}
void dong_co_chay()
{
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
// delay(1000);
}
void dong_co_dung()
{
digitalWrite(IN3,LOW);
digitalWrite(IN4,LOW);
//delay(1000);
}
void buzzer()
{
  myservo2.write(105);
  delay(1000);
  myservo2.write(0);
}
void loop(){
  
  dong_co_chay();
  
  String dulieu="";
  if (digitalRead(CB)==0)
  {
    dong_co_dung();
    while (dulieu=="")  
    {
        while (Serial.available()>0)
        {
          char c = Serial.read();
          dulieu = dulieu+c;
          delay(1);
        } 
        dulieu.trim();
        if (digitalRead(CB)==1)
        {
          break;
        }
    } 
    if (dulieu == "BLUE")
    {
      ban_dau();
      gap_vat();
      di_chuyen();
      quay_ve();
      while(digitalRead(CB)==0)
      {
        dong_co_chay();
      }
    }
    else if (dulieu =="RED")
    {
      myservo4.write(90);
      while(digitalRead(CB)==0)
      {
        dong_co_chay();
        delay(1000);
      }
    }
    else if (dulieu =="YELLOW")
    {
      myservo4.write(0);
      while(digitalRead(CB)==0)
      {
        dong_co_chay();
        delay(1000);
      }
  
    }
  }

}
