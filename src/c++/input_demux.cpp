#include <assert.h>
#include "input_demux.hpp"
#include "channel.hpp"

miffles::input_demultiplexer_t::input_demultiplexer_t() :
    m_decoder( NULL )
{
}


void
miffles::input_demultiplexer_t::register_channel( std::string channel,
                                                  type_t type )
{
    m_types[ channel ] = type;
}


void
miffles::input_demultiplexer_t::listen( std::string channel,
                                        settable_t *settable )
{
    assert( settable );
    m_channels[ channel ].push_back( settable );
}

void miffles::input_demultiplexer_t::dispatch( std::string input )
{
    assert( m_decoder );
    token_list_t tokens = m_decoder->parse( input );

    double      val_double;
    bool        val_bool;
    std::string val_str;

    if ( tokens.size() == 0 ) return;
    
    // Look up the data type for this channel information.
    miffles::type_t t = m_types[ tokens[ 0 ] ];
    switch( t ) {
    case miffles::type_t::UNKNOWN:
        // Infer type.
        break;
    case miffles::type_t::NUM:
        val_double = miffles::to_num( tokens[ 1 ] );
        break;
    case miffles::type_t::BOOL:
        val_bool = miffles::to_bool( tokens[ 1 ] );
        break;
    case miffles::type_t::STRING:
        val_str = tokens[ 1 ];
        break;
    }

    for ( auto i : m_channels[ tokens[ 0 ] ] ) {
        // XXX This really isn't an elegant way to be polymorphic.  I
        // feel dirty.  Fix this.
        //
        switch( t ) {
        case miffles::type_t::NUM:
            i->set( val_double );
            break;
        case miffles::type_t::BOOL:
            i->set( val_bool );
            break;
        case miffles::type_t::STRING:
            i->set( val_str );
            break;
        }

        
    }
}
