#include "discrete.h"


Miffles::Discrete::Discrete( char const *_name ) :
    Midget( _name ),
    m_state( -1 ),
    m_is_circular( false )
{
    /*EMPTY*/
}


void Miffles::Discrete::add_state( char const *state )
{
    if ( find( state ) != -1 ) {
        throw "duplicate state";
    }
    m_states.push_back( state );
}


void Miffles::Discrete::set( char const *state )
{
    int idx = find( state );
    if ( idx == -1 ) throw "no such state";
    m_state = idx;
}


void Miffles::Discrete::set( const int state )
{
    if ( ( state < 0 ) || ( state >= m_states.size() ) ) {
        throw "state index out of range";
    }
    m_state = state;
    m_frame->redraw();
}


void Miffles::Discrete::inc( void )
{
    ++m_state;
    if ( m_is_circular ) {
        m_state %= m_states.size();
    }
    if ( m_state >= m_states.size() ) {
        m_state = m_states.size() - 1;
    }
}


void Miffles::Discrete::dec( void )
{
    --m_state;
    if ( m_state < 0 ) {
        if ( m_is_circular ) {
            m_state = m_states.size() - 1;
        } else {
            m_state = 0;
        }
    }
}


 int Miffles::Discrete::find( char const *name )
 {
     std::string state( name );
     for ( int i = 0; i < m_states.size(); ++i ) {
         if ( m_states[ i ] == state ) {
             return i;
         }
     }
     return -1;
 }
