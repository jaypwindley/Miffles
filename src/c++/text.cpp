// -----------------------------------------------------------------------
//  File:              text.cpp
//  Description:       Miffles Text style functions
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Apr  7 16:36:07 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "text.hpp"

miffles::text_style_t::text_style_t() :
    m_h_justify( LEFT ),
    m_v_justify( BOTTOM ),
    m_font_size( 24.0 ),
    m_color( miffles::color_t::black )
{
}
