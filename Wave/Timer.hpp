#pragma once

#include <chrono>

class Timer {
public:
	void start() {
		startTime = std::chrono::system_clock::now();
		running = true;
	}

	void pause() {
		pauseTime = std::chrono::system_clock::now();
		paused = true;
	}

	void resume() {
		resumeTime = std::chrono::system_clock::now();
		startTime += (resumeTime - pauseTime);
		paused = false;
	}

	void stop() {
		endTime = std::chrono::system_clock::now();
		running = false;
	}

	int getElapsedMilliseconds() {
		std::chrono::time_point<std::chrono::system_clock> returnTime;
		if(running && !paused) {
			return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startTime).count();
		} else if(paused && running) {
			return std::chrono::duration_cast<std::chrono::milliseconds>(pauseTime - startTime).count();
		} else {
			returnTime = endTime;
		}

		return std::chrono::duration_cast<std::chrono::milliseconds>(returnTime - startTime).count();
	}

	std::chrono::milliseconds getChronoMilliseconds() {
		std::chrono::time_point<std::chrono::system_clock> returnTime;
		if(running && !paused) {
			return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startTime);
		} else if(paused && running) {
			return std::chrono::duration_cast<std::chrono::milliseconds>(pauseTime - startTime);
		} else {
			returnTime = endTime;
		}

		return std::chrono::duration_cast<std::chrono::milliseconds>(returnTime - startTime);
	}

private:
	std::chrono::time_point<std::chrono::system_clock> startTime;
	std::chrono::time_point<std::chrono::system_clock> endTime;

	std::chrono::time_point<std::chrono::system_clock> pauseTime;
	std::chrono::time_point<std::chrono::system_clock> resumeTime;

	bool running = false;
	bool paused = false;
};
