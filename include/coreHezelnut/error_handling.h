//  
//  error-handling.h
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
#ifndef coreHezelnut_error_handling_h
#define coreHezelnut_error_handling_h


CHN_EXTERN_C_BEGIN


/*!
 *
 */
CHN_EXPORT void chn_error(id object, int code, const char* format, ...);


/*!
 *
 */
CHN_EXPORT void chn_verror(id object, int code, const char* format, va_list argument);


typedef CHNBoolean (*chn_error_handler)(id, int, const char* format, va_list);


/*!
 *
 */
CHN_EXPORT chn_error_handler chn_get_error_handler(void);


/*!
 *
 */
CHN_EXPORT chn_error_handler chn_set_error_handler(chn_error_handler handler);


#define CHN_ERR_UNKNOWN                        0x0001
#define CHN_ERR_WRONG_CLASS                    0x0002
#define CHN_ERR_WRONG_ARGUMENT_COUNT           0x0004
#define CHN_ERR_NOT_FOUND                      0x0010
#define CHN_ERR_NOT_INDEXABLE                  0x0020
#define CHN_ERR_NOT_ENOUGH_ELEMENTS            0x0040
#define CHN_ERR_READONLY_OBJECT                0x0100
#define CHN_ERR_ARGUMENT_INDEX_OUT_OF_RANGE    0x0110
#define CHN_ERR_INDEX_OUT_OF_RANGE             0x1010
#define CHN_ERR_MEMORY                         0x8110



CHN_EXTERN_C_END


#endif  /* coreHezelnut_error_handling_h */
