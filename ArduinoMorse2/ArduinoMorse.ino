
#include <LiquidCrystal.h>

const int buttonPin = 7;
const int buttonPin1 = 8;
const int buttonPin2 = 9;
const int buttonPin3 = 10;
int var = 0;
int var2 = 0;
char input[6];
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int choice = 0;
bool chosen = false;
char alpha[] = "abcdefghijklmnopqrstuvwxyz ";
int alphaChoice = 0;

void setup() {
  lcd.begin(16, 2);
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  Serial.begin(9600);
}

void loop() {

  //initialize buttons
  int button = digitalRead(buttonPin);
  int button1 = digitalRead(buttonPin1);
  int button2 = digitalRead(buttonPin2);
  int button3 = digitalRead(buttonPin3);

  //set the cursor
  lcd.setCursor(var, 0);


  if (chosen) {//runs if type of  translator is chosen
    if (choice == 0) { // if the translator is morse to text.
      if (button && button3) {//space
        lcd.print("|");
        input[var] = '|';
        var++;
        delay(200);
      } else if (button1 && button3) {//backspace morse
        //backspace
        var--;
        if (var < 0) {
          var = 0;
        }
        lcd.setCursor(var, 0);
        lcd.print(" ");
        input[var] = ' ';
        delay(200);

      } else if (button2 && button3) {//backspace translate

        lcd.setCursor(var2, 1);
        lcd.print(" ");
        input[var2] = ' ';
        var2--;
        if (var2 < 0) {
          var2 = 0;
        }
        delay(200);

      } else if (button && button3 != 1) {//dot
        lcd.print(".");
        input[var] = '.';
        var++;
        delay(200);

      }  else if (button1 && button3 != 1) {//dash
        lcd.print("-");
        input[var] = '-';
        var++;
        delay(200);

      } else if (button2 && button3 != 1) {//solve
        String morse = input;

        char result = morsetotext(morse);

        var2++;

        if (var2 == 16)  {
          for (var2; var2 >= 0; var2--) {
            lcd.setCursor(var2 - 1, 1);
            lcd.print(' ');
          }
          var2 = 0;
        }
        lcd.setCursor(var2, 1);
        lcd.print(result);


        delay(200);
        for (var; var >= 0; var--) {
          input[var] = '\0';
          lcd.setCursor(var - 1, 0);
          lcd.print(' ');
        }
        var = 0;
      }
    } else if (choice == 1) {// choice == text to morse
      lcd.setCursor(0, 0);
      //text to morse here
      if (button) {
        alphaChoice++;
        if (alphaChoice > 25) {
          alphaChoice = 0;
        }
      } else if (button3) {


        String result = texttomorse(alpha[alphaChoice]);
        Serial.println(result.length());

        if (var2 > 16)  {
          for (var2; var2 >= 0; var2--) {
            lcd.setCursor(var2 - 1, 1);
            lcd.print(' ');
          }
          var2 = 0;
        }

        for (var; var >= 0; var--) {
          lcd.setCursor(var - 1, 0);

        }
        var = 0;

        lcd.setCursor(var2, 1);
        lcd.print(result);
        lcd.print(" ");
        //var2++;

        var2 += result.length();

        delay(200);



      }
      lcd.setCursor(1, 0);
      lcd.print(alpha[alphaChoice]);
      delay(200);


    } else {
      lcd.setCursor(0, 0);
      lcd.print("No Function Yet...");
      lcd.setCursor(0, 1);
      lcd.print(choice);
    }
  } else {
    lcd.setCursor(0, 0);
    if (button) {
      choice++;
      if (choice > 2) {
        choice = 0;
      }
    } else if (button2) {
      choice--;
      if (choice < 0) {
        choice = 2;
      }
    } else if (button3) {
      chosen = true;
    } else {
    }
    switch (choice) {
      case 0:
        //lcd.clear();
        lcd.print("Morse To English");
        break;
      case 1:
        //lcd.clear();
        lcd.print("English To Morse");
        break;
      case 2:
        lcd.clear();
        lcd.print("Other");
        break;
    }
    delay(200);
    lcd.clear();
  }


}


char morsetotext(String c)
{

  char text[] = "abcdefghijklmnopqrstuvwxyz "; //osv

  String morse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
                    "....", "..", ".---", "-.-", ".-..", "--",
                    "-.", "---", ".--.", "--.-", ".-.", "...", "-",
                    "..-", "...-", ".--", "-..-", "-.--", "--..", "|"
                   }; //osv

  int i;
  char result = ' ';
  for (i = 0; i < 27; i++ ) {
    int found = morse[i].compareTo(c);
    if (found == 0) {
      result = text[i];
      break;
    }
  }

  return result;
}


String texttomorse(char d)
{

  char text[] = "abcdefghijklmnopqrstuvwxyz "; //osv

  String morse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
                    "....", "..", ".---", "-.-", ".-..", "--",
                    "-.", "---", ".--.", "--.-", ".-.", "...", "-",
                    "..-", "...-", ".--", "-..-", "-.--", "--..", "|"
                   }; //osv

  int i;
  String result2 = "";
  for (i = 0; i < 27; i++ ) {
    if (text[i] == d) {
      result2 = morse[i];
      break;
    }
  }

  return result2 + " ";
}



