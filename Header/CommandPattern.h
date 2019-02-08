#ifndef COMMANDPATTERN_H
#define COMMANDPATTERN_H

#include "MovementSystem.h"

class Command
{
public:
	virtual void execute(MovementSystem& moveSystem) = 0;
};

class MoveRightCommand : public Command
{
public:
	MoveRightCommand(){ }
	void execute(MovementSystem& moveSystem)
	{
		moveSystem.Right();
	}
};

class MoveLeftCommand : public Command
{
public:
	MoveLeftCommand() { }
	void execute(MovementSystem& moveSystem)
	{
		moveSystem.Left();
	}
};

class JumpCommand : public Command
{
public:
	JumpCommand() { }
	void execute(MovementSystem& moveSystem)
	{
		moveSystem.Jump();
	}
};

class JumpDownCommand : public Command
{
public:
	JumpDownCommand() { }
	void execute(MovementSystem& moveSystem)
	{
		moveSystem.JumpDown();
	}
};


#endif // !COMMANDPATTERN_H

