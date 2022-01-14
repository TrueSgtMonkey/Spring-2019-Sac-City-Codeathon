#include <LiquidCrystal.h>

const int BUTT1 = 2;
const int BUTT2 = 3;
//whether buttons are high or low
int buttState1 = 0;
int buttState2 = 0;

//false means not registered and that they cannot park in spot[i]
///bool regSpots[10] = {false, false, false, false, false, false, false, false, false, false};
//0 means spot is empty, 1 if full
bool spots[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//both increment as spots are registered and taken up
int regSpot = 0;
int spot = 0;
bool buttPressed1 = false;  //when car leaves
bool buttPressed2 = false;  //when car parks


void setup() {
  // put your setup code here, to run once:
  pinMode(BUTT1, INPUT);
  pinMode(BUTT2, INPUT);
  Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    buttState1 = digitalRead(BUTT1);
    buttState2 = digitalRead(BUTT2);
    //buttPrintTest();  //uncomment to print button states

    //Registration button is pressed
    //Parking spots must first be registered before parking
    //parking spot button is pressed
    if(buttState1 == HIGH && !buttPressed1)
    {
        buttPressed2 = true;
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
    }
    if(buttState1 == LOW)
        buttPressed1 = false;
    if(buttState2 == LOW)
        buttPressed2 = false;
}

//just prints our two buttons for testing
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
}

