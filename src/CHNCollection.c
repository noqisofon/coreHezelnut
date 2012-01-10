//  
//  CHNCollection.c
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

#include "core-hezelnut/CHNCollection.h"


CHNCollection_ref CHNCollection_new(CHNMetaClass self_class)
{
    CHNCollection_ref new;

    if ( !self_class )
        self_class = CHNCollection;

    assert( self_class != nil );
    
    if ( self_class == CHNCollection || CHNClassDescriptor_inheritFrom( self_class, CHNCollection ) )
        new = (CHNCollection_ref)CHNClass_create_instance( self_class );
    else
        return CHNBatClassError_signalOn( self_class );

    return new;
}


CHNCollection_ref CHNCollection_from(CHNMetaClass self_class, CHNArray_ref array)
{
    return CHNCollection_withAll( self_class, array );
}


CHNCollection_ref CHNCollection_withAll(CHNMetaClass self_class, CHNCollection_ref collection)
{
    CHNCollection_ref new = CHNCollection_new( self_class );

    CHNCollection_addAll( new, collection );

    return new;
}


CHNCollection_ref CHNCollection_with(CHNMetaClass self_class, CHNObject_ref object)
{
    CHNCollection_ref new = CHNCollection_new( self_class );

    CHNCollection_add( new, object );

    return new;
}


CHNCollection_ref CHNCollection_with_with(CHNMetaClass self_class, CHNObject_ref first, CHNObject_ref second)
{
    CHNCollection_ref new = CHNCollection_new( self_class );

    CHNCollection_add( new, first );
    CHNCollection_add( new, second );

    return new;
}


CHNCollection_ref CHNCollection_with_with( CHNMetaClass self_class,
                                           CHNObject_ref first,
                                           CHNObject_ref second,
                                           CHNObject_ref  third )
{
    CHNCollection_ref new = CHNCollection_new( self_class );

    CHNCollection_add( new, first );
    CHNCollection_add( new, second );
    CHNCollection_add( new, third );

    return new;
}


CHNCollection_ref CHNCollection_with_with_with_with( CHNMetaClass self_class,
                                                     CHNObject_ref first,
                                                     CHNObject_ref second,
                                                     CHNObject_ref third,
                                                     CHNObject_ref fourth )
{
    CHNCollection_ref new = CHNCollection_new( self_class );

    CHNCollection_add( new, first );
    CHNCollection_add( new, second );
    CHNCollection_add( new, third );
    CHNCollection_add( new, fourth );

    return new;
}


CHNCollection_ref CHNCollection_with_with_with_with_with( CHNMetaClass self_class,
                                                          CHNObject_ref first,
                                                          CHNObject_ref second,
                                                          CHNObject_ref third,
                                                          CHNObject_ref fourth,
                                                          CHNObject_ref fifth )
{
    CHNCollection_ref new = CHNCollection_new( self_class );

    CHNCollection_add( new, first );
    CHNCollection_add( new, second );
    CHNCollection_add( new, third );
    CHNCollection_add( new, fourth );
    CHNCollection_add( new, fifth );

    return new;
}
