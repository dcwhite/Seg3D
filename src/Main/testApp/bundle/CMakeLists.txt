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
  ../main_test.cc
  ../Seg3DBase.h
  ../Seg3DBase.cc
  ../Seg3DGui.h
  ../Seg3DGui.cc
)

###########################################
# Build the Seg3D executable
###########################################
LIST(APPEND MAIN_SRCS ${APPLICATION_OSX_ICON_FULL_PATH})
SET_SOURCE_FILES_PROPERTIES(${APPLICATION_OSX_ICON_FULL_PATH}
  PROPERTIES

MACOSX_PACKAGE_LOCATION Resources)

ADD_EXECUTABLE(Seg3d_test_bundle MACOSX_BUNDLE ${MAIN_SRCS})

TARGET_LINK_LIBRARIES(Seg3d_test_bundle
  ${SCI_BOOST_LIBRARY}

  QtUtils_Utils
  QtUtils_Widgets
  QtUtils_Bridge
  Interface_Application


  ${RESOURCES_LIBRARY}
)


SET_TARGET_PROPERTIES(Seg3d_test_bundle
  PROPERTIES
  MACOSX_BUNDLE_INFO_PLIST ${SEG3D_SOURCE_DIR}/Resources/info.plist
  MACOSX_BUNDLE_ICON_FILE ${APPLICATION_OSX_ICON}
)

IF(APPLE)
  SET_TARGET_PROPERTIES(Seg3d_test_bundle
    PROPERTIES
    LINK_FLAGS "-framework CoreGraphics"
  )
ENDIF()

IF(BUILD_WITH_PYTHON)
  TARGET_LINK_LIBRARIES(Seg3d_test_bundle
    Core_Python
    Application_Socket
  )
ENDIF()

# add libraries with plug-ins and extensions
REGISTERED_TARGET_LINK_LIBRARIES(Seg3d_test_bundle)

###########################################
# SETUP MACOSX APPLICATION BUNDLE
# There is no good way for incorporating
# external libraries into a bundle, hence
# it is hard coded here what needs to be
# done to generate an application that
# does not depend on anything except the
# operating system
###########################################



  # set up app bundle
  ADD_CUSTOM_COMMAND(TARGET Seg3d_test_bundle
    POST_BUILD
    # configure Qt libs
    COMMAND ${MACDEPLOYQT} Seg3d_test_bundle.app -verbose=${MACDEPLOYQT_OUTPUT_LEVEL}
    WORKING_DIRECTORY ${SEG3D_BINARY_DIR})
  

  INSTALL(TARGETS Seg3d_test_bundle
        RUNTIME DESTINATION .
        BUNDLE DESTINATION .
  )
