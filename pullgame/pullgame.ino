// Tahsin Can Sarlak - Tufts ENP 162 Fall 2020 Arduino 2 sensors reading



//The following lines define the pins & variables we'll be using

int potPin = A0;

int but = 6;

int led = 4;

int val = 0;

int state_but = 0;


void setup() {

  // This will start the serial where you can write sensor values

  Serial.begin(9600);

  pinMode(led, OUTPUT); // Prepare the LED Pin for receiving output
  
  pinMode(potPin, INPUT); // Prepare the Potentiometer Pin for receiving input

  pinMode(but, INPUT); // Prepare the Button Pin for receiving input
}



void loop() {

  //reads the analogue voltage from the pot via ADC and stores it in the variable. It will range between 0 to 1023

  val = analogRead(potPin);

  // This will write the potentiometer and will put a comma after it.

  // P5.js code will be able distunguish two sensor values by seperating the line with the comma.

  Serial.print(val);

  Serial.print(',');

  // reads the digital voltage value and will store it in the variable. It will be either 0 or 1

  state_but = digitalRead(but);

  // This will write the button's state and will end the line, so that the next time void loop() runs,

  // the new values will be on the other line.

  Serial.println(state_but);

  // Will put a delay of 200 ms

  delay(200);

  // This code will control the LED on the button. If the button is pressed, it will light up the LED

  digitalWrite(led,state_but?HIGH:LOW);

}
