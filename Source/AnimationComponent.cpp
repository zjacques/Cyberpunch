#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(SDL_Rect & overallSize, SDL_Rect & frameSize, int frames, float duration, bool loop) :
	m_loop(loop),
	m_duration(duration),
	m_maxFrames(frames),
	m_completed(false),
	m_currentFrame(0),
	m_timeGone(0)
{
	//Get the time per frame
	m_timePerFrame = m_duration / m_maxFrames;
}

void AnimationComponent::setLoop(bool loop)
{
	m_loop = loop;
	//If loop is true, set completed to false, else set it to true
	if(m_currentFrame >= m_maxFrames)
		m_completed = loop ? false : true;
}

bool & AnimationComponent::getLoop()
{
	return m_loop;
}

bool & AnimationComponent::getCompleted()
{
	return m_completed;
}

int & AnimationComponent::getCurrentFrame()
{
	return m_currentFrame;
}

int & AnimationComponent::getMaxFrames()
{
	return m_maxFrames;
}

float & AnimationComponent::getTimeGone()
{
	return m_timeGone;
}

float & AnimationComponent::getTimePerFrame()
{
	return m_timePerFrame;
}
