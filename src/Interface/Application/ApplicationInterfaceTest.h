/*
 For more information, please see: http://software.sci.utah.edu

 The MIT License

 Copyright (c) 2016 Scientific Computing and Imaging Institute,
 University of Utah.


 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation
 the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
 */

#ifndef INTERFACE_APPLICATION_APPLICATIONINTERFACETEST_H
#define INTERFACE_APPLICATION_APPLICATIONINTERFACETEST_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef Q_MOC_RUN

// Qt includes
#include <QMainWindow>
#include <QDockWidget>
#include <QWidget>
#include <QPointer>

// Boost includes
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>

// Application Interface components.
#include <Application/InterfaceManager/InterfaceManager.h>
#include <Interface/Application/SplashScreen.h>
#include <Core/Action/Actions.h>
#include <Core/Utils/ConnectionHandler.h>

#endif

namespace Seg3D
{

/// -- ApplicationInterface --
/// This class is the main application window
/// All the menus and viewers dock into this window
/// The event loop of this window is the main event
/// loop for the program

/// Although there is only one instance of this class
/// in the program


class ApplicationInterfacePrivate;


class ApplicationInterfaceTest : public QMainWindow
{
Q_OBJECT

// -- constructor/destructor --
public:
  // Constructor
  ApplicationInterfaceTest(std::string file_to_view_on_open = "");


  /// OPEN_INITIAL_PROJECT:
  /// Opens a project. Intended for use on startup.
  bool open_initial_project ( std::string filename );

  /// ACTIVATE_SPLASH_SCREEN:
  /// opens the splash screen
  void activate_splash_screen();
//
//  // -- functions to handle the properties of the interface --
private:
  /// HANDLE_OSX_FILE_OPEN_EVENT:
  /// Open a file via OS X file associations
  void handle_osx_file_open_event ( std::string filename );

private:
  QPointer< SplashScreen > splash_screen_;
};

} //end namespace

#endif
