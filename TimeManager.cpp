#include "stdafx.h"
#include "TimeManager.h"

TimeManager::TimeManager()
	:beginTime_(std::chrono::steady_clock::now()),
	endTime_(std::chrono::steady_clock::now()),
	duration_(0.0)
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Tick()
{
	endTime_ = std::chrono::steady_clock::now();
	duration_ = endTime_ - beginTime_;
	beginTime_ = std::chrono::steady_clock::now();
}

int TimeManager::GetElapsedTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(duration_).count();
}
