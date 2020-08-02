// ArgsHandler.h
// Author: Zdenek Zeman
// Last change: 19-11-22

#ifndef SPOOLER_H
#define SPOOLER_H

#include <string>
//#include <vector>
//#include <iostream>
#include <memory>

#include "ArgsHandler.h"

class Spooler
{
private:
  std::shared_ptr< ArgsHandler > args_handler_;

  std::string file_buffer_;


public:
  Spooler() {};
  //void provideArgsHandler( ArgsHandler args_handler ) { args_handler_ = args_handler; }
  std::string getArgs() { return ( *args_handler_ ).getArgs(); }
};

#endif