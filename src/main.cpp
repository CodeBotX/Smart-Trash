#include <Servo.h>  
Servo servo;     
int trig_1_Pin = 5 ;    // Chân Trig của cảm biến siêu âm
int echo_1_Pin = 6 ;   //Chân Echo của cảm biến siêu âm


int trig_2_Pin = 3 ;    // Chân Trig của cảm biến siêu âm
int echo_2_Pin = 4 ;   //Chân Echo của cảm biến siêu âm

int servo_Pin = 10  ; //Chân tín hiệu của Servo
int speaker_Pin = 9 ; //Chân tín hiệu của Speaker

long  duration, 
      dist,
      height_inside,
      verage;   
long aver[3];  
void setup() 
{           
  servo.attach(servo_Pin);    
  pinMode(trig_1_Pin, OUTPUT);  //Chân phát tín hiệu  p
  pinMode(echo_1_Pin, INPUT);  //Chân nhận tín hiệu   P
  pinMode(trig_2_Pin, OUTPUT);  //Chân phát tín hiệu Sp   
  pinMode(echo_2_Pin, INPUT);  //Chân nhận tín hiệu   Sp
  pinMode(speaker_Pin, OUTPUT); 

  servo.write(0);         //Góc về của Servo    
  delay(100);            //  Thời gian đo khoảng cách
   servo.detach(); 
   Serial.begin(9600);
}
void measure() 
{  
    unsigned long duration; // biến đo thời gian
    int distance;           // biến lưu khoảng cách
    
    /* Phát xung từ chân trig */
    digitalWrite(trig_1_Pin,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig_1_Pin,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig_1_Pin,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration = pulseIn(echo_1_Pin,HIGH);  
    // Tính khoảng cách đến vật.
    distance = int(duration/2/29.412);
    /* In kết quả ra Serial Monitor */
    Serial.print("Sensor 1: ");
    Serial.print(distance);
    Serial.println("cm");
    dist = distance;
    
    /* Phát xung từ chân trig */
    digitalWrite(trig_2_Pin,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig_2_Pin,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig_2_Pin,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration = pulseIn(echo_2_Pin,HIGH);  
    // Tính khoảng cách đến vật.
    distance = int(duration/2/29.412);
    /* In kết quả ra Serial Monitor */
    Serial.print("Sensor 2: ");
    Serial.print(distance);
    Serial.println("cm");
    height_inside = distance;

}
void loop() 
{ 
  dist = 0;
    //average distance
        measure();       
  if ( dist < 30 ) 
  {   //Khoảng cách đến vật thể để kích hoạt mở nắp
    servo.attach(servo_Pin); 
    delay(1);
    servo.write(100);  //Góc mở của Servo
    delay(3000);      //Thời gian dừng lại khi mở nắp
    servo.write(0);    //Góc đóng của Servo 
    delay(300);
    servo.detach();      
  }
  delay(100);
  //average distance
      measure();      
  if ( height_inside < 10 ) 
  {   //Khoảng cách đến vật thể để kích hoạt mở nắp
    digitalWrite(speaker_Pin, HIGH);
    delay(100);
    digitalWrite(speaker_Pin, LOW);
    delay(100);
  }

}