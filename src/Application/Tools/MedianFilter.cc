/*
 For more information, please see: http://software.sci.utah.edu
 
 The MIT License
 
 Copyright (c) 2009 Scientific Computing and Imaging Institute,
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

// Application includes
#include <Application/Tool/ToolFactory.h>
#include <Application/Tools/MedianFilter.h>
#include <Application/LayerManager/LayerManager.h>

namespace Seg3D
{

// Register the tool into the tool factory
SCI_REGISTER_TOOL(MedianFilter)

MedianFilter::MedianFilter( const std::string& toolid ) :
  Tool( toolid )
{
  // Need to set ranges and default values for all parameters
  add_state( "target", target_layer_state_, "<none>" );
  add_state( "radius", radius_state_, 1, 100, 1, 2 );
  add_state( "replace", replace_state_, false );

  // Add constaints, so that when the state changes the right ranges of
  // parameters are selected
  target_layer_state_->value_changed_signal_.connect( boost::bind(
      &MedianFilter::target_constraint, this, _1 ) );
  
  LayerManager::Instance()->layers_changed_signal_.connect(
    boost::bind( &MedianFilter::handle_layers_changed, this ) );

}

MedianFilter::~MedianFilter()
{
  disconnect_all();
}
  
void MedianFilter::handle_layers_changed()
{
  std::vector< LayerHandle > target_layers;
  LayerManager::Instance()->get_layers( target_layers );
  bool target_found = false;
  
  for( int i = 0; i < static_cast< int >( target_layers.size() ); ++i )
  {
    if( target_layers[i]->get_layer_name() == target_layer_state_->get() ) {
      target_found = true;
      break;
    }
  }
  
  if( !target_found )
    target_layer_state_->set( "", ActionSource::NONE_E );
  
}

void MedianFilter::target_constraint( std::string layerid )
{
}

void MedianFilter::activate()
{
}

void MedianFilter::deactivate()
{
}

} // end namespace Seg3D
