#include <iostream>
using namespace std;

enum class Event
{
	PRESS_ON,
	PRESS_OFF,
	DETECTED_GRAFFITI,
	MOVE,
	TURN30,
	TURN_SPRAY_GUN,
	START_PAINTING,
	STOP_PAINTING
};

enum class States
{
	ON,
	OFF,
	GETTINGCOORDINATES,
	MOVESTRAIGHT,
	TURN,
	TURNSPRAYGUN,
	PAINTING
};

class Robot {
	States state;
public:

	void pevent(const Event& e)
	{
		switch (e)
		{
		case Event::PRESS_ON:
			on();
			state = States::ON;
			break;

		case Event::PRESS_OFF:
			off();
			state = States::OFF;
			break;

		case Event::MOVE:
			move();
			state = States::MOVESTRAIGHT;
			break;

		case Event::TURN30:
			turn30();
			state = States::TURN;
			break;

		case Event::TURN_SPRAY_GUN:
			turn_spray_gun();
			state = States::TURNSPRAYGUN;
			break;

		case Event::DETECTED_GRAFFITI:
			detected_graffiti();
			state = States::GETTINGCOORDINATES;
			break;

		case Event::START_PAINTING:
			start_painting();
			state = States::PAINTING;
			break;

		case Event::STOP_PAINTING:
			stop_painting();
			state = States::OFF;
			break;
		}
	}

	void on() {
		state = States::ON;
	}

	void off() {
		state = States::OFF;
	}

	void getting_coordinated() {
		state = States::GETTINGCOORDINATES;
	}

	void move() {
		state = States::MOVESTRAIGHT;
	}

	void turn30() {
		state = States::TURN;
	}

	void turn_spray_gun() {
		state = States::TURNSPRAYGUN;
	}

	void start_painting() {
		state = States::PAINTING;
	}

	void stop_painting() {
		state = States::OFF;
	}

	void detected_graffiti() {
		state = States::GETTINGCOORDINATES;
	}
};

class CameraSystem {
	States state;
public:
	void detected_graffiti() {
		state = States::GETTINGCOORDINATES;
	}

	void call_user() {
		state = States::GETTINGCOORDINATES;
	}

	void call_robot_coordinates() {
		state = States::GETTINGCOORDINATES;
	}
};

class ConsoleCommand {
public:
	Event getEvent()
	{
		char c;

		while (true)
		{
			cin >> c;

			switch (c)
			{
			case '0':
				return Event::PRESS_OFF;

			case '1':
				return Event::PRESS_ON;

			case 'm':
				return Event::MOVE;

			case 't':
				return Event::TURN30;

			case 's':
				return Event::TURN_SPRAY_GUN;

			case 'd':
				return Event::DETECTED_GRAFFITI;

			case 'p':
				return Event::START_PAINTING;

			case 'e':
				return Event::STOP_PAINTING;
			default:
				cout << "incorrect";
			}
		}
	}
};

int main() {
	Robot r;
	ConsoleCommand cmd;

	while (true)
	{
		Event e = cmd.getEvent();
		r.pevent(e);
	}
}

