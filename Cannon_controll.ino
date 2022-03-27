#include <LiquidCrystal.h>
int Pump {2};
int Valve {3};
int Safety {4};
int A {A0};
int B {A1};
int C {A2};
int D {A3};
int rs {7};
int en {8};
int d4 {9};
int d5 {10};
int d6 {11};
int d7 {12};
int X {0};
int Safety_state = 1;
int Last_state = 1;
int Pressure = 0;
int C_set = 0;
int Last_C;
int PSI = 40;
int Run_time = 5000;
LiquidCrystal lcd (rs,en,d4,d5,d6,d7);
void (*resetFunc)(void)=0;
void setup() {
lcd.begin(16,2);
pinMode(Pump,OUTPUT);
  digitalWrite(Pump,HIGH);
pinMode(Valve,OUTPUT);
  digitalWrite(Valve,HIGH);
pinMode(Safety,OUTPUT);
  digitalWrite(Safety,HIGH);

pinMode(A,INPUT);
  digitalWrite(A,HIGH);
pinMode(B,INPUT);
  digitalWrite(B,HIGH); 
pinMode(C,INPUT);
  digitalWrite(C,HIGH);
pinMode(D,INPUT);
  digitalWrite(D,HIGH);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Safety ON ");
lcd.print(PSI);
lcd.print("PSI");
lcd.setCursor(0,1);
lcd.print("Press A to ARM");
  
}

void loop() {
  // put your main code here, to run repeatedly:
int A_val = digitalRead(A);
int B_val = digitalRead(B);
int C_val = digitalRead(C);
int D_val = digitalRead(D);

if(A_val == 0 && B_val == 0 && C_val == 0 && D_val ==0){
  resetFunc();
}

if (A_val == 0){
  Safety_state *= -1;
  delay(500);}

if (Last_state != Safety_state){
    Last_state = Safety_state;
    lcd.clear();
    if (Safety_state == -1 && Pressure == 0){
      digitalWrite(Safety,LOW);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("C:Set Pressure");
      lcd.setCursor(0,1);
      lcd.print("B:Pressurize ");
      lcd.print(PSI);}
    if (Safety_state == -1 && Pressure == 1){
      digitalWrite(Safety,LOW);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Safety OFF   ");
      lcd.print(PSI);
      lcd.setCursor(0,1);
      lcd.print("D To Fire    PSI");}
    
    if (Safety_state == 1){
      digitalWrite(Safety,HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Safety ON ");
      lcd.print(PSI);
      lcd.print("PSI");
      lcd.setCursor(0,1);
      lcd.print("Press A to ARM");}}

if (B_val == 0 && Safety_state == -1){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pressurizing to:");
  lcd.setCursor(0,1);
  lcd.print(PSI);
  lcd.print(" Please Wait");
  digitalWrite(Pump,LOW);
  delay(Run_time);
  digitalWrite(Pump,HIGH);
  Pressure += 1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Cannon Ready!");
  lcd.setCursor(0,1);
  lcd.print("D To Fire ");
  lcd.print(PSI);
  lcd.print("PSI");
}
if (C_val == 0 && Pressure == 0){
  C_set += 1;
  delay(100);
  if(C_set > 11){
    C_set=0;}
  if (C_set == 0){
    Run_time = 5000;
    PSI = 40;}
  if (C_set == 1){
    Run_time = 6000;
    PSI = 50;}
  if (C_set == 2){
    Run_time = 7500;
    PSI = 60;}
  if (C_set == 3){
    Run_time = 9000;
    PSI = 70;}
  if (C_set == 4){
    Run_time = 11000;
    PSI = 80;}
  if (C_set == 5){
    Run_time = 13000;
    PSI = 90;}
  if (C_set == 6){
    Run_time = 15000;
    PSI = 100;}
  if (C_set == 7){
    Run_time = 16500;
    PSI = 110;}
  if (C_set == 8){
    Run_time = 18000;
    PSI = 120;}
  if (C_set == 9){
    Run_time = 20000;
    PSI = 130;}
  if (C_set == 10){
    Run_time = 25000;
    PSI = 140;}
  if (C_set == 11){
    Run_time = 35000;
    PSI = 150;}}

if (Last_C != C_set){
    Safety_state = 1;
    Last_C = C_set;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PSI set to");
    lcd.setCursor(0,1);
    lcd.print(PSI);  
    lcd.print( "PSI");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Safety ON ");
    lcd.print(PSI);
    lcd.print("PSI");
    lcd.setCursor(0,1);
    lcd.print("Press A to ARM"); }


if (D_val == 0 && Safety_state == -1){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Cannon Fired!");
  lcd.setCursor(0,1);
  lcd.print("Resetting Safety");  
  digitalWrite(Valve,LOW);
  delay(2000);
  lcd.clear();
  digitalWrite(Safety,HIGH);
  digitalWrite(Valve,HIGH);
  Safety_state = 1;
  Pressure = 0;
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Safety ON    ");
  lcd.print(PSI);
  lcd.setCursor(0,1);
  lcd.print("Press A to ARM");
  resetFunc();}}
