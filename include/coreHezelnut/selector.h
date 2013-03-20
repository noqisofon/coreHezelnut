//  
//  selector.h
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
#ifndef coreHezelnut_selector_h
#define coreHezelnut_selector_h

#include "coreHezelnut/runtime.h"


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


CHN_EXTERN_C_END


#endif  /* coreHezelnut_selector_h */
// Local Variables:
//   coding: utf-8
// End:
