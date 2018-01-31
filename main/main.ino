#include <PS2X_lib.h>

#define PS2_CMD        A0
#define PS2_DAT        A1
#define PS2_SEL        A2
#define PS2_CLK        A3


int la_h = 0;
int la_l = 1;
int ra_h = 2;
int ra_l = 3;
int lb_h = 4;
int lb_l = 5;
int rb_h = 6;
int rb_l = 7;

int pla = 8;
int pra = 9;
int plb = 10;
int prb = 11;


/******************************************************************
   select modes of PS2 controller:
     - pressures = analog reading of push-butttons
     - rumble    = motor rumbling
   uncomment 1 of the lines for each mode selection
 ******************************************************************/
//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

PS2X ps2x; // create PS2 Controller Class

int error = 0;
byte type = 0;
byte vibrate = 0;

// Reset func
void (* resetFunc) (void) = 0;

void setup() {

  //设置电机驱动
  pinMode(la_h, OUTPUT);
  pinMode(la_l, OUTPUT);
  pinMode(ra_h, OUTPUT);
  pinMode(ra_l, OUTPUT);
  pinMode(lb_h, OUTPUT);
  pinMode(lb_l, OUTPUT);
  pinMode(rb_h, OUTPUT);
  pinMode(rb_l, OUTPUT);

  //串口监听 波特率115200
  Serial.begin(115200);

  delay(500);  //added delay to give wireless ps2 module some time to startup, before configuring it
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  if (error == 0) {
    Serial.print("发现控制器，控制器连接成功！\n");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");

    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
  }

  else if (error == 1)
    Serial.println("未扫描到控制器\n");

  else if (error == 2)
    Serial.println("捕捉到控制器，但控制器似乎并不接受我们的输入，请检查接线情况\n");

  else if (error == 3)
    Serial.println("控制器拒绝连接，或是不支持当前设备\n ");

  type = ps2x.readType();

  switch (type) {
    case 0:
      Serial.println("未知的控制器类型\n");
      break;
    case 1:
      Serial.println("发现手柄控制器\n");
      break;
    case 2:
      Serial.println("发现吉他英雄控制器(与本项目无关)\n");
      break;
    case 3:
      Serial.println("发现山寨索尼手柄控制器\n");
      break;
  }
}


//匀速前进
void advance() {
  digitalWrite(pla, HIGH);
  digitalWrite(pra, HIGH);
  digitalWrite(plb, HIGH);
  digitalWrite(prb, HIGH);

  digitalWrite(la_h, HIGH);
  digitalWrite(ra_h, HIGH);
  digitalWrite(lb_h, HIGH);
  digitalWrite(rb_h, HIGH);
  
  digitalWrite(la_l, LOW);
  digitalWrite(ra_l, LOW);
  digitalWrite(lb_l, LOW);
  digitalWrite(rb_l, LOW);

}
//匀速后退
void back() {
  digitalWrite(pla, HIGH);
  digitalWrite(pra, HIGH);
  digitalWrite(plb, HIGH);
  digitalWrite(pra, HIGH);

  digitalWrite(la_h, LOW);
  digitalWrite(ra_h, LOW);
  digitalWrite(lb_h, LOW);
  digitalWrite(rb_h, LOW);

  digitalWrite(la_l, HIGH);
  digitalWrite(ra_l, HIGH);
  digitalWrite(lb_l, HIGH);
  digitalWrite(rb_l, HIGH);
}

//停车
void stop() {
  digitalWrite(pla, LOW);
  digitalWrite(pra, LOW);
  digitalWrite(plb, LOW);
  digitalWrite(prb, LOW);
}


void loop() {
  if (error == 1) { //skip loop if no controller found
    resetFunc();
  }

  if (type == 2) { //Guitar Hero Controller
    Serial.println("你接入了吉他英雄控制器(与本项目无关)\n");
  } else { //手柄控制器

    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed

    if (ps2x.Button(PSB_START))        //will be TRUE as long as button is pressed
      Serial.println("START键被按下\n");

    if (ps2x.Button(PSB_SELECT))
      Serial.println("SELECT键被按下\n");

    if (ps2x.Button(PSB_PAD_UP)) {     //will be TRUE as long as button is pressed

      Serial.print("前进键被按下\n");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      advance();

    }
    if (ps2x.Button(PSB_PAD_RIGHT)) {
      Serial.print("右转键被按下\n");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
    if (ps2x.Button(PSB_PAD_LEFT)) {
      Serial.print("左转键被按下\n");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }
    if (ps2x.Button(PSB_PAD_DOWN)) {
      Serial.print("后退键被按下\n");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      back();
    }

    vibrate = ps2x.Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button

    if (ps2x.NewButtonState()) {        //will be TRUE if any button changes state (on to off, or off to on)
      if (ps2x.Button(PSB_L3))
        Serial.println("L3键被按下\n");
      if (ps2x.Button(PSB_R3))
        Serial.println("R3键被按下\n");
      if (ps2x.Button(PSB_L2))
        Serial.println("L2键被按下\n");
      if (ps2x.Button(PSB_R2)) { //停车
        Serial.println("R2键被按下\n");
        stop();
      }

      if (ps2x.Button(PSB_TRIANGLE))
        Serial.println("三角形键被按下\n");
    }

    if (ps2x.ButtonPressed(PSB_CIRCLE)) {   //will be TRUE if button was JUST pressed
      advance();
      Serial.println("圆圈键被按下\n");
    }


    if (ps2x.NewButtonState(PSB_CROSS))              //will be TRUE if button was JUST pressed OR released
      Serial.println("X键状态改变\n");
    if (ps2x.ButtonReleased(PSB_SQUARE))             //will be TRUE if button was JUST released
      Serial.println("方形键被放开\n");

    if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) { //print stick values if either is TRUE
      Serial.print("接收到动作元数据\n");
      Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC);
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC);
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC);
    }
  }
  delay(50);
}

