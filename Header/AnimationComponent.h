#pragma once
#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H
#include "Component.h"
#include "SDL.h"

class AnimationComponent : public Component
{
public:
	AnimationComponent(SDL_Rect& overallSize, SDL_Rect& frameSize, int frames, float duration, bool loop);

	void setLoop(bool loop);

	//getters
	bool& getLoop();
	bool& getCompleted();
	int& getCurrentFrame();
	int& getMaxFrames();
	float& getTimeGone();
	float& getTimePerFrame();
private:
	std::vector<SDL_Rect> m_frames; //The frames of the animation
	int m_currentFrame; //The current frame of the animation
	int m_maxFrames; //Maximum frames in the animation
	float m_duration; //The duration of the animation
	float m_timePerFrame; // The time to display each frame
	float m_timeGone; //The time gone since last animation frame
	bool m_loop; //Wheter the animation loops or plays once
	bool m_completed; //Wheter the animation is finished or not
};
#endif