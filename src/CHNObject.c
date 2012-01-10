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
#include "core-hezelnut/CHNObject.h"


CHN_EXPORT CHNObject_ref chn_object_alloc(CHNClass_ref _class, CHNAllocator_ref allocator)
{
}


CHN_EXPORT CHMClassID chn_get_class_id(CHNObject_ref object)
{
    if ( object != nil )
        return *(object->getClassID)();
    else
        return CHNNil_getClassID();
}


CHN_EXPORT CHNString_ref chn_copy_class_id_description(CHNObject_ref object)
{
}


CHN_EXPORT CHNObject_ref chn_retain(CHNObject_ref object)
{
}


CHN_EXPORT void chn_release(CHNObject_ref object)
{
}


CHN_EXPORT CHNIndex chn_retain_count(CHNObject_ref object)
{
}


CHN_EXPORT CHNBoolean chn_equals(CHNObject_ref left, CHNObject_ref right)
{
    if ( left == nil || right == nil ) {
        if ( left != nil )
            return *(left->equals)( right );
        else if ( right != nil )
            return *(right->equals)( left );
        else
            return left == right;
    }
    if ( left->class_id == right->class_id )
        return *(left->equals)( right );
    return left == right;
}


CHN_EXPORT CHNHashCode chn_hash(CHNObject_ref object)
{
    if ( object != nil )
        return *(object->hash)( object );
    else
        return 0;
}


CHN_EXPORT CHNString_ref chn_copy_description(CHNObject_ref object)
{
}


CHN_EXPORT CHNAllocator_ref chn_get_allocator(CHNObject_ref object)
{
}
// Local Variables:
//   coding: utf-8
// End:
