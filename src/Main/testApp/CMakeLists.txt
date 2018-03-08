#
#  For more information, please see: http://software.sci.utah.edu
#  The MIT License
#
#  Copyright (c) 2016 Scientific Computing and Imaging Institute,
#  University of Utah.
#
#
#  Permission is hereby granted, free of charge, to any person obtaining a
#  copy of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom the
#  Software is furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included
#  in all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
#  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#  DEALINGS IN THE SOFTWARE.
#


############################################
# Set Seg3D main sources
###########################################

SET(MAIN_SRCS
  main_test.cc
  Seg3DBase.h
  Seg3DBase.cc
  Seg3DGui.h
  Seg3DGui.cc
)

###########################################
# Build the Seg3D executable
###########################################


ADD_EXECUTABLE(Seg3d_test ${MAIN_SRCS})

TARGET_LINK_LIBRARIES(Seg3d_test
  ${SCI_BOOST_LIBRARY}
 
  QtUtils_Utils
  QtUtils_Widgets
  QtUtils_Bridge
  Interface_Application

  
  ${RESOURCES_LIBRARY}
)

IF(WIN32)
  TARGET_LINK_LIBRARIES(Seg3d_test ${Qt5Core_QTMAIN_LIBRARIES} )
  SET_TARGET_PROPERTIES(Seg3d_test
    PROPERTIES
    LINK_FLAGS "/INCREMENTAL:NO")
ENDIF()

IF(APPLE)
  SET_TARGET_PROPERTIES(Seg3d_test
    PROPERTIES
    LINK_FLAGS "-framework CoreGraphics"
  )
ENDIF()

IF(BUILD_WITH_PYTHON)
  TARGET_LINK_LIBRARIES(Seg3d_test
    Core_Python
    Application_Socket
  )
ENDIF()

# add libraries with plug-ins and extensions
REGISTERED_TARGET_LINK_LIBRARIES(Seg3d_test)

###########################################
# SETUP MACOSX APPLICATION BUNDLE
# There is no good way for incorporating
# external libraries into a bundle, hence
# it is hard coded here what needs to be
# done to generate an application that
# does not depend on anything except the
# operating system
###########################################

IF(APPLE)
  # set up app bundle
  ADD_CUSTOM_COMMAND(TARGET Seg3d_test
    POST_BUILD
    # configure Qt libs
    COMMAND ${MACDEPLOYQT} Seg3d_test.app -verbose=${MACDEPLOYQT_OUTPUT_LEVEL}
    WORKING_DIRECTORY ${SEG3D_BINARY_DIR})
  IF(BUILD_WITH_PYTHON)
    SET(VERSION_PATH Versions/${SCI_PYTHON_VERSION_SHORT})
    SET(FRAMEWORK_PATH Frameworks/Python.framework)
    SET(PYTHON_PATH Seg3d_test.app/Contents/${FRAMEWORK_PATH}/${VERSION_PATH})
      ADD_CUSTOM_COMMAND(TARGET Seg3d_test
      POST_BUILD
      # macdeployqt puts frameworks in app/Content/Frameworks
      COMMAND ${CMAKE_COMMAND} ARGS -E chdir Seg3d_test.app/Contents/Frameworks tar xf ${SCI_PYTHON_FRAMEWORK_ARCHIVE}
      COMMAND chmod u+w  ${PYTHON_PATH}/Python
      COMMAND  install_name_tool -id Python ${PYTHON_PATH}/Python
      COMMAND  install_name_tool -change ${SCI_PYTHON_FRAMEWORK}/${VERSION_PATH}/Python @executable_path/../${FRAMEWORK_PATH}/${VERSION_PATH}/Python Seg3d_test.app/Contents/MacOS/Seg3d_test
      # TODO: other executables...
      COMMAND  install_name_tool -change ${SCI_PYTHON_FRAMEWORK}/${VERSION_PATH}/Python @executable_path/../Python ${PYTHON_PATH}/bin/python${SCI_PYTHON_VERSION_SHORT}
      WORKING_DIRECTORY ${SEG3D_BINARY_DIR})
  ENDIF()

ENDIF()

IF(APPLE)
  INSTALL(TARGETS Seg3d_test
        RUNTIME DESTINATION .
        BUNDLE DESTINATION .
  )
ELSE()
  GET_FILENAME_COMPONENT(QTCORENAME ${QtCore_location_Release} NAME_WE)
  GET_FILENAME_COMPONENT(QTGUINAME ${QtGui_location_Release} NAME_WE)
  GET_FILENAME_COMPONENT(QTOPENGLNAME ${QtOpenGL_location_Release} NAME_WE)
  GET_FILENAME_COMPONENT(QTWIDGETSNAME ${QtWidgets_location_Release} NAME_WE)
  GET_FILENAME_COMPONENT(QTSVGNAME ${QtSvg_location_Release} NAME_WE)

  IF(WIN32)
    INSTALL(TARGETS Seg3d_test
      RUNTIME DESTINATION bin
    )

    INSTALL(PROGRAMS
      ${SEG3D_BINARY_DIR}/$<CONFIG>/${QTCORENAME}.dll
      ${SEG3D_BINARY_DIR}/$<CONFIG>/${QTGUINAME}.dll
      ${SEG3D_BINARY_DIR}/$<CONFIG>/${QTOPENGLNAME}.dll
      ${SEG3D_BINARY_DIR}/$<CONFIG>/${QTWIDGETSNAME}.dll
      ${SEG3D_BINARY_DIR}/$<CONFIG>/${QTSVGNAME}.dll
        DESTINATION bin
    )


  ENDIF()
ENDIF()
