const int frontwheel = 10; //MOSFET Gate control for front wheel
const int backwheel = 11; //MOSFET Gate control for front wheel
const int LED1 = 5;
const int LED2 = 6;
const int trigPin = 3; //Output pin for sensor
const int echoPin = 4; //Sensing pin for sensor
const int D1 = 16.5; // Distance before the motor slows down, D1 = D2+10
const int D2 = 7.5; // Distance before the motor stops
long duration;
long distance;
// Motor will stop at D1, wait till its almost 60 sec
// then run at a slower speed till it hits D2 so as to
// reach at 1 min
unsigned long t_time = 10000; // Time (in ms) to pass before it starts moving from D1 to D2
unsigned long tracked_time = 0
int LED_tracker = 0;
__attribute__((section(".noinit"))) unsigned int mode; // Mode to on and off

void setup() {
  // put your setup code here, to run once:
  pinMode(frontwheel, OUTPUT);
  pinMode(backwheel, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT); 
  Serial.begin(9600); // Starts the serial communication

  if (mode == 1){
    mode = 0;
  }else{
    mode = 1;
  }
}

void loop() {
  // To alternate between 2 different light colours
  if ((millis() - tracked_time) > 50){
    if (LED_tracker == 0){
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
    }
    if (LED_tracker == 1){
      digitalWrite(LED2, HIGH);
      digitalWrite(LED1, LOW);
    }
    if (LED_tracker == 0){
      LED_tracker = 1;
    }else{
      LED_tracker = 0;
    }
    tracked_time = millis();
  }

  if (mode == 0){
      // Clears the trigPin
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      // Calculating the distance
      distance= duration*0.034/2;
      Serial.println(distance);

      if (distance >= D1){
        analogWrite(frontwheel, 255);
        analogWrite(backwheel, 255);
      }
      
      if ((distance < D1) && (distance > D2)){
        if (millis() < t_time){
          analogWrite(frontwheel, 5);
          analogWrite(backwheel, 5);
        }else{
          analogWrite(frontwheel, 130);
          analogWrite(backwheel, 130);
        }
      }

      if (distance <= D2){
        analogWrite(frontwheel, 0);
        analogWrite(backwheel, 0);
      }
  }
}
