// -----------------------------------------------------------------------
//  File:              indicators.cpp
//  Description:       Functions for various indicators
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 18:47:55 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "indicators.h"
#include "macros.h"
#include "meter.h"
#include "field.h"
#include "types.h"

Miffles::Basic_Needle_Indicator::Basic_Needle_Indicator( char const *_name ) :
    Indicator( _name ),
    m_length( 90 ),
    m_thick( 1 )
{
}


bool
Miffles::Basic_Needle_Indicator::draw( const Midget::Cairo_Context &cr ) {

    assert( m_frame );
    
    // XXX all this should move into Field or Scale.
    try {
        Miffles::Meter *m =
            static_cast <Miffles::Meter *> ( m_frame );
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



Miffles::Basic_Pointer_Indicator::Basic_Pointer_Indicator( char const *_name ) :
    Indicator( _name ),
    m_thick( 1 )
{
}


bool
Miffles::Basic_Pointer_Indicator::draw( const Midget::Cairo_Context &cr )
{
    assert( m_frame );

    static Miffles::Color gutter( "gray50" );
    
    // XXX all this should move into Field or Scale.
    try {
        Miffles::Meter *m =
            static_cast <Miffles::Meter *> ( m_frame );
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

        Miffles::Linear_Field *lfield =
            static_cast<Linear_Field *> ( m->m_field );

        cr->set_source_rgba( COLOR_SPEC( gutter ) );
        cr->rectangle( -30,
                       lfield->m_origin,
                       60,
                       lfield->m_extent );
        cr->fill();

        cr->set_source_rgba( COLOR_SPEC( Miffles::Color::Red ) );
        cr->set_line_width( m_thick );

        switch( lfield->m_orientation ) {
        case Miffles::Linear_Field::VERTICAL:
            cr->move_to( -50, pos );
            cr->line_to(  50, pos );
            break;
        case Miffles::Linear_Field::HORIZONTAL:
            cr->move_to( pos, -50 );
            cr->line_to( pos,  50 );
            break;
        }

        cr->stroke();

    } catch ( std::bad_cast e ) {
        /*EMPTY*/
    }
    
}
