int redPin = 23;
int yellowPin = 22;
int greenPin = 21;
int btnPin = 18;

int state = 1;      
long timer = 0;      

volatile int count = 0;            
volatile long lastPress = 0;       
volatile bool redIsOn = false;     
volatile bool printCount = false;  

void IRAM_ATTR buttonISR() {
  if (redIsOn == true) {
    return; 
  }

  long now = millis();
  if (now - lastPress > 250) { 
    if (digitalRead(btnPin) == HIGH) { 
      count++;
      lastPress = now;
      printCount = true; 
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(btnPin, INPUT); 
  
  attachInterrupt(digitalPinToInterrupt(btnPin), buttonISR, RISING);

  digitalWrite(greenPin, HIGH);
  Serial.println("Current system status: Green");
  timer = millis();
}

void loop() {
  long currentTime = millis();

  if (printCount == true) {
    Serial.print("Number of button presses: ");
    Serial.println(count);
    printCount = false;
  }

  switch (state) {
    case 1: 
      if (currentTime - timer >= 10000) { 
        digitalWrite(greenPin, LOW);
        
        if (count >= 3) {
          
          digitalWrite(redPin, HIGH);
          redIsOn = true;
          Serial.println("Direct Jump: Green -> Red (Pedestrian Mode)");
          state = 4;
          count = 0; 
        } else {
        
          digitalWrite(yellowPin, HIGH);
          Serial.println("Normal Transition: Green -> Yellow");
          state = 2;
        }
        timer = currentTime;
      }
      break;

    case 2: 
      if (currentTime - timer >= 3000) { 
        digitalWrite(yellowPin, LOW);
        digitalWrite(redPin, HIGH);
        redIsOn = true;
        Serial.println("Current system status: Red (Normal)");
        state = 3; 
        count = 0; 
        timer = currentTime;
      }
      break;

    case 3: 
      if (currentTime - timer >= 10000) { 
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, HIGH);
        Serial.println("Current system status: Green");
        redIsOn = false; 
        state = 1;
        timer = currentTime;
      }
      break;

    case 4: 
      if (currentTime - timer >= 8000) { 
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, HIGH);
        Serial.println("Current system status: Green");
        redIsOn = false; 
        state = 1;
        timer = currentTime;
      }
      break;
  }
}