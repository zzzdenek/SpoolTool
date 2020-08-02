// ArgsHandler.cpp
// Author: Zdenek Zeman
// Last change: 19-11-22

#include <sstream>

#include "FileHandler.h"

FileHandler::FileHandler( std::string file_name )
{
  in_file_name_ = file_name;
  in_file_path_.append( in_file_name_ );
  in_file_path_.append( file_type_ );
}

bool FileHandler::readFile()
{
  std::stringstream ss_file_buffer;
  std::ifstream in_file;
  in_file.open( in_file_path_.c_str() );
  ss_file_buffer << in_file.rdbuf();
  file_buffer_ = ss_file_buffer.str();
  in_file.close();

  return !file_buffer_.empty();
}