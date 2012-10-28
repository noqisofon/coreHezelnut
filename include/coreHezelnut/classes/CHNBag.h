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


typedef struct chn_bag*  CHNBag_ref;


/*!
 *
 */
CHN_EXTERN id CHNBag_class_alloc(void);


/*!
 *
 */
CHN_EXTERN CHNBag_ref CHNBag_class_new(void);


/*!
 *
 */
CHN_EXTERN CHNBag_ref CHNBag_class_new_(size_t size);


/*!
 *
 */
CHN_EXTERN CHNBag_ref CHNBag_add(CHNBag_ref self, id new_object);


/*!
 *
 */
CHN_EXTERN CHNBag_ref CHNBag_add_withOccurrences(CHNBag_ref self, id new_object, int an_integer);


/*!
 *
 */
CHN_EXTERN id CHNBag_remove_ifAbsent(CHNBag_ref self, id old_object, CHNCompiledBlock_ref an_exception_block);


/*!
 *
 */
CHN_EXTERN CHNArray_ref CHNBag_sortedByCount(CHNBag_ref self);


/*!
 *
 */
CHN_EXTERN int CHNBag_occurrencesOf(CHNBag_ref self, id an_object);


/*!
 *
 */
CHN_EXTERN CHNBoolean CHNBag_includes(CHNBag_ref self, id an_object);


/*!
 *
 */
CHN_EXTERN size_t CHNBag_size(CHNBag_ref self);


/*!
 *
 */
CHN_EXTERN CHNHashCode CHNBag_hash(CHNBag_ref self);


/*!
 *
 */
CHN_EXTERN int CHNBag_equals(CHNBag_ref self, CHNBag_ref other);


/*!
 *
 */
CHN_EXTERN CHNSet_ref CHNBag_asSet(CHNBag_ref self);


/*!
 *
 */
CHN_EXTERN CHNIterator_ref CHNSet_iterator(CHNBag_ref self);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_classes_CHNBag_h */
// Local Variables:
//   coding: utf-8
// End:
