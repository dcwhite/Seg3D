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

// For the version numbers
#include "ApplicationConfiguration.h"

// Boost include
#include <boost/lexical_cast.hpp>

#include <QMessageBox>
#include <QDesktopWidget>
#include <QApplication>
#include <QCloseEvent>

// Core includes
#include <Core/Application/Application.h>
#include <Core/Interface/Interface.h>
#include <Core/State/Actions/ActionSet.h>

// Application includes
#include <Application/PreferencesManager/PreferencesManager.h>
#include <Application/PreferencesManager/Actions/ActionSavePreferences.h>
#include <Application/ProjectManager/ProjectManager.h>
#include <Application/ProjectManager/Actions/ActionSaveSession.h>
#include <Application/ProjectManager/Actions/ActionNewProject.h>
#include <Application/ProjectManager/Actions/ActionLoadProject.h>

// QtUtils includes
#include <QtUtils/Utils/QtApplication.h>
#include <QtUtils/Utils/QtPointer.h>
#include <QtUtils/Bridge/QtBridge.h>

// Resource includes
#include <Resources/QtResources.h>

// Interface includes
#include <Interface/Application/ApplicationInterfaceTest.h>
#include <Interface/Application/ApplicationInterface.h>
#include <Interface/Application/StyleSheet.h>
#include <Interface/Application/ControllerInterface.h>
#include <Interface/Application/HistoryDockWidget.h>
#include <Interface/Application/LayerIOFunctions.h>
#include <Interface/Application/LayerManagerDockWidget.h>
#include <Interface/Application/RenderingDockWidget.h>
#include <Interface/Application/Menu.h>
#include <Interface/Application/MessageWindow.h>
#include <Interface/Application/PreferencesInterface.h>
#include <Interface/Application/ProjectDockWidget.h>
#include <Interface/Application/ShortcutsInterface.h>

#include <Interface/Application/StatusBarWidget.h>
#include <Interface/Application/ToolsDockWidget.h>
#include <Interface/Application/ProvenanceDockWidget.h>
#include <Interface/Application/ViewerInterface.h>
#include <Interface/Application/SaveProjectAsWizard.h>


#ifdef BUILD_WITH_PYTHON
#include <Interface/Application/PythonConsoleWidget.h>
#endif

#include <Interface/Application/ProgressWidget.h>

namespace Seg3D
{

ApplicationInterfaceTest::ApplicationInterfaceTest(std::string file_to_view_on_open)
{
  // Ensure that resources are available
  // This function ensures that all the images are available
  InitQtResources();

  this->setStyleSheet( StyleSheet::MAIN_STYLE_C );

  // Set the window information and set the version numbers
  this->setWindowTitle( "Test Seg3d for file double-clicking: " + QString::fromStdString(file_to_view_on_open) );

  // Tell Qt what size to start up in
  this->resize( 1280, 720 );

  this->splash_screen_ = new SplashScreen(false, this);

  // add signal connection for OS X file assocation open event
  QtUtils::QtApplication::Instance()->osx_file_open_event_signal_.connect(boost::bind(
    &ApplicationInterfaceTest::handle_osx_file_open_event, this, _1));
}

void ApplicationInterfaceTest::activate_splash_screen()
{
  this->splash_screen_->show();
  ApplicationInterface::center_seg3d_gui_on_screen(this->splash_screen_);
}

void ApplicationInterfaceTest::handle_osx_file_open_event(std::string filename)
{
  std::cerr << __FUNCTION__ << " " << filename << std::endl;
  syslog (LOG_WARNING, __FUNCTION__);
  logStuff("filename", filename.c_str(), __LINE__);
  //QMessageBox::information(nullptr, "", "handle_osx_file_open_event: " + QString::fromStdString(filename));
  // must do this to make sure a double-click on a project file doesn't use this executable session
  bool useCurrentSession = InterfaceManager::Instance()->splash_screen_visibility_state_->get();
  LOG_STUFF(useCurrentSession);
  if ( !this->splash_screen_ || this->splash_screen_->get_user_interacted() )
  {
    useCurrentSession = false;
  }
  LOG_STUFF(useCurrentSession);

  if (useCurrentSession)
  {
    this->open_initial_project(filename);
  }
  else
  {
    boost::filesystem::path app_filepath;
    Core::Application::Instance()->get_application_filepath(app_filepath);

    std::string command = app_filepath.parent_path().parent_path().string() + "/Contents/MacOS/Seg3D2 \"" + filename + "\" &";

    LOG_STUFF(command);
    system(command.c_str());

  }
  syslog (LOG_WARNING, "Exiting handle_osx_file_open_event");
}



bool ApplicationInterfaceTest::open_initial_project(std::string filename)
{
  //static int callCount = 0;
  // QMessageBox::information(nullptr, "", QString::number(callCount++) +
  //   " open_initial_project: " + QString::fromStdString(filename));
  syslog (LOG_WARNING, __FUNCTION__);
  syslog (LOG_WARNING, filename.c_str());
  std::cerr << __FUNCTION__ << " " << filename << std::endl;
#if 0
  bool useCurrentSession = InterfaceManager::Instance()->splash_screen_visibility_state_->get();
  if (!this->splash_screen_ || this->splash_screen_->get_user_interacted())
  {
    useCurrentSession = false;
  }

  if (useCurrentSession)
  {
    std::cout << useCurrentSession << std::endl;
  }

  filename = ApplicationInterface::find_project_file(filename);

  if ( filename == "" ) return false;

  std::string extension = boost::filesystem::extension( boost::filesystem::path( filename ) );

  Core::ActionSet::Dispatch( Core::Interface::GetWidgetActionContext(),
                             InterfaceManager::Instance()->splash_screen_visibility_state_, false );

  if ( ( extension == ".nrrd" ) || ( extension == ".nhdr" ) )
  {
    // No location is set, so no project will be generated on disk for now
    ActionNewProject::Dispatch( Core::Interface::GetWidgetActionContext(),
                                "", "Untitled Project" );
    LayerIOFunctions::ImportFiles( this, filename );
    return true;
  }

  std::vector<std::string> project_file_extensions = Project::GetProjectFileExtensions();
  if ( std::find( project_file_extensions.begin(), project_file_extensions.end(), extension ) !=
       project_file_extensions.end() )
  {
    ActionLoadProject::Dispatch( Core::Interface::GetWidgetActionContext(), filename );
  }

  std::vector<std::string> project_folder_extensions = Project::GetProjectPathExtensions();
  if ( std::find( project_folder_extensions.begin(), project_folder_extensions.end(), extension ) !=
       project_folder_extensions.end() )
  {
    ActionLoadProject::Dispatch( Core::Interface::GetWidgetActionContext(), filename );
  }
#endif
  return !filename.empty();
}



} // end namespace Seg3D
