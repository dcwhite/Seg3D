/*
 For more information, please see: http://software.sci.utah.edu
 
 The MIT License
 
 Copyright (c) 2018 Scientific Computing and Imaging Institute,
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

// Core includes
#include <Core/Interface/Interface.h>

//QtGui includes
#include "ui_MRIBiasFieldCorrectionFilterInterface.h"

//Application Includes
#include <Application/Tools/MRIBiasFieldCorrectionFilter.h>

//QTUtils Includes
#include <QtUtils/Bridge/QtBridge.h>

// Interaface includes
#include <Interface/ToolInterface/MRIBiasFieldCorrectionFilterInterface.h>


SCI_REGISTER_TOOLINTERFACE( Seg3D, MRIBiasFieldCorrectionFilterInterface );

namespace Seg3D
{

class MRIBiasFieldCorrectionFilterInterfacePrivate
{
public:
  Ui::MRIBiasFieldCorrectionFilterInterface ui_;
};

MRIBiasFieldCorrectionFilterInterface::MRIBiasFieldCorrectionFilterInterface() :
private_( new MRIBiasFieldCorrectionFilterInterfacePrivate )
{
}

MRIBiasFieldCorrectionFilterInterface::~MRIBiasFieldCorrectionFilterInterface()
{
}

// build the interface and connect it to the state manager
bool MRIBiasFieldCorrectionFilterInterface::build_widget( QFrame* frame )
{
  //Step 1 - build the Qt GUI Widget
  this->private_->ui_.setupUi( frame );
  this->private_->ui_.horizontalLayout_2->setAlignment( Qt::AlignHCenter );
  this->private_->ui_.horizontalLayout_3->setAlignment( Qt::AlignHCenter );
  
  //Step 2 - get a pointer to the tool
 MRIBiasFieldCorrectionFilter* tool = dynamic_cast< MRIBiasFieldCorrectionFilter* > ( this->tool().get() );
  
  //Step 3 - connect the gui to the tool through the QtBridge
  QtUtils::QtBridge::Connect( this->private_->ui_.target_layer_, 
                             tool->target_layer_state_ );
  QtUtils::QtBridge::Connect( this->private_->ui_.use_active_layer_, 
                             tool->use_active_layer_state_ );
  QtUtils::QtBridge::Connect( this->private_->ui_.replaceCheckBox, 
                             tool->replace_state_ );
  QtUtils::QtBridge::Connect( this->private_->ui_.mask_,
                             tool->mask_state_ );
  QtUtils::QtBridge::Connect( this->private_->ui_.invert_mask_,
                             tool->mask_invert_state_ );
  QtUtils::QtBridge::Connect( this->private_->ui_.replace_with_,
                             tool->replace_with_state_ );
    
  //QtUtils::QtBridge::Connect( this->private_->ui_.preserve_data_format_,
                             //tool->preserve_data_format_state_ );
  
  //QtUtils::QtBridge::Connect( this->private_->ui_.radius_,
                             //tool->radius_state_ );
  
  QtUtils::QtBridge::Enable( this->private_->ui_.runFilterButton,
                            tool->valid_target_state_ );
  
  QtUtils::QtBridge::Show( this->private_->ui_.message_alert_, tool->valid_target_state_, true );
  
  QtUtils::QtBridge::Enable( this->private_->ui_.target_layer_, 
                            tool->use_active_layer_state_, true );
  QtUtils::QtBridge::Connect( this->private_->ui_.runFilterButton, boost::bind(
                                                                               &Tool::execute, tool, Core::Interface::GetWidgetActionContext() ) );
  
  //this->private_->ui_.radius_->set_description( "Radius" );
  
  return true;
} // end build_widget
  
} // end namespace Seg3D