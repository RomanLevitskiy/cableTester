
// include
// подключаем библиотеку LiquidCrystal_I2C
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
 
// создаем объект-экран, передаём используемый адрес 
// и разрешение экрана:
LiquidCrystal_I2C lcd(0x38, 20, 4);

// define 
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


#define CONTROLL_BUTTON 5

#define CONTACT     0
#define NO_CONTACT  1
#define TRU_VALUE   2
#define ERROR_VALUE 3
#define NUM_XS1 14
#define NUM_XS2 14
// const


// variables
char flag_error = 0;
bool flagButtonState = false;

int pinArrayXS1[] = {J_XS1, D_XS1, A_XS1, B_XS1, C_XS1, E_XS1, F_XS1, L_XS1, H_XS1, K_XS1, M_XS1, N_XS1, P_XS1, R_XS1};

int pinArrayXS2[] = {H_XS2, C_XS2, B_XS2, A_XS2, F_XS2, D_XS2, L_XS2, J_XS2, E_XS2, K_XS2, M_XS2, N_XS1, P_XS1, R_XS1};


char vJ[14] = {0};
char vD[14] = {0};
char vA[14] = {0};
char vB[14] = {0};
char vC[14] = {0};
char vE[14] = {0};
char vF[14] = {0};
char vL[14] = {0};
char vH[14] = {0};
char vK[14] = {0};
char vM[14] = {0};
char vN[14] = {0};
char vP[14] = {0};
char vR[14] = {0};
char * vistavka[14] = {vJ, vD, vA, vB, vC, vE, vF, vL, vH, vK, vM, vN, vP, vR};

char nH[14] = {0};
char nC[14] = {0};
char nB[14] = {0};
char nA[14] = {0};
char nF[14] = {0};
char nD[14] = {0};
char nL[14] = {0};
char nJ[14] = {0};
char nE[14] = {0};
char nK[14] = {0};
char nM[14] = {0};
char nN[14] = {0};
char nP[14] = {0};
char nR[14] = {0};
char * nabludatel[14] = {nH, nC, nB, nA, nF, nD, nL, nJ, nE, nK, nM, nN, nP, nR};

char t1[14] = {0};
char t2[14] = {0};
char t3[14] = {0};
char t4[14] = {0};
char t5[14] = {0};
char t6[14] = {0};
char t7[14] = {0};
char t8[14] = {0};
char t9[14] = {0};
char t10[14] = {0};
char t11[14] = {0};
char t12[14] = {0};
char t13[14] = {0};
char t14[14] = {0};
char * tester[14] = {t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14};

void initArrayVistavkaAndNabludatel()
{
  for(int i = 0; i < NUM_XS1; i++){
    for(int j = 0; j < NUM_XS2; j++){
       vistavka[i][j] = nabludatel[i][j] = 1;
    }
  }
  // xs1 J-0, D-1, A-2, B-3, C-4, E-5, F-6, L-7, H-8, K-9, M-10, N-11, P-12, R-13
  // xs2 H-0, C-1, B-2, A-3, F-4, D-5, L-6, J-7, E-8, K-9, M-10, N-11, P-12, R-13
  // set data connection for vistavka: doc РНБЦ.4042.521.0305СБ
  vistavka[2][5] = 0;//XS1:A-XS2:D; 
  vistavka[3][7] = 0;//XS1:B-XS2:J; 
  vistavka[1][3] = 0;//XS1:D-XS2:A;  
  vistavka[0][2] = 0;//XS1:J-XS2:B; 
  vistavka[4][1] = 0;//XS1:C-XS2:C; 
  vistavka[8][0] = 0;//XS1:H-XS2:H; 
  vistavka[11][11] = 0;//XS1:N-XS2:N; 
  vistavka[12][12] = 0;//XS1:P-XS2:P;    

  //set data connection for nabludatel: doc РНБЦ.4042.481.0100СБ
  nabludatel[3][5] = 0;//XS1:B - XS2:D
  nabludatel[1][2] = 0;//XS1:D - XS2:B
  nabludatel[4][1] = 0;//XS1:C - XS2:C
  nabludatel[8][0] = 0;//XS1:H - XS2:H
  nabludatel[11][11] = 0;//XS1:N - XS2:N
  nabludatel[12][12] = 0;//XS1:P - XS2:P
}

void setAllPinPullUp()
{
  // set all pin XS1 in +5
  for(int i = 0; i < NUM_XS1; i++){
    pinMode(pinArrayXS1[i], INPUT_PULLUP);
  }
  // set all pin XS2 in +5;
  for(int i = 0; i < NUM_XS2; i++){
    pinMode(pinArrayXS2[i], INPUT_PULLUP);
  }
}

void check_XS1_against_XS2()
{
  for(int i = 0; i < NUM_XS1; i++){
    setAllPinPullUp();
    pinMode(pinArrayXS1[i], OUTPUT);
    digitalWrite(pinArrayXS1[i], LOW);
    delay(1);
    for(int j = 0; j < NUM_XS2; j++){
       (digitalRead(pinArrayXS2[j])==1) ? (tester[i][j] = 1):(tester[i][j] = 0);
    }
  }
}

void checkTesterAgainstVistavka()
{
  flag_error = 0;
  for(int i = 0; i < NUM_XS1; i++){
    for(int j = 0; j < NUM_XS2; j++){
       // if value corect set tester[i][j] = 2, else set 3
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
  flag_error = 0;
  for(int i = 0; i < NUM_XS1; i++){
    for(int j = 0; j < NUM_XS2; j++){
      // if value corect set tester[i][j] = 2, else set 3
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

char ConvertorPintNumberToCharXS1(int x)
{
  //look pinArrayXS1[] = {J_XS1, D_XS1, A_XS1, B_XS1, C_XS1, E_XS1, F_XS1, L_XS1, H_XS1, K_XS1, M_XS1, N_XS1, P_XS1, R_XS1};
  switch(x){
    case 0://J_XS1:
      return 'J';
    case 1://D_XS1:
      return 'D';
    case 2://A_XS1:
      return 'A';
    case 3://B_XS1:
      return 'B';
    case 4://C_XS1:
      return 'C';
    case 5://E_XS1:
      return 'E';
    case 6://F_XS1:
      return 'F';
    case 7://_XS1:
      return 'L';
    case 8://H_XS1:
      return 'H';
    case 9://K_XS1:
      return 'K';
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

char ConvertorPintNumberToCharXS2(int x)
{
  //look pinArrayXS2[] = {H_XS2, C_XS2, B_XS2, A_XS2, F_XS2, D_XS2, L_XS2, J_XS2, E_XS2, K_XS2, M_XS2, N_XS1, P_XS1, R_XS1};
  switch(x){
    case 0://H_XS2:
      return 'H';
    case 1://C_XS2:
      return 'C';
    case 2://B_XS2:
      return 'B';
    case 3://A_XS2:
      return 'A';
    case 4://F_XS2:
      return 'F';
    case 5://D_XS2:
      return 'D';
    case 6://L_XS2:
      return 'L';
    case 7://J_XS1:
      return 'J';
    case 8://E_XS2:
      return 'E';
    case 9://K_XS2:
      return 'K';
    case 10://M_XS2:
      return 'M';
    case 11://N_XS2:
      return 'N';
    case 12://P_XS2:
      return 'P';
    case 13://R_XS2:
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
           array1[nowCursorPosition]=ConvertorPintNumberToCharXS1(i);
           array2[nowCursorPosition]=ConvertorPintNumberToCharXS2(j);
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
    // инициализируем экран
    lcd.init();
    // включаем подсветку
    lcd.backlight();
    // устанавливаем курсор в колонку 0, строку 0
    lcd.setCursor(6, 1);
    // печатаем первую строку
    lcd.print("POWER ON");
    
    initArrayVistavkaAndNabludatel();
    delay(3000);
}

void loop() {
  while(1){
    checkButtonState();
    setAllPinPullUp();
    check_XS1_against_XS2();
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
    else{// nabludatel
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
