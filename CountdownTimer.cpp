#include <algorithm>
#include <chrono>
#include <string>
#include "CountdownTimer.h"

long CountdownTimer::_getMillis()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

CountdownTimer::CountdownTimer(int seconds) {
    _seconds = seconds;
    _isStarted = false;
    _isPaused = false;
    _startedAt = -1;
}

void CountdownTimer:: Start() {
    _startedAt = _getMillis();
    _isStarted = true;
}

void CountdownTimer::Pause() {
    _seconds = GetRemainingSeconds();
    _isPaused = true;
}

void CountdownTimer::Resume() {
    _startedAt = _getMillis();
    _isPaused = false;
}

bool CountdownTimer::IsPaused() {
    return _isPaused;
}

long CountdownTimer::GetRemainingSeconds() {
    if (_isStarted && !_isPaused) {
        long elapsedSecs = (_getMillis() - _startedAt) / 1000;
        return std::max(_seconds - elapsedSecs, (long)0);
    }
    else {
        return _seconds;
    }
}

std::string CountdownTimer::GetRemainingTime() {
    long remaining_seconds = GetRemainingSeconds();
    int minutes = remaining_seconds / 60;
    int seconds = remaining_seconds % 60;

    std::string minutes_string = std::to_string(minutes);
    if (minutes < 10) {
        minutes_string = "0" + minutes_string;
    }

    std::string seconds_string = std::to_string(seconds);
    if (seconds < 10) {
        seconds_string = "0" + seconds_string;
    }

    return minutes_string + ":" + seconds_string;
}