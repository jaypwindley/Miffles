#include <assert.h>
#include "input_demux.h"
#include "channel.h"

Miffles::Input_Demultiplexer::Input_Demultiplexer() :
    m_decoder( NULL )
{
    /*EMPTY*/
}


void
Miffles::Input_Demultiplexer::register_channel( std::string channel,
                                                Type type )
{
    m_types[ channel ] = type;
}


void
Miffles::Input_Demultiplexer::listen( std::string channel,
                                      Settable *settable )
{
    assert( settable );
    m_channels[ channel ].push_back( settable );
}

void Miffles::Input_Demultiplexer::dispatch( std::string input )
{
    assert( m_decoder );
    Token_List tokens = m_decoder->parse( input );

    double      val_double;
    bool        val_bool;
    std::string val_str;

    if ( tokens.size() == 0 ) return;
    
    // Look up the data type for this channel information.
    Miffles::Type t = m_types[ tokens[ 0 ] ];
    switch( t ) {
    case Miffles::Type::UNKNOWN:
        // Infer type.
        break;
    case Miffles::Type::NUM:
        val_double = Miffles::to_num( tokens[ 1 ] );
        break;
    case Miffles::Type::BOOL:
        val_bool = Miffles::to_bool( tokens[ 1 ] );
        break;
    case Miffles::Type::STRING:
        val_str = tokens[ 1 ];
        break;
    }

    for ( auto i = m_channels[ tokens[ 0 ] ].begin();
          i != m_channels[ tokens[ 0 ] ].end();
          ++i ) {

        // XXX This really isn't an elegant way to be polymorphic.  I
        // feel dirty.  Fix this.
        //
        switch( t ) {
        case Miffles::Type::NUM:
            (*i)->set( val_double );
            break;
        case Miffles::Type::BOOL:
            (*i)->set( val_bool );
            break;
        case Miffles::Type::STRING:
            (*i)->set( val_str );
            break;
        }

        
    }
}
