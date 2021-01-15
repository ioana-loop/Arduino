// Tahsin Can Sarlak ENP162 buzzer volume

#include "Volume.h" // Include the Volume library

Volume vol; // Plug your speaker into the default pin for your board type which is D5:
// https://github.com/connornishijima/arduino-volume1#supported-pins

// Declares the pins for the buzzer, button, LED and
// the potentiometer. Make sure it matches with 
int buzzer_pin = 5;
int but_pin = 6;
int led_pin = 4;
int poten_pin = A0;

// Index to be used for the desired_vol array
int i = 0;

// An array that holds the values for desired values by people
int desired_vol[4];

// The boolean that makes sure the code is run onced
boolean once = true;

// The variable that is used to decide where the potentiometer needs to start
int var;

// Declares a variable to keep the potentiometer value and the button value
int potent_val, but_val;

// The mapped value of the potentiometer to be used as a volume. 
// Please note that the volume needs to be in byte
byte mapped_val;

// The frequency used on the buzzer
int freq = 240;

// The delay time in milliseconds
int ms = 5000;

// The variable for the average of the 4 desired volumes 
int average; 

// The variable for the total of 4 desired volumes 
int total;

// The variable used to calculate the average of 4 desired volumes
int old = 0;


void setup() {
  // We need to set our pin types. 
  // Since the buzzer and LED will recieve a signal, they need to be OUTPUT
  pinMode(buzzer_pin, OUTPUT);

  pinMode(led_pin,OUTPUT);
  
  //Since we will read the potentiometer and the button, they need to be INPUT. 
  pinMode(poten_pin, INPUT);

  pinMode(but_pin,INPUT);
  
  // Initializes a Serial so that we can have readings to debug easier
  Serial.begin(9600);

  // Starts using the Volume library
  vol.begin();
}

void loop() {
  // Makes sure the test is done once
  if(once == true){
    vol_level_order();
    once = false;
  }
}

// The function calls the volume test 4 times 
// and calculates the average of desired value
void vol_level_order(){
  // This for loop calls the volume level function and asks the user start from most left  
  for(int a = 0; a<2; a++){
    var = 1;
    vol_level(var);
  }
  
  // This for loop calls the volume level function and asks the user start from most right
  for(int b = 0; b<2; b++){
    var = 2;
    vol_level(var);
  }

  // This for loop calculates the average of 4 desired values and prints it
  for(int c = 0 ; c<4; c++){
    old = desired_vol[c];
    total = old + total;
  }
  average = total / 4;
  Serial.print("Average : ");Serial.println(average); 
}

// The function that asks the user to decide on a desired volume.
void vol_level(int var){
  // The switch case decides which orientation the potentiometer will start
  switch(var){
    // This case makes the potentiometer start from most left
    case 1:
      Serial.println("Move your potentiometer to the most left");
      delay(ms);
      Serial.println("Please start rotating");
      delay(ms); 
      // Does this loop while the button is not pushed.
      do {
        // Analog reads the potentiometer. It is analog because it has a range between 0 to 1023. 
        // If it was digital, it could only be either 0 or 1, 
        // like a button, either pressed or not pressed.
        potent_val = analogRead(poten_pin);
        
        // Maps the potentiometer value. It converts the voltage reading to a number between 0 and 255. 
        // You can always change the minimum and maximum number to be whatever you want.
        mapped_val = map(potent_val, 0, 1023, 0, 255); 
          
        // It writes the mapped_val to the buzzer_pin.
        vol.tone(freq,mapped_val);

        // Reads the button value to check if the button is pressed
        but_val = digitalRead(but_pin);
      } while(but_val == 0);

      // If the button is pressed, it saves the desired value to the array 
      // and prints out the number.
      if(but_val == 1){
        desired_vol[i] = mapped_val;
        i++;
        Serial.print("Your desired value: ");Serial.println(mapped_val);
        delay(ms);   
      }
      break;
      
    // This case makes the potentiometer start from most right
    case 2:
      Serial.println("Move your potentiometer to the most right");
      delay(ms);
      Serial.println("Please start rotating");
      delay(ms); 
      // Does this loop while the button is not pushed.
      do {
        // Analog reads the potentiometer. It is analog because it has a range between 0 to 1023. 
        // If it was digital, it could only be either 0 or 1, 
        // like a button, either pressed or not pressed.
        potent_val = analogRead(poten_pin);
        
        // Maps the potentiometer value. It converts the voltage reading to a number between 0 and 255. 
        // You can always change the minimum and maximum number to be whatever you want.
        mapped_val = map(potent_val, 0, 1023, 0, 255); 
          
        // It writes the mapped_val to the buzzer_pin.
        vol.tone(freq,mapped_val);

        // Reads the button value to check if the button is pressed
        but_val = digitalRead(but_pin);
      } while(but_val == 0);

      // If the button is pressed, it saves the desired value to the array 
      // and prints out the number.
      if(but_val == 1){
        desired_vol[i] = mapped_val;
        i++;
        Serial.print("Your desired value: ");Serial.println(mapped_val);
        delay(ms);   
      }
      break;
  }
}
