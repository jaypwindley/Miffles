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

#include "types.hpp"
#include "frame.hpp"
#include "midget.hpp"


miffles::frame_t::frame_t( char const *_name ) :
    Gtk::DrawingArea(),
    m_name( std::string( _name ) ),
    m_origin( point_t( 0, 0 ) ),
    m_size( extent_t( 16, 16 ) ),
    m_resize( FIT ),
    m_midgets( new midget_list_t() )
{
}


miffles::frame_t::~frame_t()
{
    delete m_midgets;
}


void miffles::frame_t::add( midget_t *m ) {
    m->m_frame = this;
    m_midgets->push_back( m );
}


void miffles::frame_t::redraw( void )
{
    Glib::RefPtr<Gdk::Window> win = get_window();
    extent_t e = actual_extent();
    Gdk::Rectangle r( 0, 0, e.width(), e.height() );
    win->invalidate_rect( r, false );
}



bool
miffles::frame_t::on_draw( const ::Cairo::RefPtr<::Cairo::Context> &cr ) {
    assert( m_midgets );
    double div = 1.0;
    
    // Place the Midget origin in its center.
    extent_t e = actual_extent();
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
    for ( auto i : *m_midgets ) {
        cr->save();
        i->draw( cr );
        cr->restore();
    }
}


miffles::extent_t miffles::frame_t::actual_extent( void ) {
    // Get these from Glib, regardless of what the original setup might
    // have been.
    //
    auto a = get_allocation();
    auto w = a.get_width();
    auto h = a.get_height();
    return extent_t( w, h );
}
