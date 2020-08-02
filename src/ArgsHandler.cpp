// ArgsHandler.cpp
// Author: Zdenek Zeman
// Last change: 19-11-22

#include "ArgsHandler.h"

bool argIsNumber( char* argv[] )
{
  if ( argv[ 2 ][ 0 ] == '0' || argv[ 2 ][ 0 ] == '1' || argv[ 2 ][ 0 ] == '2' || argv[ 2 ][ 0 ] == '3'
    || argv[ 2 ][ 0 ] == '4' || argv[ 2 ][ 0 ] == '5' || argv[ 2 ][ 0 ] == '6' || argv[ 2 ][ 0 ] == '7'
    || argv[ 2 ][ 0 ] == '8' || argv[ 2 ][ 0 ] == '9' ) return true;
  else return false;
}

ArgsHandler::ArgsHandler( int argc, char* argv[] )
{
  addNewArgs( "file_name" );
  addArgToArgs( "file_name", argc > 1 ? argv[1] : "" );
  addNewArgs( "number_of_orders" );

  if ( argc > 2 && argIsNumber( argv ) ) addArgToArgs( "number_of_orders", argv[2] );
  else addArgToArgs( "number_of_orders", "1" );

  std::string arg_name;

  for ( int counter = 2; counter < argc; counter++ )
  {
    std::string temp( argv[ counter ] );

    if ( temp.find( '-', 0 ) == 0 )
    {
      temp.erase( 0, 1 );
      arg_name.erase( 0 );
      arg_name = temp;
      addNewArgs( arg_name );
    }
    else if ( !arg_name.empty() ) addArgToArgs( arg_name, temp );

    temp.erase( 0 );
  }  
}

void ArgsHandler::addNewArgs( std::string in_title )
{
  std::shared_ptr< Arguments > args ( new Arguments( in_title ) );
  args_.push_back( args );
}

void ArgsHandler::addArgToArgs( std::string in_arg_title, std::string in_arg )
{
  for ( std::shared_ptr< Arguments > arg : args_ )
  {
    if ( ( *arg ).getTitle() == in_arg_title ) ( *arg ).addArgument( in_arg );
  }
}

std::string ArgsHandler::getArgs()
{
  std::string out_args;

  for( std::shared_ptr< Arguments > arg : args_ )
  {
    out_args.append( ( *arg ).getTitle() );
    out_args.append( "\n" );
    out_args.append( ( *arg ).getArgs() );
    out_args.append( "\n" );
  }

  return out_args;
}

std::string ArgsHandler::getFileName()
{
  std::string out_file_name;
    
  for ( std::shared_ptr< Arguments > arg : args_ )
  {
    if ( ( *arg ).getTitle() == "file_name" ) out_file_name = ( *arg ).getArgument();
  }
  
  return out_file_name;
}