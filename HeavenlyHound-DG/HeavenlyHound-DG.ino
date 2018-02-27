/*
 *天狗号 遥控车 
 * DG专版
 * Chorder 2018/02/09
 */

#include <PS2X_lib.h>

#define PS2_DAT   A0
#define PS2_CMD   A1
#define PS2_SEL   A2
#define PS2_CLK   A3

int en1 = 2;
int en2 = 3;
int en3 = 4;
int en4 = 5;

int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int in5 = 10;
int in6 = 11;
int in7 = 12;
int in8 = 13;




/******************************************************************
   select modes of PS2 controller:
     - pressures = analog reading of push-butttons
     - rumble    = motor rumbling
   uncomment 1 of the lines for each mode selection
 ******************************************************************/
//#define pressures   true
//#define rumble      true
#define pressures   false
#define rumble      false

PS2X ps2x; //create PS2 Controller Class

int error = 0;
byte type = 0;
byte vibrate = 0;

// Reset func
void (* resetFunc) (void) = 0;

void setup(){

  //设置电机驱动
  pinMode(en1, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(en3, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(en4, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);

  Serial.begin(115200); //串口监听 波特率115200

  delay(5);  //等待控制器连接
  
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  if (error == 0)      Serial.print("控制器连接成功！\n");
  else if (error == 1) Serial.println("正在搜寻控制器...\n");
  else if (error == 2) Serial.println("检测到控制器，但控制器并不接受输入，请检查接线情况\n");
  else if (error == 3) Serial.println("控制器拒绝连接，或是不支持当前设备\n ");

  type = ps2x.readType();

  switch (type){
    case 0:
      Serial.println("未知的控制器类型\n");
      break;
    case 1:
      Serial.println("检测到手柄控制器\n");
      break;
  }
} //end setup

//匀速前进
void forward(){
  digitalWrite(en1,HIGH);
  digitalWrite(en2,HIGH);
  digitalWrite(en3,HIGH);
  digitalWrite(en4,HIGH); 
  
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  digitalWrite(in5,HIGH);
  digitalWrite(in6,LOW);
  digitalWrite(in7,HIGH);
  digitalWrite(in8,LOW);
}
//匀速后退
void back() {
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(en3, HIGH);
  digitalWrite(en4, HIGH);

  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in7, LOW);

  digitalWrite(in2, HIGH);
  digitalWrite(in4, HIGH);
  digitalWrite(in6, HIGH);
  digitalWrite(in8, HIGH);
}

void left(){
  digitalWrite(en1,HIGH);
  digitalWrite(en2,HIGH);
  digitalWrite(en3,HIGH);
  digitalWrite(en4,HIGH); 
  
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  digitalWrite(in5,HIGH);
  digitalWrite(in6,LOW);
  digitalWrite(in7,LOW);
  digitalWrite(in8,HIGH);
}

void right(){
  digitalWrite(en1,HIGH);
  digitalWrite(en2,HIGH);
  digitalWrite(en3,HIGH);
  digitalWrite(en4,HIGH); 
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  digitalWrite(in5,LOW);
  digitalWrite(in6,HIGH);
  digitalWrite(in7,HIGH);
  digitalWrite(in8,LOW);
}


void accelerate(){
  int i = 0;
  for(i=0;i<i+1;i++){
    analogWrite(en1,i);
    analogWrite(en2,i);
    analogWrite(en3,i);
    analogWrite(en4,i);
  }
}

//急刹车
void stop_fast() {
  digitalWrite(en1, LOW);
  digitalWrite(en2, LOW);
  digitalWrite(en3, LOW);
  digitalWrite(en4, LOW);
}

//缓慢减速
void stop_slow(){
  int i = 255;
  for(i=255;i<0;i++){
    analogWrite(en1,i);
    analogWrite(en2,i);
    analogWrite(en3,i);
    analogWrite(en4,i);
  }
}


void loop() {
  if (error == 1) { //skip loop if no controller found
    resetFunc();
  }

  ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed

  if (ps2x.Button(PSB_START))        //will be TRUE as long as button is pressed
    Serial.println("START键被按下\n");

  if (ps2x.Button(PSB_SELECT))
    Serial.println("SELECT键被按下\n");

  if (ps2x.Button(PSB_PAD_UP)) {     //will be TRUE as long as button is pressed
    Serial.print("前进\n");
    Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    forward();
  }
  
  if (ps2x.Button(PSB_PAD_RIGHT)) {
    Serial.print("右转\n");
    Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    right();
  }
  
  if (ps2x.Button(PSB_PAD_LEFT)) {
    Serial.print("左转\n");
    Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    left();
  }
  
  if (ps2x.Button(PSB_PAD_DOWN)) {
    Serial.print("后退\n");
    Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    back();
  }

  vibrate = ps2x.Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button

  if (ps2x.NewButtonState()) {        //will be TRUE if any button changes state (on to off, or off to on)
    if (ps2x.Button(PSB_L3))
      Serial.println("L3键被按下\n");
      
    if (ps2x.Button(PSB_R3))
      Serial.println("R3键被按下\n");
      
    if (ps2x.Button(PSB_L2)){
      Serial.println("L2键被按下\n"); 
      stop_slow();
    }
    if (ps2x.Button(PSB_R2)) { //停车
      Serial.println("R2键被按下\n");
      stop_fast();
    }

    if (ps2x.Button(PSB_TRIANGLE))
      Serial.println("三角形键被按下\n");
      
  }

  if (ps2x.ButtonPressed(PSB_CIRCLE)) {   //will be TRUE if button was JUST pressed
    forward();
    Serial.println("圆圈键被按下\n");
  }


  if (ps2x.NewButtonState(PSB_CROSS))              //will be TRUE if button was JUST pressed OR released
    Serial.println("X键状态改变\n");
    
  if (ps2x.ButtonReleased(PSB_SQUARE))             //will be TRUE if button was JUST released
    Serial.println("方形键被放开\n");

  if (ps2x.Button(PSB_L1)) { //加速前进
    Serial.print("接收到动作元数据\n");
    Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_LX), DEC);
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_RY), DEC);
    Serial.print(",");
    Serial.println(ps2x.Analog(PSS_RX), DEC);
    Serial.print((ps2x.Analog(PSS_LY),DEC)+(ps2x.Analog(PSS_LX), DEC)+(ps2x.Analog(PSS_RY), DEC)+(ps2x.Analog(PSS_RX), DEC));
    //accelerate();
  }

//  if (ps2x.Button(PSB_R1)){ //加速
//    int i = 0;
//    for(i=0;i<i+1;i++){
//      analogWrite(en1,i);
//      analogWrite(en2,i);
//      analogWrite(en3,i);
//      analogWrite(en4,i);
//    }
//  }

  delay(50);
}
