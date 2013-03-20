//  
//  callbacks.h
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
#ifndef coreHezelnut_callbacks_h
#define coreHezelnut_callbacks_h

#include "coreHezelnut/runtime.h"


/*!
 * \typedef chn_if_abesent_callback
 * ifAbsent: に渡すための関数ポインタの型です。
 */
typedef id (*chn_if_absent_callback)(void* pcontext);


/*!
 * \typedef chn_doing_callback
 */
typedef id (*chn_doing_callback)(void* pcontext, id element);


/*!
 * \typedef chn_predicate1_callback
 */
typedef CHNBoolean (*chn_predicate1_callback)(void* pcontext, id element);


/*!
 * \typedef chn_if_error_callback
 */
typedef id (*chn_if_error_callback)(void* pcontext);


#endif  /* coreHezelnut_callbacks_h */
// Local Variables:
//   coding: utf-8
// End:
