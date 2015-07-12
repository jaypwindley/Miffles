// -----------------------------------------------------------------------
//  File:              domain.h
//  Description:       Measurement domain
//  Author:            Jay Windley <jwindley>
//  Created:           Thu Mar 12 20:14:33 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#include <limits>


namespace miffles {

    static const double MAX_OPEN = std::numeric_limits<double>::infinity();
    static const double MIN_OPEN = -MAX_OPEN;

    //******************************************************************
    // Establishes the domain for a measurement, its minimum and maximum
    // values.  The special values MAX_OPEN and MIN_OPEN can be used to
    // indicate an open-ended value for either endpoint.  m_max - m_min
    // must be non-zero for explicitly numerical endpoints.
    //
    class domain_t {

    private:
        
    protected:
        double m_min;
        double m_max;
        
    public:
        domain_t( double _min, double _max ) :
            m_min( _min ),
            m_max( _max )
        {
            if ( m_max <= m_min ) throw "invalid Domain arguments";
        }
            
        virtual ~domain_t() {}

        double min( void ) { return m_min; }
        double max( void ) { return m_max; }
    };
    
}
