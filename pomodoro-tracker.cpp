#include "pomodoro-tracker.h"
#include <iostream>

PomodoroTracker::PomodoroTracker(int work, int shortBreak, int longBreak)
    : currentSession(nullptr), workSessionsCompleted(0), totalWorkMinutes(0),
      workDuration(work), shortBreakDuration(shortBreak), longBreakDuration(longBreak) {}

void PomodoroTracker::startWorkSession(const std::string& taskName) {
    if (hasActiveSession()) {
        std::cout << "Please complete or cancel the current session first.\n";
        return;
    }
    
    currentSession = std::make_shared<PomodoroSession>(
        PomodoroSession::SessionType::WORK,
        workDuration,
        taskName
    );
    currentSession->start();
    sessions.push_back(currentSession);
}

void PomodoroTracker::startBreak(bool isLongBreak) {
    if (hasActiveSession()) {
        std::cout << "Please complete or cancel the current session first.\n";
        return;
    }
    
    PomodoroSession::SessionType breakType = isLongBreak 
        ? PomodoroSession::SessionType::LONG_BREAK
        : PomodoroSession::SessionType::SHORT_BREAK;
    
    int breakDuration = isLongBreak ? longBreakDuration : shortBreakDuration;
    
    currentSession = std::make_shared<PomodoroSession>(breakType, breakDuration);
    currentSession->start();
    sessions.push_back(currentSession);
}

void PomodoroTracker::pauseCurrentSession() {
    if (currentSession) {
        currentSession->pause();
    }
}

void PomodoroTracker::completeCurrentSession() {
    if (currentSession) {
        currentSession->complete();
        
        if (currentSession->getType() == PomodoroSession::SessionType::WORK) {
            workSessionsCompleted++;
            totalWorkMinutes += workDuration;
        }
        
        currentSession = nullptr;
    }
}

void PomodoroTracker::printStats() const {
    std::cout << "\n--- Your Stats ---\n";
    std::cout << "Sessions completed: " << workSessionsCompleted << "\n";
    std::cout << "Total study time: " << totalWorkMinutes << " minutes\n";
    std::cout << "------------------\n\n";
}

void PomodoroTracker::printCurrentSession() const {
    if (!currentSession) {
        std::cout << "No session running right now\n";
        return;
    }
    
    std::cout << "\nCurrent session:\n";
    std::cout << "Time left: " << currentSession->getFormattedTimeRemaining() << "\n";
    
    if (!currentSession->getTaskName().empty()) {
        std::cout << "Task: " << currentSession->getTaskName() << "\n";
    }
    std::cout << "\n";
}

