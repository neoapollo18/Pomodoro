#include "pomodoro-tracker.h"

PomodoroTracker::PomodoroTracker() : current(nullptr), count(0) {}

void PomodoroTracker::startWork(const std::string& task) {
    if (isActive()) return;
    
    current = std::make_shared<PomodoroSession>(PomodoroSession::SessionType::WORK, 25);
    current->setTask(task);
    current->start();
}

void PomodoroTracker::startBreak() {
    if (isActive()) return;
    
    current = std::make_shared<PomodoroSession>(PomodoroSession::SessionType::BREAK, 5);
    current->start();
}

void PomodoroTracker::finish() {
    if (current && current->getType() == PomodoroSession::SessionType::WORK) {
        count++;
    }
    current = nullptr;
}
