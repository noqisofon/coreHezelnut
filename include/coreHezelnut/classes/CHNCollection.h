//  
//  CHNCollection.h
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
#ifndef coreHezelnut_classes_CHNCollection_h
#define coreHezelnut_classes_CHNCollection_h

#include "coreHezelnut/classes/CHNIteratable.h"


CHN_EXTERN_C_BEGIN


typedef struct chn_iterator* CHNIterator_ref;
typedef struct chn_compiled_block* CHNCompiledBlock_ref;
typedef struct chn_compiled_method* CHNCompiledMethod_ref;

typedef struct chn_collection* CHNCollection_ref;


#define  CHN_ASCOLLECTION(_that_) ((CHNCollection_ref)_that_)


/*!
 * 
 */
CHN_EXPORT CHNCollection_ref CHNCollection_class_from(CHNArray_ref an_array);


/*!
 * 
 */
CHN_EXPORT CHNCollection_ref CHNCollection_class_withAll(CHNCollection_ref a_collection);


/*!
 * 
 */
CHN_EXPORT CHNCollection_ref CHNCollection_class_with1(id an_object);


/*!
 * 
 */
CHN_EXPORT CHNCollection_ref CHNCollection_class_with2(id first_object, id second_object);


/*!
 * 
 */
CHN_EXPORT CHNCollection_ref CHNCollection_class_with3(id first_object, id second_object, id third_object);


/*!
 * 
 */
CHN_EXPORT CHNCollection_ref CHNCollection_class_with4(id first_object, id second_object, id third_object, id fourth_object);


/*!
 * 
 */
CHN_EXPORT CHNCollection_ref CHNCollection_class_with5(id first_object, id second_object, id third_object, id fourth_object, id fifth_object);


/*!
 * 
 */
CHN_EXPORT CHNIterator_ref CHNCollection_get_iterator(CHNCollection_ref self);


/*!
 *
 */
CHN_EXPORT id CHNCollection_add(CHNCollection_ref self, id new_object);


/*!
 *
 */
CHN_EXPORT CHNCollection_ref CHNCollection_addAll(CHNCollection_ref self, CHNCollection_ref a_collection);


/*!
 *
 */
CHN_EXPORT CHNCollection_ref CHNCollection_empty(CHNCollection_ref self);


/*!
 *
 */
CHN_EXPORT id CHNCollection_remove(CHNCollection_ref self, id old_object);


/*!
 *
 */
CHN_EXPORT id CHNCollection_remove_ifAbsent(CHNCollection_ref self, id old_object, CHNCompiledBlock_ref a_block);


/*!
 *
 */
CHN_EXPORT CHNCollection_ref CHNCollection_removeAllSuchThat(CHNCollection_ref self, CHNCompiledBlock_ref a_block);


/*!
 * 
 */
CHN_EXPORT id CHNCollection_checkIndexableBounds_ifAbsent(CHNCollection_ref self, int index, CHNCompiledBlock_ref a_block);


/*!
 * 
 */
CHN_EXPORT id CHNCollection_copyReplaceFrom_to_with(CHNCollection_ref self, int start, int stop, CHNCollection_ref a_collection);


/*!
 * 
 */
CHN_EXPORT CHNCollection_ref CHNCollection_firstTake(CHNCollection_ref self, int n);


/*!
 * 
 */
CHN_EXPORT CHNBoolean CHNCollection_anySatisfy(CHNCollection_ref self, void* pcontext, CHNCompiledBlock_ref a_block);


/*!
 * 
 */
CHN_EXPORT id CHNCollection_copyWith(CHNCollection_ref self, id value);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_classes_CHNCollection_h */
// Local Variables:
//   coding: utf-8
// End:
