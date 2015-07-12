// -----------------------------------------------------------------------
//  File:              input_demux.hpp
//  Description:       Miffles Input Demultiplexer
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Apr  7 09:08:08 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#include <map>
#include <string>
#include "settable.hpp"

namespace miffles {

    class channel_decoder_t;

    //******************************************************************
    //
    //  Channel data types.
    //
    //******************************************************************
    enum type_t { UNKNOWN = 0, STRING, NUM, BOOL };


    //******************************************************************
    //
    //  Maps a channel name to its data type.
    //
    //******************************************************************
    typedef std::map< std::string, type_t > type_registry_t;


    //******************************************************************
    //
    //  Demultiplexes the channel input and dispatches the channel data
    //  to the Settable objects that listen on it.  Supports any of
    //  multiple decoding methods.
    //
    //******************************************************************
    class input_demultiplexer_t {

    public:
        std::map< std::string, settable_list_t >   m_channels;
        channel_decoder_t                         *m_decoder;
        type_registry_t                            m_types;

    public:
        input_demultiplexer_t();
        virtual ~input_demultiplexer_t() {}

        
        //--------------------------------------------------------------
        // Record that the given channel has a specific data type.  This
        // saves time later when decoding the channel and dispatching
        // it.
        //
        virtual void register_channel( std::string channel, type_t type );

        
        //--------------------------------------------------------------
        // Listen on channel for the given Settable.
        //
        virtual void listen( std::string channel, settable_t *settable );

        
        //--------------------------------------------------------------
        // Decode the channel input and dispatch the data to all the
        // Settable instances that are interested in it.
        //
        virtual void dispatch( std::string input );
    };
    
}
