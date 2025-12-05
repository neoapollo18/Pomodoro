#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
private:
    std::string name;
    int completedWorkSessions;

public:
    Task(const std::string& taskName);

    std::string getName() const;
    int getCompletedWorkSessions() const;

    void incrementCompleted();
};

#endif
