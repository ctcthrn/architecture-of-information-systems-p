#include <iostream>
using namespase std;

enum States
{
	ON,
	OFF,
	GETTINGCOORDINATES
	MOVESTRAIGHT,
	TURN,
	TURNSPRAYGUN,
	PAINTING
	
}

class Robot{
 	States state;
 
  void on(){
  	state = States::ON;
  }
  
  void off(){
  	state = States::OFF;
  }
  
  void getting_coordinated(){
  	state = States::GETTINGCOORDINATES;
  }
  
  void move(){
  	state = States::MOVESTRAIGHT;
  }
  
  void turn30(){
  	state = States::TURN;
  }
  
  void spray_gun_wall(){
  	state = States::TURNSPRAYGUN;
  	
  }
  
   void spray_gun_floor(){
  	state = States::TURNSPRAYGUN;
  	
  }
  
  void start_painting(){
  	state = States::PAINTING;
  }
  
  void stop_painting(){
  	state = States::OFF;
  }
}

class CameraSystem{
  States state;
  
  void detected_graffiti(){
  	state = States::GETTINGCOORDINATES;
  } 
  
  void call_user(){
  	state = States::GETTINGCOORDINATES;
  } 
  
  void call_robot_coordinates(){
  	state = States::GETTINGCOORDINATES;
  } 
}

int main(){
}