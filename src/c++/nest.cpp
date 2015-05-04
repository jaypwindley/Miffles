#include "app.h"
#include "dashboard.h"
#include "scale.h"
#include "sweep.h"
#include "meter.h"
#include "field.h"
#include "macros.h"
#include "indicators.h"
#include "input_demux.h"
#include "channel.h"
#include "label.h"
#include "text.h"
#include "nest.h"
#include "background.h"

int main( int argc, char **argv )
{
    using namespace Miffles;

    // Create the application.
    App::create( argc, argv, "Miffles" );

    // Connect it to standard input as the channel stream.
    App::app()->add_input( fileno( stdin ) );
    App::app()->m_demux->m_decoder = new WS_Channel_Decoder();
    App::app()->m_demux->register_channel( "temp", Miffles::Type::NUM );
    App::app()->m_demux->register_channel( "setpoint", Miffles::Type::NUM );
    
    // Create a specialized radial meter.
    Radial_Meter meter( "Nest Temperature" );
    Radial_Field *field =
        new Radial_Field( DEG_TO_RAD( Nest::field_org ),
                          DEG_TO_RAD( Nest::field_arc ) );
    meter.set_field( field );
    meter.m_size = Extent( 480, 480 );

    // Linear scale from 60 F to 90 F.
    Linear_Scale scale( Domain( 60, 90 ) );

    // Black background with the dashed arc.
    Nest::Background bg( "background" );
    meter.add( &bg );

    // Setpoint indicator.
    Nest::Setpoint_Temp setpoint( "setpoint" );
    setpoint.m_sweep = new Sweep( 3.0 );
    App::app()->m_tickables->add( setpoint.m_sweep, &meter );
    setpoint.m_scale = &scale;
    setpoint.listen( "setpoint" );
    meter.add( &setpoint );

    // Center readout.
    Nest::Setpoint_Readout readout( "readout" );
    readout.m_style->m_h_justify = Miffles::Text_Style::CENTER;
    readout.m_style->m_v_justify = Miffles::Text_Style::MIDDLE;
    readout.m_style->m_font_size = 75;
    readout.m_style->m_color = Miffles::Color::White;
    readout.listen( "setpoint" );
    meter.add( &readout );
    
    // Temperature indicator.
    Nest::Actual_Temp actual_temp( "actual_temp" );
    actual_temp.m_sweep = new Sweep( 3.0 );
    App::app()->m_tickables->add( actual_temp.m_sweep, &meter );
    actual_temp.m_scale = &scale;
    actual_temp.listen( "temp" );
    meter.add( &actual_temp );

    App::app()->m_dashboard->add( Point( 0, 0 ), &meter );    
    App::app()->run();
}
