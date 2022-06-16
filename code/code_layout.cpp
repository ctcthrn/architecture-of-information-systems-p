#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

const int MSG_SIZE = 2;
const int SERVER_PORT = 3425;

enum class Event
{
	PRESS_ON,
	PRESS_OFF,
	MOVE,
	TURN,
	TURN_SPRAY_GUN,
	PAINT
};

enum class States
{
	OFF,
    AWAITING,
	GETTING_COORDINATES,
	MOVING_STRAIGHT,
	TURNING,
	TURNING_SPRAY_GUN,
	PAINTING
};

class Engine
{
public:
    void run();
}

class SprayGun
{
public:
    void turn();
    void spray();
}

class Robot {
	States state;
    const StrategyCommand* cmdrcv;
    const Engine* eng;
    const SprayGun* gun;
public:

    Robot(const StrategyCommand &cmd, const Engine &engines, const SprayGun &spg): cmdrcv(cmd), eng(engines), gun(spg) {}

	void proc_event(const Event& e)
	{
		switch (e)
		{
		case Event::PRESS_ON:
			on();
			state = States::AWAITING;
			break;

		case Event::PRESS_OFF:
			off();
			state = States::OFF;
			break;

		case Event::MOVE:
			state = States::MOVING_STRAIGHT;
            move();
			state = States::AWAITING;
			break;

		case Event::TURN:
			state = States::TURNING;
            turn();
            state = States::AWAITING;
			break;

		case Event::TURN_SPRAY_GUN:
            state = States::TURNING_SPRAY_GUN;
			turn_spray_gun();
			state = States::AWAITING;
			break;

		case Event::PAINT:
            state = States::PAINTING;
			start_painting();
			state = States::AWAITING;
			break;

		default:
            cout << "Error while processing event" << endl;
		}
	}

    void run()
    {
        while (true)
            this->proc_event(cmdrcv->getEvent());
    }

	void on() {
		//starting procedures
	}

	void off() {
		//stopping procedures
	}

	void move() {
        eng[0].run();
        eng[1].run();
		//run engines
	}

	void turn() {
        eng[0].run();
		//run engines
	}

	void turn_spray_gun() {
        gun.turn();
		//turn spray gun
	}

	void paint() {
        gun.spray();
		//paint
	}
};

//СТРАТЕГИЯ
class StrategyCommand
{
public:
	virtual Event getEvent() = 0;
};

class InternetCommand : public StrategyCommand
{
    int sock;
    struct sockaddr_in addr;
    char buf[MSG_SIZE+1];
    int bytes_read;

public:
    InternetCommand()
    {
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        
        addr.sin_family = AF_INET;
        addr.sin_port = htons(SERVER_PORT);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);

        this->Connect();
    }

    void Connect()
    {
        if(bind(sock, (struct sockaddr*)&addr, sizeof(addr))<0)
        {
            cout << "Error couldnt bind" << endl;
        }
    }

	Event getEvent()
    {
        bytes_read = recvfrom(sock, buf, MSG_SIZE, 0, NULL, NULL);
        buf[MSG_SIZE] = '\0';

        
        switch (buf[0])
        {
        case '0':
            return Event::PRESS_OFF;

        case '1':
            return Event::PRESS_ON;

        case 'm':
            return Event::MOVE;

        case 't':
            return Event::TURN;

        case 's':
            return Event::TURN_SPRAY_GUN;

        case 'p':
            return Event::PAINT;

        default:
            cout << "incorrect" << endl;
        }

    }

    ~InternetCommand()
    {
        delete[] buf;
        close(sock);
    }
};

class ConsoleCommand : public StrategyCommand
{
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
				return Event::TURN;

			case 's':
				return Event::TURN_SPRAY_GUN;

			case 'p':
				return Event::PAINT;

			default:
				cout << "incorrect" << endl;
			}
		}
	}
};

int main()
{
	Robot r;
	StrategyCommand* cmd = new ConsoleCommand();

    r.run(cmd);
}
