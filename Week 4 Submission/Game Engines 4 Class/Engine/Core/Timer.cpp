#include "Timer.h"

Timer::Timer()
{
	CurrentTicks = 0;
	PrevTicks = 0;
}

Timer::~Timer()
{
}

void Timer::Start()
{
	PrevTicks = CurrentTicks = SDL_GetTicks();
}

void Timer::UpdateFrameTicks()
{
	PrevTicks = CurrentTicks;
	CurrentTicks = SDL_GetTicks();
}

float Timer::GetDeltaTime() const
{
	return (CurrentTicks - PrevTicks) / MILLI_TO_SEC;
}

unsigned int Timer::GetSleepTime(const unsigned int fps_) const
{
	unsigned int milliSecondsPerFrame = MILLI_TO_SEC / fps_;

	if (milliSecondsPerFrame == 0) {
		return 0; // We want to return 0 because there's no calculation of time if it's equal to 0
	}

	unsigned int SleepTime = milliSecondsPerFrame - (SDL_GetTicks() - CurrentTicks);

	if (SleepTime > milliSecondsPerFrame) {
		return milliSecondsPerFrame; // This ensures that the engine will run around at 60 fps (if it's not there then it will run faster than 60 fps
	}

	return SleepTime; // Calculates the amount of time the engine will need to sleep for to maintain 60 fps consistently
}

float Timer::GetCurrentTickMilli() const
{
	return static_cast<float>(CurrentTicks);
}

float Timer::GetCurrentTickSec() const
{
	return CurrentTicks / MILLI_TO_SEC;
}
