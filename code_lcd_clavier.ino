#include <LiquidCrystal.h>
#include <Keypad.h>
#define Password_Lenght 5
#define DefaultPass 0000
    int MyPassVal;
    int Val_Etat=0;
    const int SystAlarm=7;
    char Data[Password_Lenght]; 
    byte data_count = 0;
    char customKey;
    char MyVal_1;
    char MyVal_2;    
    boolean Active=false;
    boolean Desactive=true;
    boolean Pass=false;
    boolean Etat=false;
    const byte ROWS = 4; 
    const byte COLS = 3; 
    char keys[ROWS][COLS] = {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'},
        {'*','0','#'}
    };
     int key[4];   //int key[2]; 
     
    byte rowPins[ROWS] = {0, 1, 2, 3}; 
    byte colPins[COLS] = {4, 5, 6}; 
     
    LiquidCrystal lcd(13,12,11,10,9,8);
    Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);
     
    void setup() {
      pinMode(SystAlarm,OUTPUT);    //???
      lcd.begin(16, 2);
      lcd.clear();
      lcd.print("Welcome");
      delay(500);
      
    } 
    void loop() {
  
        while(1)
        {    
                   
            Etat=true;       
            lcd.setCursor(0,0);
            lcd.print("Pass to ");
            if(Desactive==true)
            {
              lcd.print("active");
              Active=false;
            }
            else
            {
              lcd.print("Dsctv");
              Active=true;
            }                                   
            customKey = customKeypad.getKey();
            if (customKey) 
            {
              Data[data_count] = customKey; 
              lcd.setCursor(data_count,1);
              lcd.print(Data[data_count]); 
              data_count++; 
              delay(50); 
            }  
                
            if(data_count == Password_Lenght-1)     
            {     
                MyPassVal=(Data[0]-48)*1000+(Data[1]-48)*100+(Data[2]-48)*10+(Data[3]-48);
                if(MyPassVal!=DefaultPass)
                {
                   lcd.clear();
                   lcd.setCursor(0,0);
                   lcd.print("Error Pass");
                   lcd.setCursor(0,1);
                   lcd.print("try again");
                   delay(500);
                   Pass=false;
                   lcd.clear();
                   clearData();   
                   data_count=0;
                }
                else{Pass=true;}                                                                                                               
                while(Etat==true && Pass==true)                
                {
                   lcd.clear();
                   lcd.setCursor(0,0);
                  while(Etat==true && Active==false )   //Alarm  activé
                  {
                     
                      {
                        //prog_ activation
                        digitalWrite(SystAlarm,HIGH);
                      }
                      lcd.clear();
                      Desactive=false;
                      lcd.print("Alarm activated ");
                      lcd.setCursor(0,1);
                      lcd.print("press 1 to dsctvt");
                      
                      MyVal_1 = customKeypad.getKey();
                      if(MyVal_1)
                      { 
                        Val_Etat=(MyVal_1 -48);
                        if(Val_Etat==1)
                        {                          
                          Pass=false;
                          lcd.clear();
                          lcd.print("good ");
                          delay(30);
                          Etat=false;  
                        }
                        else
                        {
                          lcd.clear();
                          lcd.print("Error");
                          delay(50);
                        }
                      }                              
                      delay(50);
                  }
                  while(Etat==true && Active==true)       //Alarm désactivé
                  {
                    {
                        //prog_ activation
                      digitalWrite(SystAlarm,LOW);
                    }
                    Pass=false;
                    lcd.clear();
                    Desactive=true;
                    lcd.print("Alarm desactivated ");
                    lcd.setCursor(0,1);
                    lcd.print("press 2 to actvt");

                    MyVal_2 = customKeypad.getKey();
                    if(MyVal_2)
                    {
                        Val_Etat=(MyVal_2 -48);
                        if(Val_Etat==2)
                        {
                       
                          lcd.clear();
                          lcd.print("good");
                          delay(30);
                          Etat=false;                                      
                        }
                        else
                        {
                          lcd.clear();
                          lcd.print("Error");
                          delay(50);
                        }
                    }
                     delay(50);                               
                  }                                               
                  delay(500);
                  lcd.clear();
                }                   
              lcd.clear();
              clearData();   
              data_count=0;
            }
     }
 }

  void clearData()
  {
    while(data_count !=0)
    {   
      Data[data_count--] = 0; 
    }
    return;
  }

