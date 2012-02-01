//  
//  messaging.h
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
#ifndef coreHezelnut_messaging_h
#define coreHezelnut_messaging_h

#include "coreHezelnut/runtime.h"
#include "coreHezelnut/selector.h"


CHN_EXTERN_C_BEGIN


CHN_EXPORT IMP (*__CHN_message_forward)(SEL);
CHN_EXPORT IMP (*__CHN_message_forward2)(id, SEL);


/*!
 *
 */
CHN_EXPORT IMP chn_message_lookup(id receiver, SEL op);


CHN_INLINE IMP chn_method_get_imp(Method_ref method)
{
    return (method != METHOD_NULL) ? method->method_imp : NULL;
}


/*!
 *
 */
CHN_EXPORT IMP chn_get_imp(CHNClass_ref klass, SEL selector);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_messaging_h */
