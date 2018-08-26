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

#ifndef QVAPPLICATION_H
#define QVAPPLICATION_H

#include <QSet>
#include <QString>
#include <QStringList>
#include <QApplication>
#include <QMutex>

#include <qvdefines.h>

class QVGUI;
class QVPropertyContainer;
class QVProcessingBlock;
class QVImageCanvas;

#define qvApp ((QVApplication*) qApp)

/*!
@class QVApplication qvblockprogramming/qvapplication.h QVApplication
@brief Main class for QVision applications

This is a class that should be used to create a unique application object in every QVision application, generally in the <i>main()</i> function.

This object should be created before any QVProcessingBlock, QVCamera, QVImageCanvas, or QVDefaultGUI object.
It is similar to a <a href="http://doc.trolltech.com/4.2/qapplication.html">QApplication</a> object in Qt applications not based on QVision.
The QVApplication object object initializes the camera block objects in the application, and sets the block parameters from the command line, amongst other things.

@ingroup qvblockprogramming
*/
class QVApplication : public QApplication
{
	Q_OBJECT
public:
	/// @brief Creates a QVApplication object.
	///
	/// This constructor should receive command line arguments array from the <i>main()</i>
	/// function parameters, in the parameters @ref argc and @ref argv.
	///
	/// @param argc Number of command line arguments.
	/// @param argv Array of arrays of chars containing command line arguments.
	/// @param info Optional QString containing an informational message for
	///        the application (shown when asked for help).
	/// @param GUIEnabled If FALSE, the application will run in a terminal
	///        without graphics. Note that in this case you will not be able to
	///        use any kind of graphical user interface (including the 
	///        QVDefaultGUI).
	QVApplication (int &argc, char **argv,
				   QString info = QString(), bool GUIenabled = TRUE);

        /// @brief Process command line arguments without executing.
        ///
        /// Just as in QVApplication::exec, this method checks if the user asked
        /// for help with the command line option "--help", and in that case it
        /// shows help on the application and on all the input parameters of
        /// every QVPropertyContainer created until now, and returns. Otherwise, just as exec,
        /// it also checks for any possible error on any QVPropertyContainer, and if finds any,
        /// shows an adequate error message, and returns. Again as exec, any unused command line
        /// argument will also lead to an error and the corresponding error message.
        /// But, unlike the exec method, after parsing every argument from the command
        /// line, this method simply returns without entering any event loop.
        /// Therefore, use this method in any QVApplication in which you want to
        /// use the command line facility without having to enter a QApplication event loop.
        /// @return 0, if help was asked, -1 if some error was found in the command line, +1 if everything was parsed OK.
        int processArguments();

	/// @brief Starts execution of the QVApplication.
	///
	/// Before starting the application, this method checks if the user asked
	/// for help with the command line option "--help", and in that case it
	/// shows help on the application and on all the input parameters of
	/// every QVPropertyContainer created until now, and exits. Otherwise, it
	/// checks for any possible error on any QVPropertyContainer, and if finds any,
	/// shows an adequate error message and exits. Any unused command line
	/// argument will also lead to an error and the corresponding error message.
	/// This function also opens any possibly created QVCameras, letting
	/// them ready for being read by adequately linked QVProcessingBlocks's.
	/// Finally, if everything was initialized OK, the GUI main loop starts
	/// executing, showing every graphical element, and finally all the created
	/// QVProcessingBlocks also start their executions.
	/// @return The int code returned by the QVApplication.
	int exec();

	/// @brief Makes an application finish or not when its last block finishes.
	///
	/// Call this function to decide if you want your application to finish when
	/// its last block does. Default behavior is TRUE (the application finishes
	/// with its last block, unless qApp->setTerminateOnLastBlock(FALSE) has
	/// been explicitly called by the programmer.
	/// @param terminate flag to indicate desired behavior.
	void setTerminateOnLastBlock(bool terminate) { terminateOnLastBlock=terminate; };

	/// @brief Marks a given command line argument as used.
	///
	/// This function is useful if the programmer wish to process manually 
	/// a command line argument (which is not intended to initialize any
	/// property of a QVPropertyContainer). In that case, he should call this
	/// function when the argument has been adequately processed, in order to
	/// avoid the QVApplication::exec() early termination with an
	/// "unused argument" message. Use in conjunction with
	/// QVApplication::getUnusedArguments().
	/// @param argument QString with the argument to mark as used. Must be
	///        exactly as contained in the corresponding argv[i] (including
	///        hyphens and/or equal characters, if present).
	void setArgumentAsUsed(QString argument);

	/// @brief Gets the list of unprocessed arguments.
	///
	/// This function is useful if the programmer wish to process manually 
	/// a command line argument (which is not intended to initialize any
	/// property of a QVPropertyContainer). In that case, he should call this
	/// function to obtain the list of unprocessed arguments, in order to
	/// process them adequately. Use in conjunction with 
	/// QVApplication::setArgumentAsUsed().
	/// @returns List of unused arguments as a QStringList.
	QStringList getUnusedArguments();

	/// @brief Tells if a QVApplication is already in the exec() loop.
	/// @return TRUE if the QVApplication is already in the exec() loop.
	bool isRunning() { return isRunningFlag; };

	/// @brief Tells if a QVApplication is called for print help.
	/// @return TRUE if the QVApplication is called for print help.
	bool forHelp() { return forHelpFlag; };

	/// @brief Gets help for a QVApplication.
	/// @return A (very long, containing carriage returns) QString containing help for the application.
	QString getHelp();

	/// @brief Gets a pointer to the only QVApplication instance.
	/// @return Pointer to the only QVApplication instance (equivalent to qvApp).
	static QVApplication* instance() { return dynamic_cast<QVApplication*>(qApp); }

	/*
	/// @brief Adds a given command line argument.
	///
	/// This function adds a command line argument to the application object.
	/// Registered block processing objects will get these arguments as if
	/// they were provided by the user through the command line.
	///
	/// @param argument QString containing the argument to add.
	void addArgument(const QString &argument) { unusedArguments << argument; };
	*/

	/// @brief Gets the number of total arguments.
	///
	/// This function is useful if the programmer wish to process manually 
	/// a command line parameter. This method will indicate the programmer how many
	/// console line parameters were provided by the user.
	/// @returns Number of command line parameters.
	int getNumberOfArguments() const		{ return arguments().size(); }

	/// @brief Gets the value of an application argument.
	///
	/// This function is useful if the programmer wish to process manually 
	/// a command line parameter. This method will return the command line parameter
	/// located at the index.
	/// 
	/// @param index Index for the command line parameter
	/// @return Command line parameter located at the index.
	QString getArgument(const int index)
		{
		const QString argument = arguments()[index];

		setArgumentAsUsed(argument);

		return argument;
		}

	/// @brief Gets the argument values.
	///
	/// This function returns the command line arguments in a QString list.
	/// It also marks all arguments as used.
	/// 
	/// @return Command line parameters.
	QStringList getArguments()
		{
		foreach(QString argument, arguments())
			setArgumentAsUsed(argument);

		return arguments();
		}

#ifndef DOXYGEN_IGNORE_THIS
	void registerQVPropertyContainer(QVPropertyContainer *qvp);
	void deregisterQVPropertyContainer(QVPropertyContainer *qvp);
	void registerGUI(QVGUI *visionInterface);
	void deregisterGUI();
	QSet<QVPropertyContainer *> getQVPropertyContainers() { return qvps; };
	QMutex mutex; // A global mutex
#endif

public slots:
	/// @brief Start the application items.
	///
	/// This slot, when called, provokes the start of all the QVApplication's items.
	bool startItems();

	/// @brief Terminates the application items.
	///
	/// This slot, when called, provokes the termination of the QVApplication's items.
	/// Previously, it cleanly finishes all the QVProcessingBlocks and closes all the
	/// open QVCameras.
	void quitItems();

	void quitBlock(QVProcessingBlock *block);

	/// @brief Terminates an application.
	///
	/// This slot, when called, provokes the termination of the QVApplication.
	/// Previously, it quitItems.
	void quit();

private slots:
	void blockFinished();

private:
	QString info;
	QStringList unusedArguments;
	QSet<QVPropertyContainer *> qvps;
	QVGUI *visionInterface;
	bool isRunningFlag;
	int blockCount;
	bool terminateOnLastBlock, forHelpFlag;

	void printHelp();
};
#endif // QVAPPLICATION_H
