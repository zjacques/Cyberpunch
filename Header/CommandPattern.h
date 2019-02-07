#ifndef COMMANDPATTERN_H
#define COMMANDPATTERN_H

#include "MovementSystem.h"

class Command
{
	public:
		virtual ~Command() = 0;
		virtual void execute(MovementSystem& moveSystem) = 0;

private:
	//Command * move_up;
	//Command *move_down;
	//Command *move_left;
	//Command *move_right;
	//Command *jump;

	//std::map <int, Command*> commands;


	//bool input_mapping();
	//void dispatcher(std::vector<Command*> &command_queue);

	//void keydown(SDL_Event &event);
	//void keyup(SDL_Event &event);

	//bool is_held(int key);
	//bool was_pressed(int key);


};

class MoveRightCommand : public Command
{
public:
	void execute(MovementSystem& moveSystem)
	{
		moveSystem.Right();
	}
private:
};


#endif // !COMMANDPATTERN_H

