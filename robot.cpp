#include <Servo.h>

class robot{
	public:
		robot(); //constructor
		int getCurrentState();
		bool inputSignal1Pressed;
		bool inputSignal2Pressed;
		bool startButtonPressed;
                void setState(int);
		void move();
		void turnLeft();
		void turnRight();
		void detectEnvironment();
		void doTaskA();
		void doTaskB();
		void doTaskC();
		void doTaskD();
		void doTaskE();
	private:
		//ones that the robot will sense
		int currentState;
		int robotLocation[2];
		int gameBoardLocation[2];
		//hardcoded locations to be set by user button entries
		int possibleHopperLocations[12];
		int userInputHopperLocation;
		bool userInputHopperOrientation;
		//robot components
		int IRPin;
		int sonarPins[8];
		Servo myServo[2]; //
		int myMotors[4]; // Right: index 0, 1; Left: index 2,3

};

robot::robot(){
        int sonarPinsTemp[8] = {46,47,48,49,50,51,52,53};
        int myMotorsTemp[4] = {4,5,6,7};
        for(int i = 0; i < 8; ++i){
          if( i < 4)
            myMotors[i] = myMotorsTemp[i];
          sonarPins[i] = sonarPinsTemp[i];
        }
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

void robot::setState(int state){
  (*this).currentState = state;
  return;
}

int robot::getCurrentState(){
  return (*this).currentState;
  
}

void robot::doTaskA(){
	(*this).currentState = 2;
	return;
}


void robot::doTaskB(){
	(*this).currentState = 3;
	return;	
}

void robot::doTaskC(){
	(*this).currentState = 4;
	return;
}

void robot::doTaskD(){
	(*this).currentState = 5;
	return;
}

void robot::doTaskE(){
	(*this).currentState = 2;
	return;
}
//Main code
int outputPinsArray[14] = {4,5,6,7,9,10,46,48,50,52};
int inputPinsArray[4] = {47,49,51,53};

robot myRobot;
void setup(){
	
	Serial.begin(9600);
	for(int i = 0; i < sizeof(outputPinsArray); ++i){
		pinMode(i, OUTPUT);
	}
	for(int i = 0; i < sizeof(inputPinsArray); ++i){
		pinMode(i, INPUT);
	}	
}

void loop(){
	switch(myRobot.getCurrentState()){
		case 1: myRobot.doTaskA();
		case 2: myRobot.doTaskB();
		case 3: myRobot.doTaskC();
		case 4: myRobot.doTaskD();
		case 5: myRobot.doTaskE();
		default: myRobot.setState(2);
	}
	delay(50);
}