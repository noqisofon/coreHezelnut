//  
//  chn_runtime.h
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
#ifndef coreHezelnut_runtime_h
#define coreHezelnut_runtime_h

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <ctype.h>
#include <assert.h>

#include "coreHezelnut/chn_internal.h"
#include "coreHezelnut/chn_api.h"
#include "coreHezelnut/chn_class.h"

#include "coreHezelnut/selector.h"
#include "coreHezelnut/messaging.h"
#include "coreHezelnut/error_handling.h"
#include "coreHezelnut/callbacks.h"
#include "coreHezelnut/threading.h"
#include "coreHezelnut/hashing.h"


CHN_EXTERN_C_BEGIN


/*!
 * object に selector がある場合に真を返します。
 */
CHN_EXPORT CHNBoolean __chn_responds_to(id object, SEL selector);


/*!
 * プリミティブ整数用の max 関数です。 n か m のうち、大きい方を返します。
 */
CHN_EXPORT int32_t chn_int_max(int32_t n, int32_t m);


/*!
 * プリミティブ整数用の max 関数です。 n か m のうち、小さい方を返します。
 */
CHN_EXPORT int32_t chn_int_min(int32_t n, int32_t m);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_runtime_h */
