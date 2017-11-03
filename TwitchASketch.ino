#include <Wire.h>
#include <Adafruit_MotorShield.h>
#define INPUT_SIZE 35
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *upDown = AFMS.getStepper(32, 2);
// forward for down, backward for up
Adafruit_StepperMotor *leftRight = AFMS.getStepper(32, 1);
// forward for left, backward for right.
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  AFMS.begin();
  upDown->setSpeed(50); //50 RPM for max speed
  leftRight->setSpeed(50);
  Serial.println("ACTIVE");
}

void loop() {
 
// Get next command from Serial (add 1 for final 0)
char input[INPUT_SIZE + 1];
byte size = Serial.readBytes(input, INPUT_SIZE);
// Add the final 0 to end the C string
input[size] = 0;
int multiplier = 100; //Amplify movements due to small amount of stepper motor steps




// Read each command pair 
char* command = strtok(input, " ");
while (command != 0)
{
    // Split the command in two values
    char* separator = strchr(command, 'x');
    if (separator != 0)
    {
        // Actually split the string in 2: replace ':' with 0
        *separator = 0;
        
        int servoId = atoi(command);
        
        
        ++separator;
        int position = atoi(separator);
        position = position * multiplier; //Amplify movement due to small steps of motor
        
         switch (servoId) {
          case 1: //right
           leftRight->step(position, FORWARD, SINGLE);
           //Serial.print("Moved right by ");
           //Serial.println(position);
           break;
          case 2: //left
           leftRight->step(position, BACKWARD, SINGLE);
           //Serial.print("Moved left by ");
           //Serial.println(position);
           break;
          case 3: //up
           upDown->step(position, BACKWARD, SINGLE);
           //Serial.print("Moved up by ");
           //Serial.println(position);
           break;
          case 4: //down
           upDown->step(position, FORWARD, SINGLE);
           //Serial.print("Moved down by ");
           //Serial.println(position);
           break;
          default:
           //Serial.println("ERROR: servoId is invalid.");
           //Serial.print(servoId);
           break;
         }

        
        }
    // Find the next command in input string
    command = strtok(0, " ");
}
}
