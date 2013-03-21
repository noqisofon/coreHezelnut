//  
//  CHNContextPart.h
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
#ifndef coreHezelnut_classes_CHNContextPart_h
#define coreHezelnut_classes_CHNContextPart_h


CHN_EXTERN_C_BEGIN


typedef struct chn_stream* CHNStream_ref;
typedef struct chn_block_closure* CHNBlockClosure_ref;

typedef struct chn_context_part* CHNContextPart_ref;

const CHNClass_ref CHNContextPart;


#define CHN_THIS_CONTEXT CHNContextPart_class_thisContext()


/*!
 * 
 */
CHN_EXPORT int CHNContextPart_class_spindex(void);


/*!
 * 
 */
CHN_EXPORT id CHNContextPart_class_backtrace(void);


/*!
 * 
 */
CHN_EXPORT id CHNContextPart_class_backtraceOn(CHNStream_ref a_stream);


/*!
 * 
 */
CHN_EXPORT CHNContextPart_ref CHNContextPart_class_thisContext(void);


/*!
 * 
 */
CHN_EXPORT id CHNContextPart_backtrace(CHNContextPart_ref self);


/*!
 * 
 */
CHN_EXPORT id CHNContextPart_backtraceOn(CHNContextPart_ref self, CHNStream_ref a_stream);


/*!
 * 
 */
CHN_EXPORT id CHNContextPart_client(CHNContextPart_ref self);


/*!
 *
 */
CHN_EXPORT id CHNContextPart_get_environment(CHNContextPart_ref self);


/*!
 *
 */
CHN_EXPORT int CHNContextPart_get_initialIP(CHNContextPart_ref self);


/*!
 *
 */
CHN_EXPORT CHNBoolean CHNContextPart_isDisabled(CHNContextPart_ref self);


/*!
 * 
 */
CHN_EXPORT CHNBoolean CHNContextPart_isUnwind(CHNContextPart_ref self);


/*!
 * 
 */
CHN_EXPORT CHNBoolean CHNContextPart_isEnvironment(CHNContextPart_ref self);


/*!
 * 
 */
CHN_EXPORT CHNBoolean CHNContextPart_isProcess(CHNContextPart_ref self);


/*!
 * 
 */
CHN_EXPORT CHNContextPart_ref CHNContextPart_get_parentContext(CHNContextPart_ref self);


/*!
 * 
 */
CHN_EXPORT id CHNContextPart_set_parentContext(CHNContextPart_ref self, CHNContextPart_ref a_context);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_classes_CHNContextPart_h */
// Local Variables:
//   coding: utf-8
// End:
