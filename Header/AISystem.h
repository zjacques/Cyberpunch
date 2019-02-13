#ifndef AISYSTEM_H
#define AISYSTEM_H

#include "System.h"
#include "Component.h"
#include "AIComponent.h"

class AISystem : public System 
{
public:
	void initialiseActions();
	void createTree();
	void runTree();
	void update(double dt);
	void addComponent(Component *);
private:

};

#endif