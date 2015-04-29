// -----------------------------------------------------------------------
//  File:              channel.h
//  Description:       Miffles data Channel
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Apr  7 08:42:43 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#ifndef __MIFFLES_CHANNEL_H__
#define __MIFFLES_CHANNEL_H__

#include <string>
#include <vector>

namespace Miffles {

    //******************************************************************
    //
    //  A vector of words that represent a channel input record after
    //  decoding.
    //
    //******************************************************************
    typedef std::vector<std::string> Token_List;

    //------------------------------------------------------------------
    // Test whether the strings can be decoded into the given atomic
    // types.
    //
    bool is_bool(    const std::string &val );
    bool is_string(  const std::string &val );
    bool is_num(     const std::string &val );

    
    //------------------------------------------------------------------
    // Convert the strings to their atomic values.  Words like "true"
    // and "yes" convert to Boolean-true.  Strings of digits, signs, and
    // decimals convert to numbers (double).
    //
    bool   to_bool(  const std::string &val );
    double to_num(   const std::string &val );


    //******************************************************************
    //
    //  Channel Decoder decomposes channel input into channel names,
    //  values, etc.
    //
    //******************************************************************
    class Channel_Decoder {
    public:
        virtual ~Channel_Decoder() {}
        virtual Token_List parse( std::string &data ) = 0;
    };


    //******************************************************************
    //
    //  Channel Decoder that separates tokens by white space.
    //
    //******************************************************************
    class WS_Channel_Decoder : public Channel_Decoder {
    public:
        virtual ~WS_Channel_Decoder() {}
        virtual Token_List parse( std::string &data );
    };   
}

#endif /*__MIFFLES_CHANNEL_H__*/
