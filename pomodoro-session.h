#ifndef POMODORO_SESSION_H
#define POMODORO_SESSION_H

#include <string>
#include <chrono>

// Session class for tracking pomodoro timers
class PomodoroSession {
public:
    enum class SessionType {
        WORK,
        SHORT_BREAK,
        LONG_BREAK
    };

    enum class SessionStatus {
        NOT_STARTED,
        IN_PROGRESS,
        PAUSED,
        COMPLETED,
        CANCELLED
    };

private:
    SessionType type;
    SessionStatus status;
    int durationMinutes;
    int remainingSeconds;
    std::string taskName;
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;

public:
    PomodoroSession(SessionType type, int duration, const std::string& task = "");
    
    // getters
    SessionType getType() const { return type; }
    SessionStatus getStatus() const { return status; }
    int getRemainingSeconds() const { return remainingSeconds; }
    std::string getTaskName() const { return taskName; }
    
    void setTaskName(const std::string& task) { taskName = task; }
    
    void start();
    void pause();
    void complete();
    void updateRemainingTime(int seconds);
    
    std::string getFormattedTimeRemaining() const;
    bool isActive() const;
};

#endif // POMODORO_SESSION_H

