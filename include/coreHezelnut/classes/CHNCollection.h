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


typedef struct chn_collection* CHNCollection_ref;


#define  CHN_ASCOLLECTION(_that_) ((CHNCollection_ref)_that_)


/*!
 * 
 */
CHN_EXPORT CHNCollection_ref CHNCollection_class_from(CHNClass_ref self, CHNArray_ref an_array);


/*!
 * 
 */
CHN_EXPORT CHNCollection_ref CHNCollection_class_withAll(CHNClass_ref self, CHNCollection_ref a_collection);


/*!
 * 
 */
CHN_EXPORT CHNCollection_ref CHNCollection_class_with1(CHNClass_ref self, id an_object);


/*!
 * 
 */
CHN_EXPORT CHNCollection_ref CHNCollection_class_with2(CHNClass_ref self, id first_object, id second_object);


/*!
 * 
 */
CHN_EXPORT CHNCollection_ref CHNCollection_class_with3(CHNClass_ref self, id first_object, id second_object, id third_object);


/*!
 * 
 */
CHN_EXPORT CHNCollection_ref CHNCollection_class_with4(CHNClass_ref self, id first_object, id second_object, id third_object, id fourth_object);


/*!
 * 
 */
CHN_EXPORT CHNCollection_ref CHNCollection_class_with5(CHNClass_ref self, id first_object, id second_object, id third_object, id fourth_object, id fifth_object);


/*!
 * 
 */
CHN_EXPORT CHNIterator_ref CHNCollection_get_iterator(CHNCollection_ref self);


/*!
 * 
 */
CHN_EXPORT id CHNCollection_checkIndexableBounds_ifAbsent(CHNCollection_ref self, int index, chn_if_absent_callback a_block);


/*!
 * 
 */
CHN_EXPORT id Collection_copyReplaceFrom_to_with(CHNCollection_ref self, int start, int stop, CHNByteArray_ref byte_array, int replace_start);


/*!
 * 
 */
CHN_EXPORT id CHNCollection_copyWith(CHNCollection_ref self, id value);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_classes_CHNCollection_h */
// Local Variables:
//   coding: utf-8
// End:
