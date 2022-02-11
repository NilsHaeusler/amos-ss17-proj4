/**
 * @file ecu_timer.cpp
 *
 */

#include "ecu_timer.h"
#include <iostream>
#include <thread>

using namespace std;
using std::chrono::system_clock;

EcuTimer::EcuTimer() {
    t_id_ = 0;
}

/**
 * Starts the timer. If the timer is already running, calling this function 
 * resets the timer.
 * 
 * @param ms: time value in milliseconds before the timer wakes up
 */
void EcuTimer::start(int ms)
{
    mutex_.lock();
    t_start_ = system_clock::now();
    duration_ = ms;
    t_id_ += 1;
    mutex_.unlock();

    thread t(&EcuTimer::sleep, this);
    t.detach();
    usleep(5000);
}


/**
 * This functions sleeps the appropriate amount of time.
 */
void EcuTimer::sleep()
{
    int id_begin;
    int id_now;
    int duration;

    mutex_.lock();
    id_begin = t_id_;
    duration = duration_;
    mutex_.unlock();

    usleep(useconds_t(duration_) * useconds_t(1000));

    while (true)
    {
        mutex_.lock();
        auto diff = chrono::duration_cast<chrono::milliseconds>(system_clock::now() - t_start_);
        id_now = t_id_;
        duration = duration_;
        mutex_.unlock();

        if (id_begin != id_now)
        {
            return;  // timer has been restarted
        }
        if (diff.count() >= duration)
        {
            break;
        }
        else
        {
            int sleep_for_ms = duration - diff.count();
            usleep(useconds_t(sleep_for_ms) * useconds_t(1000));
        }
    }

    // wakeup procedure depends on the derived class
    // call this only if the timer wasn't restarted
    mutex_.lock();
    bool cond = (id_now == t_id_);
    mutex_.unlock();

    if (cond)
    {
        wakeup();
    }
}

/**
 * Resets the timer.
 */
void EcuTimer::reset()
{
    mutex_.lock();
    t_start_ = system_clock::now();
    mutex_.unlock();
}
