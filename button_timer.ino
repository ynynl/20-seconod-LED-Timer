/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;
int distance;
int state = 0;

int setting = 0;
int reset = 0;

//buttons
const int button0 = 12;    // the number of the pushbutton pin

void setup() 
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  
  // declare the LED pins as outputs
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() 
{
  setting = readButton();
  if (state != 0) 
  {
    counting(state); // read setting and counts from there
  }
  else if (setting > 2)
  {
    state = setting;
  }
}



int counting(int setting)
{
    for (int i=2; i<setting; i+=2) 
    {
      digitalWrite(i, HIGH);
    }
    
    // Count 20 seconds.
    for (int j=setting-1; j>1; j-=2) 
    {
      //blink 4 times per sec
      for (int k=0; k<4; k++) 
      {        
        reset = readButton();
        if (reset != 0)
        {
          for (int i=2; i<= setting; i+=2) //turn off and restart
              {
                digitalWrite(i, LOW);
              }
          if (reset != 0)
          {
            state = reset;
          }
          else
          {
            state = 0;
          }
          return;
        }        
        digitalWrite(j, LOW);
        delay(20);
        digitalWrite(j, HIGH);
        delay(980);
      }
      digitalWrite(j, LOW);
    }
    state = 0;
}

int readButton() 
{
  for (int h=3; h<9; h = h+2) 
  {
    if (digitalRead(h) == HIGH) 
    {  
      Serial.println(h); 
      return h;
    }
  }
  if (digitalRead(12) == HIGH)
  {
    Serial.println(-1);
    return -1;
  }
  Serial.println(0);
  return 0;
}
