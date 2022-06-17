#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <platform/platform.h>
#include <kos_net.h>

#include <iostream>

#define MSG_SIZE 2
#define SERVER_PORT 1106

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


//strategy pattern
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
            std::cerr << "Error couldnt bind" << std::endl;
        }
        std::cerr << "Bind successful" << std::endl;
    }

	Event getEvent()
    {
    	while(1)
    	{
    		std::cerr << "Client is listening!" << std::endl;
		bytes_read = recvfrom(sock, buf, MSG_SIZE, 0, NULL, NULL);
		buf[MSG_SIZE] = '\0';

		std::cerr << "Client received: " << buf << std::endl;
		
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
		    std::cout << "incorrect" << std::endl;
		}
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
			std::cin >> c;

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
				std::cout << "incorrect" << std::endl;
			}
		}
	}
};



class Engine
{
public:
    void run() {}
};

class SprayGun
{
public:
    void turn() {}
    void spray() {}
};

class Robot 
{
private:
	States state;
    StrategyCommand* cmdrcv;
    Engine* eng[2];
    SprayGun* gun;
public:

    Robot(StrategyCommand* cmd, SprayGun* spg): cmdrcv(cmd), gun(spg), eng({new Engine(), new Engine()}) {}

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
			paint();
			state = States::AWAITING;
			break;

		default:
            std::cout << "Error while processing event" << std::endl;
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
        eng[0]->run();
        eng[1]->run();
		//run engines
	}

	void turn() {
        eng[0]->run();
		//run engines
	}

	void turn_spray_gun() {
        gun->turn();
		//turn spray gun
	}

	void paint() {
        gun->spray();
		//paint
	}
};


int main()
{
	StrategyCommand* cmd = new InternetCommand();
	SprayGun* spg = new SprayGun();
	Robot* r= new Robot(cmd, spg);

	std::cerr << "Client has started!" << std::endl;
    r->run();
    
    return EXIT_SUCCESS;
}
