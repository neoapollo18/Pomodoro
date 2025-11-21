#ifndef POMODORO_TRACKER_H
#define POMODORO_TRACKER_H

#include "pomodoro-session.h"
#include <vector>
#include <memory>

// tracks all the pomodoro sessions
class PomodoroTracker {
private:
    std::vector<std::shared_ptr<PomodoroSession>> sessions;
    std::shared_ptr<PomodoroSession> currentSession;
    int workSessionsCompleted;
    int totalWorkMinutes;
    
    int workDuration;
    int shortBreakDuration;
    int longBreakDuration;

public:
    PomodoroTracker(int work = 25, int shortBreak = 5, int longBreak = 15);
    
    void startWorkSession(const std::string& taskName = "");
    void startBreak(bool isLongBreak = false);
    void pauseCurrentSession();
    void completeCurrentSession();
    
    std::shared_ptr<PomodoroSession> getCurrentSession() const { return currentSession; }
    int getWorkSessionsCompleted() const { return workSessionsCompleted; }
    int getTotalWorkMinutes() const { return totalWorkMinutes; }
    bool hasActiveSession() const { return currentSession != nullptr && currentSession->isActive(); }
    
    void setWorkDuration(int minutes) { workDuration = minutes; }
    void setShortBreakDuration(int minutes) { shortBreakDuration = minutes; }
    void setLongBreakDuration(int minutes) { longBreakDuration = minutes; }
    
    int getWorkDuration() const { return workDuration; }
    int getShortBreakDuration() const { return shortBreakDuration; }
    int getLongBreakDuration() const { return longBreakDuration; }
    
    void printStats() const;
    void printCurrentSession() const;
};

#endif // POMODORO_TRACKER_H

