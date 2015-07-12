// -----------------------------------------------------------------------
//  File:              channel.h
//  Description:       Miffles data Channel
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Apr  7 08:42:43 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#include <string>
#include <vector>

namespace miffles {

    //******************************************************************
    //
    //  A vector of words that represent a channel input record after
    //  decoding.
    //
    //******************************************************************
    typedef std::vector<std::string> token_list_t;

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
    class channel_decoder_t {
    public:
        virtual ~channel_decoder_t() {}
        virtual token_list_t parse( std::string &data ) = 0;
    };


    //******************************************************************
    //
    //  Channel Decoder that separates tokens by white space.
    //
    //******************************************************************
    class ws_channel_decoder_t : public channel_decoder_t {
    public:
        virtual ~ws_channel_decoder_t() {}
        virtual token_list_t parse( std::string &data );
    };   
}

