#define svet1 A5
#define svet2 A4

#define H1 4
#define E1 5
#define E2 6
#define H2 7

#define trig 10
#define echo 11

#define button 13
#define sd 12

#define srv 8

#include <Servo.h>
Servo servo;


int sv1 = 0;
int sv2 = 0;
int ult = 0;

const int SPEED = 100;
const float Kp = 0.4;
const float Kd = 4;
int last_er = 0;

void VOID(){}

void setup() {
  // put your setup code here, to run once:
  pinMode(svet1, INPUT);
  pinMode(svet2, INPUT);
  pinMode(H1, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(H2, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(sd, OUTPUT);

  servo.attach(srv);

  Serial.begin(9600);

}

void drive(int lh, int rh)
{
  if (lh >= 0)
  {
    digitalWrite(H1, LOW);
    analogWrite(E1, lh);
  }
  else
  {
    digitalWrite(H1, HIGH);
    analogWrite(E1, abs(lh));
  }

  if (rh >= 0)
  {
    digitalWrite(H2, LOW);
    analogWrite(E2, rh);
  }
  else
  {
    digitalWrite(H2, HIGH);
    analogWrite(E2, abs(rh));
  }
}
void stop()
{
  drive(-255, -255);
  delay(10);
  drive(0, 0);
}

void read_svet()
{
  sv1 = map(analogRead(svet1), 860, 420, 0, 100);
  sv2 = map(analogRead(svet2), 702, 32, 0, 100);
  // sv1 = analogRead(svet1);
  // sv2 = analogRead(svet2);
}

void read_ult()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  int duration = pulseIn(echo, HIGH, 500000);
  ult = duration*0.017;
}
void read_ult_n()
{
  int sm = 0;
  for (int i = 0; i < 5; i++)
  {
    read_ult();
    sm += ult;
  }
  ult = sm / 5;
}

int PD(int a, int b)
{
  int er = a - b;
  int dV = Kp*er + Kd*(er-last_er);
  last_er = er;
  return dV;
}

void go_lin(int lenght_of_pers = 1, void (event)() = VOID)
{
  for (int i = 0; i < lenght_of_pers; i++)
  {
    read_svet();
    while (sv1 > 40 or sv2 > 40)
    {
      read_svet();
      int dV = PD(sv1, sv2);
      drive(SPEED+dV, SPEED-dV);
  //     Serial.print(SPEED-dV);
  // Serial.print("\t");
  // Serial.println(SPEED+dV);
    }
    event();
    drive(SPEED, SPEED);
    delay(120);
  }
  stop();
}
void left_lin()
{
  drive(SPEED, SPEED);
  delay(230);
  drive(-SPEED, SPEED);
  delay(470);
  read_svet();
  while (sv2 > 40) {read_svet();}
  drive(255, -255);
  delay(10);
  drive(0, 0);
}
void right_lin()
{
  drive(SPEED, SPEED);
  delay(230);
  drive(SPEED, -SPEED);
  delay(470);
  read_svet();
  while (sv1 > 40) {read_svet();}
  drive(-255, 255);
  delay(10);
  drive(0, 0);
}

void go_back(int l_pers, bool flag)
{
  servo.write(75);
  delay(1000);
  drive(-SPEED, -SPEED);
  delay(200);
  drive(0, 0);
  if (flag)
  {
    right_lin();
    go_lin(l_pers);
    left_lin();
    go_lin(2);
    left_lin();
    go_lin(l_pers);
    right_lin();
    delay(500);
    servo.write(180);
    delay(500);
    drive(-SPEED, -SPEED);
    delay(200);
    drive(0, 0);
    right_lin();
    go_lin(l_pers);
    right_lin();
    go_lin(2);
  }
  else
  {
    left_lin();
    go_lin(l_pers);
    right_lin();
    go_lin(2);
    right_lin();
    go_lin(l_pers);
    left_lin();
    delay(500);
    servo.write(180);
    delay(500);
    drive(-SPEED, -SPEED);
    delay(200);
    drive(0, 0);
    left_lin();
    go_lin(l_pers);
    left_lin();
    go_lin(2);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  read_svet();

  if (!digitalRead(button))
  {
    go_lin();
    left_lin();
    go_lin();
    left_lin();
    go_lin();
    left_lin();
    read_ult_n();
    if (ult > 2 && ult < 30)
    {
      go_back(1, false);
      left_lin();
      go_lin(2);
    }
    else
    {
      drive(-SPEED, -SPEED);
      delay(200);
      drive(0, 0);
      right_lin();
      go_lin();
    }
    left_lin();
    go_lin();
    read_ult_n();
    if (ult > 2 && ult < 30)
    {
      go_back(2, false);
    }
  }
  // Serial.print(sv1);
  // Serial.print("\t");
  // Serial.println(sv2);
  servo.write(180);
}
