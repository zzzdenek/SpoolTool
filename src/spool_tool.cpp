//
// Created by zeman on 18.11.2019.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string arg_seq;
std::string arg_start;
std::string arg_ass;
std::string arg_dest;
std::string arg_lou;
std::string arg_art;

std::string in_file_name;
std::string in_file_path = "/kisoft/user/KiSoft-One/wcs/lager/spool/spool_tool/";
std::string file_buffer;
std::string out_buffer;
std::string out_file_name;
std::string out_file_path = "/kisoft/user/KiSoft-One/wcs/lager/spool/spool_tool/temp/";

std::string createLineBuffer( std::string begin_buffer, std::string pre_value_buffer, std::string post_value_buffer,
    std::string end_buffer, bool incremented );
std::string getArg( std::string mode );
std::string getInsertMode( std::string arg );
void updateFileBuffer( std::string old_string, std::string new_string );

void addArg( std::string insert_mode, std::string arg )
{
  if ( insert_mode.compare( "seq" ) == 0 )
  {
    arg_seq.append( arg );
    arg_seq.append( "," );
  }
  else if ( insert_mode.compare( "start" ) == 0 )
  {
    arg_start.append( arg );
    arg_start.append( "," );
  }
  else if ( insert_mode.compare( "ass" ) == 0 )
  {
    arg_ass.append( arg );
    arg_ass.append( "," );
  }
  else if ( insert_mode.compare( "dest" ) == 0 )
  {
    arg_dest.append( arg );
    arg_dest.append( "," );
  }
  else if ( insert_mode.compare( "lou" ) == 0 )
  {
    arg_lou.append( arg );
    arg_lou.append( "," );
  }
  else if ( insert_mode.compare( "art" ) == 0 )
  {
    arg_art.append( arg );
    arg_art.append( "," );
  }
}

void collectArgs( int argc, char* argv[] )
{
  std::string insert_mode;

  for ( int counter = 2; counter < argc; counter++ )
  {
    std::string temp( argv[ counter ] );

    if ( temp.find( '-', 0 ) == 0 )
    {
      insert_mode.erase( 0 );
      insert_mode.append( getInsertMode( temp ) );
    }
    else addArg( insert_mode, temp );

    temp.erase( 0 );
  }
}

std::string createLine( std::string buffer, std::string mode, int incr_number )
{
  std::string begin_buffer;
  std::string end_buffer;
  std::string pre_value_buffer;
  std::string post_value_buffer;
  std::string output_buffer;
  int position = 0;

  for ( int counter = 0; buffer.at( counter ) == '0' || buffer.at( counter ) == ' '; counter++ )
  {
    begin_buffer.append( 1, buffer.at( counter ) );
    position = counter + 1;
  }

  for ( unsigned int counter = position; counter < buffer.length() ; counter++ )
  {
    if ( buffer.at( counter ) == ' ' ) end_buffer.append( 1, buffer.at( counter ) );
    else
    {
      end_buffer.erase( 0 );
      pre_value_buffer.append( 1, buffer.at( counter ) );
    }
    position = counter;
  }

  bool incremented = false;

  if ( mode.compare( "none" ) != 0 ) post_value_buffer.append( getArg( mode ) );
  else
  {
    std::stringstream ss_value( pre_value_buffer );
    int value = 0;
    ss_value >> value;
    value += incr_number;
    std::stringstream ss_value0;
    ss_value0 << value;
    post_value_buffer = ss_value0.str();
    incremented = true;
  }

  buffer.erase( 0 );
  buffer.append( createLineBuffer( begin_buffer, pre_value_buffer, post_value_buffer, end_buffer, incremented ) );

  return buffer;
}

std::string createLineBuffer( std::string begin_buffer, std::string pre_value_buffer, std::string post_value_buffer,
    std::string end_buffer, bool incremented )
{
  int difference = post_value_buffer.length() - pre_value_buffer.length();

  if ( difference > 0 )
  {
    unsigned int uns_diff = difference;
    unsigned int erase_length = uns_diff > begin_buffer.length() ? begin_buffer.length() : difference;
    difference -= erase_length;
    begin_buffer.erase( 0, erase_length );

    if ( difference > 0 && !incremented )
    {
      uns_diff = difference;
      erase_length = uns_diff > end_buffer.length() ? end_buffer.length() : difference;
      difference -= erase_length;
      end_buffer.erase( 0, erase_length );
    }

    if ( difference > 0 )
    {
      post_value_buffer.erase( 0, difference );
      std::stringstream temp( post_value_buffer );
      int temp_num;
      temp >> temp_num;
      if ( temp_num == 0 ) post_value_buffer.replace( post_value_buffer.length() - 1, 1, "1" );
    }
  }
  else if ( difference < 0 )
  {
    difference *= ( -1 );
    if ( begin_buffer.length() > 0 ) begin_buffer.append( difference, begin_buffer.at( 0 ) );
    else begin_buffer.append( difference, '0' );
  }

  std::string buffer;
  buffer.append( begin_buffer );
  buffer.append( post_value_buffer );
  buffer.append( end_buffer );

  return buffer;
}

void createOutfile()
{
  std::ofstream out_file;
  out_file_name = "F.";
  out_file_name.append( in_file_name );
  out_file_path.append( out_file_name );
  out_file.open( out_file_path.c_str() );
  out_file << out_buffer;
  out_file.close();
}

void determineInfile()
{
  if ( in_file_name.empty() )
  {
    std::cout << "FILE?" << std::endl;
    getline( std::cin, in_file_name );
  }

  in_file_name.append( ".txt" );
  in_file_path.append( in_file_name );
}

std::string getArg( std::string mode )
{
  std::string arg;
  int comma_position;

  if ( mode.compare( "seq" ) == 0 )
  {
    comma_position = arg_seq.find( "," );
    arg.append( arg_seq.substr( 0, comma_position ) );
    arg_seq.erase( 0, comma_position + 1 );
  }
  else if ( mode.compare( "start" ) == 0 )
  {
    comma_position = arg_start.find( "," );
    arg.append( arg_start.substr( 0, comma_position ) );
    arg_start.erase( 0, comma_position + 1 );
  }
  else if ( mode.compare( "ass" ) == 0 )
  {
    comma_position = arg_ass.find( "," );
    arg.append( arg_ass.substr( 0, comma_position ) );
    arg_ass.erase( 0, comma_position + 1 );
  }
  else if ( mode.compare( "dest" ) == 0 )
  {
    comma_position = arg_dest.find( "," );
    arg.append( arg_dest.substr( 0, comma_position ) );
    arg_dest.erase( 0, comma_position + 1 );
  }
  else if ( mode.compare( "lou" ) == 0 )
  {
    comma_position = arg_lou.find( "," );
    arg.append( arg_lou.substr( 0, comma_position ) );
    arg_lou.erase( 0, comma_position + 1 );
  }
  else if ( mode.compare( "art" ) == 0 )
  {
    comma_position = arg_art.find( "," );
    arg.append( arg_art.substr( 0, comma_position ) );
    arg_art.erase( 0, comma_position + 1 );
  }
  return arg;
}

std::string getArgMode( std::string buffer )
{
  int position0 = buffer.find( "\"" );
  int position1 = buffer.find( "\"", position0 + 1 );
  if ( position0 < 0 || position1 < 0 ) return "none";
  std::string mode( buffer.substr( position0 + 1, position1 - position0 - 1 ) );

  if ( mode.compare( "seq" ) == 0 && !arg_seq.empty() );
  else if ( mode.compare( "start" ) == 0 && !arg_start.empty() );
  else if ( mode.compare( "ass" ) == 0 && !arg_ass.empty() );
  else if ( mode.compare( "dest" ) == 0 && !arg_dest.empty() );
  else if ( mode.compare( "lou" ) == 0 && !arg_lou.empty() );
  else if ( mode.compare( "art" ) == 0 && !arg_art.empty() );
  else
  {
    mode.erase( 0 );
    mode.append( "none" );
  }

  return mode;
}

std::string getInsertMode( std::string arg )
{
  std::string insert_mode;

  if ( arg.compare( "-seq" ) == 0 ) insert_mode.append( "seq" );
  else if ( arg.compare( "-start" ) == 0 ) insert_mode.append( "start" );
  else if ( arg.compare( "-ass" ) == 0 ) insert_mode.append( "ass" );
  else if ( arg.compare( "-dest" ) == 0 ) insert_mode.append( "dest" );
  else if ( arg.compare( "-lou" ) == 0 ) insert_mode.append( "lou" );
  else if ( arg.compare( "-art" ) == 0 ) insert_mode.append( "art" );

  return insert_mode;
}

void readFile()
{
  std::stringstream ss_file_buffer;
  std::string line_buffer;
  std::ifstream in_file;
  in_file.open( in_file_path.c_str() );
  ss_file_buffer << in_file.rdbuf();
  file_buffer = ss_file_buffer.str();
  in_file.close();
}

void spooling( int loop_count )
{
  int incr_number = loop_count > 0 ? 1 : 0;
  std::stringstream temp_file_buffer;
  temp_file_buffer << file_buffer;
  std::string line_buffer;
  std::string temp_buffer;
  int position;

  do
  {
    std::string arg_mode = "none";
    getline( temp_file_buffer, line_buffer );

    if ( line_buffer.find( "\"" ) != std::string::npos )
    {
      arg_mode.erase( 0 );
      arg_mode.append( getArgMode( line_buffer ) );
    }

    position = line_buffer.find( ":" );

    if ( position >= 0 && line_buffer.at( 0 ) != '#' )
    {
      bool increment = line_buffer.at( 0 ) == '*';
      position += 2;
      line_buffer.erase( 0, position );
      line_buffer.erase( line_buffer.end() - 1 );

      if ( ( increment && incr_number ) || arg_mode.compare( "none" ) != 0 )
      {
        if ( arg_mode.compare( "lou" ) == 0 ) std::cout << "line_buffer<" << line_buffer << ">" << std::endl;

        std::string old_string( line_buffer );
        std::string temp_buffer( createLine( line_buffer, arg_mode, incr_number ) );
        line_buffer.erase( 0 );
        line_buffer.append( temp_buffer );

        if ( arg_mode.compare( "lou" ) == 0 ) std::cout << "line_buffer<" << line_buffer << ">" << std::endl;

        if ( old_string.compare( line_buffer ) != 0 ) updateFileBuffer( old_string, line_buffer );
      }
      out_buffer.append( line_buffer );
    }
  } while ( line_buffer.compare( "EOF" ) && line_buffer.size() );
}

void updateFileBuffer( std::string old_string, std::string new_string )
{
  unsigned int position = file_buffer.find( old_string, 0 );
  if ( position == std::string::npos ) return;
  file_buffer.replace( position, new_string.length(), new_string );
}

int main( int argc, char* argv[] )
{
  in_file_name = argc > 1 ? argv[1] : "";
  std::stringstream ss_number_of_orders;
  if ( argv[ 2 ][ 0 ] == '0' || argv[ 2 ][ 0 ] == '1' || argv[ 2 ][ 0 ] == '2' || argv[ 2 ][ 0 ] == '3'
    || argv[ 2 ][ 0 ] == '4' || argv[ 2 ][ 0 ] == '5' || argv[ 2 ][ 0 ] == '6' || argv[ 2 ][ 0 ] == '7'
    || argv[ 2 ][ 0 ] == '8' || argv[ 2 ][ 0 ] == '9' ) ss_number_of_orders << argv[ 2 ];
  else ss_number_of_orders << "1";

  collectArgs( argc, argv );

  int number_of_orders = 0;
  ss_number_of_orders >> number_of_orders;
  determineInfile();
  readFile();

  for ( int counter = 0; counter < number_of_orders; counter++ )
  {
    spooling( counter );
    if ( counter < number_of_orders - 1 ) out_buffer.append( "\n" );
  }

  createOutfile();
  std::cout << out_buffer << std::endl;

  return 0;
}