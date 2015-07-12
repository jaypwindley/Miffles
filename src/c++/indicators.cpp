// -----------------------------------------------------------------------
//  File:              indicators.cpp
//  Description:       Functions for various indicators
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 18:47:55 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "indicators.hpp"
#include "macros.hpp"
#include "meter.hpp"
#include "field.hpp"
#include "types.hpp"

miffles::basic_needle_indicator_t::basic_needle_indicator_t( char const *_name ) :
    indicator_t( _name ),
    m_length( 90 ),
    m_thick( 1 )
{
}


bool
miffles::basic_needle_indicator_t::draw( const midget_t::cairo_context_t &cr ) {

    assert( m_frame );
    
    // XXX all this should move into Field or Scale.
    try {
        miffles::meter_t *m =
            static_cast <miffles::meter_t *> ( m_frame );
        assert( m->m_field );

        // Compute the angle that corresponds to the Scale-normalized
        // position of the indicator.
        //
        // XXX make fraction() enforce the peg constraint.
        double ang = m->m_field->m_origin -
            m->m_field->m_extent * fraction();

        // If the field is pegged, clamp the angle to the pegs.
        if ( m->m_field->m_has_peg ) {
            if ( ang > m->m_field->m_origin )
                ang = m->m_field->m_origin;
            if ( fraction() > 1.0 )
                ang = m->m_field->m_origin - m->m_field->m_extent;
        }
        
        cr->rotate( ang );
    } catch ( std::bad_cast e ) {
        /*EMPTY*/
    }
    
    cr->set_source_rgb( 0, 0, 0 );
    cr->set_line_width( m_thick );
    cr->move_to( 0, 0 );
    cr->line_to( m_length, 0 );
    cr->stroke();
}



miffles::basic_pointer_indicator_t::basic_pointer_indicator_t( char const *_name ) :
    indicator_t( _name ),
    m_thick( 1 )
{
}


bool
miffles::basic_pointer_indicator_t::draw( const midget_t::cairo_context_t &cr )
{
    assert( m_frame );

    static miffles::color_t gutter( "gray50" );
    
    // XXX all this should move into Field or Scale.
    try {
        miffles::meter_t *m =
            static_cast <miffles::meter_t *> ( m_frame );
        assert( m->m_field );


        // XXX make fraction() enforce the peg constraint.
        double pos = m->m_field->m_origin +
            m->m_field->m_extent * fraction();

        // If the field is pegged, clamp the angle to the pegs.
        if ( m->m_field->m_has_peg ) {
            if ( pos < m->m_field->m_origin )
                pos = m->m_field->m_origin;
            if ( fraction() > 1.0 )
                pos = m->m_field->m_origin + m->m_field->m_extent;
        }

        miffles::linear_field_t *lfield =
            static_cast<linear_field_t *> ( m->m_field );

        cr->set_source_rgba( COLOR_SPEC( gutter ) );
        cr->rectangle( -30,
                       lfield->m_origin,
                       60,
                       lfield->m_extent );
        cr->fill();

        cr->set_source_rgba( COLOR_SPEC( miffles::color_t::red ) );
        cr->set_line_width( m_thick );

        switch( lfield->m_orientation ) {
        case miffles::linear_field_t::VERTICAL:
            cr->move_to( -50, pos );
            cr->line_to(  50, pos );
            break;
        case miffles::linear_field_t::HORIZONTAL:
            cr->move_to( pos, -50 );
            cr->line_to( pos,  50 );
            break;
        }

        cr->stroke();

    } catch ( std::bad_cast e ) {
        /*EMPTY*/
    }
    
}
