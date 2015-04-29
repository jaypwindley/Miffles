// -----------------------------------------------------------------------
//  File:              frame.cpp
//  Description:       Miffles Frame functions
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 12:36:27 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include <gtkmm.h>
#include <string>

#include "types.h"
#include "frame.h"
#include "midget.h"


Miffles::Frame::Frame( char const *_name ) :
    Gtk::DrawingArea(),
    m_name( std::string( _name ) ),
    m_origin( Point( 0, 0 ) ),
    m_size( Extent( 16, 16 ) ),
    m_resize( FIT ),
    m_midgets( new Midget_List() )
{
    /*EMPTY*/
}


Miffles::Frame::~Frame()
{
    delete m_midgets;
}


void Miffles::Frame::add( Midget *m ) {
    m->m_frame = this;
    m_midgets->push_back( m );
}


void Miffles::Frame::redraw( void )
{
    Glib::RefPtr<Gdk::Window> win = get_window();
    Extent e = actual_extent();
    Gdk::Rectangle r( 0, 0, e.width(), e.height() );
    win->invalidate_rect( r, false );
}



bool
Miffles::Frame::on_draw( const ::Cairo::RefPtr<::Cairo::Context> &cr ) {
    assert( m_midgets );
    double div = 1.0;
    
    // Place the Midget origin in its center.
    Extent e = actual_extent();
    cr->translate( m_origin.x() + e.width()  / 2,
                   m_origin.y() + e.height() / 2 );

    // Scale the Midget according to the Frame's resize policy.
    switch( m_resize ) {
    case FIT:
        div = ( e.width() > e.height() ) ? e.height() : e.width();
        break;
    case CLIP:
        div = ( e.width() < e.height() ) ? e.height() : e.width();
        break;
    }
    cr->scale( div / 200.0, div / -200.0 );

    // Now tell each Midget, in order, to draw itself with the
    // transformed context.
    //
    for ( auto i = m_midgets->begin();
          i != m_midgets->end(); ++i ) {
        cr->save();
        (*i)->draw( cr );
        cr->restore();
    }
}


Miffles::Extent Miffles::Frame::actual_extent( void ) {
    // Get these from Glib, regardless of what the original setup might
    // have been.
    //
    auto a = get_allocation();
    auto w = a.get_width();
    auto h = a.get_height();
    return Extent( w, h );
}
