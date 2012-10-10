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


CHN_EXTERN_C_BEGIN


typedef struct chn_selector {
    void*               actual_id;       /*!< 関数ポインタ。 */
    const char*         func_type;       /*!< その関数の型。 */
} *SEL;


#ifdef CHN_INLINE
CHN_INLINE CHNBoolean sel_eq(SEL left, SEL right)
{
    if ( left == NULL || right == NULL )
        return left == right;
    else
        return left->actual_id == right->actual_id;
}
#else
#   define sel_eq(_left_, _right_)  __sel_eq(_left_, _right_)
#endif  /* def CHN_INLINE */


CHN_EXPORT CHNBoolean __sel_eq(SEL left, SEL right);


typedef id (*IMP)(id, SEL, ...);


typedef struct chn_varible {
    const char*                         var_name;
    const char*                         var_type;
    int                                 var_offset;
} *CHNVariable_ref;


typedef struct chn_varible_list {
    struct chn_varible*                 head;
    struct chn_varible_list*            tail;
} *CHNVariableList_ref;


CHN_EXPORT void chn_error(id context, int error_code, const char* format, ...);


typedef id (*chn_if_abesent_callback)(void* context);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_chn_api_h */
