//
// Created by zeman on 02.07.2019.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main( int argc, char* argv[] )
{
  ifstream in_file;
  ofstream out_file;
  string in_buffer;
  string out_buffer;
  int position;
  string in_file_name = argc > 1 ? argv[1] : "";
  string in_file_path;
  string out_file_name;
  string out_file_path;

  if ( in_file_name.empty() )
  {
    cout << "FILE?" << endl;
    getline( cin, in_file_name );
  }

  in_file_name.append( ".txt" );
  in_file_path = "./";
  in_file_path.append( in_file_name );
  out_file_name = "F.";
  out_file_name.append( in_file_name );
  out_file_path = "./temp/";
  out_file_path.append( out_file_name );
  in_file.open( in_file_path.c_str() );

  do
  {
    getline( in_file, in_buffer );
    position = in_buffer.find( ":" );
    if( position >= 0 && in_buffer.at( 0 ) != '#' )
    {
      position += 2;
      in_buffer.erase( 0, position );
      in_buffer.erase( in_buffer.end() - 1 );
      out_buffer.append( in_buffer );
    }
  } while( in_buffer.compare( "EOF" ) && in_buffer.size() );

  toClipboard( out_buffer.str() );

  in_file.close();
  out_file.open( out_file_path.c_str() );
  out_file << out_buffer;
  out_file.close();
  cout << out_buffer << endl;

  return 0;
}