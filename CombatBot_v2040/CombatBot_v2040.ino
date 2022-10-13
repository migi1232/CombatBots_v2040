
  //------------------------------------------------------------------------------------//
 //                                      SET-UP
//------------------------------------------------------------------------------------//
//RC channel pin definitions
#define RC_Ch1 9
#define RC_Ch2 8
#define RC_Ch3 7
#define RC_Ch4 6

//Motor Driver Pin definitions
#define Motor_1A 20
#define Motor_1B 21
#define Motor_2A 18
#define Motor_2B 19
#define Motor_3A 16
#define Motor_3B 17

//Servo Header Pin definition
#define ServoData 14

//GPIO Pin Definitions
#define GPIO_4 10   //I2C: SDA_1,   SPI: SCK
#define GPIO_3 11   //I2C: SCL_1,   SPI: DO
#define GPIO_2 12   //I2C: SDA_0,   SPI: DI,    UART: TX_0
#define GPIO_1 13   //I2C: SCL_0,   SPI: CS,    UART: RX_0

int ch1, ch2, ch3, ch4, ch1Map, ch2Map, ch3Map, ch4Map, HPWM, VPWM, RWD, LWD;

void setup() {

//Essential pin setups - Changing NOT recommended-----
  //Motor Drivers IO pin setup:
  pinMode(Motor_1A, OUTPUT);
  pinMode(Motor_1B, OUTPUT);
  pinMode(Motor_2A, OUTPUT);
  pinMode(Motor_2B, OUTPUT);
  pinMode(Motor_3A, OUTPUT);
  pinMode(Motor_3B, OUTPUT);
  // RC channels IO pin setup:
  pinMode(RC_Ch1, INPUT_PULLUP);
  pinMode(RC_Ch2, INPUT_PULLUP);
  pinMode(RC_Ch3, INPUT_PULLUP);
  pinMode(RC_Ch4, INPUT_PULLUP);
//----------------------------------------------------


// User changable pinmodes----------------------------
  //Servo Data pin setup:
  pinMode(ServoData, OUTPUT);
  //GPIO pins setup: 
  pinMode(GPIO_1, OUTPUT);
  pinMode(GPIO_2, OUTPUT);
  pinMode(GPIO_3, OUTPUT);
  pinMode(GPIO_4, OUTPUT);
//----------------------------------------------------

  Serial.begin(9600);
 
}

void loop() {
  // put your main code here, to run repeatedly:

  ch1 = pulseIn(RC_Ch1, HIGH, 30000); // Read the pulse width of 
  ch2 = pulseIn(RC_Ch2, HIGH, 30000); // each channel
  ch3 = pulseIn(RC_Ch3, HIGH, 30000); // Read the pulse width of 
  ch4 = pulseIn(RC_Ch4, HIGH, 30000); // each channel

  Serial.print("ch1: ");
  Serial.print(ch1);
  Serial.print(",  ch2: ");
  Serial.print(ch2);
  Serial.print(",  ch3: ");
  Serial.print(ch3);
  Serial.print(",  ch4: ");
  Serial.print(ch4);
  Serial.print("\n\r");


  HPWM = map(ch1, 1000, 2000, 0, 510); // 1000 & 2000, Experimental Pulse Width Values for CombatBotPCB v2040
  VPWM = map(ch2, 1000, 2000, 0, 510); //   1000 & 2000, Experimental Pulse Width Values for CombatBotPCB v2040

  RWD = VPWM - (HPWM - 255);  // Right Wheel Drive: 0-200 backwards, 200-300 Stationary, 300 - 510 forwards
  LWD = VPWM + (HPWM - 255); //   Left Wheel Drive: 0-200 backwards, 200-300 Stationary, 300 - 510 forwards
  
  //-------------------------------//
 //         Left wheel PWM
//--------------------------------//
  if (LWD >= 300) {                           // Move Fowards
    analogWrite(Motor_1A, 0);
    analogWrite(Motor_1B, int(LWD - 255));
  } else if (LWD >= 200 && LWD <= 300) {   //Stationary, apply brake
    analogWrite(Motor_1B, 1);
    analogWrite(Motor_1A, 1);
  } else {                              // Move Backwards
    analogWrite(Motor_1B, 0);
    analogWrite(Motor_1A, int(255 - LWD));
  }


  //-------------------------------//
 //        Right wheel PWM
//--------------------------------//
  if (RWD >= 300) {                         // Move Fowards
    analogWrite(Motor_2B, 0);
    analogWrite(Motor_2A, int(RWD - 255));
  } else if (RWD >= 200 && RWD <= 300) { // Stationary, apply brake
    analogWrite(Motor_2B, 1);
    analogWrite(Motor_2A, 1);
  } else {                             // Move Backwards
    analogWrite(Motor_2A, 0);
    analogWrite(Motor_2B, int(255 - RWD));
  }
  
  /*
  delay(2000);
  
  analogWrite(Motor_1A, 0);
  analogWrite(Motor_1B, 254);
  analogWrite(Motor_2A, 1);
  analogWrite(Motor_2B, 1);
  analogWrite(Motor_3A, 1);
  analogWrite(Motor_3B, 1);
  
  delay(2000);
  
  analogWrite(Motor_1A, 1);
  analogWrite(Motor_1B, 1);
  analogWrite(Motor_2A, 0);
  analogWrite(Motor_2B, 254);
  analogWrite(Motor_3A, 1);
  analogWrite(Motor_3B, 1);

  delay(2000);

  analogWrite(Motor_1A, 1);
  analogWrite(Motor_1B, 1);
  analogWrite(Motor_2A, 1);
  analogWrite(Motor_2B, 1);
  analogWrite(Motor_3A, 0);
  analogWrite(Motor_3B, 254);
  */
  
}
