#ifndef POMODORO_TRACKER_H
#define POMODORO_TRACKER_H

#include "pomodoro-session.h"
#include <memory>

class PomodoroTracker {
private:
    std::shared_ptr<PomodoroSession> current;
    int count;

public:
    PomodoroTracker();
    
    void startWork(const std::string& task = "");
    void startBreak();
    void finish();
    
    std::shared_ptr<PomodoroSession> getCurrent() const { return current; }
    int getCount() const {return count; }
    bool isActive() const {return current != nullptr && current->isRunning();}
};

#endif
