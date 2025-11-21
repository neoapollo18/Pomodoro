#include "pomodoro-tracker.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printHeader() {
    std::cout << CYAN << "\n=== Pomodoro Timer ===\n" << RESET;
}

void printMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Start work session\n";
    std::cout << "2. Start break\n";
    std::cout << "3. View current session\n";
    std::cout << "4. View stats\n";
    std::cout << "5. Settings\n";
    std::cout << "6. Complete session\n";
    std::cout << "0. Quit\n";
    std::cout << "\nChoice: ";
}

void runTimer(PomodoroTracker& tracker) {
    auto session = tracker.getCurrentSession();
    if (!session) return;
    
    int totalSeconds = 25 * 60; 
    for (int elapsed = 0; elapsed <= totalSeconds; elapsed++) {
        if (session->getStatus() != PomodoroSession::SessionStatus::IN_PROGRESS) {
            break;
        }
        
        int remaining = totalSeconds - elapsed;
        session->updateRemainingTime(remaining);
        
        clearScreen();
        std::cout << "\nTimer: " << session->getFormattedTimeRemaining() << "\n";
        
        if (!session->getTaskName().empty()) {
            std::cout << "Working on: " << session->getTaskName() << "\n";
        }
        
        // simple progress bar
        int barWidth = 30;
        float progress = (float)elapsed / totalSeconds;
        int filled = (int)(barWidth * progress);
        
        std::cout << "[";
        for (int i = 0; i < barWidth; i++) {
            if (i < filled) std::cout << "=";
            else std::cout << " ";
        }
        std::cout << "]\n";
        
        if (remaining <= 0) {
            std::cout << GREEN << "Done!\n" << RESET;
            tracker.completeCurrentSession();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void settingsMenu(PomodoroTracker& tracker) {
    clearScreen();
    
    std::cout << "\nSettings:\n";
    std::cout << "1. Work time (current: " << tracker.getWorkDuration() << " min)\n";
    std::cout << "2. Break time (current: " << tracker.getShortBreakDuration() << " min)\n";
    std::cout << "3. Back\n";
    std::cout << "\nChoice: ";
    
    int choice;
    std::cin >> choice;
    
    if (choice == 1 || choice == 2) {
        std::cout << "New duration (min): ";
        int duration;
        std::cin >> duration;
        
        if (duration > 0) {
            if (choice == 1) tracker.setWorkDuration(duration);
            else tracker.setShortBreakDuration(duration);
            std::cout << "Updated!\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    PomodoroTracker tracker;
    bool running = true;
    
    std::cout << "Pomodoro Timer\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    while (running) {
        clearScreen();
        printHeader();
        
        std::cout << "Completed: " << tracker.getWorkSessionsCompleted() 
                  << " sessions (" << tracker.getTotalWorkMinutes() << " min)\n";
        
        printMenu();
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1: {
                std::cout << "Task name: ";
                std::string taskName;
                std::getline(std::cin, taskName);
                
                tracker.startWorkSession(taskName);
                std::cout << "Starting work session...\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                runTimer(tracker);
                break;
            }
            case 2:
                tracker.startBreak(false);
                std::cout << "Break time!\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                runTimer(tracker);
                break;
            case 3:
                tracker.printCurrentSession();
                std::cout << "Press enter...";
                std::cin.get();
                break;
            case 4:
                tracker.printStats();
                std::cout << "Press enter...";
                std::cin.get();
                break;
            case 5:
                settingsMenu(tracker);
                break;
            case 6:
                tracker.completeCurrentSession();
                std::cout << "Session completed\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                break;
            case 0:
                std::cout << "\nBye!\n";
                running = false;
                break;
            default:
                std::cout << "Invalid choice\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    
    return 0;
}
