
// include
// подключаем библиотеку LiquidCrystal_I2C
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
 
// создаем объект-экран, передаём используемый адрес 
// и разрешение экрана:
LiquidCrystal_I2C lcd(0x38, 20, 4);

// define nicname for pins
// XS1
#define J_XS1 26
#define D_XS1 27
#define A_XS1 28
#define B_XS1 29
#define C_XS1 30
#define E_XS1 31
#define F_XS1 32
#define L_XS1 33
#define H_XS1 34
#define K_XS1 35
#define M_XS1 36
#define N_XS1 37
#define P_XS1 38
#define R_XS1 39
// XS2
#define H_XS2 40
#define C_XS2 41
#define B_XS2 42
#define A_XS2 43
#define F_XS2 44
#define D_XS2 45
#define L_XS2 46
#define J_XS2 47
#define E_XS2 48
#define K_XS2 49
#define M_XS2 50
#define N_XS2 51
#define P_XS2 52
#define R_XS2 53

//CHAR-NUM
#define A_CHAR 0
#define B_CHAR 1
#define C_CHAR 2
#define D_CHAR 3
#define E_CHAR 4
#define F_CHAR 5
#define H_CHAR 6
#define J_CHAR 7
#define K_CHAR 8
#define L_CHAR 9
#define M_CHAR 10
#define N_CHAR 11
#define P_CHAR 12
#define R_CHAR 13


#define CONTROLL_BUTTON 5

#define TRU_VALUE   2
#define ERROR_VALUE 3
#define NUM_XS1 14 // num pin of xs1
#define NUM_XS2 14
// const


// global variables
char flag_error = 0;
bool flagButtonState = false;

char pinArrayXS1[] = {A_XS1, B_XS1, C_XS1, D_XS1, E_XS1, F_XS1, H_XS1, J_XS1, K_XS1, L_XS1, M_XS1, N_XS1, P_XS1, R_XS1}; // array pin on xs1
char pinArrayXS2[] = {A_XS2, B_XS2, C_XS2, D_XS2, E_XS2, F_XS2, H_XS2, J_XS2, K_XS2, L_XS2, M_XS2, N_XS2, P_XS2, R_XS2}; // array pin on xs2

char vistavka[NUM_XS1][NUM_XS2];

char nabludatel[NUM_XS1][NUM_XS2];

char oneToOne[NUM_XS1][NUM_XS2];

char tester[NUM_XS1][NUM_XS2];


void initArrayVistavkaAndNabludatel()
{
  for(int i = 0; i < NUM_XS1; i++){
    for(int j = 0; j < NUM_XS2; j++){
       vistavka[i][j] = '1';
       nabludatel[i][j] = '1';
       oneToOne[i][j] = '1';
    }
  }
  // xs1 J-0, D-1, A-2, B-3, C-4, E-5, F-6, L-7, H-8, K-9, M-10, N-11, P-12, R-13
  // xs2 H-0, C-1, B-2, A-3, F-4, D-5, L-6, J-7, E-8, K-9, M-10, N-11, P-12, R-13
  // set data connection for vistavka: doc РНБЦ.4042.521.0305СБ - VISTAVKA
  vistavka[A_CHAR][D_CHAR] = '0';//XS1:A-XS2:D; 
  vistavka[B_CHAR][J_CHAR] = '0';//XS1:B-XS2:J; 
  vistavka[D_CHAR][A_CHAR] = '0';//XS1:D-XS2:A;  
  vistavka[J_CHAR][B_CHAR] = '0';//XS1:J-XS2:B; 
  vistavka[C_CHAR][C_CHAR] = '0';//XS1:C-XS2:C; 
  vistavka[H_CHAR][H_CHAR] = '0';//XS1:H-XS2:H; 
  vistavka[N_CHAR][N_CHAR] = '0';//XS1:N-XS2:N; 
  vistavka[P_CHAR][P_CHAR] = '0';//XS1:P-XS2:P;    
 
  //set data connection for nabludatel: doc РНБЦ.4042.481.0100СБ - NABLUDATEL'
  nabludatel[B_CHAR][D_CHAR] = '0';//XS1:B - XS2:D
  nabludatel[D_CHAR][B_CHAR] = '0';//XS1:D - XS2:B
  nabludatel[C_CHAR][C_CHAR] = '0';//XS1:C - XS2:C
  nabludatel[H_CHAR][H_CHAR] = '0';//XS1:H - XS2:H
  nabludatel[N_CHAR][N_CHAR] = '0';//XS1:N - XS2:N
  nabludatel[P_CHAR][P_CHAR] = '0';//XS1:P - XS2:P

  //set data connection for one to one cable 
  oneToOne[A_CHAR][A_CHAR] = 0;//XS1:A - XS2:A
  oneToOne[A_CHAR][A_CHAR] = 0;//XS1:B - XS2:B
  oneToOne[A_CHAR][A_CHAR] = 0;//XS1:C - XS2:C
  oneToOne[1][5] = 0;//XS1:D - XS2:D
  oneToOne[5][8] = 0;//XS1:E - XS2:E
  oneToOne[6][4] = 0;//XS1:F - XS2:F
  oneToOne[8][0] = 0;//XS1:H - XS2:H
  oneToOne[0][7] = 0;//XS1:J - XS2:J
  oneToOne[9][9] = 0;//XS1:K - XS2:K
  oneToOne[7][6] = 0;//XS1:L - XS2:L
  oneToOne[10][10] = 0;//XS1:M - XS2:M
  oneToOne[11][11] = 0;//XS1:N - XS2:N
  oneToOne[12][12] = 0;//XS1:P - XS2:P
  oneToOne[13][13] = 0;//XS1:R - XS2:R
}

void setAllPinPullUp()
{
  // set all pin XS1 in +5v
  for(int n = 0; n < NUM_XS1; n++){
    pinMode(pinArrayXS1[n], INPUT_PULLUP);
  }
  // set all pin XS2 in +5v
  for(int n = 0; n < NUM_XS2; n++){
    pinMode(pinArrayXS2[n], INPUT_PULLUP);
  }
}

void check_XS1_against_XS2()
{
  setAllPinPullUp();
  for(int i = 0; i < NUM_XS1; i++){
    for(int j = 0; j < NUM_XS2; j++){
      tester[i][j]='1';
    }
  }
  for(int i = 0; i < NUM_XS1; i++){
    pinMode(pinArrayXS1[i], OUTPUT);
    digitalWrite(pinArrayXS1[i], LOW);
    delay(2);// delay for mutable state pin, 1 ms
    for(int j = 0; j < NUM_XS2; j++){
       (digitalRead(pinArrayXS2[j])==1) ? (tester[i][j] = '1'):(tester[i][j] = '0');
    }
    pinMode(pinArrayXS1[i], INPUT_PULLUP);
  }
}


void printTesterArray()
{
  for(int i = 0; i < NUM_XS1; i++){
    Serial.print("-------------------------------------------");
    Serial.print('\n');
    Serial.print(ConvertorPintNumberToCharXS(i));
    Serial.print("| ");
    for(int j = 0; j < NUM_XS2; j++){
      Serial.print(ConvertorPintNumberToCharXS(j));
      Serial.print("-");
      //Serial.print(oneToOne[i][j]);
      if(tester[i][j]=='1'){
        Serial.print('1');
      }
      else{
        Serial.print('0');
      }
      Serial.print('\t');   
    }
    Serial.print('\n');
    Serial.print("-------------------------------------------");
    Serial.print('\n');
    Serial.print('\n');
    Serial.print('\n');
  }
}



void checkTesterAgainstVistavka()
{
  // need add reverse check cable for absolut toleranse in time check
  // create temp table i, j and write revers value array tester
  flag_error = 0;
  for(int i = 0; i < NUM_XS1; i++){
    for(int j = 0; j < NUM_XS2; j++){
       // if value corect set tester[i][j] = TRU_VALUE, else set ERROR_VALUE
       if(tester[i][j] == vistavka[i][j]){
        tester[i][j] = TRU_VALUE;
       }
       else{
        tester[i][j] = ERROR_VALUE;
        flag_error = 1;
       }
    }
  }
}


void checkTesterAgainstNabludatel()
{
  // need add reverse check cable for absolut toleranse in time check
  // create temp table i, j and write revers value array tester
  flag_error = 0;
  for(int i = 0; i < NUM_XS1; i++){
    for(int j = 0; j < NUM_XS2; j++){
      // if value corect set tester[i][j] = TRU_VALUE, else set ERROR_VALUE
       if(tester[i][j] == nabludatel[i][j]){
        tester[i][j] = TRU_VALUE;
       }
       else{
        tester[i][j] = ERROR_VALUE;
        flag_error = 1;
       }
    }
  }
}

void checkTesterAgainstOneToOne()
{
  // need add reverse check cable for absolut toleranse in time check
  // create temp table i, j and write revers value array tester
  flag_error = 0;
  for(int i = 0; i < NUM_XS1; i++){
    for(int j = 0; j < NUM_XS2; j++){
      // if value corect set tester[i][j] = TRU_VALUE, else set ERROR_VALUE
       if(tester[i][j] == oneToOne[i][j]){
        tester[i][j] = TRU_VALUE;
       }
       else{
        tester[i][j] = ERROR_VALUE;
        flag_error = 1;
       }
    }
  }
}

void checkButtonState()
{
  int counter = 0;
  static int buttonState = 0;
  for(int i = 0; i < 30; i++){
    delay(10);
    if(digitalRead(CONTROLL_BUTTON)== 0){
      counter++;
    }
  }
  if((counter >= 30)&&(buttonState != 1)){
    flagButtonState = !flagButtonState;
    buttonState = 1;
    
  }
  else{
    buttonState = 0;
  }
  
}

char ConvertorPintNumberToCharXS(int x)
{
  //look pinArrayXS1[] = {A_XS1, B_XS1, C_XS1, D_XS1, E_XS1, F_XS1, H_XS1, J_XS1, K_XS1, L_XS1, M_XS1, N_XS1, P_XS1, R_XS1}; 
  switch(x){
    case 0://J_XS1:
      return 'A';
    case 1://D_XS1:
      return 'B';
    case 2://A_XS1:
      return 'C';
    case 3://B_XS1:
      return 'D';
    case 4://C_XS1:
      return 'E';
    case 5://E_XS1:
      return 'F';
    case 6://F_XS1:
      return 'H';
    case 7://_XS1:
      return 'J';
    case 8://H_XS1:
      return 'K';
    case 9://K_XS1:
      return 'L';
    case 10://M_XS1:
      return 'M';
    case 11://N_XS1:
      return 'N';
    case 12://P_XS1:
      return 'P';
    case 13://R_XS1:
      return 'R';
    default:
      return '?';
  }
}

void printErrorPins()
{
  char array1[20]={' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
  char array2[20]={' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
  
  array1[0]='x';
  array1[1]='s';
  array1[2]='1';
  array2[0]='x';
  array2[1]='s';
  array2[2]='2';
  int nowCursorPosition = 4;
  const int maxPrintPairErrorPin = 7;// two char in line for one error 
  int counterPrintError = 0;
  
  for(int i = 0; i < NUM_XS1; i++){
    for(int j = 0; j < NUM_XS2; j++){
       if(tester[i][j] == ERROR_VALUE){
           array1[nowCursorPosition]=ConvertorPintNumberToCharXS(i);
           array2[nowCursorPosition]=ConvertorPintNumberToCharXS(j);
           nowCursorPosition++;
           array1[nowCursorPosition]=' ';
           array2[nowCursorPosition]=' ';
           nowCursorPosition++;
           counterPrintError++;
           if(counterPrintError >= maxPrintPairErrorPin){
            lcd.setCursor(0, 2);// print
            lcd.print(array1);
            lcd.setCursor(0, 3);// print
            lcd.print(array2);
            return;
           }
       }
    }
  }
  lcd.setCursor(0, 2);// print
  lcd.print(array1);
  lcd.setCursor(0, 3);// print
  lcd.print(array2);
  return;
}

void setup() {
    pinMode(CONTROLL_BUTTON, INPUT_PULLUP);
    setAllPinPullUp();
    // инициализируем экран
    lcd.init();
    lcd.backlight();
    lcd.setCursor(6, 1);
    lcd.print("POWER ON");
    lcd.command(0b101000);// zero page lcd
    delay(1000);
    initArrayVistavkaAndNabludatel();
    delay(1000);
    //Serial.begin(9600);
}

void loop() {
  while(1){
    checkButtonState();
    //setAllPinPullUp();
    check_XS1_against_XS2();
    //printTesterArray();
    /*
    // test
    if((flagButtonState == true)||(flagButtonState == false)){ //vistavka
      checkTesterAgainstOneToOne();
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("TEST ONE-TO-ONE");
      if(flag_error == 0){
        lcd.setCursor(0, 1);
        lcd.print("CORECT CONNECT");
      }
      else{
        lcd.setCursor(0, 1);
        lcd.print("ERROR PINS:");
        printErrorPins();
      }
    }
    */
    
    // vistavka
    if(flagButtonState == true){ //vistavka
      checkTesterAgainstVistavka();
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("VISTAVKA");
      if(flag_error == 0){
        lcd.setCursor(0, 1);
        lcd.print("CORECT CONNECT");
      }
      else{
        lcd.setCursor(0, 1);
        lcd.print("ERROR PINS:");
        printErrorPins();
      }
    }
    // nabludatel
    else{
      checkTesterAgainstNabludatel();
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("NABLUDATEL'");
      if(flag_error == 0){
        lcd.setCursor(0, 1);
        lcd.print("CORECT CONNECT");
      }
      else{
        lcd.setCursor(0, 1);
        lcd.print("ERROR PINS:");
        printErrorPins();
      }
      
    }
    
    delay(1000);
  }

}
      }
    }
    // nabludatel
    else{
      checkTesterAgainstNabludatel();
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("NABLUDATEL'");
      if(flag_error == 0){
        lcd.setCursor(0, 1);
        lcd.print("CORECT CONNECT");
      }
      else{
        lcd.setCursor(0, 1);
        lcd.print("ERROR PINS:");
        printErrorPins();
      }
      
    }
    
    delay(1000);
  }

}
