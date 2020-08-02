// ArgsHandler.h
// Author: Zdenek Zeman
// Last change: 19-11-22

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <string>
//#include <vector>
//#include <iostream>
//#include <memory>

//#include "Arguments.h"

class FileHandler
{
private:
  std::string file_type_ = ".txt";

  std::string in_file_name_;
  std::string in_file_path_ = "./";
  std::string file_buffer_;

  std::string out_file_name_;
  std::string out_file_path_ = "./temp/";

public:
  FileHandler( std::string file_name );

  std::string getFileBuffer() { return file_buffer_; }

  bool readFile();

};

#endif