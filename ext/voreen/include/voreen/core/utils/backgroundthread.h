/***********************************************************************************
 *                                                                                 *
 * Voreen - The Volume Rendering Engine                                            *
 *                                                                                 *
 * Copyright (C) 2005-2013 University of Muenster, Germany.                        *
 * Visualization and Computer Graphics Group <http://viscg.uni-muenster.de>        *
 * For a list of authors please refer to the file "CREDITS.txt".                   *
 *                                                                                 *
 * This file is part of the Voreen software package. Voreen is free software:      *
 * you can redistribute it and/or modify it under the terms of the GNU General     *
 * Public License version 2 as published by the Free Software Foundation.          *
 *                                                                                 *
 * Voreen is distributed in the hope that it will be useful, but WITHOUT ANY       *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR   *
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.      *
 *                                                                                 *
 * You should have received a copy of the GNU General Public License in the file   *
 * "LICENSE.txt" along with this file. If not, see <http://www.gnu.org/licenses/>. *
 *                                                                                 *
 * For non-commercial academic use see the license exception specified in the file *
 * "LICENSE-academic.txt". To get information about commercial licensing please    *
 * contact the authors.                                                            *
 *                                                                                 *
 ***********************************************************************************/

#ifndef VRN_BACKGROUNDTHREAD_H
#define VRN_BACKGROUNDTHREAD_H

#include "voreen/core/voreencoreapi.h"

#include <boost/thread.hpp>

namespace voreen {

/**
 * Provides an encapsulation of a boost::thread object.
 * When deriving classes from this, be sure
 * <ul>
 * <li> not to use logger output within the code actually executed by the worker thread as it is not thread-safe
 * <li> to set interruption points using interruptionPoint() within threadMain() method (thread may only be interrupted at those points)
 * <\ul>
 */
class VRN_CORE_API BackgroundThread {

    public:

        BackgroundThread() : finished_(false), running_(false) {}

        /**
         * Destructor waits for internal thread to finish (does NOT interrupt it... for interruption, interrupt()
         * or interruptAndJoin() has to be called first).
         *
         * If the destructor of a derived class destroys data the internal thread is working on, join() or interruptAndJoin()
         * have to be called within the destructor of the derived class (before destroying the data!) or (outside the destructor)
         * before destroying the (derived) thread object, as otherwise the internal thread may still try to access the data.
         */
        virtual ~BackgroundThread();

        /// Call this method to start the internal thread. If it is already running, it is interrupted before starting the new computation.
        virtual void run();

        /// wait for the thread to finish
        virtual void join();

        /// sends and interrupt signal to the internal thread, but does not wait for it to finish
        virtual void interrupt();

        /// interrupts the internal thread and waits for it to finish
        virtual void interruptAndJoin();

        /// indicates if the background computation is finished
        virtual bool isFinished() { return finished_;}

        /// indicates if the background thread is currently running
        virtual bool isRunning() { return running_;}

    protected:

        /// overwrite this method that the internal thread is supposed to execute
        virtual void threadMain() = 0;

        /// Overwrite for clean-ups. Is called in case a running background thread is interrupted (ie. interrupt()-call or interruptAndJoin()-call).
        virtual void handleInterruption() {}

        /// Sets an interruption point. Worker thread may only be interrupted during execution of threadMain() when arriving at such a point.
        inline void interruptionPoint() {
            boost::this_thread::interruption_point();
        }

        /// calls threadMain and sets flag if finished. If interrupted handleInterruption() is called
        virtual void execute();

        boost::thread internalThread_; ///< the actual boost::thread object

        bool finished_; ///< indicates if background computation is complete
        bool running_; ///< indicates if background computation is currently running
};

//-------------------------------------------------------------------------------------------------

/**
 * Worker thread for a processor, automatically invalidates processor when finished.
 * When using a class derived from this template, T must be derived from Processor class.
 *
 * ATTENTION - if calling join() from process() method in associated processor, it is necessary to first call unlockMutex()
 *  (and afterwards call lockMutex()), because at the end of its computations the background thread tries to lock the mutex
 *  before invalidating the processor, which otherwise would lead to deadlock. The same goes for calling the destructor within process()
 *  (as it contains an implicit join()) and interruptAndJoin(), because the interrupt signal might arrive at the thread
 *  when computation is finished and the thread will not be interrupted before trying to lock the mutex.
 *
 * If the destructor of a derived class destroys data the internal thread is working on, join() or interruptAndJoin()
 * have to be called within the destructor of the derived class (before destroying the data!) or (outside the destructor)
 * before destroying the (derived) thread object, as otherwise the internal thread may still try to access the data.
 */
template <class T>
class ProcessorBackgroundThread : public BackgroundThread {

    public:

        ProcessorBackgroundThread(T* p) : BackgroundThread(), processor_(p) {}

    protected:

        /// locks the mutex of the associated processor
        void lockProcessorMutex() {
            if (processor_)
                processor_->lockMutex();
        }

        /// unlocks the mutex of the associated processor
        void unlockProcessorMutex() {
            if (processor_)
                processor_->unlockMutex();
        }

        /// invalidates the associated processor
        void invalidateProcessor() {
            if (processor_)
                processor_->invalidate();
        }

        /// Calls threadMain. If finished: sets flag and invalidates processor. If interrupted handleInterruption() is called.
        void execute() {
            try {
                threadMain();
                running_ = false;
                finished_ = true;

                //invalidate processor
                lockProcessorMutex();
                invalidateProcessor();
                unlockProcessorMutex();
            }
            catch (boost::thread_interrupted& /*interruption*/) {
                //thread has been interrupted: handle the interruption
                handleInterruption();
                running_ = false;
                return;
            }
        }

        T* processor_; ///< the processor starting the background thread
};

} //namespace

#endif // VRN_BACKGROUNDTHREAD_H
