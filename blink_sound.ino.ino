
#include "Volume.h" // Include the Volume library

Volume vol; // Plug your speaker into the default pin for your board type which is D5:
// https://github.com/connornishijima/arduino-volume1#supported-pins

// Declares the pins for the buzzer, button, LED and
// the potentiometer. Make sure it matches with 
int beeper_pin = 5;
int but_pin = 6;
int led_pin = 4;
int poten_pin = A0;

// The state of the button
int state_but =0;

// The following variable will be used to decide if the buzzer will be turned on
int randNum;

// the frequency of the beeper
int frequency = 440;

// The volume levels
byte volume_low = 0;
byte volume_high = 125;

// The following variables will be used to keep track of 
// the total number of trials and the conditions
int trial = 1;
int hitrate = 0;
int falsealarm = 0;
int miss = 0;
int correctrej = 0;

void setup() {
  // This will start the serial where you can write sensor values
  Serial.begin(9600);

  // This initializes the pin modes
  pinMode(but_pin,INPUT);
  pinMode(led_pin,OUTPUT);
  pinMode(beeper_pin,OUTPUT);

  // Starts using the Volume library
  vol.begin();
}

// This is the main function that collects data and prints out the results
void experiment(){
  // Turns on the light 
  digitalWrite(led_pin,HIGH);
  // Decides if the beeper will be turned on or off randomly
  randNum = random(1,3);

  // Uses the random number to decide if the beeper is going to beep or not
  if(randNum == 1){
    vol.tone(frequency, volume_low);
    vol.delay(1000);
    }
  else{
    vol.tone(frequency, volume_high);
    vol.delay(1000);
    }

 // reads the digital voltage value and will store it in the variable.
  // It will be either 0 or 1
  state_but = digitalRead(but_pin);
  vol.delay(1000);

  // This is the logic behind the experiment. 
  // If the beeper is on and the button is pushed, you are in the hit rate zone
  // If the beeper is on and the button is not pushed, you are in the miss zone
  // If the beeper is off and the button is pushed, you are in the false alarm zone
  // If the beeper is off and the button is not pushed, you are in the correct reject zone
  if( randNum == 2 && state_but == 1){
    hitrate++;
  }
  else if( randNum == 2 && state_but == 0){
    miss++;
  } 
  else if (randNum == 1 && state_but == 1){
    falsealarm++;
  }
  else if (randNum == 1 && state_but == 0){
    correctrej++;
  } 

 // Turns off the LED and the beeper before the next trial
  digitalWrite(led_pin,LOW);
  vol.noTone();
  vol.delay(1000);
  // Prints out the sensor readings with a comma in between
  // p5.js will use this information to print out the number of times each condition is met
  Serial.print(hitrate);Serial.print(",");Serial.print(falsealarm);Serial.print(",");Serial.print(miss);Serial.print(",");Serial.print(correctrej);Serial.print(",");Serial.println(trial); 
}

void loop() {
  // The code will run only 20 times since it can run only 
  // while the trial is less than 21
  while(trial<21){
    // Calls the function that does the experiment
    experiment();
    // Increases the number of trials each time the function is called
    trial++;
  }
}
