#include "annunciator.hpp"
#include "frame.hpp"

miffles::annunciator_t::annunciator_t( char const *_name ) :
    midget_t( _name )
{
}


void miffles::annunciator_t::set( bool _is_on )
{
    m_is_on = _is_on;
    m_frame->redraw();
}


bool miffles::annunciator_t::draw( const cairo_context_t &cr )
{
    return true;
}


