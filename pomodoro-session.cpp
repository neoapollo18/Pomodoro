#include "pomodoro-session.h"
#include <sstream>
#include <iomanip>

PomodoroSession::PomodoroSession(SessionType t, int mins)
    : type(t), timeLeft(mins * 60), task(""), running(false) {}

void PomodoroSession::tick() {
    if (running && timeLeft > 0) {
        timeLeft--;
    }
    if (timeLeft <= 0) {
        running = false;
    }
}

std::string PomodoroSession::formatTime() const {
    int mins = timeLeft / 60;
    int secs = timeLeft % 60;
    
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << mins << ":"
        << std::setfill('0') << std::setw(2) << secs;
    return oss.str();
}
