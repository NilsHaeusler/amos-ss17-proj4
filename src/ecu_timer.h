/**
 * @file ecu_timer.h
 *
 */

#ifndef ECU_TIMER_H
#define ECU_TIMER_H

#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <errno.h>
#include <mutex>
#include <chrono>

class EcuTimer {
public:
    EcuTimer();
    EcuTimer(const EcuTimer& orig)= default;
    virtual ~EcuTimer() = default;
    void start(int ms);
    void reset();

private:
    std::mutex mutex_;
    useconds_t duration_; // [ms]
    std::chrono::system_clock::time_point t_start_;
    int t_id_;

    void sleep();
    virtual void wakeup() = 0;  // overwrite this in derived timers
};


#endif /* ECU_TIMER_H */
