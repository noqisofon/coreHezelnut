//  
//  CHNArray.h
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
#ifndef coreHezelnut_classes_CHNArray_h
#define coreHezelnut_classes_CHNArray_h

#include "coreHezelnut/classes/CHNArrayedCollection.h"


CHN_EXTERN_C_BEGIN


typedef struct chn_byte_array* CHNByteArray_ref;

typedef struct chn_array* CHNArray_ref;

CHN_EXPORT const CHNClass_ref CHNArray;


#define CHN_ASARRAY(_that_) ((CHNArray_ref)_that_)

#define  CHN_ARRAY_LITERAL_EMPTY                CHN_ASARRAY(CHN_new( CHNArray ))
#define  CHN_ARRAY_LITERAL1(_arg0_)             CHN_ASARRAY(CHNArrayedCollection_class_with1( CHNArray, _arg0_ ))
#define  CHN_ARRAY_LITERAL2(_arg0_, _arg1_)     CHN_ASARRAY(CHNArrayedCollection_class_with2( CHNArray, _arg0_, _arg1_ ))


/*!
 *
 */
CHN_EXPORT id CHNArray_class_alloc(void);


/*!
 *
 */
CHN_EXPORT CHNArray_ref CHNArray_class_new(void);


/*!
 * 
 */
CHN_EXPORT CHNArray_ref CHNArray_class_from(CHNArray_ref an_array);


/*!
 *
 */
CHN_EXPORT CHNArray_ref CHNArray_initWithSize(id self, size_t size);


/*!
 *
 */
CHN_EXPORT id CHNArray_free(CHNArray_ref self);


/*!
 *
 */
CHN_EXPORT id CHNArray_release(CHNArray_ref self);


/*!
 * 
 */
CHN_EXPORT CHNArray_ref CHNArray_copy(CHNArray_ref self);


/*!
 * 
 */
CHN_EXPORT id CHNArray_at(CHNArray_ref self, int an_index);


/*!
 * 
 */
CHN_EXPORT id CHNArray_at_ifAbsent(CHNArray_ref self, int an_index, CHNCompiledBlock_ref a_block);


/*!
 * 
 */
CHN_EXPORT id CHNArray_printOn(CHNArray_ref self, CHNStream_ref a_stream);


/*!
 * 
 */
CHN_EXPORT CHNBoolean CHNArray_isLiteralObject(CHNArray_ref self);


/*!
 * 
 */
CHN_EXPORT id CHNArray_replaceFrom_to_with_startingAt(CHNArray_ref self, int start, int stop, CHNByteArray_ref byte_array, int replace_start);


/*!
 * 
 */
CHN_EXPORT id CHNArray_storeLiteralOn(CHNArray_ref self, CHNStream_ref a_stream);


/*!
 * 
 */
CHN_EXPORT id CHNArray_multiBecome(CHNArray_ref self, CHNArray_ref an_array);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_classes_CHNArray_h */
// Local Variables:
//   coding: utf-8
// End:
