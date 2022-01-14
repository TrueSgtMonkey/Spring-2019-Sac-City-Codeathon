#include <LiquidCrystal.h>
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

//false means not registered and that they cannot park in spot[i]
///bool regSpots[10] = {false, false, false, false, false, false, false, false, false, false};
//0 means spot is empty, 1 if full
bool spots[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//both increment as spots are registered and taken up
int regSpot = 0;
int spot = 0;
bool buttPressed1 = false;  //when car parks
bool buttPressed2 = false;  //when car leaves
bool buttPressed3 = false;  //the toggle for checking for open parking spots
bool checkingSpot = false;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTT1, INPUT);
  pinMode(BUTT2, INPUT);
  pinMode(BUTT3, INPUT);
  Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    buttState1 = digitalRead(BUTT1);
    buttState2 = digitalRead(BUTT2);
    buttState3 = digitalRead(BUTT3);
    //buttPrintTest();  //uncomment to print button states
    
    //Parking spots must first be registered before parking
    //parking spot button is pressed
    if(buttState1 == HIGH && !buttPressed1)
    {
        buttPressed1 = true;
        if(spot < 10)
        {
            spots[spot] = 1;
            spot++;
            Serial.print("Spots Available: ");
            Serial.println(10 - spot);
        }
        else
            Serial.print("No Spots.\n");
    }
    if(buttState2 == HIGH && !buttPressed2)
    {
        buttPressed2 = true;
        if(spot > 0)
        {
            spots[spot] = 0;
            spot--;
            Serial.print("Spots Available: ");
            Serial.println(10 - spot);
        }
    }
    //WE ARE CHECKING FOR AN OPEN SPOT
    if(buttState3 == HIGH && !buttPressed3)
    {
        buttPressed3 = true;
        checkingSpot = !checkingSpot;
    }
    if(checkingSpot)
    {
        printSonar();
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

void printSonar()
{
    Serial.print("Dist(cm): ");
    Serial.println(sonar.ping_cm());
}

