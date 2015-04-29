#include "annunciator.h"
#include "frame.h"

Miffles::Annunciator::Annunciator( char const *_name ) :
    Midget( _name )
{
}


void Miffles::Annunciator::set( bool _is_on )
{
    m_is_on = _is_on;
    m_frame->redraw();
}


bool Miffles::Annunciator::draw( const Cairo_Context &cr )
{
    return true;
}


