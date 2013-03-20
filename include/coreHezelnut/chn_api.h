//  
//  chn-api.h
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
#ifndef coreHezelnut_chn_api_h
#define coreHezelnut_chn_api_h

#include "coreHezelnut/chn_internal.h"
#include "coreHezelnut/selector.h"


CHN_EXTERN_C_BEGIN


/*!
 * @struct chn_varible
 *
 */
typedef struct chn_varible {
    const char*                         var_name;
    const char*                         var_type;
    int                                 var_offset;
} *CHNVariable_ref;


/*!
 * @struct chn_varible_list
 *
 */
typedef struct chn_varible_list {
    struct chn_varible*                 head;
    struct chn_varible_list*            tail;
} *CHNVariableList_ref;



CHN_EXTERN_C_END


#endif  /* coreHezelnut_chn_api_h */
