#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

constexpr float MILLI_TO_SEC = 1000.0f;

class Timer
{
public:
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete; // These instances will disable copying and moving constructors for this class
	Timer();
	~Timer();
	void Start();
	void UpdateFrameTicks();
	float GetDeltaTime() const;
	unsigned int GetSleepTime(const unsigned int fps_) const;
	float GetCurrentTickMilli() const;
	float GetCurrentTickSec() const;

private:
	unsigned int PrevTicks;
	unsigned int CurrentTicks;
};

#endif //!TIMER_H