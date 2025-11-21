# Pomodoro Timer

A simple C++ pomodoro timer I made for studying.

## What it does

- 25 minute work sessions
- 5 minute breaks
- Tracks how many sessions you've done
- Simple terminal interface

## How to build

```bash
make
```

## How to run

```bash
./pomodoro
```

## Usage

Just pick an option from the menu. Pretty straightforward.

The timer will count down and show a progress bar. Press Ctrl+C if you need to exit early.

## Files

- `pomodoro-session.h/cpp` - handles individual timer sessions
- `pomodoro-tracker.h/cpp` - keeps track of all your sessions
- `pomodoro.cpp` - main program

## Notes

The Pomodoro Technique is supposed to help you focus by breaking work into intervals. Work for 25 min, break for 5, repeat.

## Building

You need g++ with C++11 support. Should work on Mac/Linux. Probably works on Windows with MinGW but I haven't tested it.

To clean up:
```bash
make clean
```
