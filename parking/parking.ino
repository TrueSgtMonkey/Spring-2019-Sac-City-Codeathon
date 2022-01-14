//ACM Smart Parking Solutions
//Code with arduino including the newping library for the echolocater

#include <NewPing.h>

#define TRIGGER_PIN 13
#define ECHO_PIN 12
#define MAX_DISTANCE 400

const int BUTT1 = 2;  //parking button
const int BUTT2 = 3;  //leaving parking zone button
const int BUTT3 = 4;  //checking for open spot trigger
//whether buttons are high or low
int buttState1 = 0;
int buttState2 = 0;
int buttState3 = 0;


///bool regSpots[10] = {false, false, false, false, false, false, false, false, false, false};
//0 means spot is empty, 1 if full
bool spots[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//increments as spots are taken up until full
int spot = 0;
bool buttPressed1 = false;  //when car parks
bool buttPressed2 = false;  //when car leaves
bool buttPressed3 = false;  //the toggle for checking for open parking spots

//toggles whether we are checking for spots with the sonar
bool checkingSpot = false;
int counter = 0;  //used for a pseudo-random spot pick based on iteration
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

void setup() 
{
  //setting up all of our buttons as inputs
  pinMode(BUTT1, INPUT);
  pinMode(BUTT2, INPUT);
  pinMode(BUTT3, INPUT);
  //getting ready for inputs
  Serial.begin(9600);
}

void loop() {
    //counter increments until 10 upon each loop and then resets itself
    counter++;
    if(counter >= 10)
        counter = 0;
    //getting the states of the buttons (LOW OR HIGH/PRESSED OR NOT)
    buttState1 = digitalRead(BUTT1);
    buttState2 = digitalRead(BUTT2);
    buttState3 = digitalRead(BUTT3);
    //buttPrintTest();  //uncomment to print button states
    
    //Parking spots must first be registered before parking
    //parking spot button is pressed
    if(buttState1 == HIGH && !buttPressed1)
    {
        //making sure that pressing the button performs a function once
        buttPressed1 = true;
        //if there is an empty spot
        if(spot < 10)
        {
            int rNum;
            if(spot < 10)
            {
                //a random number used for selecting a parking spot
                rNum = counter;
                //making sure our random number doesn't select the same spot
                while(spots[rNum] == true)
                {
                    counter++;  //will search for the first spot available after the spot
                    if(counter >= 10)
                    {
                        counter = 0;
                    }
                    rNum = counter;
                }
                //means that a spot is filled up
                spots[rNum] = 1;
                spot++;
            }
            Serial.print("Spots Available: ");
            Serial.println(10 - spot);
            Serial.print("spot[");
            Serial.print(rNum);
            Serial.println("] taken.");
        }
        else
            Serial.print("No Spots.\n");
    }
    //swtiched on when "person leaves"
    if(buttState2 == HIGH && !buttPressed2)
    {
        //making sure button doesn't perform function more than once upon button press
        buttPressed2 = true;
        //if no spots are taken up, this won't run.
        if(spot > 0)
        {
            //means that a spot is empty
            spots[spot] = 0;
            spot--;
            Serial.print("Spots Available: ");
            Serial.println(10 - spot);
        }
    }
    //WE ARE CHECKING FOR AN OPEN SPOT
    if(buttState3 == HIGH && !buttPressed3)
    {
        //makes sure that this code isn't run more than once
        buttPressed3 = true;
        //toggling our checkingSpot
        checkingSpot = !checkingSpot;
    }
    //true means that we are checking for open parking spots
    if(checkingSpot)
    {
        //printing distances given by echolocater
        printSonar();
        //our parking spots are about 11 cm
        if(sonar.ping_cm() > 11)  //open spot
        {
            Serial.print("Spot open!\n");
        }
        else
        {
            Serial.print("Spot is filled up.\n");
        }
        delay(100);
    }
    //when one of the buttons aren't pressed down, these bool values are reset to false
    if(buttState1 == LOW)
        buttPressed1 = false;
    if(buttState2 == LOW)
        buttPressed2 = false;
    if(buttState3 == LOW)
        buttPressed3 = false;
}

//just prints our three buttons for testing
void buttPrintTest()
{
    if(buttState1 == HIGH)
      Serial.println("buttState1: HIGH");
    else
      Serial.println("buttState1: LOW");
    if(buttState2 == HIGH)
      Serial.println("buttState2: HIGH");
    else
      Serial.println("buttState2: LOW");
    if(buttState3 == HIGH)
      Serial.println("buttState3: HIGH");
    else
      Serial.println("buttState3: LOW");
}

//prints our distance in centimeters
void printSonar()
{
    Serial.print("Dist(cm): ");
    Serial.println(sonar.ping_cm());
    /*
     * We can print in inches, but we were only using centimeters.
     */
}

