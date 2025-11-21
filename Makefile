# Makefile for Pomodoro Study Tracker

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = pomodoro
OBJS = pomodoro.o pomodoro-session.o pomodoro-tracker.o

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile pomodoro.cpp
pomodoro.o: pomodoro.cpp pomodoro-tracker.h pomodoro-session.h
	$(CXX) $(CXXFLAGS) -c pomodoro.cpp

# Compile pomodoro-session.cpp
pomodoro-session.o: pomodoro-session.cpp pomodoro-session.h
	$(CXX) $(CXXFLAGS) -c pomodoro-session.cpp

# Compile pomodoro-tracker.cpp
pomodoro-tracker.o: pomodoro-tracker.cpp pomodoro-tracker.h pomodoro-session.h
	$(CXX) $(CXXFLAGS) -c pomodoro-tracker.cpp

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET) pomodoro_data.txt

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run

