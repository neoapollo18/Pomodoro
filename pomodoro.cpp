#include "pomodoro-tracker.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void runTimer(PomodoroTracker& tracker) {
    auto session = tracker.getCurrent();
    if (!session) return;
    
    while (session->isRunning()) {
        clear();
        
        std::cout << "\n" << session->formatTime() << "\n";
        
        if (!session->getTask().empty()) {
            std::cout << session->getTask() << "\n";
        }
        
        std::cout << "\n";
        
        session->tick();
        
        if (!session->isRunning()) {
            std::cout << "Done!\n";
            tracker.finish();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    PomodoroTracker tracker;
    
    while (true) {
        clear();
        
        std::cout << "\nPomodoro Timer\n";
        std::cout << "Completed: " << tracker.getCount() << "\n\n";
        
        std::cout << "1. Work\n";
        std::cout << "2. Break\n";
        std::cout << "0. Quit\n";
        std::cout << "\n> ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        if (choice == 1) {
            std::cout << "Task: ";
            std::string task;
            std::getline(std::cin, task);
            
            tracker.startWork(task);
            runTimer(tracker);
        } 
        else if (choice == 2) {
            tracker.startBreak();
            runTimer(tracker);
        }
        else if (choice == 0) {
            break;
        }
    }
    
    return 0;
}
