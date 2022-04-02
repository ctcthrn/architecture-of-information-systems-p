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
public: 
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
public:
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
	Robot r;
	while (true)
	{
		char c;
		cin >> c;
		switch(c)
		{
			case 'm':
				r.move();
				break;
				
			case 't':
				r.turn30();
				break;
			
			case 'f':
				r.spray_gun_floor();
				break;
			
			case 'w':
				r.spray_gun_wall();
				break;
			
			case 'g':
				r.getting_coordinated();
				break;
				
			case '0':
				r.off();
				break;
				
			case '1':
				r.on();
				break;
				
			case '1p':
				r.start_painting();
				break;
				
			case '0p':
				r.stop_painting();
				break;
		}
	
	}
}
