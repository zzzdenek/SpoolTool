// ArgsHandler.h
// Author: Zdenek Zeman
// Last change: 19-11-21

#ifndef ARGSHANDLER_H
#define ARGSHANDLER_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include "Arguments.h"

class ArgsHandler
{
private:
    std::vector< std::shared_ptr< Arguments > > args_;

    ArgsHandler( const ArgsHandler &copy ) {};

public:
    ArgsHandler( int, char** );
    ~ArgsHandler() {};

    void addNewArgs( std::string );
    void addArgToArgs( std::string, std::string );

    std::string getArgs();
    std::string getFileName();
};

#endif