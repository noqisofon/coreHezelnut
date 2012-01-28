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

#include "coreHezelnut/chn-internal.h"
#include "coreHezelnut/classes.h"


CHN_EXTERN_C_BEGIN


typedef struct chn_selector {
    void* actual_id;            /*!< 関数ポインタ。 */
    const char* func_type;       /*!< その関数の型。 */
} *SEL;


typedef struct chn_object {
    struct chn_class* class_pointer;
} *id;


#ifdef CHN_INLINE
CHN_INLINE CHNBoolean sel_eq(SEL left, SEL right)
{
    if ( left == NULL || right == NULL )
        return left == right;
    else
        return left->actual_id == right->actual_id;
}
#else
#   define sel_eq(_left_, _right_)  __sel_eq(_left_, _right_)
#endif  /* def CHN_INLINE */


CHN_EXPORT CHNBoolean __sel_eq(SEL left, SEL right);


typedef id (*IMP)(id, SEL, ...);


#define nil ((id)0)



typedef CHNComparisonResult (*CHNComparisonFunction)(id left, id right);


#define CHN_ASOBJECT(_that_)  ((id)_that_)


/*!
 * 
 */
CHN_EXPORT id CHN_alloc(CHNClass_ref super_class);


/*!
 * 
 */
CHN_EXPORT id CHN_init(id self);


/*!
 * 
 */
CHN_EXPORT id CHN_basicNew(CHNClass_ref super_class);


/*!
 * 
 */
CHN_EXPORT id CHN_new(CHNClass_ref super_class);


/*!
 *
 */
CHN_EXPORT CHNClass_ref CHN_getclass(id self);


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
CHN_EXPORT void CHN_release(id self);


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
CHN_EXPORT CHNBoolean CHN_isNil(id self);


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
CHN_EXPORT int CHN_instSize(id self);


/*!
 *
 */
CHN_EXPORT int CHN_instSize(id self);


/*!
 *
 */
CHN_EXPORT id CHN_instVarAt(id self, int index);


/*!
 *
 */
CHN_EXPORT void CHN_instVarAt_put(id self, int index, id value);


/*!
 *
 */
CHN_EXPORT id CHN_basicAt(id self, int index);


/*!
 *
 */
CHN_EXPORT void CHN_basicAt_put(id self, int index, id value);


/*!
 *
 */
CHN_EXPORT id CHN_at(id self, int index);


/*!
 *
 */
CHN_EXPORT void CHN_at_put(id self, int index, id value);


/*!
 *
 */
CHN_EXPORT id CHN_checkIndexableBounds(id self, int index);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_objects_h */
