// -----------------------------------------------------------------------
//  File:              channel.cpp
//  Description:       Channel and Channel Decoder functions
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Apr  7 08:56:51 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include <algorithm>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include "channel.hpp"

miffles::token_list_t
miffles::ws_channel_decoder_t::parse( std::string &data )
{
    static const std::string delim = " \t\n";
    token_list_t tokens;

    // Tokenize input string according to white space.
    std::string::size_type lpos = data.find_first_not_of( delim, 0 );
    std::string::size_type pos = data.find_first_of( delim, lpos );
    while ( std::string::npos != pos || std::string::npos != lpos ) {
        tokens.push_back( data.substr( lpos, pos - lpos ) );
        lpos = data.find_first_not_of( delim, pos );
        pos = data.find_first_of( delim, lpos );
    }
    return tokens;
}


bool miffles::is_bool( const std::string &val )
{
    std::string s = val;
    std::transform( s.begin(), s.end(), s.begin(), ::tolower );
    if ( s == "true"  ) return true;
    if ( s == "false" ) return true;
    if ( s == "yes"   ) return true;
    if ( s == "no"    ) return true;
    if ( s == "on"    ) return true;
    if ( s == "off"   ) return true;
    return false;
}


bool miffles::is_string( const std::string &val )
{
    return true;
}


bool miffles::is_num( const std::string &val )
{
    for ( auto ch : val ) {
        if ( ch == '.' )       continue;
        if ( ch == '+' )       continue;
        if ( ch == '-' )       continue;
        if ( ::isdigit( ch ) ) continue;
        return false;
    }
    return true;
}


bool miffles::to_bool( const std::string &val )
{
    std::string s = val;
    std::transform( s.begin(), s.end(), s.begin(), ::tolower );
    if ( s == "true" ||
         s == "yes"  ||
         s == "on" )
        return true;
    else return false;
}


double miffles::to_num( const std::string &val )
{
    double num;
    if ( sscanf( val.c_str(), "%lf", &num ) != 1 ) {
        throw "Miffles::to_num() cannot convert string to number";
    }
    return num;
}
