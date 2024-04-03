int currentLED = 0;
int numOfLEDs = 9;
int ledPins[]= {13,12,11,10,9,8,7,6,5};
unsigned long time = 0;

//We are jusing lastJump here since sometimes the arduino might not execute exacty when it is %intervals == 0
unsigned long interval =600;
unsigned long lastTime = 0;

int win=0;

#define UP 1
#define DOWN 0

int direction = DOWN;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //Red
  //2 yellow
  //Green
  //Blue
  //Green
  //2Yellow
  //Red
  //Sets them to output
  for(int i = 0;i<9;i++){
    pinMode(ledPins[i],OUTPUT);
    // digitalWrite(ledPins[i],HIGH);
    // Serial.println(i);
  }

  //Then there's the button
  pinMode(2,INPUT);
}

//Lights moving from up to Down
void moveDown(){
  //Turns on currentLED and turns off the one before it
  digitalWrite(ledPins[currentLED],HIGH);
  
  //Turns off previous lights
  if(currentLED != 0){
    digitalWrite(ledPins[currentLED-1],LOW);
    Serial.print(currentLED);
    Serial.println(" TURN OFF MOVEDOWN");

  }
  else{
    digitalWrite(ledPins[currentLED+1],LOW);
  }

  //4th LED leads to the win, so mark it as winnable.(currentLED will no longer be 4 so we need to save that this is a win)
  if(currentLED == 4){
    win = 1;
  }
  else
    win = 0;

  currentLED++;

  // Serial.print(currentLED);
  // Serial.println("movingDown");

  
  //If last LED change direction of light movement
  if(currentLED == numOfLEDs-1){
    direction = UP;
  }
}

//Lights moving from Down to Up
void moveUp(){
  //Turns on currentLED and turns off the one before it
  digitalWrite(ledPins[currentLED],HIGH);
  
  //Turns off previous light
  if(currentLED != numOfLEDs-1){
    digitalWrite(ledPins[currentLED+1],LOW);
    Serial.print(currentLED);
    Serial.println("TURN OFF MOVEUP");
  }
  else
  {
    digitalWrite(ledPins[currentLED-1],LOW);
  }
  //4th LED leads to the win, so mark it as winnable.(currentLED will no longer be 4 so we need to save that this is a win)
  if(currentLED == 4){
    win = 1;
  }
  else
    win = 0;
    
  currentLED--;
  
  // Serial.print(currentLED);
  // Serial.println(" movingUP");

  //If last LED change direction of light movement
  if(currentLED == 0){
    direction = DOWN;
  }
}

void victoryAnimation(){
  //Animation of lights extending from center
  for(int i = 0;i<numOfLEDs;i++){
      digitalWrite(ledPins[currentLED+i],HIGH);
      digitalWrite(ledPins[currentLED-i],HIGH);
      delay(70);
  }
  delay(100);
}

//Turns off all lights and resets direction
void restart(){
  for(int i = 0;i<numOfLEDs;i++){
    digitalWrite(ledPins[i],LOW);
    delay(30);
  }
  direction = DOWN;
  currentLED = 0;
}

//Increases difficulty by reducing interval
void increaseDifficulty(){
  if(interval>300){
    interval -= 100;
  }
  else
  if(interval>100){
    interval -= 50;
  }
  else
  {
    interval -=15;
  }
}
void loop() {
  unsigned long currTime = millis();
  //Move Up Down every duration seconds;
  if(currTime - lastTime>= interval){
    lastTime = currTime;
    // Serial.println(currTime);
    if(direction == UP){
      moveUp();
    }
    else
    if(direction == DOWN){
      moveDown();
    }
  }

  //If clicked when on blue (pin 8) win, otherwise lose. Different animations for win/loss
  if(digitalRead(2)){

    //If won (assuming winning LED is the 5th)
    if(currentLED>=3 && currentLED<=5 && win){
      //Set direction to not UP/DOWN so that it stops the movingup and down
      direction = 70;
      victoryAnimation();
      Serial.print("Difficulty: ");
      Serial.println(interval);
      //Increase interval speed
      increaseDifficulty();
      //Restaerts
    }
    delay(100);
      restart();
    // Serial.print(clicked);
  }
}
