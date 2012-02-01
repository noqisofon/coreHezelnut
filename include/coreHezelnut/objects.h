//  
//  objects.h
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
#ifndef coreHezelnut_objects_h
#define coreHezelnut_objects_h

#include "coreHezelnut/classes.h"


CHN_EXTERN_C_BEGIN


#define CHN_ASOBJECT(_that_)  ((id)_that_)


/*!
 * 
 */
CHN_EXPORT id CHN_alloc(const CHNClass_ref super_class);


/*!
 * 
 */
CHN_EXPORT id CHN_init(id self);


/*!
 * 
 */
CHN_EXPORT id CHN_basicNew(const CHNClass_ref super_class);


/*!
 *
 */
CHN_EXPORT CHNClass_ref CHN_get_class(id self);


/*!
 *
 */
CHN_EXPORT id CHN_retain(id self);


/*!
 *
 */
CHN_EXPORT CHNBoolean CHN_tryRetain(id self);


/*!
 *
 */
CHN_EXPORT id CHN_release(id self);


/*!
 *
 */
CHN_EXPORT CHNBoolean CHN_isDeallocating(id self);


/*!
 *
 */
CHN_EXPORT CHNBoolean CHN_equals(id left, id right);


/*!
 *
 */
CHN_EXPORT CHNBoolean CHN_identityEquals(id left, id right);


/*!
 * 
 */
CHN_EXPORT CHNBoolean CHN_isKindOf(id self, CHNClass_ref _class);


/*!
 * 
 */
CHN_EXPORT CHNBoolean CHN_isMemberOf(id self, CHNClass_ref _class);


/*!
 * 
 */
CHN_EXPORT CHNBoolean CHN_isReadOnly(id self);


/*!
 * 
 */
CHN_EXPORT CHNBoolean CHN_isNil(id self);


/*!
 * 
 */
CHN_EXPORT CHNBoolean CHN_isSymbol(id self);


/*!
 * 
 */
CHN_EXPORT CHNBoolean CHN_respondsTo(id self, CHNSymbol_ref a_symbol);


/*!
 * 
 */
CHN_EXPORT id CHN_makeReadOnly(id self);


/*!
 * 
 */
CHN_EXPORT id CHN_copy(id self);


/*!
 * 
 */
CHN_EXPORT id CHN_postCopy(id self);


/*!
 * 
 */
CHN_EXPORT id CHN_shallowCopy(id self);


/*!
 * 
 */
CHN_EXPORT id CHN_deepCopy(id self);


/*!
 *
 */
CHN_EXPORT int CHN_size(id self);


/*!
 *
 */
CHN_EXPORT int CHN_instSize(id self);


/*!
 *
 */
CHN_EXPORT int CHN_basicSize(id self);


/*!
 * 
 */
CHN_EXPORT id CHN_VarNamed(id self, CHNString_ref a_string);


/*!
 * 
 */
CHN_EXPORT id CHN_VarNamed_put(id self, CHNString_ref a_string, id object);


/*!
 *
 */
CHN_EXPORT id CHN_instVarAt(id self, int index);


/*!
 *
 */
CHN_EXPORT id CHN_instVarAt_put(id self, int index, id value);


/*!
 *
 */
CHN_EXPORT id CHN_allInstVarNames(id self);


/*!
 *
 */
CHN_EXPORT id CHN_basicAt(id self, int index);


/*!
 *
 */
CHN_EXPORT id CHN_basicAt_put(id self, int index, id value);


/*!
 *
 */
CHN_EXPORT id CHN_checkIndexableBounds(id self, int index);


/*!
 *
 */
CHN_EXPORT id CHN_checkIndexableBounds_put(id self, int index, id value);


/*!
 *
 */
CHN_EXPORT id CHN_at(id self, int index);


/*!
 *
 */
CHN_EXPORT id CHN_at_put(id self, int index, id value);


/*!
 *
 */
CHN_EXPORT id CHN_become(id self, id other_object);


/*!
 *
 */
CHN_EXPORT id CHN_becomeFoward(id self, id other_object);


/*!
 *
 */
CHN_EXPORT int CHN_identityHash(id self);


/*!
 *
 */
CHN_EXPORT int CHN_hash(id self);


/*!
 *
 */
CHN_EXPORT id CHN_nextInstance(id self);


/*!
 *
 */
CHN_EXPORT id CHN_perform(id self, id selector_or_message_or_method);


/*!
 *
 */
CHN_EXPORT id CHN_perform_with0(id self, id selector_or_method, id arg0);


/*!
 *
 */
CHN_EXPORT id CHN_perform_with1(id self, id selector_or_method, id arg0, id arg1);


/*!
 *
 */
CHN_EXPORT id CHN_perform_with2(id self, id selector_or_method, id arg0, id arg1, id arg2);


/*!
 *
 */
CHN_EXPORT id CHN_perform_with3(id self, id selector_or_method, id arg0, id arg1, id arg2, id arg3);


/*!
 *
 */
CHN_EXPORT id CHN_perform_withArguments(id self, id selector_or_method, CHNArray_ref argument_array);


/*!
 *
 */
CHN_EXPORT id CHN_error(id self, CHNString_ref message);


/*!
 *
 */
CHN_EXPORT id CHN_doesNotUnderstand(id self, CHNMessage_ref message);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_objects_h */
