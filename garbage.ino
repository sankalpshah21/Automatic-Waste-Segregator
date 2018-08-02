
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int moisture;
int induct;
int val;

#define m1 6
#define m2 7
#define mo A0
#define in A1
#define se 11
#define ir 13
#define v 3
//#define g1 6
#define g2 5

void rservo(char );

void setup() {

  myservo.attach(se);

  pinMode(m1, OUTPUT); //motor
  pinMode(m2, OUTPUT); //motor
  pinMode(mo, INPUT); //moisture
  pinMode(in, INPUT); //indu
  pinMode(se, OUTPUT); //servo
  pinMode(ir, INPUT); //ir
  pinMode(v, OUTPUT); //vcc
  Serial.begin(9600);
  digitalWrite(v, HIGH);
  digitalWrite(g2, LOW);
}

void loop() {

  int IR = digitalRead(ir);
  if (IR == HIGH)
  {
    val = 1;
  }
  else
    val = -1;

  delay(1000);
  for (; val > 0; val--)
  {
    moisture = analogRead(mo);
    induct = analogRead(in);
    //  Serial.println(moisture);
    if ((moisture <= 150) && (induct <= 150))
    {
      rservo('m');
    }
    else if (moisture <= 150)
    {
      rservo('w');
    }

    else if (induct <= 150)
    {
      rservo('m');
    }
    else
    {
      rservo('d');
    }
    Serial.println(val);
    delay(500);
  }
  if (val == -1)
  {
    Serial.println("motor off");
    digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);

  }
  if (val == 0)
  {
    Serial.println("motor on");
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    delay(300);
    digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);
    delay(2000);
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    delay(300);
    digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);

  }
  //delay(1000);
  //myservo.write(0);
}
void rservo(char ch)
{
  if (ch == 'w')
  {
    Serial.println("WET");
    myservo.write(0);
  }
  if (ch == 'm')
  {
    Serial.println("METAL");
    for (pos = 0; pos <= 90; pos += 1)
    { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);
    }
  }
  if (ch == 'd')
  {
    Serial.println("DRY");
    Serial.println("Servo Rotation started");
    for (pos = 0; pos <= 180; pos += 1)
    {
      Serial.println(pos);
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);
    }
    Serial.println("Servo Rotation complete");
  }

}


