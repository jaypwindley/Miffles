#include "nest.h"
#include "types.h"
#include "field.h"
#include "meter.h"
#include "macros.h"
#include "text.h"
#include "sweep.h"
#include "scale.h"

Miffles::Nest::Background::Background( char const *_name ) :
    Miffles::Color_Background( _name )
{
    /*EMPTY*/
}


bool Miffles::Nest::Background::draw( const Midget::Cairo_Context &cr )
{
    Miffles::Color_Background::draw( cr );
    Miffles::Radial_Meter *m = dynamic_cast <Radial_Meter *> ( m_frame );
    assert( m->m_field );
    cr->set_line_width( Miffles::Nest::band_thick );
    cr->set_source_rgba( COLOR_SPEC( Color( 0.6, 0.6, 0.6 ) ) );
    std::vector<double> dashes;
    dashes.push_back( Miffles::Nest::dash );
    cr->save();
    cr->set_dash( dashes, 0 );
    cr->arc_negative( 0, 0,
                      Miffles::Nest::radius,
                      m->m_field->m_origin,
                      m->m_field->m_origin - m->m_field->m_extent );
    cr->stroke();
    cr->restore();

    return true;
}
    

Miffles::Nest::Actual_Temp::Actual_Temp( char const *_name ) :
    Miffles::Bug( _name )
{
    /*EMPTY*/
}

bool Miffles::Nest::Actual_Temp::draw( const Midget::Cairo_Context &cr )
{
    Miffles::Radial_Meter *m = dynamic_cast <Radial_Meter *> ( m_frame );
    assert( m->m_field );

    double ang = m->m_field->m_origin -
        m->m_field->m_extent * fraction();

    cr->set_line_width( Miffles::Nest::band_thick );
    cr->set_source_rgba( COLOR_SPEC( Color( 0.8, 0.8, 0.8 ) ) );
    std::vector<double> dashes;
    dashes.push_back( Miffles::Nest::dash );
    cr->save();
    cr->set_dash( dashes, 0 );
    cr->arc_negative( 0, 0,
                      Miffles::Nest::radius,
                      m->m_field->m_origin,
                      ang );
    cr->stroke();

    ang -= 0.1;
    std::string text;
    {
        char s[ 4 ];
        sprintf( s, "%2.0f", m_scale->measure( m_sweep->at() ) );
        text = s;
    }

    {
        Miffles::Text_Style style;
        style.m_h_justify = Miffles::Text_Style::CENTER;
        style.m_v_justify = Miffles::Text_Style::MIDDLE;
        style.m_font_size = 12.0;
        style.m_color = Color( 0.8, 0.8, 0.8 );
        Point pt( Miffles::Nest::radius * cos( ang ),
                  Miffles::Nest::radius * sin( ang ) );
        render_text( cr, &style, pt, text );
    }
    
    cr->restore();


    return true;
}

Miffles::Nest::Setpoint_Temp::Setpoint_Temp( char const *_name ) :
    Miffles::Indicator( _name )
{
}

bool Miffles::Nest::Setpoint_Temp::draw( const Midget::Cairo_Context &cr )
{
    Miffles::Radial_Meter *m = dynamic_cast <Radial_Meter *> ( m_frame );
    assert( m->m_field );

    double ang = m->m_field->m_origin -
        m->m_field->m_extent * fraction();

    cr->save();
    cr->rotate( ang );
    cr->set_source_rgba( COLOR_SPEC( Miffles::Color::White ) );
    cr->set_line_width( 3.0 );
    cr->move_to( Miffles::Nest::radius - (Miffles::Nest::band_thick / 2) - Miffles::Nest::bug_offset, 0 );
    cr->line_to( Miffles::Nest::radius + (Miffles::Nest::band_thick / 2), 0 );
    cr->stroke();
    cr->restore();
    
    return true;
}


Miffles::Nest::Setpoint_Readout::Setpoint_Readout( char const *_name ) :
    Miffles::Readout( _name )
{
    /*EMPTY*/
}

bool
Miffles::Nest::Setpoint_Readout::draw( const Midget::Cairo_Context &cr )
{
    char label[8];
    sprintf( label, "%2.0f", m_value );
    m_text = label;
    Miffles::Label::draw( cr );
    return true;
}
