
#define DBGpinENABLE

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
      if (state == true){
      #ifdef DBGpinENABLE
        digitalWrite(DEBUGpin, true); 
      #else
        digitalWrite(Relay, HIGH);
      #endif
    }
      else{

      #ifdef DBGpinENABLE
        digitalWrite(DEBUGpin, false);
      #else
        digitalWrite(Relay, LOW);      
      #endif
    }
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
//  delay(50);
  delay(10);
  if((buttonWasPressed == true) && (buttonWasReleased == true)){
    buttonWasPressed = false;
    buttonWasReleased = false;
    swCounter++;
    InterruptCounter = 0;
  }

  selectProgram(swCounter);
 
  if (swCounter >= 6){
    switchOffAllLEDs();
    swCounter = 0;
  }
  
//  delay(50);
  delay(10);
  if (timer_is_enable == true){
    increment_100msTimer();  
  }
  
}

void increment_100msTimer(){
    t_100msTimer++;
    // if (t_100msTimer >= 10){
    if (t_100msTimer >= 1){    
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

  switch(inPram){
  case 0:
    // system is off - No logic is enable and no timers are active
    timer_is_enable = false;
    program0Selected();
    break;
  case 1:
    timer_is_enable = true;
    program1Selected();
    break;
  case 2:
    timer_is_enable = true;
    program2Selected();
    break;
  case 3:
    timer_is_enable = true;
    program3Selected();
    break;
  case 4:
    timer_is_enable = true;
    program4Selected();
    break;
  case 5:
    timer_is_enable = true;
    program5Selected();
    break;
  case 6:
    timer_is_enable = true;  
    program6Selected();
    break;
  case 7:
    timer_is_enable = true;  
    program7Selected();
    break;
  case 8:
    timer_is_enable = true;
    program8Selected();
    break;
  }
}
void program0Selected(){
    setTimerVariablesToZero();
    setOut(9,false);
    firstCall = true;
    swCounter = 0;
}
void program1Selected(){
  if (firstCall == true){
    setTimerVariablesToZero();
    firstCall = false;
  }
  if (swCounter != 1){
    firstCall = true;
    setTimerVariablesToZero();
  }
    // 12 minutes ON
    if (t_minTimer <= 12){    
    setOut(9,true);
    }
    // 12 minutes OFF | Total minutes: 24
    else if ((t_minTimer >= 12) && (t_minTimer <= 24)){
      setOut(9,false);
    }
    // 6 minutes ON | Total minutes: 30
    else if ((t_minTimer >= 24) && (t_minTimer <= 30)){
      setOut(9,true);
    }
    // 12 minutes OFF | Total minutes: 42
    else if ((t_minTimer >= 30) && (t_minTimer <= 42)){
      setOut(9,false); 
    }
    // 6 minutes ON | Total minutes: 48
    else if ((t_minTimer >= 42) && (t_minTimer <= 48)){
      setOut(9,true); 
    }
  // Stop timers and switch program to 0
    else if (t_minTimer >= 48){
      setOut(9,false);
      switchOffAllLEDs();
      setTimerVariablesToZero();
      swCounter = 0;
      firstCall = true;
    }
    else{
      // no action
    }
}
void program2Selected(){
  
if (firstCall == true){
    setTimerVariablesToZero();
    firstCall = false;
  }
  if (swCounter != 2){
    firstCall = true;
    setTimerVariablesToZero();
  }
    // 12 minutes ON
    if (t_minTimer <= 12){    
    setOut(9,true);
    }
    // 12 minutes OFF | Total minutes: 24
    else if ((t_minTimer >= 12) && (t_minTimer <= 24)){
      setOut(9,false);
    }
    // 6 minutes ON | Total minutes: 30
    else if ((t_minTimer >= 24) && (t_minTimer <= 30)){
      setOut(9,true);
    }
    // 12 minutes OFF | Total minutes: 42
    else if ((t_minTimer >= 30) && (t_minTimer <= 42)){
      setOut(9,false); 
    }
    // 6 minutes ON | Total minutes: 48
    else if ((t_minTimer >= 42) && (t_minTimer <= 48)){
      setOut(9,true); 
    }
    // 12 minutes OFF | Total minutes: 60
    else if ((t_minTimer >= 48) && (t_minTimer <= 60)){
      setOut(9,false);    
    }
    // 6 minutes ON | Total minutes: 66
    else if ((t_minTimer >= 60) && (t_minTimer <= 66)){
      setOut(9,true);
    }
  // 12 minutes ON | Total minutes: 78
    else if ((t_minTimer >= 66) && (t_minTimer <= 78)){
      setOut(9,false);
    }
  // 6 minutes ON | Total minutes: 84
    else if ((t_minTimer >= 78) && (t_minTimer <= 84)){
      setOut(9,true);
    }
  // 12 minutes ON | Total minutes: 96
    else if ((t_minTimer >= 84) && (t_minTimer <= 96)){
      setOut(9,false);
    }
  // 12 minutes ON | Total minutes: 102
    else if ((t_minTimer >= 96) && (t_minTimer <= 102)){
      setOut(9,true);
    }
  // Stop timers and switch program to 0
    else if (t_minTimer >= 102){
      setOut(9,false);
      switchOffAllLEDs();
      timer_is_enable == false;
      setTimerVariablesToZero();
      swCounter = 0;
      firstCall = true;
    }
    else{
    // no action
    }
}
void program3Selected(){
  if (firstCall == true){
    setTimerVariablesToZero();
    firstCall = false;
  }
  if (swCounter != 3){
    firstCall = true;
    setTimerVariablesToZero();
  }
    // 12 minutes ON
    if ((t_minTimer >= 12) && (t_minTimer <= 0)){    
    setOut(9,true);
    }
    // 12 minutes OFF | Total minutes: 24
    else if ((t_minTimer >= 12) && (t_minTimer <= 24)){
      setOut(9,false);
    }
    // 6 minutes ON | Total minutes: 30
    else if ((t_minTimer >= 24) && (t_minTimer <= 30)){
      setOut(9,true);
    }
    // 12 minutes OFF | Total minutes: 42
    else if ((t_minTimer >= 30) && (t_minTimer <= 42)){
      setOut(9,false); 
    }
    // 6 minutes ON | Total minutes: 48
    else if ((t_minTimer >= 42) && (t_minTimer <= 48)){
      setOut(9,true); 
    }
  // No action for next 12 hours
    else if ((t_minTimer >= 48)&& (t_minTimer <= 12 * 60)){
      setOut(9,false);                        // 720
    }   
  // 12 minutes ON after 12 * 60 minutes has elapsed
    else if ((t_minTimer >= 0 + 12 * 60) && (t_minTimer <= 12 + 12 * 60)){    
    setOut(9,true);      // 720                                             // 732
    }
    // 12 minutes OFF | Total minutes: 24 after 12 * 60 minutes has elapsed
    else if ((t_minTimer >= 12 + 12 * 60) && (t_minTimer <= 24 + 12 * 60)){
      setOut(9,false);
    }
  // 6 minutes ON | Total minutes: 30 after 12 * 60 minutes has elapsed
    else if ((t_minTimer >= 24 + 12 * 60) && (t_minTimer <= 30 + 12 * 60)){
      setOut(9,true);
    }
  // 12 minutes OFF | Total minutes: 42 after 12 * 60 minutes has elapsed
    else if ((t_minTimer >= 30 + 12 * 60) && (t_minTimer <= 42 + 12 * 60)){
      setOut(9,false); 
    }
  // 6 minutes ON | Total minutes: 48 after 12 * 60 minutes has elapsed
    else if ((t_minTimer >= 42 + 12 * 60) && (t_minTimer <= 48 + 12 * 60)){
      setOut(9,true); 
    }
  // Stop timers and switch program to 0
    else if (t_minTimer >=  48 + 12 * 60){
      setOut(9,false);
      switchOffAllLEDs();
      timer_is_enable == false;
      setTimerVariablesToZero();
      swCounter = 0;
      firstCall = true;
    }
    else{
      // no action
    }
}
void program4Selected(){
  if (firstCall == true){
    setTimerVariablesToZero();
    firstCall = false;
  }
  if (swCounter != 4){
    firstCall = true;
    setTimerVariablesToZero();
  }
    // 12 minutes ON
    if ((t_minTimer >= 12) && (t_minTimer <= 0)){    
    setOut(9,true);
    }
    // 12 minutes OFF | Total minutes: 24
    else if ((t_minTimer >= 12) && (t_minTimer <= 24)){
      setOut(9,false);
    }
    // 6 minutes ON | Total minutes: 30
    else if ((t_minTimer >= 24) && (t_minTimer <= 30)){
      setOut(9,true);
    }
    // 12 minutes OFF | Total minutes: 42
    else if ((t_minTimer >= 30) && (t_minTimer <= 42)){
      setOut(9,false); 
    }
    // 6 minutes ON | Total minutes: 48
    else if ((t_minTimer >= 42) && (t_minTimer <= 48)){
      setOut(9,true); 
    }
  // No action for next 11 hours
    else if ((t_minTimer >= 48)&& (t_minTimer <= 11 * 60)){
      setOut(9,false); 
    }   
  // 12 minutes ON after 11 * 60 minutes has elapsed
    else if ((t_minTimer >= 0 + 11 * 60) && (t_minTimer <= 12 + 11 * 60)){    
    setOut(9,true);      // 660                                             // 672
    }
    // 12 minutes OFF | Total minutes: 24 after 11 * 60 minutes has elapsed
    else if ((t_minTimer >= 12 + 11 * 60) && (t_minTimer <= 24 + 11 * 60)){
      setOut(9,false);
    }
  // 6 minutes ON | Total minutes: 30 after 11 * 60 minutes has elapsed
    else if ((t_minTimer >= 24 + 11 * 60) && (t_minTimer <= 30 + 11 * 60)){
      setOut(9,true);
    }
  // 12 minutes OFF | Total minutes: 42 after 11 * 60 minutes has elapsed
    else if ((t_minTimer >= 30 + 11 * 60) && (t_minTimer <= 42 + 11 * 60)){
      setOut(9,false); 
    }
  // 6 minutes ON | Total minutes: 48 after 11 * 60 minutes has elapsed
    else if ((t_minTimer >= 42 + 11 * 60) && (t_minTimer <= 48 + 11 * 60)){
      setOut(9,true); 
    }
  // Stop timers and switch program to 0
    else if (t_minTimer >=  48 + 11 * 60){
      setOut(9,false);
      switchOffAllLEDs();
      timer_is_enable == false;
      setTimerVariablesToZero();
      swCounter = 0;
      firstCall = true;
    }
    else{
      // no action
    }
}
void program5Selected(){
  if (firstCall == true){
    setTimerVariablesToZero();
    firstCall = false;
  }
  if (swCounter != 5){
    firstCall = true;
    setTimerVariablesToZero();
  }
    // 12 minutes ON
    if ((t_minTimer >= 12) && (t_minTimer <= 0)){    
    setOut(9,true);
    }
    // 12 minutes OFF | Total minutes: 24
    else if ((t_minTimer >= 12) && (t_minTimer <= 24)){
      setOut(9,false);
    }
    // 6 minutes ON | Total minutes: 30
    else if ((t_minTimer >= 24) && (t_minTimer <= 30)){
      setOut(9,true);
    }
    // 12 minutes OFF | Total minutes: 42
    else if ((t_minTimer >= 30) && (t_minTimer <= 42)){
      setOut(9,false); 
    }
    // 6 minutes ON | Total minutes: 48
    else if ((t_minTimer >= 42) && (t_minTimer <= 48)){
      setOut(9,true); 
    }
  // No action for next 10 hours
    else if ((t_minTimer >= 48)&& (t_minTimer <= 10 * 60)){
      setOut(9,false); 
    }   
  // 12 minutes ON after 12 * 60 minutes has elapsed
    else if ((t_minTimer >= 0 + 10 * 60) && (t_minTimer <= 12 + 10 * 60)){    
    setOut(9,true);      // 600                                             // 612
    }
    // 12 minutes OFF | Total minutes: 24 after 10 * 60 minutes has elapsed
    else if ((t_minTimer >= 12 + 10 * 60) && (t_minTimer <= 24 + 10 * 60)){
      setOut(9,false);
    }
  // 6 minutes ON | Total minutes: 30 after 10 * 60 minutes has elapsed
    else if ((t_minTimer >= 24 + 10 * 60) && (t_minTimer <= 30 + 10 * 60)){
      setOut(9,true);
    }
  // 12 minutes OFF | Total minutes: 42 after 10 * 60 minutes has elapsed
    else if ((t_minTimer >= 30 + 10 * 60) && (t_minTimer <= 42 + 10 * 60)){
      setOut(9,false); 
    }
  // 6 minutes ON | Total minutes: 48 after 10 * 60 minutes has elapsed
    else if ((t_minTimer >= 42 + 10 * 60) && (t_minTimer <= 48 + 10 * 60)){
      setOut(9,true); 
    }
  // Stop timers and switch program to 0
    else if (t_minTimer >=  48 + 10 * 60){
      setOut(9,false);
      switchOffAllLEDs();
      timer_is_enable == false;
      setTimerVariablesToZero();
      swCounter = 0;
      firstCall = true;
    }
    else{
      // no action
    }
}
void program6Selected(){
  if (firstCall == true){
    setTimerVariablesToZero();
    firstCall = false;
  }
  if (swCounter != 6){
    firstCall = true;
    setTimerVariablesToZero();
  }
    // 12 minutes ON
    if ((t_minTimer >= 12) && (t_minTimer <= 0)){    
    setOut(9,true);
    }
    // 12 minutes OFF | Total minutes: 24
    else if ((t_minTimer >= 12) && (t_minTimer <= 24)){
      setOut(9,false);
    }
    // 6 minutes ON | Total minutes: 30
    else if ((t_minTimer >= 24) && (t_minTimer <= 30)){
      setOut(9,true);
    }
    // 12 minutes OFF | Total minutes: 42
    else if ((t_minTimer >= 30) && (t_minTimer <= 42)){
      setOut(9,false); 
    }
    // 6 minutes ON | Total minutes: 48
    else if ((t_minTimer >= 42) && (t_minTimer <= 48)){
      setOut(9,true); 
    }
  // No action for next 9 hours
    else if ((t_minTimer >= 48)&& (t_minTimer <= 9 * 60)){
      setOut(9,false); 
    }   
  // 12 minutes ON after 12 * 60 minutes has elapsed
    else if ((t_minTimer >= 0 + 9 * 60) && (t_minTimer <= 12 + 9 * 60)){    
    setOut(9,true);      // 540                                           // 552
    }
    // 12 minutes OFF | Total minutes: 24 after 9 * 60 minutes has elapsed
    else if ((t_minTimer >= 12 + 9 * 60) && (t_minTimer <= 24 + 9 * 60)){
      setOut(9,false);
    }
  // 6 minutes ON | Total minutes: 30 after 9 * 60 minutes has elapsed
    else if ((t_minTimer >= 24 + 9 * 60) && (t_minTimer <= 30 + 9 * 60)){
      setOut(9,true);
    }
  // 12 minutes OFF | Total minutes: 42 after 9 * 60 minutes has elapsed
    else if ((t_minTimer >= 30 + 9 * 60) && (t_minTimer <= 42 + 9 * 60)){
      setOut(9,false); 
    }
  // 6 minutes ON | Total minutes: 48 after 9 * 60 minutes has elapsed
    else if ((t_minTimer >= 42 + 9 * 60) && (t_minTimer <= 48 + 9 * 60)){
      setOut(9,true); 
    }
  // Stop timers and switch program to 0 after 9 * 60 minutes has elapsed
    else if (t_minTimer >=  48 + 9 * 60){
      setOut(9,false);
      switchOffAllLEDs();
      timer_is_enable == false;
      setTimerVariablesToZero();
      swCounter = 0;
      firstCall = true;
    }
    else{
      // no action
    }
}
void program7Selected(){
    setOut(9,false);// Relay disable
    setTimerVariablesToZero();
  
}
void program8Selected(){
    setOut(9,false);// Relay disable
    setTimerVariablesToZero();
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