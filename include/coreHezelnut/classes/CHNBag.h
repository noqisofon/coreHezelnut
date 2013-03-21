//  
//  CHNBag.h
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
#ifndef coreHezelnut_classes_CHNBag_h
#define coreHezelnut_classes_CHNBag_h

#include "coreHezelnut/classes/CHNCollection.h"


CHN_EXTERN_C_BEGIN


typedef struct chn_stream* CHNStream_ref;
typedef struct chn_iterator* CHNIterator_ref;
typedef struct chn_compiled_block* CHNCompiledBlock_ref;
typedef struct chn_set* CHNSet_ref;

typedef struct chn_bag*  CHNBag_ref;

CHN_EXPORT const CHNClass_ref CHNBag;


/*!
 *
 */
CHN_EXPORT id CHNBag_class_alloc(void);


/*!
 *
 */
CHN_EXPORT CHNBag_ref CHNBag_class_new(void);


/*!
 *
 */
CHN_EXPORT CHNBag_ref CHNBag_class_new_(size_t size);


/*!
 *
 */
CHN_EXPORT CHNBag_ref CHNBag_class_basicNew(void);


/*!
 *
 */
CHN_EXPORT CHNBag_ref CHNBag_initContents(id base, size_t size);


/*!
 *
 */
CHN_EXPORT CHNClass_ref CHNBag_dictionaryClass(CHNBag_ref self);


/*!
 *
 */
CHN_EXPORT CHNBag_ref CHNBag_add(CHNBag_ref self, id new_object);


/*!
 *
 */
CHN_EXPORT CHNBag_ref CHNBag_add_withOccurrences(CHNBag_ref self, id new_object, int an_integer);


/*!
 *
 */
CHN_EXPORT id CHNBag_remove_ifAbsent(CHNBag_ref self, id old_object, CHNCompiledBlock_ref an_exception_block);


/*!
 *
 */
CHN_EXPORT CHNArray_ref CHNBag_sortedByCount(CHNBag_ref self);


/*!
 *
 */
CHN_EXPORT int CHNBag_occurrencesOf(CHNBag_ref self, id an_object);


/*!
 *
 */
CHN_EXPORT CHNBoolean CHNBag_includes(CHNBag_ref self, id an_object);


/*!
 *
 */
CHN_EXPORT size_t CHNBag_size(CHNBag_ref self);


/*!
 *
 */
CHN_EXPORT CHNHashCode CHNBag_hash(CHNBag_ref self);


/*!
 *
 */
CHN_EXPORT int CHNBag_equals(CHNBag_ref self, CHNBag_ref other);


/*!
 *
 */
CHN_EXPORT CHNSet_ref CHNBag_asSet(CHNBag_ref self);


/*!
 *
 */
CHN_EXPORT CHNIterator_ref CHNSet_iterator(CHNBag_ref self);


/*!
 *
 */
CHN_EXPORT CHNClass_ref CHNBag_class(CHNBag_ref self);


/*!
 *
 */
CHN_EXPORT CHNBag_ref CHNBag_storeOn(CHNBag_ref self, CHNStream_ref a_stream);


/*!
 *
 */
CHN_EXPORT CHNBag_ref CHNBag_printOn(CHNBag_ref self, CHNStream_ref a_stream);


/*!
 *
 */
CHN_EXPORT CHNMappedCollection_ref CHNBag_keyAndValues(CHNBag_ref self);


/*!
 *
 */
CHN_EXPORT CHNMappedCollection_ref CHNBag_contents(CHNBag_ref self);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_classes_CHNBag_h */
// Local Variables:
//   coding: utf-8
// End:
