#include "pomodoro-session.h"
#include <sstream>
#include <iomanip>

PomodoroSession::PomodoroSession(SessionType type, int duration, const std::string& task)
    : type(type), status(SessionStatus::NOT_STARTED), durationMinutes(duration),
      remainingSeconds(duration * 60), taskName(task) {}

void PomodoroSession::start() {
    status = SessionStatus::IN_PROGRESS;
    startTime = std::chrono::system_clock::now();
}

void PomodoroSession::pause() {
    if (status == SessionStatus::IN_PROGRESS) {
        status = SessionStatus::PAUSED;
    }
}

void PomodoroSession::complete() {
    status = SessionStatus::COMPLETED;
    endTime = std::chrono::system_clock::now();
    remainingSeconds = 0;
}

void PomodoroSession::updateRemainingTime(int seconds) {
    remainingSeconds = seconds;
    if (remainingSeconds <= 0) {
        complete();
    }
}

std::string PomodoroSession::getFormattedTimeRemaining() const {
    int minutes = remainingSeconds / 60;
    int seconds = remainingSeconds % 60;
    
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << seconds;
    return oss.str();
}

bool PomodoroSession::isActive() const {
    return status == SessionStatus::IN_PROGRESS || status == SessionStatus::PAUSED;
}

