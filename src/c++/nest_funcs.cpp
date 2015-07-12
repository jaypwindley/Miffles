#include <gdkmm/pixbuf.h>
#include "nest.hpp"
#include "types.hpp"
#include "field.hpp"
#include "meter.hpp"
#include "macros.hpp"
#include "text.hpp"
#include "sweep.hpp"
#include "scale.hpp"

miffles::nest::background_t::background_t( char const *_name ) :
    miffles::color_background_t( _name )
{
}


bool miffles::nest::background_t::draw( const midget_t::cairo_context_t &cr )
{
    miffles::color_background_t::draw( cr );
    miffles::radial_meter_t *m = dynamic_cast <radial_meter_t *> ( m_frame );
    assert( m->m_field );
    cr->set_line_width( miffles::nest::band_thick );
    cr->set_source_rgba( COLOR_SPEC( color_t( 0.6, 0.6, 0.6 ) ) );
    std::vector<double> dashes;
    dashes.push_back( miffles::nest::dash );
    cr->save();
    cr->set_dash( dashes, 0 );
    cr->arc_negative( 0, 0,
                      miffles::nest::radius,
                      m->m_field->m_origin,
                      m->m_field->m_origin - m->m_field->m_extent );
    cr->stroke();
    cr->restore();

    return true;
}
    
#if 0
Miffles::Nest::Actual_Temp::Actual_Temp( char const *_name ) :
    Miffles::Bug( _name )
{
    /*EMPTY*/
}
#else
miffles::nest::actual_temp_t::actual_temp_t( char const *_name,
                                             std::string file,
                                             miffles::point_t _anchor ) :
    miffles::bug_t( _name ),
    m_anchor( _anchor )
{
    m_pixbuf = Gdk::Pixbuf::create_from_file( file );    
}
#endif

bool miffles::nest::actual_temp_t::draw( const midget_t::cairo_context_t &cr )
{
    miffles::radial_meter_t *m = dynamic_cast <radial_meter_t *> ( m_frame );
    assert( m->m_field );

    double ang = m->m_field->m_origin -
        m->m_field->m_extent * fraction();

 #if 0
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
 #else

    cr->save();

    // Rotate into the indicated angle.
    cr->rotate( ang );

    // "fudge" compensates in this one and only case for the likelihood
    // that the images that describe a radial indicator are about half
    // the size of the intended pixel resolution of the Frame/Meter.  In
    // the final form, the proper scale factor should be inferred from
    // objective data.
    //
    static const double fudge = 1.7;
    double scale_factor = ( 200.0 / fudge ) / m_pixbuf->get_width();

    // Translate the pixel map to the designated (scaled) anchor point.
    cr->translate( -m_anchor.x() * scale_factor, -m_anchor.y() * scale_factor );

    // ...and then scale the pixmap to standard [-200,200] coordinates.
    cr->scale( scale_factor, scale_factor );
    
    Gdk::Cairo::set_source_pixbuf( cr, m_pixbuf, 0, 0 );
    cr->paint();
    
    cr->restore();
    
 #endif

    return true;
}

miffles::nest::setpoint_temp_t::setpoint_temp_t( char const *_name ) :
    miffles::indicator_t( _name )
{
}

bool miffles::nest::setpoint_temp_t::draw( const midget_t::cairo_context_t &cr )
{
    miffles::radial_meter_t *m = dynamic_cast <radial_meter_t *> ( m_frame );
    assert( m->m_field );

    double ang = m->m_field->m_origin -
        m->m_field->m_extent * fraction();

    cr->save();
    cr->rotate( ang );
    cr->set_source_rgba( COLOR_SPEC( miffles::color_t::white ) );
    cr->set_line_width( 3.0 );
    cr->move_to( miffles::nest::radius - (miffles::nest::band_thick / 2) - miffles::nest::bug_offset, 0 );
    cr->line_to( miffles::nest::radius + (miffles::nest::band_thick / 2), 0 );
    cr->stroke();
    cr->restore();
    
    return true;
}


miffles::nest::setpoint_readout_t::setpoint_readout_t( char const *_name ) :
    miffles::readout_t( _name )
{
}

bool
miffles::nest::setpoint_readout_t::draw( const midget_t::cairo_context_t &cr )
{
    char label[8];
    sprintf( label, "%2.0f", m_value );
    m_text = label;
    miffles::label_t::draw( cr );
    return true;
}
