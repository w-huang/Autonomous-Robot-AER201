#include <Servo.h>

class robot{
	public:
		robot(); //constructor
		int getCurrentState();
		bool inputSignal1Pressed;
		bool inputSignal2Pressed;
		bool startButtonPressed;
                void setState(int);
		void incBallCount();
		void move(int, int);
		void turnLeft();
		void turnRight();
		float detectDistances(int);
		void doTaskA();
		void doTaskB();
		void doTaskC();
		void doTaskD();
		void doTaskE();
		void driveForward(int);
	private:
		//ones that the robot will sense
		int currentDirection; //1 = north, 2 = west, 3 = south, 4 = east
		int ballCounter;
		int currentState;
		int robotLocation[2];//index 0 is X, index Y is 1;
		int gameBoardLocation[2];
		//hardcoded locations to be set by user button entries
		int possibleHopperLocations[12];
		int userInputHopperLocation;
		bool userInputHopperOrientation;
		int dummyLocationX;
		int dummyLocationY;
		//robot components
		int IRPin;
		int sonarPins[8]; //0,1 front; 2,3 left; 4,5 back; 6,7 right
		Servo myServo[2]; //
		int myMotors[4]; // Right: index 0, 1; Left: index 2,3
		int motorEnablePins[2]; //left = 4, index 0, right = 5, index 1
};

robot::robot(){
    Serial.println("robot constructor function");
	//constructor for robot class; initializes the necessary hard-coded values such as hopper location, motor pins, etc.
    int sonarPinsTemp[8] = {46,47,48,49,50,51,52,53};
    int myMotorsTemp[4] = {32,33,30,31}; //32,33 for right; 30,31 for left.
    for(int i = 0; i < 8; ++i){
        if( i < 4)
        myMotors[i] = myMotorsTemp[i];
        sonarPins[i] = sonarPinsTemp[i];
    }
    motorEnablePins[0] = 5;
    motorEnablePins[1] = 4;
    currentDirection = 1;
    dummyLocationX = 50;
    dummyLocationY = 50;
	IRPin = A0;
    robotLocation[0] = 0;
    robotLocation[1] = 0;
    gameBoardLocation[0] = 0;
	gameBoardLocation[1] = 100;
	currentState = 1;
	myServo[0].attach(9);
	myServo[1].attach(10);
	myServo[0].write(0);
	myServo[1].write(0);
}


float robot::detectDistances(int side){
        //Serial.println("detectDistances function");
	//returns the distance measured by the sonar on the specified side
	//side key: 0 = front, 1 = left, 2 = back, 3 = right
	int offset = side * 2;
	int duration;
	float distance;

	digitalWrite(46 + offset,LOW);
  	delayMicroseconds(5);
  	digitalWrite(46 + offset, HIGH);
  	delayMicroseconds(15);
  	digitalWrite(46 + offset, LOW);
  	delayMicroseconds(5);  
	duration = pulseIn(47 + offset, HIGH);
  	distance = duration/58.2;
  	
  	return distance;
}

//NEEDS COMPLETION; USE IS QUESTIONABLE
/*void mapDistancesToPosition(){
	float[4] sonarDistances = {0,0,0,0}; //index correlation: 0 front 1 left 2 right 3 back
	for (int i = 0; i < 0; ++i){
		sonarDistances[i] = detectDistances(i);
	}

	return;
}*/

void robot::turnLeft(){
        Serial.println("turnLeft function");
	(*this).currentDirection += 1;
	if ((*this).currentDirection > 4)
		(*this).currentDirection -= 4;

	digitalWrite((*this).myMotors[0], HIGH);
	digitalWrite((*this).myMotors[1], LOW);
	digitalWrite((*this).myMotors[2], LOW);
	digitalWrite((*this).myMotors[3], HIGH);
}

void robot::turnRight(){
        Serial.println("turnRight function");
	(*this).currentDirection -= 1;
	if ((*this).currentDirection < 0)
		(*this).currentDirection += 4;
	digitalWrite((*this).myMotors[0], LOW);
	digitalWrite((*this).myMotors[1], HIGH);
	digitalWrite((*this).myMotors[2], HIGH);
	digitalWrite((*this).myMotors[3], LOW);
}

void robot::driveForward(int sideWallToFollow){
//        Serial.println("Forward Function");
	digitalWrite((*this).myMotors[0], HIGH);
	digitalWrite((*this).myMotors[1], LOW);
	digitalWrite((*this).myMotors[2], HIGH);
	digitalWrite((*this).myMotors[3], LOW);
        Serial.println((*this).detectDistances(0));
	while((*this).detectDistances(0) > 5){
                Serial.println((*this).detectDistances(sideWallToFollow));
		if ((*this).detectDistances(sideWallToFollow) > 10 + 2){
                Serial.println("distance > 10");
			switch(sideWallToFollow){
		            case 1: analogWrite(motorEnablePins[1], 192);
                                    analogWrite(motorEnablePins[0], 255);
                                    Serial.println("Left wheel is weak - 1"); 
                                    delay(200);
                                    analogWrite(motorEnablePins[1], 255);
                                    analogWrite(motorEnablePins[0], 255);
                                    delay(150);
                                    analogWrite(motorEnablePins[1], 255);
                                    analogWrite(motorEnablePins[0], 192);
                                    delay(200);
                                    
                                    break;
			    case 3: analogWrite(motorEnablePins[0], 192);
                                    analogWrite(motorEnablePins[1], 255);
                                    Serial.println("Right wheel is weak - 1");
                                    delay(200);
                                    analogWrite(motorEnablePins[1], 255);
                                    analogWrite(motorEnablePins[0], 255);
                                    delay(150);
                                    analogWrite(motorEnablePins[0], 255);
                                    analogWrite(motorEnablePins[1], 192);
                                    delay(200);
                                    break;
			}
		}else if((*this).detectDistances(sideWallToFollow) < 10 - 2){
                         Serial.println("distance < 10");
                         switch(sideWallToFollow){
		            case 3: analogWrite(motorEnablePins[1], 192);
                                    analogWrite(motorEnablePins[0], 255);
                                    Serial.println("Left wheel is weak - 1"); 
                                    delay(500);
                                    analogWrite(motorEnablePins[1], 255);
                                    analogWrite(motorEnablePins[0], 255);
                                    delay(500);
                                    analogWrite(motorEnablePins[1], 255);
                                    analogWrite(motorEnablePins[0], 192);
                                    delay(500);
                                    
                                    break;
			    case 1: analogWrite(motorEnablePins[0], 192);
                                    analogWrite(motorEnablePins[1], 255);
                                    Serial.println("Right wheel is weak - 1");
                                    delay(500);
                                    analogWrite(motorEnablePins[1], 255);
                                    analogWrite(motorEnablePins[0], 255);
                                    delay(500);
                                    analogWrite(motorEnablePins[0], 255);
                                    analogWrite(motorEnablePins[1], 192);
                                    delay(500);
                                    break;
			}
                }else{
			analogWrite(motorEnablePins[0],255);
			analogWrite(motorEnablePins[1],255);
		}
	delay(50);
        }
        
        Serial.println("stopping");
	digitalWrite((*this).myMotors[0], LOW);
	digitalWrite((*this).myMotors[1], LOW);
	digitalWrite((*this).myMotors[2], LOW);
	digitalWrite((*this).myMotors[3], LOW);
        
	return;
}
//CURRENTLY WORKING ON MOVE ALGORITHM. CONTINUE HERE AND/OR IN THE DRIVEFORWARD/TURN FUNCTIONS
void robot::move(int xLocation, int yLocation){
	while ((*this).robotLocation[0] - xLocation > 10 || (*this).robotLocation[1] - yLocation > 10 ){

	}
}

void robot::incBallCount(){
	(*this).ballCounter += 1;
	return;
}

void robot::setState(int state){
//  Serial.println("setState function");
  (*this).currentState = state;
  return;
}

int robot::getCurrentState(){

	return (*this).currentState;
}

void robot::doTaskA(){
//        Serial.println("In function A");
  	(*this).currentState = 2;
	return;
}

void robot::doTaskB(){
        (*this).driveForward(3);
        //(*this).stop();
        //(*this).driveForward(3);
        //(*this).setState(3);
	//MOVEMENT TO SPECIFIED LOCATION (X,Y)
	return;	
}

void robot::doTaskC(){
	(*this).setState(4);
	return;
}

void robot::doTaskD(){
	(*this).setState(5);
	return;
}

void robot::doTaskE(){
	(*this).setState(2);
	return;
}
//Main code
int outputPinsArray[12] = {4,5,30,31,32,33,9,10,46,48,50,52};
int inputPinsArray[4] = {47,49,51,53};

robot myRobot;


void setup(){
	
	Serial.begin(9600);
	for(int i = 0; i < sizeof(outputPinsArray); ++i){
		pinMode(outputPinsArray[i], OUTPUT);
	}
	for(int i = 0; i < sizeof(inputPinsArray); ++i){
		pinMode(inputPinsArray[i], INPUT);
	}	
}

void loop(){
  
//        Serial.print("Current State: ");
        Serial.println(myRobot.getCurrentState());
	switch(myRobot.getCurrentState()){
		case 1: myRobot.doTaskA(); break;
		case 2: myRobot.doTaskB(); break;
		case 3: myRobot.doTaskC(); break;
		case 4: myRobot.doTaskD(); break;
		case 5: myRobot.doTaskE(); break;
	}

	delay(50);
}
