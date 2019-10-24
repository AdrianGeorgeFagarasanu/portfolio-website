/* 
 * This is what a comment looks like. It has no bearing on the actual code. 
 * As far as the compiler is concerned, these lines do not exist.
 * Use all of the following comments as guides for the tasks and for better understanding of surrounding code.
 */ 
  //This is another type of comment.
 
//the time we give the sensor to calibrate in seconds
int calibrationTime = 10;       
 
//the time when the sensor outputs a low impulse
long unsigned int lowIn;        
 
//the amount of milliseconds the sensor has to be in LOW state (no voltage provided)
//before we assume all motion has stopped in milliseconds
long unsigned int pause = 500; 

//These values are booleans with two possible states: true or false.
boolean lockLow = true;
boolean takeLowTime; 
boolean motion = false;
boolean taskAccomplished = false;

int counter = 5; //We will use an integer variable to store the number that we want to show on the 7 segment display.

/*                   //
 *  PART 1: MACROS  //
*/                 //

#define pirPin 3   //The digital pin connected to the PIR sensor's output

/*
 * ______________________________________________________________________________________________________________________
 * TASK 1: Define the following Macros: All 7 segments of digital display, all 3 led pins, and the buzzer (piezospeaker).
 * Segment A - G has pins 4 - 10 in order (e.g. #define segA 4, #define segB 5, #define segC 6, etc). 
 * LED pins 1 - 3 has pins 11 - 13 (e.g. #define ledPin1 11, #define ledPin2 12, etc).
 * Finally, the buzzer has pin 2.
 * ______________________________________________________________________________________________________________________
 */
#define segA 4
#define segB 5
#define segC 6
#define segD 7
#define segE 8
#define segF 9
#define segG 10
 
#define ledPin1 11
#define ledPin2 12
#define ledPin3 13

#define buzzer 2
 
 
/*                 //
 * PART 2: SETUP  //
*/               //
 
void setup(){
  Serial.begin(9600);

  /*
   * ________________________________________________________________________________________________________________
   * TASK 2: We must now setup all pin modes with the corresponding macros and correct type of signal transmission.
   * Setup a pin mode like this: pinMode(macro name, INPUT or OUTPUT). 
   * All existing macros are an OUTPUT signal, except for pirPin which is detecting a signal therefore it is INPUT.
   * ________________________________________________________________________________________________________________
   */
  pinMode(pirPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  digitalWrite(pirPin, LOW); //Setting the sensor detection to off by default (LOW state) - Will be turned on when motion is detected
 
  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
  }

 /*                //
  * PART 3: LOOP  //
 */              //
  
////////////////////////////
//The following code in the loop will continue to execute as long as there is power being pushed to the arduino
void loop(){

     /* 
      *  ___________________________________________________________________________________________________________
      *  TASK 3: Call the method numDisplay which we will later work on in task 6.
      *  This method will display a given number on the digital counter once the code is complete.
      *  Inside the brackets of the method, an interger variable is required to give the display a number to show.
      *  We will provide the method with the variable "counter" which was set at the top of the code.
      * ____________________________________________________________________________________________________________
      */
     numDisplay(counter);
 
     if(digitalRead(pirPin) == HIGH && !motion && !taskAccomplished){
         /* 
          *  _____________________________________________________________________________________________________________
          *  TASK 4: Once the sensor detects motion, we need to provide some commands.
          *  The first command is for the piezospeaker to make a subtle noise when motion is detected - 
          *  do it like this: tone(buzzer, frequency, duration);
          *  Make the buzzer 250Hz and make it last for 25 milliseconds.
          *  Next, we need to light up the LEDs in the correct pattern using the digitalWrite method - 
          *  e.g. digitalWrite(ledPin1, HIGH)... (remember, HIGH gives the light power as opposed to LOW).
          *  Light up each indivdual LED in ascending order with a delay of 150 milliseconds in between - 
          *  (don't forget to turn off the previous LED along the way).
          *  Then turn on all LEDs at once followed by a delay of 1000 milliseconds. 
          *  Finally, turn off all lights and begin the descend with the LEDs (same as before, just opposite direction).
          *  _____________________________________________________________________________________________________________
          */
         tone(buzzer, 250, 25);
         digitalWrite(ledPin1, HIGH);   //the led visualizes the sensors output pin state
         delay(150);
         digitalWrite(ledPin1, LOW);
         digitalWrite(ledPin2, HIGH);
         delay(150);
         digitalWrite(ledPin2, LOW);
         digitalWrite(ledPin3, HIGH);
         delay(150);
         digitalWrite(ledPin3, LOW);
         delay(150);
         digitalWrite(ledPin1, HIGH);
         digitalWrite(ledPin2, HIGH);
         digitalWrite(ledPin3, HIGH);
         delay(1000);
         digitalWrite(ledPin1, LOW);
         digitalWrite(ledPin2, LOW);
         digitalWrite(ledPin3, LOW);
         delay(150);
         digitalWrite(ledPin3, HIGH);  
         delay(150);
         digitalWrite(ledPin3, LOW);
         digitalWrite(ledPin2, HIGH);
         delay(150);
         digitalWrite(ledPin2, LOW);
         digitalWrite(ledPin1, HIGH);
         
         if(lockLow){ 
           //makes sure we wait for a transition to LOW before any further output is made:
           lockLow = false;           
           Serial.println("---");
           Serial.print("motion detected at ");
           Serial.print(millis()/1000);
           Serial.println(" sec");
           delay(50);
         }        
         takeLowTime = true;
         motion = true;
         /*
          * __________________________________________________________________________________________________________
          * TASK 5: Subtract 1 from the counter variable so that every time motion is detected, a countdown happens.
          * When the counter reaches 0, a distinct buzzer should go off.
          * Make the buzzer 1000Hz frequency, and last for 1000 milliseconds.
          * __________________________________________________________________________________________________________
          */
         counter = counter - 1;
         if (counter == 0){
           tone(buzzer, 1000, 1000); //Place buzzer code right before this comment.
           taskAccomplished = true;
         }
        }
 
     if(digitalRead(pirPin) == LOW){      
       digitalWrite(ledPin1, LOW);  //the led visualizes the sensors output pin state
       digitalWrite(ledPin2, LOW);
       digitalWrite(ledPin3, LOW);
 
       if(takeLowTime){
          lowIn = millis();          //save the time of the transition from high to LOW
          takeLowTime = false;       //make sure this is only done at the start of a LOW phase
          }
         //if the sensor is low for more than the given pause,
         //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){ 
             //makes sure this block of code is only executed again after
             //a new motion sequence has been detected
             lockLow = true;                       
             Serial.print("motion ended at ");      //output
             Serial.print((millis() - pause)/1000);
             Serial.println(" sec");
             delay(50);
          } 
          motion = false;
       }

  }

/*                                         //
 * PART 4: DIGITAL COUNTER DISPLAY METHOD //
*/                                       //

/*
 * ___________________________________________________________________________________________________________________________________
 * TASK 6: To create actual number on the 7 segment display, 
 * we are going to have to find the right combinations of which 7 LED parts need to be turned off and on to form that given number.
 * Don't forget that the type of 7 segment display we are using today is a Common Anode - 
 * meaning that we need to power off a segment (use LOW state) in order for that segment to turn on and vice versa for turning off.
 * ___________________________________________________________________________________________________________________________________
 */
  void numDisplay(int num) {
    switch(num) {
      case 0:
        //Insert segment combination for 0 here.
        digitalWrite(segA, LOW);
        digitalWrite(segB, LOW);
        digitalWrite(segC, LOW);
        digitalWrite(segD, LOW);
        digitalWrite(segE, LOW);
        digitalWrite(segF, LOW);
        digitalWrite(segG, HIGH);
        break;
      case 1:
        //Insert segment combination for 1 here.
        digitalWrite(segA, HIGH);
        digitalWrite(segB, LOW);
        digitalWrite(segC, LOW);
        digitalWrite(segD, HIGH);
        digitalWrite(segE, HIGH);
        digitalWrite(segF, HIGH);
        digitalWrite(segG, HIGH);
        break;
      case 2:
        //Insert segment combination for 2 here.
        digitalWrite(segA, LOW);
        digitalWrite(segB, LOW);
        digitalWrite(segC, HIGH);
        digitalWrite(segD, LOW);
        digitalWrite(segE, LOW);
        digitalWrite(segF, HIGH);
        digitalWrite(segG, LOW);
        break;
      case 3:
        //Insert segment combination for 3 here.
        digitalWrite(segA, LOW);
        digitalWrite(segB, LOW);
        digitalWrite(segC, LOW);
        digitalWrite(segD, LOW);
        digitalWrite(segE, HIGH);
        digitalWrite(segF, HIGH);
        digitalWrite(segG, LOW);
        break;
      case 4:
        //Insert segment combination for 4 here.
        digitalWrite(segA, HIGH);
        digitalWrite(segB, LOW);
        digitalWrite(segC, LOW);
        digitalWrite(segD, HIGH);
        digitalWrite(segE, HIGH);
        digitalWrite(segF, LOW);
        digitalWrite(segG, LOW);
        break;
      case 5:
        //Insert segment combination for 5 here.
        digitalWrite(segA, LOW);
        digitalWrite(segB, HIGH);
        digitalWrite(segC, LOW);
        digitalWrite(segD, LOW);
        digitalWrite(segE, HIGH);
        digitalWrite(segF, LOW);
        digitalWrite(segG, LOW);
        break;
    }
  }
