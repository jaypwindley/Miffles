#include "discrete.hpp"


miffles::discrete_t::discrete_t( char const *_name ) :
    midget_t( _name ),
    m_state( -1 ),
    m_is_circular( false )
{
}


void miffles::discrete_t::add_state( char const *state )
{
    if ( find( state ) != -1 ) {
        throw "duplicate state";
    }
    m_states.push_back( state );
}


void miffles::discrete_t::set( char const *state )
{
    int idx = find( state );
    if ( idx == -1 ) throw "no such state";
    m_state = idx;
}


void miffles::discrete_t::set( const int state )
{
    if ( ( state < 0 ) || ( state >= m_states.size() ) ) {
        throw "state index out of range";
    }
    m_state = state;
    m_frame->redraw();
}


void miffles::discrete_t::inc( void )
{
    ++m_state;
    if ( m_is_circular ) {
        m_state %= m_states.size();
    }
    if ( m_state >= m_states.size() ) {
        m_state = m_states.size() - 1;
    }
}


void miffles::discrete_t::dec( void )
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


 int miffles::discrete_t::find( char const *name )
 {
     std::string state( name );
     for ( int i = 0; i < m_states.size(); ++i ) {
         if ( m_states[ i ] == state ) {
             return i;
         }
     }
     return -1;
 }
