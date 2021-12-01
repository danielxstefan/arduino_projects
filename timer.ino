//Used inputs:
const int inputButton = 13; // This port is used as input
//Used outputs:
const int Relay     =  4;   // This port is used for Relay
const int LEDout1   =  5;   // This port is used for LED1
const int LEDout2   =  6;   // This port is used for LED2
const int LEDout3   = 10;   // This port is used for LED3
const int LEDout4   = 11;   // This port is used for LED4
const int LEDout5   =  7;   // This port is used for LED5
const int LEDout6   =  8;   // This port is used for LED6
const int LEDout7   =  9;   // This port is used for LED7
const int LEDout8   = 12;   // This port is used for LED8
const int LEDbutton =  3;   // This port is used for LED inside the button
const int DEBUGpin =   2;   // This port is used for check the logic and times with logic analyzer
//Variables
int buttonState = 0; 
int switchState = 0;
bool buttonIsPressed  = false;
bool buttonWasReleased = false;
int multiplication = 0;
int countMinutes = 0;
// LOW  = 0
// HIGH = 1

//Used times
const int toggleTime = 100;
const int pressDelayTime = 10;
int delayStartRelay = 0;
int delayStopRelay = 0;
int secToMinutes = 0;
int msToSeconds = 0;


void setOut(int param, bool state){
  switch (param){
    case 0:
      if (state == true){digitalWrite(LEDbutton, HIGH);}
      else{digitalWrite(LEDbutton, LOW);}
      break;
    case 1:
      if (state == true){digitalWrite(LEDout1, HIGH);}
      else{digitalWrite(LEDout1, LOW);}
      break;
    case 2:
      if (state == true){digitalWrite(LEDout2, HIGH);}
      else{digitalWrite(LEDout2, LOW);}
      break;
    case 3:
      if (state == true){digitalWrite(LEDout3, HIGH);}
      else{digitalWrite(LEDout3, LOW);}
      break;
    case 4:
      if (state == true){digitalWrite(LEDout4, HIGH);}
      else{digitalWrite(LEDout4, LOW);}
      break;
    case 5:
      if (state == true){digitalWrite(LEDout5, HIGH);}
      else{digitalWrite(LEDout5, LOW);}
      break;
    case 6:
      if (state == true){digitalWrite(LEDout6, HIGH);}
      else{digitalWrite(LEDout6, LOW);}
      break;
    case 7:
      if (state == true){digitalWrite(LEDout7, HIGH);}
      else{digitalWrite(LEDout7, LOW);}
      break;
    case 8:
      if (state == true){digitalWrite(LEDout8, HIGH);}
      else{digitalWrite(LEDout8, LOW);}
      break;
    case 9:
      if (state == true){digitalWrite(Relay, HIGH);}
      else{digitalWrite(Relay, LOW);}
      break;              
    default:
        ;
      break;
  }
}

void initPhase(void){
  for (int x = 0; x < 9; x++){
    setOut(x, true);
    delay(100);
  }
    for (int x = 8; x >= 0; x--){
    setOut(x, false);
    delay(100);
  }
}

void setup() {
  // put your setup code here, to run once:

  pinMode(inputButton, INPUT);
  pinMode(Relay, OUTPUT); 
  pinMode(LEDout1, OUTPUT);
  pinMode(LEDout2, OUTPUT);
  pinMode(LEDout3, OUTPUT);
  pinMode(LEDout4, OUTPUT);
  pinMode(LEDout5, OUTPUT);
  pinMode(LEDout6, OUTPUT);
  pinMode(LEDout7, OUTPUT);
  pinMode(LEDout8, OUTPUT);
  pinMode(LEDbutton, OUTPUT);
  pinMode(DEBUGpin, OUTPUT);
  initPhase();
}


void loop() {

//for (secToMinutes = 0; secToMinutes < 4; secToMinutes++)
for (secToMinutes = 0; secToMinutes < 12; secToMinutes++)
{
  for (msToSeconds = 0; msToSeconds < 50; msToSeconds++)
  {
    // this code keep the button state(preesed or released) and 
    // increments the switchState 
    // START HERE
      buttonState = digitalRead(inputButton);
      if (buttonState == HIGH) {
        digitalWrite(LEDbutton, HIGH);
        buttonIsPressed = true;
      }
      else{
        //digitalWrite(LEDbutton, LOW);
        buttonIsPressed = false;
      }
      delay(pressDelayTime);
      if (buttonIsPressed == true){
        buttonWasReleased = true;
      }
    
      if ((buttonWasReleased == true) && (buttonState == LOW)){
        switchState+=1;
        buttonWasReleased = false;
        //reset counter and relay after each state change
        countMinutes = 0;
//        setOut(9,false);// Relay disable
      }
    // END HERE
      if (switchState >= 9){
        for (int i = 1; i < 9; i ++){
          setOut(i,false);
        }
        switchState = 0;
      }
      delay(pressDelayTime);
    
      //Show the current state
      setOut(switchState,true);
      if (switchState == 0){
        setOut(9,false);// Relay disable
      }
      
  }
  // after this iteration delay is 1 sec
  switch(switchState){
    case 0:
      //secToMinutes = 10;
      countMinutes = 0;
      setOut(9,false);// Relay disable
      break;
    case 1:
      multiplication = 15;
      //setOut(9,false);// Relay disable
      break;
    case 2:
      multiplication = 20;
      //setOut(9,false);// Relay disable
      break;
    case 3:
      multiplication = 25;
      //setOut(9,false);// Relay disable
      break;
    case 4:
      multiplication = 30;
      //setOut(9,false);// Relay disable
      break;
    case 5:
      multiplication = 35;
      //setOut(9,false);// Relay disable
      break;
    case 6:
      multiplication = 40;
      //setOut(9,false);// Relay disable
      break;
    case 7:
      multiplication = 45;
      //setOut(9,false);// Relay disable
      break;
    case 8:
      multiplication = 50;
      //setOut(9,false);// Relay disable
      break;
    default:
      break;
  }
  
}
// after this iteration delay is 12 seconds

if (countMinutes > (9 * multiplication)){
  countMinutes = 0;
}
if (countMinutes < (5 * multiplication)){
  if (switchState != 0){
    setOut(9,true);// Relay Enable
    digitalWrite(DEBUGpin, HIGH);
  }
}
else {
  setOut(9,false);// Relay disable
  digitalWrite(DEBUGpin, LOW);
}

//      if (countMinutes % 2 == 0){
//        digitalWrite(DEBUGpin, HIGH);
//      }
//      else
//      {
//        digitalWrite(DEBUGpin, LOW);
//      }

countMinutes++;
//int delayStartRelay = 0;
//int delayStopRelay = 0;

}
