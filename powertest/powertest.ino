//小车前进与后退
//时间20120902
int PWM1=11;  //ena port
int in1=7; //IN1　port 
int in2=6;  //IN2  port
int PWM2=10;  //enb port
int in3=5;  //in3 port
int in4=4; //in4 port

void setup()
{   
pinMode(PWM1, OUTPUT); //定义PWM输出
pinMode(in1, OUTPUT);     
pinMode(in2, OUTPUT);     
pinMode(PWM2, OUTPUT); //定义PWM输出
pinMode(in3, OUTPUT);   
pinMode(in4, OUTPUT);  
} 
void advance()//前进
{
  digitalWrite(PWM1,HIGH);
  digitalWrite(PWM2,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}
 void back()//后退
{
  digitalWrite(PWM1,HIGH);
  digitalWrite(PWM2,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
void loop() 
{
    advance();//小车前进
   delay(10000);//延迟1秒
    back();//小车后退
   delay(10000);//延迟1秒
}
//http://yfrobot.taobao.com/
//YFRobot配件中心
