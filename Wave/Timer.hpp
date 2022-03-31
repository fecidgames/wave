#pragma once

#include <chrono>

class Timer {
public:
	void start() {
		startTime = std::chrono::system_clock::now();
		running = true;
	}

	void stop() {
		endTime = std::chrono::system_clock::now();
		running = false;
	}

	int getElapsedMilliseconds() {
		std::chrono::time_point<std::chrono::system_clock> endTime;
		if(running)
			endTime = std::chrono::system_clock::now();
		else 
			endTime = this->endTime;

		return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	}

	std::chrono::milliseconds getChronoMilliseconds() {
		std::chrono::time_point<std::chrono::system_clock> endTime;
		if(running)
			endTime = std::chrono::system_clock::now();
		else 
			endTime = this->endTime;

		return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
	}

private:
	std::chrono::time_point<std::chrono::system_clock> startTime;
	std::chrono::time_point<std::chrono::system_clock> endTime;
	bool running = false;
};
