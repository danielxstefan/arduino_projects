//Used inputs:
const int inputButton = 2; // This port is used as input
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
const int DEBUGpin =   13;   // This port is used for check the logic and times with logic analyzer
//Variables
volatile byte InterruptCounter = 0;
byte swCounter = 0;
bool buttonWasPressed = false;
bool buttonWasReleased = false;

// LOW  = 0
// HIGH = 1
bool debugPinState = false;

//Used times
int t_100msTimer = 0;
int t_secTimer = 0;
int t_minTimer = 0;
bool timer_is_enable = false;
bool firstCall = false;


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

  //pinMode(inputButton, INPUT);
  pinMode(inputButton, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(inputButton), btnLowToHi, RISING);
  attachInterrupt(digitalPinToInterrupt(inputButton), btnStateChange, CHANGE);
  
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
  setOut(swCounter, true);
  if(InterruptCounter == 1){
    buttonWasPressed = true;
  }
  delay(50);
  if((buttonWasPressed == true) && (buttonWasReleased == true)){
    buttonWasPressed = false;
    buttonWasReleased = false;
    swCounter++;
    InterruptCounter = 0;
  }

  selectProgram(swCounter);
 
  if (swCounter >= 9){
    switchOffAllLEDs();
    swCounter = 0;
  }
  
  delay(50);
  increment_100msTimer();
}

void increment_100msTimer(){
    t_100msTimer++;
    if (t_100msTimer >= 10){
    // if 1 second elapsed
      t_secTimer++;      
      // if 1 minute elapsed
//      if (t_secTimer >= 60){
      if (t_secTimer >= 1){
        increment_1minTimer();
        t_secTimer = 0;
      }
    t_100msTimer = 0;
    }
}

void increment_1minTimer(){
  t_minTimer++;
  if(t_minTimer >= 20000){
      t_minTimer = 0;
  }
//  debugPinState = !debugPinState;
//  digitalWrite(DEBUGpin, debugPinState);
}

void selectProgram(byte inPram){

//if (inPram == 1){
//  setOut(7,true);
//}
//else {
//  setOut(7,false);
//}
  switch(inPram){
  case 0:
    // system is off - No logic is enable and no timers are active
    program0Selected();
    break;
  case 1:
    program1Selected();
    break;
  case 2:
    program2Selected();
    break;
  case 3:
    program3Selected();
    break;
  case 4:
    program4Selected();
    break;
  case 5:
    program5Selected();
    break;
  case 6:
    program6Selected();
    break;
  case 7:
    program7Selected();
    break;
  case 8:
    program8Selected();
    break;

  }
  
}
void program0Selected(){
  // all timers are off
//  timer_is_enable == false;
  setTimerVariablesToZero();
  // Relay is OFF
  setOut(9,false);
}
void program1Selected(){
  if (firstCall == true){
    setTimerVariablesToZero();
    firstCall = false;
  }
  if (swCounter != 1){
    firstCall = true;
  }

    // 12 minutes ON
    if (t_minTimer <= 12){
      setOut(9,true);
      digitalWrite(DEBUGpin, true); 
    }
    // 12 minutes OFF | Total minutes: 24
    else if ((t_minTimer >= 12) && (t_minTimer <= 24))
    {
      setOut(9,false);
      digitalWrite(DEBUGpin, false); 
    }
    // 6 minutes ON | Total minutes: 30
    else if ((t_minTimer >= 24) && (t_minTimer <= 30))
    {
      setOut(9,true);    
      digitalWrite(DEBUGpin, true); 
    }
    // 12 minutes OFF | Total minutes: 42
    else if ((t_minTimer >= 30) && (t_minTimer <= 42))
    {
      setOut(9,false);    
      digitalWrite(DEBUGpin, false); 
    }
    // 6 minutes ON | Total minutes: 48
    else if ((t_minTimer >= 42) && (t_minTimer <= 48))
    {
      setOut(9,true);    
      digitalWrite(DEBUGpin, true); 
    }
    // 6 minutes ON | Total minutes: 48
    else if (t_minTimer >= 48)
    {
      setOut(9,false);
      digitalWrite(DEBUGpin, false); 
      switchOffAllLEDs();
      timer_is_enable == false;
      setTimerVariablesToZero();
      swCounter = 0;
      firstCall = true;
    }
    else{
      //END program 1
//      setOut(6,true);
    }
    
  
}
void program2Selected(){
    setOut(9,false);// Relay disable
  
}
void program3Selected(){
    setOut(9,false);// Relay disable
  
}
void program4Selected(){
    setOut(9,false);// Relay disable
  
}
void program5Selected(){
    setOut(9,false);// Relay disable
  
}
void program6Selected(){
    setOut(9,false);// Relay disable
  
}
void program7Selected(){
    setOut(9,false);// Relay disable
  
}
void program8Selected(){
    setOut(9,false);// Relay disable
  
}

void setTimerVariablesToZero(){
  t_100msTimer = 0;
  t_secTimer = 0;
  t_minTimer = 0;
}





void switchOffAllLEDs(){
  for (int i = 1; i < 9; i ++){
    setOut(i,false);
  }
}

void btnStateChange(){
  // - when the button is pressed;
  InterruptCounter = 1;
  if(buttonWasPressed == true){
    buttonWasReleased = true;
  }
}

