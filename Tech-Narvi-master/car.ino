//Initialize Motor 1
int motor1Pin1 = 8;
int motor1Pin2 = 9;
int enable1Pin = 5;
 
//Initialize Motor 2
int motor2Pin1 = 10; 
int motor2Pin2 = 11; 
int enable2Pin = 6;
 
// For Ultrasonic sensor
const int trigPin = 2;
const int echoPin = 3;
 
 
int state;
void setup() {
    // sets the pins as outputs:
    
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(enable1Pin, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(enable2Pin, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
}
 
void loop() {
    //if some date is sent, reads it and saves in state
    if(Serial.available())
    {     
      state = Serial.read();
        // establish variables for duration of the ping, 
    // and the distance result in inches and centimeters:
    }
    long duration,cm;
   
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
   
    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    duration = pulseIn(echoPin, HIGH);
   
    // convert the time into a distance
    cm = microsecondsToCentimeters(duration);
    
    
    delay(100);
    // if the state is '1' the DC motor will go forward 
     
      if (state == 49) // forward
    {
        if (cm <= 20){
            analogWrite(enable1Pin, 0);
            analogWrite(enable2Pin, 0);
        }
       else if (cm > 20){        
            digitalWrite(motor1Pin1, HIGH); 
            digitalWrite(motor1Pin2, LOW);
            digitalWrite(motor2Pin1, HIGH);
            digitalWrite(motor2Pin2, LOW);
            analogWrite(enable1Pin, 180);
            analogWrite(enable2Pin, 180);
       }
 
        
        delay(300);
        Serial.println("Forward");
    }
   
    else if (state == 50)  // left
    {
      //turn left
        digitalWrite(motor1Pin1, HIGH); 
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
        analogWrite(enable1Pin, 250);
        analogWrite(enable2Pin, 250);
        
        delay(150);
        
        state = 51;
        
        
        Serial.println("left");
    }
    
    else if (state == 51) //  Stop
    {
        digitalWrite(enable1Pin, 0);
        digitalWrite(enable2Pin, 0);
        delay(300);
        Serial.println("stop");
    }
 
    else if (state == 52) // right
    {
      //TURN RIGHT
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, HIGH); 
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW);
        analogWrite(enable1Pin, 250);
        analogWrite(enable2Pin, 250);
        
        delay(150);
        
        state = 51;
        
        Serial.println("right");
      
    }
    
    else if (state == 53) //reverse
    {
        
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, HIGH); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
        analogWrite(enable1Pin, 180);
        analogWrite(enable2Pin, 180);
        delay(300);
        Serial.println("reverse");
    }
}
 
 
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}