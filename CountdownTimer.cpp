#include <Arduino.h>
#include "CountdownTimer.h"

CountdownTimer::CountdownTimer(int seconds) {
    _seconds = seconds;
    _isStarted = false;
    _isPaused = false;
    _startedAt = -1;
}

void CountdownTimer:: Start() {
    _startedAt = millis();
    _isStarted = true;
}

void CountdownTimer::Pause() {
    _seconds = GetRemainingSeconds();
    _isPaused = true;
}

void CountdownTimer::Resume() {
    _startedAt = millis();
    _isPaused = false;
}

bool CountdownTimer::IsPaused() {
    return _isPaused;
}

long CountdownTimer::GetRemainingSeconds() {
    if (_isStarted && !_isPaused) {
        long elapsedSecs = (millis() - _startedAt) / 1000;
        return max(_seconds - elapsedSecs, (long)0);
    }
    else {
        return _seconds;
    }
}

String CountdownTimer::GetRemainingTime() {
    long remaining_seconds = GetRemainingSeconds();
    int minutes = remaining_seconds / 60;
    int seconds = remaining_seconds % 60;

    String minutes_string = String(minutes);
    if (minutes < 10) {
        minutes_string = "0" + minutes_string;
    }

    String seconds_string = String(seconds);
    if (seconds < 10) {
        seconds_string = "0" + seconds_string;
    }

    return minutes_string + ":" + seconds_string;
}