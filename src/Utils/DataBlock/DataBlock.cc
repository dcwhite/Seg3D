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

#include <Utils/DataBlock/DataBlock.h>

namespace Utils
{

DataBlock::DataBlock() :
	nx_( 0 ), ny_( 0 ), nz_( 0 ), data_type_( DataType::UNKNOWN_E ), 
	data_( 0 )
{
}

DataBlock::~DataBlock()
{
}

void DataBlock::set_type( DataType type )
{
	this->data_type_ = type;

	switch( data_type_ )
	{
	case DataType::CHAR_E:
		this->get_data_func_ = boost::bind( &DataBlock::internal_get_data<char>, this, _1 );
		this->set_data_func_ = boost::bind( &DataBlock::internal_set_data<char>, this, _1, _2 );
		break;
	case DataType::UCHAR_E:
		this->get_data_func_ = boost::bind( &DataBlock::internal_get_data<unsigned char>, this, _1 ); 
		this->set_data_func_ = boost::bind( &DataBlock::internal_set_data<unsigned char>, this, _1, _2 );
		break;
	case DataType::SHORT_E:
		this->get_data_func_ = boost::bind( &DataBlock::internal_get_data<short>, this, _1 );
		this->set_data_func_ = boost::bind( &DataBlock::internal_set_data<short>, this, _1, _2 );
		break;
	case DataType::USHORT_E:
		this->get_data_func_ = boost::bind( &DataBlock::internal_get_data<unsigned short>, this, _1 ); 
		this->set_data_func_ = boost::bind( &DataBlock::internal_set_data<unsigned short>, this, _1, _2 );
		break;
	case DataType::INT_E:
		this->get_data_func_ = boost::bind( &DataBlock::internal_get_data<int>, this, _1 );
		this->set_data_func_ = boost::bind( &DataBlock::internal_set_data<int>, this, _1, _2 );
		break;
	case DataType::UINT_E:
		this->get_data_func_ = boost::bind( &DataBlock::internal_get_data<unsigned int>, this, _1 ); 
		this->set_data_func_ = boost::bind( &DataBlock::internal_set_data<unsigned int>, this, _1, _2 );
		break;
	case DataType::FLOAT_E:
		this->get_data_func_ = boost::bind( &DataBlock::internal_get_data<float>, this, _1 );
		this->set_data_func_ = boost::bind( &DataBlock::internal_set_data<float>, this, _1, _2 );
		break;
	case DataType::DOUBLE_E:
		this->get_data_func_ = boost::bind( &DataBlock::internal_get_data<double>, this, _1 );
		this->set_data_func_ = boost::bind( &DataBlock::internal_set_data<double>, this, _1, _2 );
		break;
	default:
		this->get_data_func_ = 0;
		this->set_data_func_ = 0;
		break;
	}
}

} // end namespace Utils
