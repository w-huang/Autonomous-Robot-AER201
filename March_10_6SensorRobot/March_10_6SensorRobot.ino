#include <Servo.h>
#define TOOCLOSE 1
#define TOOFAR 2

class robot{
	public:
		robot(); //constructor
		float detectDistances(int);
		int getCurrentState();
		int checkForReAdjustment(int);
		bool startButtonPressed;
        void setState(int);
		void incBallCount();
		void moveToHopper();
		void moveToGameboard();
		void turnLeft();
		void turnRight();
		void stop();
		void go();
		void changeOrientation(int);
		void reAdjust(int, int);
        void grabBall();
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
		int sonarPins[12]; //0,1 front; 2,3 left back; 4,5 left front; 6,7 back; 8,9 right back; 10, 11 right front.
		Servo myServo[2]; //
		int myMotors[4]; // Right: index 0, 1; Left: index 2,3
		int motorEnablePins[2]; //left = 4, index 0, right = 5, index 1
};

robot::robot(){
    Serial.println("robot constructor function");
	//constructor for robot class; initializes the necessary hard-coded values such as hopper location, motor pins, etc.
    int sonarPinsTemp[12] = {42,43,44,45,46,47,48,49,50,51,52,53};
    int myMotorsTemp[4] = {32,33,30,31}; //32,33 for right; 30,31 for left.
    for(int i = 0; i < 12; ++i){
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


float robot::detectDistances(int side)  {
    //Serial.print("detectDistances function");
	//returns the distance measured by the sonar on the specified side
	//side key: 0 = front, 1 = left back, 2 = left front, 3 = back, 4 = right back 5 = right front 
	int counter = 0;
	int offset = side * 2;
	int duration;
	float distance[5];
	while(counter < 5){
		digitalWrite(42 + offset,LOW);
	  	delayMicroseconds(5);
	  	digitalWrite(42 + offset, HIGH);
	  	delayMicroseconds(15);
	  	digitalWrite(42 + offset, LOW);
	  	delayMicroseconds(5);
		duration = pulseIn(43 + offset, HIGH);
		if(duration <= 0){
			continue;
		}
	  	distance[counter] = duration/58.2;
	  	++counter;
	  	delay(5);
	  }
  	return distance[2];
}
void robot::changeOrientation(int directionOfTurn){
	//direction of turn: 0 == left; 1 == right
	Serial.println("changeOrientation function");
	if (directionOfTurn){
		++(*this).currentDirection;
		if((*this).currentDirection > 4)
			(*this).currentDirection -= 4;
	}
	else{
		--(*this).currentDirection;
		if((*this).currentDirection < 0)
			(*this).currentDirection += 4;
	}
	return;
}
void robot::turnLeft(){
    Serial.println("turnLeft function");
	(*this).currentDirection += 1;
	if ((*this).currentDirection > 4)
		(*this).currentDirection -= 4;

	digitalWrite((*this).myMotors[0], HIGH);
	digitalWrite((*this).myMotors[1], LOW);
	digitalWrite((*this).myMotors[2], LOW);
	digitalWrite((*this).myMotors[3], HIGH);
	delay(1600);
	(*this).stop();
	(*this).changeOrientation(0);
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
	delay(1600);
	(*this).stop();
	(*this).changeOrientation(1);
}

int robot::checkForReAdjustment(int sideToFollowBackSonar){
	Serial.println("checkForReAdjustment Function");

    Serial.print("Side Distance from BACK: ");
    Serial.println((*this).detectDistances(sideToFollowBackSonar));
    Serial.print("Side Distance from FRONT: ");
    Serial.println((*this).detectDistances(sideToFollowBackSonar + 1));

    float backDistance = detectDistances(sideToFollowBackSonar);
    float frontDistance = detectDistances(sideToFollowBackSonar + 1);

    if (frontDistance - backDistance > 1.4){
    	return TOOFAR;
    }

    else if (frontDistance - backDistance < -1.4){
    	return TOOCLOSE;
    }
	return 0;
}


void robot::driveForward(int sideWallToFollow){
	//sideWallToFollow should be the BACK sonar of the side of interest
	Serial.println("driveForward Function");
	int reAdjustVariable;
	(*this).go();
    Serial.println((*this).detectDistances(0));
	while((*this).detectDistances(0) > 25){
        reAdjustVariable = (*this).checkForReAdjustment(sideWallToFollow);
        if (reAdjustVariable){
        	(*this).reAdjust(sideWallToFollow, reAdjustVariable);
        }
		else{
			analogWrite(motorEnablePins[0],255);
			analogWrite(motorEnablePins[1],255);
		}
	delay(50);
    }
    (*this).stop();    
	return;
}
void robot::reAdjust(int sideWallToFollow, int whichWay){
	Serial.print("reAdjust function: ");
	int i; // weak wheel
	int j; // strong wheel
	
	if(sideWallToFollow == 1 && whichWay == TOOFAR){
		Serial.println("case 1");
		i = 0;
		j = 1;
	}
	else if(sideWallToFollow == 1 && whichWay == TOOCLOSE){
		Serial.println("case 2");		
		i = 1;
		j = 0;
	}
	else if(sideWallToFollow == 4 && whichWay == TOOFAR){
		Serial.println("case 3");
		i = 0;
		j = 1;
	}
	else if(sideWallToFollow == 4 && whichWay == TOOCLOSE){
		Serial.println("case 4");
		i = 1;
		j = 0;
	}

    analogWrite(motorEnablePins[i], 128);
    analogWrite(motorEnablePins[j], 255);
    delay(350);
    analogWrite(motorEnablePins[i], 255);
    analogWrite(motorEnablePins[j], 255);
    delay(300);/*
    analogWrite(motorEnablePins[i], 255);
    analogWrite(motorEnablePins[j], 128);
    delay(200);*/
}
void robot::go(){
	Serial.println("go function");
	digitalWrite((*this).myMotors[0], HIGH);
	digitalWrite((*this).myMotors[1], LOW);
	digitalWrite((*this).myMotors[2], HIGH);
	digitalWrite((*this).myMotors[3], LOW);
}
void robot::stop(){
	Serial.println("stop function");
	digitalWrite((*this).myMotors[0], LOW);
	digitalWrite((*this).myMotors[1], LOW);
	digitalWrite((*this).myMotors[2], LOW);
	digitalWrite((*this).myMotors[3], LOW);
}
//CURRENTLY WORKING ON MOVE ALGORITHM. CONTINUE HERE AND/OR IN THE DRIVEFORWARD/TURN FUNCTIONS
void robot::moveToHopper(){
}
void robot::moveToGameboard(){
}
void robot::grabBall(){
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

int robot::getCurrentState(){return (*this).currentState;}

void robot::doTaskA(){
	//        Serial.println("In function A");
  	(*this).currentState = 2;
	return;
}

void robot::doTaskB(){
    (*this).driveForward(4);
    (*this).turnLeft();
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
int outputPinsArray[14] = {4,5,30,31,32,33,9,10,42,44,46,48,50,52};
int inputPinsArray[6] = {43,45,47,49,51,53};

robot myRobot;

void setup(){
	
	Serial.begin(9600);
        for(int i = 0; i < sizeof(outputPinsArray)/sizeof(outputPinsArray[0]); ++i){
                Serial.println(outputPinsArray[i]);
		pinMode(outputPinsArray[i], OUTPUT);
	}
	for(int i = 0; i < sizeof(inputPinsArray)/sizeof(inputPinsArray[0]); ++i){
         	pinMode(inputPinsArray[i], INPUT);
	}
        Serial.println("END OF SETUPS");
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
