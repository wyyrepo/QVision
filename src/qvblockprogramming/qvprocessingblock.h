/*
 *	Copyright (C) 2007, 2008, 2009, 2010, 2011, 2012. PARP Research Group.
 *	<http://perception.inf.um.es>
 *	University of Murcia, Spain.
 *
 *	This file is part of the QVision library.
 *
 *	QVision is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as
 *	published by the Free Software Foundation, version 3 of the License.
 *
 *	QVision is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public
 *	License along with QVision. If not, see <http://www.gnu.org/licenses/>.
 */

/// @file
/// @brief File from the QVision library.
/// @author PARP Research Group. University of Murcia, Spain.

#ifndef QVPROCESSINGBLOCK_H
#define QVPROCESSINGBLOCK_H

#include <QStringList>
#include <QThread>
#include <QTime>

#include <qvblockprogramming/qvcpustatcontroler.h>
#include <QVPropertyContainer>

/*!
@class QVProcessingBlock qvblockprogramming/qvprocessingblock.h QVProcessingBlock
@brief Base class for Block threads.

This class can be used to construct processing blocks for the @ref WorkerDesignPattern. Block threads classes should inherit from QVProcessingBlock, and implement abstract function @ref QVProcessingBlock::iterate, with the body of the function code

For further info about block programming see section @ref IntroductionToBlockProgramming.

@ingroup qvblockprogramming
*/
class QVProcessingBlock: public QThread, public QVPropertyContainer
    {
    Q_OBJECT

    public:
        /// @brief Different states in which a block object can be.
        typedef enum
            {
            /// Block is running. @ref QVProcessingBlock::iterate() function will be called
            /// continuously, until slots @ref pause() or @ref finish() are
            /// called.
            Running,
            /// Block will execute @ref QVProcessingBlock::iterate() function once, and then will
            /// change to @ref Paused status.
            RunningOneStep,
            /// Block is paused. It won't call function @ref QVProcessingBlock::iterate(), or
            /// finish execution thread, until slots @ref unPause() or
            /// @ref finish() are called respectively.
            Paused,
            /// Block is stopped. It won't call function @ref QVProcessingBlock::iterate() (but don't
            /// block its conected sychronous blocks), or finish execution thread,
            /// until slots @ref finish() are called respectively.
            Stopped,
            /// Block is finished. Execution thread ended.
            Finished
            } TBlockStatus;

        /// @brief Constructor for QVProcessingBlock class.
        ///
        /// Inits block, and set it's status to @ref Running.
        /// @param name the (optional) name given to the block.
        QVProcessingBlock(const QString name = QString());

        /// @brief Copy Constructor for the QVProcessingBlock class.
        ///
        /// Creates a new block form a given block.
        /// @param other the given block.
        QVProcessingBlock(const QVProcessingBlock &other);

        /// @brief Destructor for QVProcessingBlock class.
        ~QVProcessingBlock();

        /// @brief Function to be defined in subclasses with processing code.
        ///
        /// This function should contain the code to process data, that will be
        /// executed continuously until block is finished.
        virtual void iterate() { };

        /// @brief Sets a minimum ms delay for each iteration (default is 0)
        ///
        /// This function should be called to establish a minimum delay for
        /// each iteration (that is, it should be used to limit the speed at
        /// which the block iterates). Of course, if the real processing
        /// iteration time is longer than the delay set with this function, it
        /// will not have any visible effect.
        ///
        /// Warning: due to underlying operating system time management
        /// imprecissions, low values (typically under 40 ms) of this parameter
        /// can result in longer delays than expected.
        void setMinimumDelay(int ms) { minms = ms; };

        /// @brief Function that can be used to check finish status of block.
        /// @returns true if block is finished.
        bool isFinished() const { return status == Finished; }

        /// @brief Function that can be used to check paused status of block.
        /// @returns true if block is paused.
        bool isPaused() const { return status == Paused; }

        /// @brief Function that can be used to check stopped status of block.
        /// @returns true if block is stopped.
        bool isStopped() const { return status == Stopped; }

        /// @brief Function that can be used to check running status of block.
        /// @returns true if block is running.
        bool isRunning() const { return status == Running; }

        /// @brief Function to obtain the status of the block.
        /// @returns status of the block.
        TBlockStatus getStatus() const { return status; }

        /// @brief Function to obtain the number of iteration the block has performed.
        /// @returns number of times that the iterate() function has been called.
        int getIteration() const { return numIterations; }

        /// @brief Function to obtain if the stats are enabled.
        /// @returns if the stats are enabled.
        bool isStatsEnabled() const { return statsEnabled; }

        /// @brief Gets CpuStat object for the block.
        ///
        /// Every block has a @ref CpuStat type object that mantains cpu time
        /// performance for different parts (code fragments) of function
        /// @ref iterate(). This object is updated in method @ref timeFlag(), when
        /// establishing a performance breakpoint in the execution of the block.
        ///
        /// If th stats are disabled, return an empty QVStat.
        ///
        /// @returns constant reference to block's CpuStat object.
        QVStat getCpuStat() const {
            if (statsEnabled) return cpuStatControler->value();
            else return QVStat();
        }

        /// @brief Prints CpuStat object for the block.
        ///
        /// Periodically prints performance statistics for the block.
        /// If the stats are disabled, do nothing.
        ///
        /// @param freq The frequency (iterations) whitch prints the stats.
        ///
        void setPrintStatsFrequency(int freq)
            {
            if (statsEnabled)
                {
                cpuStatControler->setFreq(freq);
                cpuStatControler->setBlockName(getName());
                }
            }

        /// @brief Prints CpuStat object for the block.
        ///
        /// Prints performance statistics for the block.
        /// If the stats are disabled, do nothing.
        ///
        ///
        void printStats()
            {
            if (statsEnabled)
                cpuStatControler->printStats();
            }

        /// @brief Adds a trigger to the block.
        ///
        /// Triggers are just named actions that can be called upon a QVProcessingBlock
        /// to change it's state, initialize itself, or whatever action the
        /// programmer considers convenient, in a completely asynchronous
        /// manner.
        /// When added to a block, they will depict a button in the
        /// corresponding property widget in the interface, that will do a call
        /// to @ref processTrigger() function when pressed.
        ///
        /// This method is provided just for convenience. The same effect could
        /// be achieved just by adding a new slot when subclassing QVProcessingBlock,
        /// and connecting it to a button clicked signal. But using this
        /// generic function avoids the programmer to have to declare the
        /// new block class as a Q_OBJECT, if he just needs the trigger
        /// functionality, and does not want to declare any other signals or
        /// slots in his new block class.
        /// @see processTrigger()
        void addTrigger(QString name)			{ triggerList.push_back(name); }

        /// @brief Returns the list of triggers (as a QStringList) for the block.
        const QStringList getTriggerList() const	{ return triggerList; }

        /// @brief Stablish a performance breakpoint in the execution of the block.
        ///
        /// This function should be used in the body of @ref iterate() function,
        /// to establish a performance breakpoint, at which the execution time will be
        /// statistically measured.
        ///
        /// If the stats are disabled, do nothing.
        ///
        /// These statistics can be plotted through the graphical user interface (see
        /// @ref BlockWidget section at the @ref QVGUI documentation), creating a
        /// @ref QVCPUPlot object, or to the user console if the parameter
        /// <i>--"print stats"=true</i> was used in the application command line.
        void timeFlag(const QString flag)
            {
            qDebug() << "QVProcessingBlock::timeFlag("<< flag <<")";
            if (statsEnabled) cpuStatControler->setFlag(flag);
            }

    public slots:
        /// @brief Set block status to @ref QVProcessingBlock::Paused.
        ///
        void pause() { qDebug() << "QVProcessingBlock::pause()"; status = Paused; emit statusUpdate(status); }

        /// @brief Set block status to @ref QVProcessingBlock::Running.
        ///
        void unPause() { qDebug() << "QVProcessingBlock::unPause()"; status = Running; emit statusUpdate(status); }

        /// @brief Set block status to @ref QVProcessingBlock::RunningOneStep.
        ///
        void step() { qDebug() << "QVProcessingBlock::step()"; status = RunningOneStep; emit statusUpdate(status); }

        /// @brief Finish block execution.
        ///
        void stop() { qDebug() << "QVProcessingBlock::stop()"; status = Stopped; emit statusUpdate(status); }

        /// @brief Finish block execution.
        ///
        void finish() { qDebug() << "QVProcessingBlock::finish()"; status = Finished; emit statusUpdate(status); }

        /// @brief Process trigger activations in the block.
        ///
        /// Triggers are just named actions that can be called upon a QVProcessingBlock
        /// to change it's state, initialize itself, or whatever action the
        /// programmer considers convenient, in a completely asynchronous
        /// manner.
        ///
        /// When added to a block, they will depict a button in the
        /// corresponding property widget in the interface, that will do a call
        /// to @ref QVProcessingBlock::processTrigger() function when pressed.
        /// Use @ref addTrigger to add triggers to a block, and redefine this
        /// function to capture their activations.
        /// @see QVProcessingBlock::addTrigger()
        /// @param name the name of the trigger that was activated.
        virtual void processTrigger(const QString name) { Q_UNUSED(name); }

    signals:
        /// @brief Signal emited before each call to @ref QVProcessingBlock::iterate() function.
        ///
        void startIteration();

        /// @brief Signal emited after each call to @ref QVProcessingBlock::iterate() function.
        ///
        void endIteration(uint id, int iteration);

        /// @brief Signal emited when block changes its status.
        ///
        void statusUpdate(QVProcessingBlock::TBlockStatus);

    private:
        bool statsEnabled;
        QVStatControler *cpuStatControler;
        int numIterations, maxIterations;
        TBlockStatus status;
        QStringList triggerList;
        QTime iterationTime;
        int curms,minms;

    protected:
        void run();
        void blockIterate();
    };

Q_DECLARE_METATYPE(QVStat);
#endif
