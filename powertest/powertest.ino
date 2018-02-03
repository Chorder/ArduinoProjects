//小车前进与后退

int in1 = 2;
int in2 = 3;
int in3 = 4;
int in4 = 5;
int in5 = 6;
int in6 = 7;
int in7 = 8;
int in8 = 9;

int en1 = 10;
int en2 = 11;
int en3 = 12;
int en4 = 13;

void setup()
{   
pinMode(en1, OUTPUT); //定义PWM输出
pinMode(in1, OUTPUT);     
pinMode(in2, OUTPUT);     
pinMode(en2, OUTPUT); //定义PWM输出
pinMode(in3, OUTPUT);   
pinMode(in4, OUTPUT);  
pinMode(en3, OUTPUT); //定义PWM输出
pinMode(in5, OUTPUT);   
pinMode(in6, OUTPUT);  
pinMode(en4, OUTPUT); //定义PWM输出
pinMode(in7, OUTPUT);   
pinMode(in8, OUTPUT);  
} 
void advance()//前进
{
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
 void back()//后退
{
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
void loop() 
{
    advance();//小车前进
   delay(10000);//延迟1秒
   // back();//小车后退
   //delay(10000);//延迟1秒
}
//http://yfrobot.taobao.com/
//YFRobot配件中心
