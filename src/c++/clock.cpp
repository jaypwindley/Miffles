#include "app.h"
#include "dashboard.h"
#include "scale.h"
#include "sweep.h"
#include "meter.h"
#include "field.h"
#include "macros.h"
#include "graduation.h"
#include "indicators.h"
#include "input_demux.h"
#include "channel.h"
#include "annunciators.h"
#include "label.h"
#include "text.h"

int main( int argc, char **argv )
{
    using namespace Miffles;
    
    App::create( argc, argv, "Miffles" );

    //App::app()->add_input( "/var/spool/miffles/pipes/data" );
    App::app()->add_input( fileno( stdin ) );
    App::app()->m_demux->m_decoder = new WS_Channel_Decoder();
    
#if 1    
    Radial_Meter test_meter( "Temperature" );
    Radial_Field *field = new Radial_Field( DEG_TO_RAD( 240 ),
                                                DEG_TO_RAD( 300 ) );
    assert( field );
    field->m_has_peg = true;
    test_meter.set_field( field );

    test_meter.m_size = Extent( 480, 480 );

    Linear_Scale my_scale( Domain( 50, 110 ) );
    
    Basic_Needle_Indicator hand( "hand" );
    hand.m_length = 75;
    hand.m_sweep = new Sweep( 3.0 );
    hand.m_scale = &my_scale;
    App::app()->m_demux->register_channel( "temp", Miffles::Type::NUM );
    hand.listen( "temp" );
    App::app()->m_tickables->add( hand.m_sweep, &test_meter );

    Graduation grad( "temp_grad" );
    grad.m_scale = &my_scale;
    grad.m_field = field;

    test_meter.add( &grad );
    test_meter.add( &hand );
    
    App::app()->m_dashboard->add( Point( 0, 0 ), &test_meter );
#endif
#if 0
    App::app()->m_demux->register_channel( "percent", Miffles::Type::NUM );
    
    Linear_Meter foo_meter( "percent_meter" );
    Linear_Field *foo_field =
        new Linear_Field( -90, 180, Linear_Field::VERTICAL );
    foo_meter.m_size = Extent( 200, 480 );
    foo_meter.m_resize = Frame::FIT;
    foo_field->m_has_peg = true;
    foo_meter.set_field( foo_field );
    
    Linear_Scale foo_scale( Domain( 0, 100 ) );
    
    Basic_Pointer_Indicator hand( "hand" );
    hand.listen( "percent" );
    hand.m_sweep = new Sweep( 2.75 );
    hand.m_scale = &foo_scale;
    App::app()->m_tickables->add( hand.m_sweep );

    foo_meter.add( &hand );

    App::app()->m_dashboard->add( Point( 0, 0 ), &foo_meter );
#endif
#if 0
    App::app()->m_demux->register_channel( "thing", Miffles::Type::BOOL );

    Basic_Lightbulb_Annunciator ann( "thing" );
    ann.listen( "thing" );
    Frame frame( "thing" );
    frame.m_size = Extent( 128, 128 );
    frame.add( &ann );
    App::app()->m_dashboard->add( Point( 0, 0 ), &frame );
#endif
#if 0
    Miffles::Label label( "thing" );
    label.m_style->m_h_justify = Miffles::Text_Style::CENTER;
    label.m_style->m_v_justify = Miffles::Text_Style::MIDDLE;
    label.m_text = "HELLO";
    Frame frame( "thing" );
    frame.m_size = Extent( 128, 128 );
    frame.add( &label );
    App::app()->m_dashboard->add( Point( 0, 0 ), &frame );
#endif
    
    App::app()->run();
}
