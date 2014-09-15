/**
 * @file Thread.h
 * @version 1.0
 * @date 2013-2014
 * @copyright see License section
 *
 * @brief Various classes for multithreading tasks.
 * 
 * @section License
 * Copyright (c) 2013-2014 California Institute of Technology.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies, 
 * either expressed or implied, of the California Institute of Technology.
 * 
 */

#pragma once
#include <pthread.h>
#include <semaphore.h>


/**
 * @brief Encapsulates a thread and contains methods for starting 
 * and stopping one.
 */
class Thread
{
public:
    /**
     * @brief Initializes the thread.
     */
    Thread() : running_(false)
    { /* Empty */ }


    /** 
     * @brief Deinitializes the thread.
     */
    ~Thread()
    {
        kill();
    }


    /**
     * @brief Runs this thread now.
     *
     * @param[in] f The function that is to be run by this
     * thread.
     *
     * @param[in] arg The argument to pass to `f`.
     */
    void run( void* f(void*), void * arg)
    {
        pthread_create(&t_, NULL, f, arg);
        running_ = true;
    }


    /**
     * @brief Wait for this thread to finish before continuing.
     */
    void join()
    {
        if (running_)
            pthread_join(t_, NULL);
        running_ = false;
    }


    /**
     * @brief Stop this thread *now*.
     */
    void kill()
    {
        if (running_)
        {
            pthread_cancel(t_);
            pthread_join(t_, NULL);
        }
        running_ = false;
    }

private:
    Thread(const Thread&);
    const Thread& operator=(const Thread&);

    bool running_;
    pthread_t t_;
};


/**
 * @brief Encapsulates a mutex.
 */
class Mutex
{
public:
    /**
     * @brief Initializes the mutex.
     */
    Mutex()
    {
        pthread_mutex_init(&m_, NULL);
    }


    /**
     * @brief Deinitializes the mutex.
     */
    ~Mutex()
    {
        pthread_mutex_destroy(&m_);
    }


    /**
     * @brief Locks the mutex so it cannot be locked by any
     * other thread.
     */
    void lock()
    {
        pthread_mutex_lock(&m_);
    }


    /**
     * @brief Unlocks the mutex so it can be locked by other
     * threads.
     */
    void unlock()
    {
        pthread_mutex_unlock(&m_);
    }

private:
    pthread_mutex_t m_;
};


/**
 * @brief Encapsulates a semaphore.
 */
class Semaphore
{
public:
    /**
     * @brief Initializes the semaphore.
     */
    Semaphore(int value = 0)
    {
        sem_init(&sem_, 0, value);
    }


    /**
     * @brief Deinitializes the semaphore.
     */
    ~Semaphore()
    {
        sem_destroy(&sem_);
    }


    /**
     * @brief Increments the count on this semaphore.
     */
    void inc()
    {
        sem_post(&sem_);
    }


    /**
     * @brief Decrements the count on this semaphore.
     */
    void dec()
    {
        sem_wait(&sem_);
    }


    /**
     * @brief Gets the value of this semaphore.
     *
     * @return The current count.
     */
    int value()
    {
        int ret;
        sem_getvalue(&sem_, &ret);
        return ret;
    }

private:
    sem_t sem_;
};

