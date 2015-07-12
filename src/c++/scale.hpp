// -----------------------------------------------------------------------
//  File:              scale.hpp
//  Description:       Linear and nonlinear scales
//  Author:            Jay Windley <jwindley>
//  Created:           Fri Mar 13 18:24:04 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "domain.hpp"

namespace miffles {

    //******************************************************************
    // Maps a measurement to a Field.  m_origin is the measurement that
    // should be indicated at the Field.m_origin position.  The
    // specialized classes determine where subsequent values fall.
    //
    class scale_t {
        
    protected:
        double          m_origin;
        double          m_size;
        
    public:
        scale_t( double _origin, double _size) :
            m_origin( _origin ),
            m_size( _size )
        {
        }

        virtual ~scale_t()
        {
        }

        //--------------------------------------------------------------
        // Returns the fraction of the given measure evaluated according
        // to the scale.  The resulting fraction should be evaluated
        // against an appropriate Field to give an indicator value.  The
        // value can be outside the range [0,1].
        //
        virtual double fraction( const double measure ) = 0;


        //--------------------------------------------------------------
        // The inverse of fraction().  Returns a measure in Domain space
        // given the non-normalized fraction measure.  The value of
        // fraction can be outside the range [0,1].
        //
        virtual double measure( const double fraction ) = 0;
    };


    
    //******************************************************************
    // A linear scale where indicator movement is directly proportional
    // to changes in measurement.  m_origin is as specified in the
    // abstract base class above.  m_size is the amount of Domain value
    // that corresponds to Field.m_extent.  For most gauges with finite
    // domains, this is Domain.m_max - Domain.m_min.
    //
    class linear_scale_t : public scale_t {

    public:
        
        linear_scale_t( double _origin, double _size ) :
            scale_t( _origin, _size )
        {
        }

        linear_scale_t( domain_t d );

        virtual double fraction( const double measure );
        virtual double measure( const double fraction );
    };



    //******************************************************************
    // A nonlinear scale where indicator movement is proportional to the
    // logarithm of the measurement in the given base.  m_size is in
    // post-scaled units (i.e., the exponent).  m_origin is in
    // pre-scaled Domain units.
    //
    class nonlinear_scale_t : public scale_t {

    private:
        double          m_base_conv;
        
    public:

        nonlinear_scale_t( double _origin,
                           double _size,
                           double _base = 10.0 );
        
        virtual double fraction( const double measure );
        virtual double measure( const double fraction );
    };
}
