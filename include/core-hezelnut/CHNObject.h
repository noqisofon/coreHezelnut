//  
//  CHNObject.h
//  
//  Auther:
//       ned rihine <ned.rihine@gmail.com>
// 
//  Copyright (c) 2011 rihine All rights reserved.
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
#ifndef coreHezelnut_CHNObject_h
#define coreHezelnut_CHNObject_h


#include <core-Hezelnut/CHNGenericTypes.h>


extern const CHNMetaClass_ref CHNObject;


id CHNObject_alloc(CHNAllocator_ref allocator);


id CHNObject_new(void);


CHNClassID CHNObject_getClassID(void);


id CHNObject_init(id self);


id CHNObject_copy(id self);


void CHNObject_finalize(id self);


CHNBoolean CHNObject_equals(id left, id right);


CHNHashCode CHNObject_hash(id self);


id CHNObject_retain(id self);


void CHNObject_release(id self);


CHNCount CHNObject_retainCount(id self);


#endif  /* coreHezelnut_CHNObject_h */
