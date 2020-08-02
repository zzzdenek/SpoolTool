// Arguments.cpp
// Author: Zdenek Zeman
// Last change: 19-11-21

#include "Arguments.h"

std::string Arguments::popArgument()
{
  std::string arg;

  if ( Arguments::hasArguments() )
  {
    arg = arguments_.front();
    arguments_.erase( arguments_.begin() );
  }

  return arg;
}

std::string Arguments::getArgs()
{
  std::string args;

  for( std::string arg : arguments_ )
  {
    args.append( arg );
    args.append( "," );
  }

  return args;
}
