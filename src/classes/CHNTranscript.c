//  
//  CHNTranscript.c
//  
//  Auther:
//       ned rihine <ned.rihine@gmail.com>
// 
//  Copyright (c) 2012 rihine All rights reserved.
// 
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
// 
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
// 
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include "config.h"

#include <stdio.h>

#include "coreHezelnut/runtime.h"
#include "coreHezelnut/chn_class.h"
#include "coreHezelnut/callbacks.h"

#include "coreHezelnut/classes/CHNTranscript.h"


CHN_EXPORT void CHNTranscript_class_cr(void)
{
}


CHN_EXPORT void CHNTranscript_class_show(const char* a_cstring)
{
    printf( "%s", a_cstring );
}


CHN_EXPORT void CHNTranscript_class_showCr(const char* a_cstring)
{
    printf( "%s\n", a_cstring );
}
// Local Variables:
//   coding: utf-8
// End:
