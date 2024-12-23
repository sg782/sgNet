#pragma once

#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>

namespace SgNet{
    class Timer {

    public:
        std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> recentTime;
        bool muted = false;

        Timer();

        void start();

        double timeStop(std::string message);

        void logTotalElapsedTime();

        void log();

        // for when we have a lot of timers and want a one line function to pause them during debugging
        void mute();
        void unmute();
    };
}




#endif