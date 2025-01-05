#include "utils/timer.h"
#include <chrono>
#include <iostream>
#include <string>

SgNet::Timer::Timer() {
	
}


double SgNet::Timer::timeStop(std::string message) {

	if (muted == true) {
		return 0.0;
	}

	auto curTime = std::chrono::high_resolution_clock::now();

	auto recentDuration = std::chrono::duration_cast<std::chrono::milliseconds>(curTime - recentTime);

	std::cout << "\nTime Log\n";
	std::cout << "\t - " << message << "\n";
	std::cout << "\t - Time since previous call: " << recentDuration.count() << " ns\n";

	recentTime = curTime;
    return recentDuration.count();
}

void SgNet::Timer::logTotalElapsedTime() {

	if (muted == true) {
		return;
	}

	auto curTime = std::chrono::high_resolution_clock::now();
	auto totalDuration = std::chrono::duration_cast<std::chrono::milliseconds>(curTime - startTime);
	std::cout << "\nTotal time elapsed: " << totalDuration.count() << "\n";

}

void SgNet::Timer::start() {
	if (muted == true) {
		return;
	}
	std::cout << "\nStarting Timer...\n";
	startTime = std::chrono::high_resolution_clock::now();
	recentTime = startTime;
}

void SgNet::Timer::log() {
	
}

void SgNet::Timer::mute() {
	muted = true;
}

void SgNet::Timer::unmute() {
	muted = false;
}