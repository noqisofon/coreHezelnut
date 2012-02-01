//  
//  CHNCollection.c
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
#include "coreHezelnut/coreHezelnut.h"
#include "coreHezelnut/classes.h"
#include "coreHezelnut/callbacks.h"

#include "coreHezelnut/classes/CHNIterator.h"

#include "coreHezelnut/classes/CHNCollection.h"


CHN_EXPORT CHNCollection_ref CHNCollection_class_from(CHNClass_ref self, CHNArray_ref an_array)
{
    return CHNCollection_class_withAll( self, CHN_ASCOLLECTION(an_array) );
}


CHN_EXPORT CHNCollection_ref CHNCollection_class_withAll(CHNClass_ref self, CHNCollection_ref a_collection)
{
    return CHN_yourself( CHNCollection_addAll( CHN_new( self ), a_collection ) );
}


CHN_EXPORT CHNCollection_ref CHNCollection_class_with1(CHNClass_ref self, id an_object)
{
    CHNCollection_ref new = CHN_new( self );

    CHNCollection_add( new, an_object );

    return CHN_yourself( new );
}


CHN_EXPORT CHNCollection_ref CHNCollection_class_with2(CHNClass_ref self, id first_object, id second_object)
{
    CHNCollection_ref new = CHN_new( self );

    CHNCollection_add( new, first_object );
    CHNCollection_add( new, second_object ); 

    return CHN_yourself( new );
}


CHN_EXPORT CHNCollection_ref CHNCollection_class_with3(CHNClass_ref self, id first_object, id second_object, id third_object)
{
    CHNCollection_ref new = CHN_new( self );

    CHNCollection_add( new, first_object );
    CHNCollection_add( new, second_object );
    CHNCollection_add( new, third_object ); 

    return CHN_yourself( new );
}


CHN_EXPORT CHNCollection_ref CHNCollection_class_with4(CHNClass_ref self, id first_object, id second_object, id third_object, id fourth_object)
{
    CHNCollection_ref new = CHN_new( self );

    CHNCollection_add( new, first_object );
    CHNCollection_add( new, second_object );
    CHNCollection_add( new, third_object );
    CHNCollection_add( new, fourth_object );

    return CHN_yourself( new );
}


CHN_EXPORT CHNCollection_ref CHNCollection_class_with5(CHNClass_ref self, id first_object, id second_object, id third_object, id fourth_object, id fifth_object)
{
    CHNCollection_ref new = CHN_new( self );

    CHNCollection_add( new, first_object );
    CHNCollection_add( new, second_object );
    CHNCollection_add( new, third_object );
    CHNCollection_add( new, fourth_object );
    CHNCollection_add( new, fifth_object );

    return CHN_yourself( new );
}
