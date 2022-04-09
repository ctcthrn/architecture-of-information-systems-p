#include <iostream>
using namespase std;

enum Event
{
	PRESS_ON,
	PRESS_OFF
}

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
  
  void pevent(const Event& e)
  {
   	switch(e)
	{
		case Event::PRESS_ON:
			on();
			state = States::ON;
			break;
			
		case Event::PRESS_OFF:
			off();
			state = States::OFF;
			break;
	}
  }
  
  void on(){
  }

  void off(){
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

class ConsoleCommand()
{
public:
	Event getCommand()
	{
		char c;
		cin >> c;
		
		switch(c):
		{
			case '0':
				return Event::PRESS_OFF;
				
			case '1':
				return Event::PRESS_ON;
		}
	}
}

int main(){
	Robot r;
	ConsoleCommand cmd;
	
	while (true)
	{
		Event e = cmd.getEvent();
		r.pevent(e);
	}
}
