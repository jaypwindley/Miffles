// -----------------------------------------------------------------------
//  File:              macros.hpp
//  Description:       Miffles preprocessor macros
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 00:09:09 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#define PI 3.14159265359

// Convert degrees to radians.
#define DEG_TO_RAD(x)  ((x)*(PI/180.0))

// Convert the fraction of a circle to radians.
#define FRAC_TO_RAD(x) ((x)*(2*PI))

