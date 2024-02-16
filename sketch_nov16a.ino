#include<LiquidCrystal.h>

LiquidCrystal lcd(1,2,4,5,6,7);

#include<Keypad.h>

char currentTimeValue[4];

int currentState=1;

int timerSeconds=0;

int lpcnt=0;

byte rowpins[4]={13,12,11,10}; 

byte colpins[3]={9,8,3,};

char keys[4][3]={

    {'1','2','3'},

    {'4','5','6'},

    {'7','8','9'},

    {'*','0','#'}


    

};

Keypad lala=Keypad(makeKeymap(keys),rowpins,colpins,4,3); 

void setup() { 

  lcd.begin(16,2);

  

  lcd.setCursor(1,0);

  lcd.print("Time");

  currentTimeValue[0]='0';

  currentTimeValue[1]='0';

  currentTimeValue[2]='0';

  currentTimeValue[3]='0';

  showEnteredTime();

  

}


void loop() {

  char tempVal[3];

  char key = lala.getKey();

  

  if(key!= NO_KEY and currentState==1) {

    switch(key){

      case '*':

      currentTimeValue[0]='0';

      currentTimeValue[1]='0';

      currentTimeValue[2]='0';

      currentTimeValue[3]='0';

      showEnteredTime();

      currentState=1;

      lpcnt=0;

      timerSeconds=0;

      break;

      case'#':

      tempVal[0]=currentTimeValue[0];

      tempVal[1]=currentTimeValue[1];

      tempVal[2]=0;

      timerSeconds=atol(tempVal)*60;

      tempVal[0]=currentTimeValue[2];

      tempVal[1]=currentTimeValue[3];

      tempVal[2]=0;

      timerSeconds=timerSeconds+atol(tempVal);

      currentState=2;

      break;

      default:

      currentTimeValue[0]=currentTimeValue[1];

      currentTimeValue[1]=currentTimeValue[2];

      currentTimeValue[2]=currentTimeValue[3];

      currentTimeValue[3]=key;

      showEnteredTime();

      break;

      }

    

   }

   if(currentState==2){

   char key=lala.getKey(); 

   if(key!= NO_KEY){

   if(key=='*'){

    displayCodeEntryScreen();

     currentTimeValue[0]='0';

      currentTimeValue[1]='0';

      currentTimeValue[2]='0';

      currentTimeValue[3]='0';

      showEnteredTime();

      currentState=1;

      lpcnt=0;

      timerSeconds=0;

    }

    }

    else{

      if(lpcnt>9){

        lpcnt=0;

        --timerSeconds;

        showCountdown();


        if(timerSeconds <=0){

          currentState=1;

          displayCodeEntryScreen();

          showEnteredTime();

          }

          }

          ++lpcnt;

          delay(100);

        

      } 

    

    }

}

void showEnteredTime(){

  lcd.setCursor(11,0);

  lcd.print(currentTimeValue[0]);

  lcd.print(currentTimeValue[1]);

  lcd.print(":");

  lcd.print(currentTimeValue[2]);

  lcd.print(currentTimeValue[3]);

  

  }

  void showCountdown(){

    char timest[6];

    lcd.setCursor(0,1);

    lcd.print("counting ");

    sprintf(timest, "%d:%.2d",(timerSeconds/60),(timerSeconds-((timerSeconds/60)*60)));

    lcd.print(timest);

    }

    void displayCodeEntryScreen(){

      clearScreen();

      lcd.setCursor(0,2);

      lcd.print("Enter time mm:ss:"); 

      }

    void clearScreen(){

      lcd.setCursor(0,0);

      lcd.print(".");

      }  


