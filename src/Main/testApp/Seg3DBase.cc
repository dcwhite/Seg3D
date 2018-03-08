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

#ifdef _MSC_VER
#pragma warning( disable: 4244 )
#endif


#ifdef BUILD_WITH_PYTHON
#include <Python.h>
#include <Core/Python/PythonInterpreter.h>
#include <Core/Python/PythonCLI.h>
#include <Application/Socket/ActionSocket.h>

#include "ActionPythonWrapperRegistration.h"
#endif

// STL includes
#include <iostream>
#include <string>

// boost includes
#include <boost/preprocessor.hpp>

// Core includes
#include <Core/Application/Application.h>
#include <Core/Utils/Log.h>
#include <Core/Utils/LogStreamer.h>
#include <Core/Utils/LogHistory.h>
#include <Core/Interface/Interface.h>
#include <Core/Action/ActionHistory.h>
#include <Core/Log/RolloverLogFile.h>

// Application includes
#include <Application/InterfaceManager/InterfaceManager.h>
#include <Application/Tool/ToolFactory.h>

// Resource includes
#include <Resources/QtResources.h>

// File that contains a function that registers all the class that need registration,
// such as Actions and Tools
#include "ClassRegistration.h"

// Revision information
#include "Seg3D_RevisionInfo.h"
#include "Seg3DBase.h"

namespace Seg3D
{

Seg3DBaseTest::Seg3DBaseTest() 
{
  Core::Application::Instance()->check_command_line_parameter( "file_to_open_on_start", this->file_to_view );
}


} //namespace Seg3D
