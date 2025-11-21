CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = pomodoro
OBJS = pomodoro.o pomodoro-session.o pomodoro-tracker.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

pomodoro.o: pomodoro.cpp
	$(CXX) $(CXXFLAGS) -c pomodoro.cpp

pomodoro-session.o: pomodoro-session.cpp pomodoro-session.h
	$(CXX) $(CXXFLAGS) -c pomodoro-session.cpp

pomodoro-tracker.o: pomodoro-tracker.cpp pomodoro-tracker.h
	$(CXX) $(CXXFLAGS) -c pomodoro-tracker.cpp

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
