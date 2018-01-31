
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

void setup(){   
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

void advance(){
  int i = 0;
  for(i=0;i<255;i++){
    analogWrite(en1,i);
    analogWrite(en2,i);
    analogWrite(en3,i);
    analogWrite(en4,i);
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    digitalWrite(in5,HIGH);
    digitalWrite(in6,LOW);
    digitalWrite(in7,HIGH);
    digitalWrite(in8,LOW);
    delay(5);
  }
}
 void back(){
    int i = 0;
    for(i=0;i<255;i++){
      analogWrite(en1,i);
      analogWrite(en2,i);
      analogWrite(en3,i);
      analogWrite(en4,i);
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      digitalWrite(in5,LOW);
      digitalWrite(in6,HIGH);
      digitalWrite(in7,LOW);
      digitalWrite(in8,HIGH);
      delay(5);
    }
}
void loop() 
{
    advance();//小车匀加速前进
   delay(1000);//延迟1秒
    //back();//小车匀加速后退
   //delay(1000);//延迟1秒
}
//http://yfrobot.taobao.com/
//YFRobot配件中心
