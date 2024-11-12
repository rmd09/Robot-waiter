#define dW digitalWrite
#define dR digitalRead

//Пины
//in - input на драйвере l293d
//en - enable
#define in1 0
#define in2 0
#define in3 0
#define in4 0
#define en1 0
#define en2 0

#define debug_btn 0 //Кнопка на макетке для отладки

void init_motors()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
void init_debug_components() 
{
  pinMode(debug_btn, INPUT_PULLUP);
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

void setup() 
{
  init_motors();
  init_debug_components();

}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

void A_on(int en_value = 1023, bool isStraight = true)
{
  digitalWrite(in1, isStraight ? HIGH : LOW);
  digitalWrite(in2, isStraight ? LOW : HIGH);
  digitalWrite(en1, en_value);
}
void A_off()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(en1, LOW);
}
void B_on(int en_value = 1023, bool isStraight = true)
{
  digitalWrite(in3, isStraight ? LOW : HIGH);
  digitalWrite(in4, isStraight ? HIGH : LOW);
  digitalWrite(en2, en_value);
}
void B_off()
{
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(en2, LOW);
}

void test_program()
{
  A_on();
  B_on();
  delay(2000);
  A_off();
  B_off();
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

void loop() 
{
  bool but = !digitalRead(debug_btn);
  if (but) 
  {
    delay(200);
    test_program();
  }
}
