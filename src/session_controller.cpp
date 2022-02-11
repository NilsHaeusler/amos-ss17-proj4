/**
 * @file session_controller.cpp
 *
 */

#include "session_controller.h"
#include <iostream>

using namespace std;

/**
 * Starts an UDS session. The session expires after 5000 milliseconds without
 * a reset/extension message and returns to the default-session state.
 * 
 * @see SessionController::setCurrentUdsSession()
 */
void SessionController::startSession()
{
    start(5000);
}

/**
 * Returns the current UDS session state.
 *
 * @return the active UDS state
 */
UdsSession SessionController::getCurrentUdsSession() const noexcept
{
    return session_;
}

/**
 * Sets the current UDS session state.
 * 
 * @param ses: the UDS session enum to set
 */
void SessionController::setCurrentUdsSession(const UdsSession ses) noexcept
{
    if (ses == UdsSession::DEFAULT
        || ses == UdsSession::PROGRAMMING
        || ses == UdsSession::EXTENDED)
    {
        session_ = ses;
    }
    else
    {
        cerr << "switch to unkown session: " << ses << endl;
    }
}

/**
 * Overridden function which is called after the timer expired. Since the
 * `session_`-member is atomic, we don't need to use a mutex.
 */
void SessionController::wakeup()
{
    if (session_ == UdsSession::DEFAULT)
    {
        cout << "timer finished - DEFAULT" << endl;
    }
    else if (session_ == UdsSession::PROGRAMMING)
    {
        cout << "timer finished - PROGRAMMING" << endl;
    }
    else if (session_ == UdsSession::EXTENDED)
    {
        cout << "timer finished - EXTENDED" << endl;
    }

    session_ = UdsSession::DEFAULT;
}
