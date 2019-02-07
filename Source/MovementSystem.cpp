#include "MovementSystem.h"
#include "Player.h"


MovementSystem::MovementSystem(InputSystem * input) :
	m_inputPtr(input)
{
}

void MovementSystem::update(double dt)
{

}

void MovementSystem::addComponent(Component * comp)
{
}

void MovementSystem::addPlayer(Player * player)
{
	m_player = player;
}

void MovementSystem::Jump() {
	m_player->jump();
}

void MovementSystem::Left() {
	m_player->moveLeft();
}

void MovementSystem::Right() {
	m_player->moveRight();
}

void MovementSystem::Kick() {


}

void MovementSystem::crouch() {


}