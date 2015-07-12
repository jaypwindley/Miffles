// -----------------------------------------------------------------------
//  File:              input_demux.h
//  Description:       Miffles Input Demultiplexer
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Apr  7 09:08:08 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#ifndef __MIFFLES_INPUT_DEMUX_H__
#define __MIFFLES_INPUT_DEMUX_H__

#include <map>
#include <string>
#include "settable.h"

namespace Miffles {

    class Channel_Decoder;

    //******************************************************************
    //
    //  Channel data types.
    //
    //******************************************************************
    enum Type { UNKNOWN = 0, STRING, NUM, BOOL };


    //******************************************************************
    //
    //  Maps a channel name to its data type.
    //
    //******************************************************************
    typedef std::map< std::string, Type > Type_Registry;


    //******************************************************************
    //
    //  Demultiplexes the channel input and dispatches the channel data
    //  to the Settable objects that listen on it.  Supports any of
    //  multiple decoding methods.
    //
    //******************************************************************
    class Input_Demultiplexer {

    public:
        std::map< std::string, Settable_List >     m_channels;
        Channel_Decoder                           *m_decoder;
        Type_Registry                              m_types;

    public:
        Input_Demultiplexer();
        virtual ~Input_Demultiplexer() {}

        
        //--------------------------------------------------------------
        // Record that the given channel has a specific data type.  This
        // saves time later when decoding the channel and dispatching
        // it.
        //
        virtual void register_channel( std::string channel, Type type );

        
        //--------------------------------------------------------------
        // Listen on channel for the given Settable.
        //
        virtual void listen( std::string channel, Settable *settable );

        
        //--------------------------------------------------------------
        // Decode the channel input and dispatch the data to all the
        // Settable instances that are interested in it.
        //
        virtual void dispatch( std::string input );
    };
    
}

#endif /*__MIFFLES_INPUT_DEMUX_H__*/
