#pragma once
#include "Component.h"

class Entity
{
public:
	Entity(std::string name) : m_name(name) {};
	void addComponent(std::string name, Component& c) { components[name] = &c; }
	void removeComponent(std::string& name) { components.erase(name); }
	Component& getComponent(std::string name) { return *components[name]; }
	std::string& getName() { return m_name; }
private:
	std::map<std::string, Component*> components; //Collection of components
	std::string m_name; //Name of the entitiy
};
