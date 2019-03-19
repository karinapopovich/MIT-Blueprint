#include "IRremote.h"
#include <LiquidCrystal.h>

String num;
int n = 0;
int t = 0;
int b = 1;
int f = 0;
int newnum;

int receiver = 6;
int bled = 5;
int gled = 4;
int yled = 3;
int rled = 2;
IRrecv irrecv(receiver);
decode_results results;
LiquidCrystal lcd (7, 8, 9, 10, 11, 12);

void newbudget()
{
  Serial.print("Your new budget is ");
  Serial.println(newnum);
  lcd.clear();
  lcd.print("Your new budget");
  lcd.setCursor(0, 1);
  lcd.print("is $");
  lcd.setCursor(4, 1);
  lcd.print(newnum);
  delay(4000);
}


void translateIR()
{
  switch (results.value)
  {
    case 0xFFA25D: Serial.println("POWER"); break;
    case 0xFF6897: num = num + "0"; b = b + 1;   break;
    case 0xFF30CF: num = num + "1"; b = b + 1;   break;
    case 0xFF18E7: num = num + "2"; b = b + 1;   break;
    case 0xFF7A85: num = num + "3"; b = b + 1;   break;
    case 0xFF10EF: num = num + "4"; b = b + 1;   break;
    case 0xFF38C7: num = num + "5"; b = b + 1;   break;
    case 0xFF5AA5: num = num + "6"; b = b + 1;   break;
    case 0xFF42BD: num = num + "7"; b = b + 1;   break;
    case 0xFF4AB5: num = num + "8"; b = b + 1;   break;
    case 0xFF52AD: num = num + "9"; b = b + 1;   break;
    case 0xFFFFFFFF: Serial.println(" REPEAT"); break;

    default:
      Serial.println(" other button   ");
  }
  delay(500); // Do not get immediate repeat
}

void setup() {
  pinMode(bled, OUTPUT);
  pinMode(gled, OUTPUT);
  pinMode(yled, OUTPUT);
  pinMode(rled, OUTPUT);
  irrecv.enableIRIn();
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  if (n < 1)
  {
    lcd. setCursor(0, 0);
    Serial.println("Welcome to ---");
    lcd.print("Welcome to ---");

    delay(3000);

    lcd.clear();
    Serial.println("We want to help you save :)");
    lcd.print("We want to help");
    lcd. setCursor(0, 1);
    lcd.print("you save :)");
    delay(3000);

    lcd.clear();
    Serial.println("Tell us your budget. Type it in using the remote.");
    lcd.print("Type in your");
    lcd.setCursor(0, 1);
    lcd.print("budget -->");
    delay(3000);

    lcd.clear();
    n = n + 1;
  }
  else {}


  if (num == "") {
  }
  else if (t < b) {
    Serial.println(num);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("$");
    lcd.setCursor(1, 0);
    lcd.print(num);
    t = t + 1;
    f = 0;
  }
  else if (t == b)
  {
    delay(10);
    f = f + 1;
  }
  else {}


  if (f >= 600 && f <= 610) {
    Serial.print("Your budget is ");
    Serial.println(num);
    lcd.clear();
    lcd.print("Your budget is");
    lcd.setCursor(0, 1);
    lcd.print("$");
    lcd.setCursor(1, 1);
    lcd.print(num);
  }

  if ((f / 100) == 10) {

    Serial.println("Let's keep your budget this good!");
    lcd.clear();
    lcd.print("Let's keep your");
    lcd.setCursor(0, 1);
    lcd.print("budget this good!");
    delay(4000);

    Serial.println("Yikes! Here come the expenses :(");
    lcd.clear();
    lcd.print("Yikes! Here come");
    lcd.setCursor(0, 1);
    lcd.print("the expenses :(");
    delay(4000);

    newnum = num.toFloat();

    Serial.println("Morning coffee and bagel are $9");
    lcd.clear();
    lcd.print("Morning coffee");
    lcd.setCursor(0, 1);
    lcd.print("and bagel $9");
    newnum = newnum - 9;
    delay(4000);
    newbudget();


    Serial.println("Oh no! Your charlie card ran out.");
    lcd.clear();
    lcd.print("Refill your");
    lcd.setCursor(0, 1);
    lcd.print("Charlie card $3");
    newnum = newnum - 3;
    delay(4000);
    newbudget();


    Serial.println("Last minute birthday party!");
    lcd.clear();
    lcd.print("Buy your friend");
    lcd.setCursor(0, 1);
    lcd.print("a gift $43");
    newnum = newnum - 3;
    delay(4000);
    newbudget();


    Serial.println("Luckily that was the last of your expenses today. Your wallet can take a break!");
    lcd.clear();
    lcd.print("Let your wallet");
    lcd.setCursor(0, 1);
    lcd.print("take a break");
    delay(4000);


    if (17 * (num.toInt()) / 20 < newnum)
    {
      digitalWrite(bled, HIGH);

      Serial.println("You did pretty good today!");
      lcd.clear();
      lcd.print("You did a pretty");
      lcd.setCursor(0, 1);
      lcd.print("good job today!");
      delay(10000);
    }

    if (17 * (num.toInt()) / 20 > newnum && 2 * (num.toInt()) / 3 < newnum)
    {
      digitalWrite(gled, HIGH);

      Serial.println("Not bad!");
      lcd.clear();
      lcd.print("Not bad!");
      delay(10000);
    }

    if (2 * (num.toInt()) / 3 > newnum && num.toInt() / 5 < newnum)
    {
      digitalWrite(yled, HIGH);

      Serial.println("Looks like you need to work on your finances");
      lcd.clear();
      lcd.print("Try working on");
      lcd.setCursor(0, 1);
      lcd.print("your finances");
      delay(10000);
    }

    if (num.toInt() / 5 > newnum) {
      digitalWrite(rled, HIGH);

      Serial.println("OOOF");
      lcd.clear();
      lcd.print("OOOF");
      delay(10000);
    }

  }


  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    translateIR();
    irrecv.resume(); // receive the next value
  }
  else { }
}
