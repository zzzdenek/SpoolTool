// test_main.cpp
// Author: Zdenek Zeman
// Last change: 19-11-21

#include <iostream>
//#include <string>

//#include "Arguments.h"
#include "ArgsHandler.h"
#include "FileHandler.h"
#include "Spooler.h"

int main( int argc, char* argv[] )
{
  /*
  Arguments args( "args" );

  std::cout << "getTitle<" << args.getTitle() << ">" << std::endl;

  args.addArgument( "1st arg" );
  args.addArgument( "2nd arg" );
  args.addArgument( "3rd arg" );

  std::cout << "hasArguments<" << args.hasArguments() << ">" << std::endl;
  std::cout << "1 popArgument<" << args.popArgument() << ">" << std::endl;
  std::cout << "2 popArgument<" << args.popArgument() << ">" << std::endl;
  std::cout << "3 popArgument<" << args.popArgument() << ">" << std::endl;
  std::cout << "hasArguments<" << args.hasArguments() << ">" << std::endl;
  std::cout << "4 popArgument<" << args.popArgument() << ">" << std::endl;
  */

  

  ArgsHandler args_handler( argc, argv );

  //std::cout << "args_handler.getArgs()<" << std::endl << args_handler.getArgs() << ">" << std::endl;
  //std::cout << "file_name<" << args_handler.getFileName() << ">" << std::endl;

  FileHandler file_hanlder( args_handler.getFileName() );
  file_hanlder.readFile();
  //if ( file_hanlder.readFile() ) std::cout << "OK file exists and has content" << std::endl;
  //else std::cout << "NOK file doesn't exist or is empty" << std::endl;

  //std::cout << "file_handler.getFileBuffer()<" << std::endl << file_hanlder.getFileBuffer() << std::endl << ">" << std::endl;

  Spooler spooler();
  //spooler.provideArgsHandler( &args_handler );
  std::cout << &args_handler << std::endl;

  /*
  args_handler.addNewArgs( "seq" );
  args_handler.addArgToArgs( "seq", "1st argument" );
  args_handler.addArgToArgs( "seq", "2nd argument" );
  args_handler.addArgToArgs( "seq", "3rd argument" );
  
  args_handler.addNewArgs( "ass" );
  args_handler.addArgToArgs( "ass", "1st ass" );
  args_handler.addArgToArgs( "ass", "2nd ass" );
  args_handler.addArgToArgs( "ass", "3rd ass" );
  */


  //args_handler.~ArgsHandler();

  //std::string 
  //args_handler.addNewArgs( "seq" );
  //args_handler.addArgToArgs( "seq", "1st argument" );
  //args_handler.printArgs();

  //std::cout << "hello world!" << std::endl;

  return 0;
}