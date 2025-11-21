#ifndef POMODORO_SESSION_H
#define POMODORO_SESSION_H

#include <string>

class PomodoroSession {
public:
    enum class SessionType {
        WORK,
        BREAK
    };

private:
    SessionType type;
    int timeLeft;
    std::string task;
    bool running;

public:
    PomodoroSession(SessionType t, int mins);
    
    SessionType getType() const { return type; }
    int getTimeLeft() const { return timeLeft; }
    std::string getTask() const { return task; }
    bool isRunning() const { return running; }
    
    void setTask(const std::string& t) { task = t; }
    void start() { running = true; }
    void stop() { running = false; }
    void tick();
    
    std::string formatTime() const;
};

#endif
