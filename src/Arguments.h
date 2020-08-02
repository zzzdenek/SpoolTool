// Arguments.h
// Author: Zdenek Zeman
// Last change: 19-11-21

#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <string>
#include <vector>

//for testing
#include <iostream>

class Arguments
{
private:
  std::string title_;
  std::vector< std::string > arguments_;

  Arguments( const Arguments &copy ) {};

public:
  Arguments() {};
  Arguments( std::string title )      { title_ = title; }

  std::string getTitle()              { return title_; }
  std::string getArgs();
  std::string getArgument()           { return arguments_.front(); }

  std::string popArgument();

  void addArgument( std::string arg ) { arguments_.push_back( arg ); }
  bool hasArguments()                 { return !arguments_.empty(); }
};

#endif