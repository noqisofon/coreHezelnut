//  
//  CHNObject.c
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
#include "core-hezelnut/CHNAllocator.h"
#include "core-hezelnut/CHNObject.h"


CHN_DECLARE_CLASSID(CHNObject, CHNClassID_OBJECT);
CHN_DEFINE_CLASS(0,
                 CHNObject,
                 CHNObject_init,
                 CHNObject_copy,
                 CHNObject_finalize,
                 CHNObject_equals,
                 CHNObject_hash,
                 CHNObject_retain,
                 CHNObject_release,
                 CHNObject_retainCount);


id CHNObject_alloc(CHNAllocator_ref allocator)
{
    id new;

    if ( !allocator )
        allocator = g_CHNAllocator_SystemDefault;

    CHNAllocator_allocate( allocator, CHNObject->instance_size );

    new->class_pointer = CHNObject;

    return new;
}


id CHNObject_new(void)
{
    return CHNObject_init( CHNObject_alloc( NULL ) );
}


CHNClassID CHNObject_getClassID(void)
{
    return _CHNObject_ClassID;
}


id CHNObject_init(id self)
{
    return self;
}


id CHNObject_copy(id self)
{
    if ( ( self != nil ) && CHN_CLASS_IS_CLASS(CHN_CLASS_CLASSOF(self)) )
        return OBJ_COPY(object);
    else
        return nil;
}


void CHNObject_finalize(id self)
{
    if ( ( self != nil ) && CHN_CLASS_IS_CLASS(CHN_CLASS_CLASSOF(self)) )
        return OBJ_FINALIZE(self);
    else
        return nil;
}


CHNBoolean CHNObject_equals(id left, id right)
{   
    return left == right;
}


CHNHashCode CHNObject_hash(id self)
{
    return (CHNHashCode)self;
}


id CHNObject_retain(id self)
{
    return self;
}


void CHNObject_release(id self)
{
}


CHNCount CHNObject_retainCount(id self)
{
}


// Local Variables:
//   coding: utf-8
// End:
