#include <Encoder.h>
#include "Tlc5940.h"
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel LED1 = Adafruit_NeoPixel(4, 8, NEO_GRB + NEO_KHZ800);
char runing;
char number; 
#define BUTTON_PIN   6
String strIN;
String StrINHeader;
String ist;
String vorhanden;
String Refstart;
String Refstartbroad;
String Refstate;
String Position;

int sensorValue;
int SollPosition;

bool refpositionL = false;
bool refpositionR = false;

Encoder encoder1(4, 5);

void setup() {
  LED1.begin();
  LED1.setPixelColor(0, LED1.Color(0,0,10)); LED1.setPixelColor(1, LED1.Color(0,0,0)); LED1.setPixelColor(2, LED1.Color(0,0,0)); LED1.setPixelColor(3, LED1.Color(0,0,0));
  LED1.show();
  
  Tlc.init();
  Serial.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  //pinMode(4, INPUT_PULLUP); //Adresse
  //pinMode(5, INPUT_PULLUP); //Adresse
  pinMode(6, INPUT_PULLUP); //Adresse
  //pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  //int pin4 = digitalRead(4); //Adresse
  //int pin5 = digitalRead(5); //Adresse
  //int pin6 = digitalRead(6); //Adresse
  bool pin4 = true;
  bool pin5 = true; 
  bool pin6 = true;
  
  digitalWrite(7, LOW); 
  
  if (pin4 == true && pin5 == true && pin6 == true)  
     {number = '0'; ist = ":P0I"; vorhanden = ":P0V"; Refstart = ":P0R"; Refstartbroad = "*R"; Refstate = ":P0S"; Position = ":P0P";}
  if (pin4 == false && pin5 == true && pin6 == true) 
    {number = '1'; ist = ":P1I"; vorhanden = ":P1V"; Refstart = ":P1R"; Refstartbroad = "*R"; Refstate = ":P1S"; Position = ":P1P";}
  if (pin4 == false && pin5 == false && pin6 == false) 
    {number = '2'; ist = ":P2I"; vorhanden = ":P2V"; Refstart = ":P2R"; Refstartbroad = "*R"; Refstate = ":P2S"; Position = ":P2P";}  
  if (pin4 == false && pin5 == false && pin6 == false) 
     {number = '3'; ist = ":P3I"; vorhanden = ":P3V"; Refstart = ":P3R"; Refstartbroad = "*R"; Refstate = ":P3S"; Position = ":P3P";}
  if (pin4 == false && pin5 == false && pin6 == false) 
     {number = '4'; ist = ":P4I"; vorhanden = ":P4V"; Refstart = ":P4R"; Refstartbroad = "*R"; Refstate = ":P4S"; Position = ":P4P";}
  if (pin4 == false && pin5 == false && pin6 == false) 
     {number = '5'; ist = ":P5I"; vorhanden = ":P5V"; Refstart = ":P5R"; Refstartbroad = "*R"; Refstate = ":P5S"; Position = ":P5P";}
  if (pin4 == false && pin5 == false && pin6 == false) 
     {number = '6'; ist = ":P6I"; vorhanden = ":P6V"; Refstart = ":P6R"; Refstartbroad = "*R"; Refstate = ":P6S"; Position = ":P6P";}
  if (pin4 == false && pin5 == false && pin6 == false) 
     {number = '7'; ist = ":P7I"; vorhanden = ":P7V"; Refstart = ":P7R"; Refstartbroad = "*R"; Refstate = ":P7S"; Position = ":P7P";}
  if (pin4 == false && pin5 == false && pin6 == false) 
     {number = '8'; ist = ":P8I"; vorhanden = ":P8V"; Refstart = ":P8R"; Refstartbroad = "*R"; Refstate = ":P8S"; Position = ":P8P";}
  if (pin4 == false && pin5 == false && pin6 == false) 
     {number = '9'; ist = ":P9I"; vorhanden = ":P9V"; Refstart = ":P9R"; Refstartbroad = "*R"; Refstate = ":P9S"; Position = ":P9P";}
}

/***********************************END void Setup ()**************************************************************************/


char firstbytePos; //Erstes byte für Position
char secondbytePos; //Zweites byte für Position
char thirdbytePos;

char firstbyteIST; //Erstes byte für Encoder IST - Wert
char secondbyteIST; //Zweites byte für Encoder IST - Wert
char thirdbyteIST;

long i = 0; //Zähler für die Wiederholung des Paket sendens
bool Ref; //Reffahrt initiieren

  int EncValue = 0;
  int EncValue2 = 0;
  int EncValueLast = 0;
  
  int istPos = 0;
  int sollPos = 0;
  int sollPoslast = 0;
  
  int EncValue1 = 0;
  int EncValueLast1 = 0;
  int PositionEnc = 0;

  int MODE = 1;
  bool toggle = false;
  int button = 0;

  bool oldState = HIGH;

  int sollPos2 = 0;

  int PAC = 0;
  int p = 0;
  
void loop() {


/*********Routine um Motor in Refposition zu bringen************/

  
  
  //delayMicroseconds(10); //generelles Timing



/*******************************************CHAR für IST Wert aufbereiten********************************/

      //if (istPos == sollPoslast + 1 || istPos == sollPoslast - 1) {istPos = sollPoslast;}
      if (istPos<100)
      {
        thirdbyteIST = '0';
        if (istPos< 10){firstbyteIST = '0'; secondbyteIST = char(istPos+48);}
        if (istPos >= 10 && istPos <20 ){firstbyteIST = '1'; secondbyteIST = char(istPos+38);}
        if (istPos >= 20 && istPos <30 ){firstbyteIST = '2'; secondbyteIST = char(istPos+28);}
        if (istPos >= 30 && istPos <40 ){firstbyteIST = '3'; secondbyteIST = char(istPos+18);}
        if (istPos >= 40 && istPos <50 ){firstbyteIST = '4'; secondbyteIST = char(istPos+8);}
        if (istPos >= 50 && istPos <60 ){firstbyteIST = '5'; secondbyteIST = char(istPos-2);}
        if (istPos >= 60 && istPos <70 ){firstbyteIST = '6'; secondbyteIST = char(istPos-12);}
        if (istPos >= 70 && istPos <80 ){firstbyteIST = '7'; secondbyteIST = char(istPos-22);}
        if (istPos >= 80 && istPos <90 ){firstbyteIST = '8'; secondbyteIST = char(istPos-32);}
        if (istPos >= 90 && istPos <100 ){firstbyteIST = '9';secondbyteIST = char(istPos-42);}
      }
       //if (sensorValue >= 100)
       if (istPos >= 100)
       {
        thirdbyteIST = '1';
        if (istPos< 110){firstbyteIST = '0'; secondbyteIST = char(istPos-52);}
        if (istPos >= 110 && istPos <120 ){firstbyteIST = '1'; secondbyteIST = char(istPos-62);}
        if (istPos >= 120 && istPos <130 ){firstbyteIST = '2'; secondbyteIST = char(istPos-72);}
        if (istPos >= 130 && istPos <140 ){firstbyteIST = '3'; secondbyteIST = char(istPos-82);}
        if (istPos >= 140 && istPos <150 ){firstbyteIST = '4'; secondbyteIST = char(istPos-92);}
        if (istPos >= 150 && istPos <160 ){firstbyteIST = '5'; secondbyteIST = char(istPos-102);}
        if (istPos >= 160 && istPos <170 ){firstbyteIST = '6'; secondbyteIST = char(istPos-112);}
        if (istPos >= 170 && istPos <180 ){firstbyteIST = '7'; secondbyteIST = char(istPos-122);}
        if (istPos >= 180 && istPos <190 ){firstbyteIST = '8'; secondbyteIST = char(istPos-132);}
        if (istPos >= 190){firstbyteIST = '9'; secondbyteIST = '0';}
       }
    

/********Serielles Paket auswerten (GesamtString/StringHeader)***************************/
    if(Serial.available() > 0) 
        {
        strIN = Serial.readStringUntil('\n'); //gesamter Input String
        StrINHeader = strIN.substring(0,4);   //nur String Header auswerten
        }
/**********Serielles Paket für vorhanden senden (einfach nur antworten)*******************/
    if (StrINHeader == vorhanden)
        {   
        Serial.write(';'); //Kennung von Poti
        Serial.write('P'); //Komando
        Serial.write(number); //Pot number
        Serial.write('V'); //Befehl
        Serial.write('\n'); //Endzeichen
        StrINHeader = "NULL";
        i++;
        }

 if (istPos != sollPos && sollPos2 != sollPos) {PositionEnc = sollPos; sollPos2 = sollPos;}


/*********Serielles Paket für Position senden (spiegeln & SollPosition --> INT)******/      
        if (StrINHeader == Position)
        //if (StrINHeader == Position && task == 3)
        {    
        /*INT für SollPosition erzeugen*/  
        firstbytePos  = strIN.substring(4,5).toInt();
        secondbytePos = strIN.substring(5,6).toInt();
        thirdbytePos  = strIN.substring(6,7).toInt();
        
        if (thirdbytePos == 0) //hunderterStelle = 0
        {
         if (firstbytePos == 0) {sollPos = secondbytePos + 00;} //firstbytePos = 0
         if (firstbytePos == 1) {sollPos = secondbytePos + 10;} //firstbytePos = 1
         if (firstbytePos == 2) {sollPos = secondbytePos + 20;} //firstbytePos = 2
         if (firstbytePos == 3) {sollPos = secondbytePos + 30;} //firstbytePos = 3
         if (firstbytePos == 4) {sollPos = secondbytePos + 40;} //firstbytePos = 4
         if (firstbytePos == 5) {sollPos = secondbytePos + 50;} //firstbytePos = 5
         if (firstbytePos == 6) {sollPos = secondbytePos + 60;} //firstbytePos = 6
         if (firstbytePos == 7) {sollPos = secondbytePos + 70;} //firstbytePos = 7
         if (firstbytePos == 8) {sollPos = secondbytePos + 80;} //firstbytePos = 8
         if (firstbytePos == 9) {sollPos = secondbytePos + 90;} //firstbytePos = 9
        }

        if (thirdbytePos == 1) //hunderterStelle = 1
        {
         if (firstbytePos == 0) {sollPos = secondbytePos + 100;} //firstbytePos = 0
         if (firstbytePos == 1) {sollPos = secondbytePos + 110;} //firstbytePos = 1
         if (firstbytePos == 2) {sollPos = secondbytePos + 120;} //firstbytePos = 2
         if (firstbytePos == 3) {sollPos = secondbytePos + 130;} //firstbytePos = 3
         if (firstbytePos == 4) {sollPos = secondbytePos + 140;} //firstbytePos = 4
         if (firstbytePos == 5) {sollPos = secondbytePos + 150;} //firstbytePos = 5
         if (firstbytePos == 6) {sollPos = secondbytePos + 160;} //firstbytePos = 6
         if (firstbytePos == 7) {sollPos = secondbytePos + 170;} //firstbytePos = 7
         if (firstbytePos == 8) {sollPos = secondbytePos + 180;} //firstbytePos = 8
         if (firstbytePos == 9) {sollPos = secondbytePos + 190;} //firstbytePos = 9
        }
        
        StrINHeader = "NULL";
  
        }
/********************************************IST Position auslesen****************************************/   
 
        
/******************************Serielles Paket für IST-WERT senden************************/
    if (StrINHeader == ist)
        {  
        //if(sensorValue >= SollPosition +3 || sensorValue <= SollPosition -3)
        //{        
          Serial.write(';'); //Kennung von Poti
          Serial.write('P'); //Kommando  
          Serial.write(number); //Pot number
          Serial.write('I'); //Befehl
          Serial.write(firstbyteIST); //erstes Datenbyte
          Serial.write(secondbyteIST); //zweites Datenbyte
          Serial.write(thirdbyteIST);
          if (MODE == 1) {Serial.write('1');}
          if (MODE == 2) {Serial.write('2');}
          if (MODE == 3) {Serial.write('3');}
          if (MODE == 4) {Serial.write('4');}
          if (MODE == 5) {Serial.write('5');}
          Serial.write('\n'); //Endzeichen
          StrINHeader = "NULL";
          runing = 'S';
          i++;
        // }
        } 

   //if (PositionEnc != sollPos) {PositionEnc = sollPos;}
   EncValue1 = encoder1.read()/1.5;
     if (EncValue1 > EncValueLast1) {PositionEnc = PositionEnc + 1;} 
     if (EncValue1 < EncValueLast1) {PositionEnc = PositionEnc - 1;} 
     EncValueLast1 = EncValue1;
     if (PositionEnc >=63) {PositionEnc = 63;}
     if (PositionEnc <=0) {PositionEnc = 0;};
 
  if (istPos > 127) {istPos = 127;}
  if (istPos <= 0) {istPos = 0;}

  
 istPos = PositionEnc;

  p = p + 1;
  if (p > 30) {PAC = PAC+1; p=0;}
  if (PAC > 8) {PAC = 0;}
  

  //MODE=1;
  for (int k = 0; k < 64; k++)
  {
    switch (MODE)
    {
    
      case 1: //eine LED zur Zeit an!
      {
        if (k != PositionEnc) 
         {
          Tlc.set(k,0);  
         }
         
        else { 
          Tlc.set(PositionEnc,100);   
         }
      } break;

       case 2://alle LEDs unter PositionENC an.
      {
        if (k > PositionEnc) 
         {
          Tlc.set(k,0); //eine LED zur Zeit an! 
         }
         
        if (k <= PositionEnc) 
         { 
            
         Tlc.set(k,50);  
         }
      } break;
          
       case 3://alle LEDs an doller PositionENC an.
      {
        if (k > PositionEnc) 
         {
          Tlc.set(k,1); 
         }
        if (k < PositionEnc) 
         {
          Tlc.set(k,1);  
         }       
        if (k == PositionEnc) 
        { 
          Tlc.set(k,200);   
         }
      } break;

       
        case 4://Pac Man Mode
      {
        LED1.setPixelColor(0, LED1.Color(0,0,0));
        
        if (k > PositionEnc+2) 
         {
          Tlc.set(k,20); 
         }
         if (k == PositionEnc+2) 
         {
          Tlc.set(k,5); 
         }
        if (k == PositionEnc+1) 
         {
          Tlc.set(k,1); 
         }
        if (k < PositionEnc-2) 
         {
          Tlc.set(k,20);  
         }    
        if (k == PositionEnc-2) 
         {
          Tlc.set(k,5);  
         }    
        if (k == PositionEnc-1) 
         {
          Tlc.set(k,1);  
         }    
        if (k == PositionEnc) 
         { 
          Tlc.set(k,0);   
         }
      } break;



        
        case 5://Pac Man Mode
      {
        LED1.setPixelColor(0, LED1.Color(0,0,PAC));
        
        if (k > PositionEnc+PAC) 
         {
          Tlc.set(k,20); 
         }
        if (k == PositionEnc+PAC) 
         {
          Tlc.set(k,1); 
         }
        if (k < PositionEnc-PAC) 
         {
          Tlc.set(k,20);  
         }    
        if (k == PositionEnc-PAC) 
         {
          Tlc.set(k,1);  
         }    
        if (k == PositionEnc) 
         { 
          Tlc.set(k,0);   
         }
      } break;
      
     }  
   

    } 
   
  Tlc.update();
   LED1.show();

    bool newState = digitalRead(BUTTON_PIN);
    // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {
    // Short delay to debounce button.
    delay(10);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) {
      MODE++;
      if (MODE > 5)
        MODE=1;
     }
  }

  oldState = newState;

}



