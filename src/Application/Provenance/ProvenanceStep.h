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

#ifndef APPLICATION_PROVENANCE_PROVENANCESTEP_H
#define APPLICATION_PROVENANCE_PROVENANCESTEP_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

// Boost includes
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

// Application includes
#include <Application/Provenance/Provenance.h>

namespace Seg3D
{

// Forward Declaration
class ProvenanceStep;
typedef boost::shared_ptr<ProvenanceStep> ProvenanceStepHandle;
typedef std::vector< ProvenanceStepHandle > ProvenanceTrail;
typedef boost::shared_ptr< ProvenanceTrail > ProvenanceTrailHandle;
typedef long long ProvenanceStepID;

class ProvenanceStep : boost::noncopyable
{
  // -- constructor/destructor --
public:
  ProvenanceStep();

  virtual ~ProvenanceStep();

  // -- accessors --
public:
  // GET_INPUT_PROVENANCE_IDS
  // Get the input provenance ids
  const ProvenanceIDList& get_input_provenance_ids() const;
  
  // SET_INPUT_PROVENANCE_IDS
  // Set the input provenance ids
  void set_input_provenance_ids( const ProvenanceIDList& input_provenance_ids );

  // GET_OUTPUT_PROVENANCE_IDS
  // Get the input provenance ids
  const ProvenanceIDList& get_output_provenance_ids() const;
  
  // SET_OUTPUT_PROVENANCE_IDS
  // Set the input provenance ids
  void set_output_provenance_ids( const ProvenanceIDList& output_provenance_ids );

  // GET_REPLACED_PROVENANCE_IDS:
  // Get the replaced provenance ids
  const ProvenanceIDList& get_replaced_provenance_ids() const;
  
  // SET_REPLACED_PROVENANCE_IDS:
  // Set the replaced provenance ids
  void set_replaced_provenance_ids( const ProvenanceIDList& replaced_provenance_ids );

  // SET_INPUTFILES_ID
  // Set the input files cache id in the provenance step
  void set_inputfiles_id( const InputFilesID inputfiles_id );
  
  // GET_INPUTFILES_ID
  // Get the input files cache id from this provenance step
  InputFilesID get_inputfiles_id() const;

  // SET_ACTION_NAME:
  // Set the action name.
  void set_action_name( const std::string& action_name );

  // GET_ACTION_NAME:
  // Get the action name.
  const std::string& get_action_name() const;

  // SET_ACTION_PARAMS:
  // Set the action parameters string.
  void set_action_params( const std::string& action_params );

  // GET_ACTION_PARAMS:
  // Get the action parameters string.
  const std::string& get_action_params() const;
  
  // GET_USER:
  // get the user's name
  const std::string& get_username() const;

  // SET_PROVENANCE_ID_OF_INTEREST:
  // Set the provenance ID in which we are interested.
  void set_provenance_id_of_interest( ProvenanceID poi );

  // GET_PROVENANCE_ID_OF_INTEREST:
  // Get the provenance ID in which we are interested.
  ProvenanceID get_provenance_id_of_interest() const;

  // -- properties --
public:
  virtual bool is_collapsable();

  // -- internals --
protected:
  // List of provenance ids that this step depends on
  ProvenanceIDList input_provenance_ids_;
  
  // List of provenance ids that this action will generate
  ProvenanceIDList output_provenance_ids_;
  
  // List of provenance ids that this action will replace
  ProvenanceIDList replaced_provenance_ids_;

  // Name of the action
  std::string action_name_;

  // Parameters of the action
  std::string action_params_;

  // User that generated action
  std::string user_;
  
  // Input Files cache id
  InputFilesID inputfiles_id_;

  // Provenance ID of interest
  // NOTE: This is for getting back a provenance trail, when we are only
  // interested in provenance IDs of a certain layer.
  ProvenanceID provenance_id_of_interest_;
};

} // end namespace Seg3D

#endif
