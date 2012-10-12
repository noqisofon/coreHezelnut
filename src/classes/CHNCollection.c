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
#include "coreHezelnut/classes/CHNCompiledBlock.h"
#include "coreHezelnut/classes/CHNOrderedCollection.h"

#include "coreHezelnut/classes/CHNCollection.h"


CHN_EXPORT CHNCollection_ref CHNCollection_class_from(CHNArray_ref an_array)
{
    return CHNCollection_class_withAll( CHN_ASCOLLECTION(an_array) );
}


CHN_EXPORT CHNCollection_ref CHNCollection_class_withAll(CHNCollection_ref a_collection)
{
    CHNCollection_ref new;

    new = CHN_ASCOLLECTION(CHNOrderedCollection_class_new());
    CHNCollection_addAll( new, a_collection );

    return new;
}


CHN_EXPORT CHNCollection_ref CHNCollection_class_with1(id an_object)
{
    
    CHNCollection_ref new;

    new = CHN_ASCOLLECTION(CHNOrderedCollection_class_new());

    CHNCollection_add( new, an_object );

    return new;
}


CHN_EXPORT CHNCollection_ref CHNCollection_class_with2(id first_object, id second_object)
{
    CHNCollection_ref new;

    new = CHN_ASCOLLECTION(CHNOrderedCollection_class_new());

    CHNCollection_add( new, first_object );
    CHNCollection_add( new, second_object ); 

    return new;
}


CHN_EXPORT CHNCollection_ref CHNCollection_class_with3(id first_object, id second_object, id third_object)
{
    CHNCollection_ref new;

    new = CHN_ASCOLLECTION(CHNOrderedCollection_class_new());

    CHNCollection_add( new, first_object );
    CHNCollection_add( new, second_object );
    CHNCollection_add( new, third_object ); 

    return new;
}


CHN_EXPORT CHNCollection_ref CHNCollection_class_with4(id first_object, id second_object, id third_object, id fourth_object)
{
    CHNCollection_ref new;

    new = CHN_ASCOLLECTION(CHNOrderedCollection_class_new());

    CHNCollection_add( new, first_object );
    CHNCollection_add( new, second_object );
    CHNCollection_add( new, third_object );
    CHNCollection_add( new, fourth_object );

    return new;
}


CHN_EXPORT CHNCollection_ref CHNCollection_class_with5(id first_object, id second_object, id third_object, id fourth_object, id fifth_object)
{
    CHNCollection_ref new;

    new = CHN_ASCOLLECTION(CHNOrderedCollection_class_new());

    CHNCollection_add( new, first_object );
    CHNCollection_add( new, second_object );
    CHNCollection_add( new, third_object );
    CHNCollection_add( new, fourth_object );
    CHNCollection_add( new, fifth_object );

    return new;
}


CHN_EXPORT CHNIterator_ref CHNCollection_get_iterator(CHNCollection_ref self)
{
}


CHN_EXPORT id CHNCollection_add(CHNCollection_ref self, id new_object)
{
    return CHNObject_subclassResponsibility( CHN_ASOBJECT(self) );
}


CHN_EXPORT CHNCollection_ref CHNCollection_addAll(CHNCollection_ref self, CHNCollection_ref a_collection)
{
    CHNIterator_ref    it;
    id                 element;

    it = CHNCollection_get_iterator( self );
    for ( ; CHNIterator_finished( it ); CHNIterator_next( it ) ) {
        element = CHNIterator_current( it );

        CHNCollection_add( self, element );
    }
    CHNIterator_release( it );

    return a_collection;
}


CHN_EXPORT CHNCollection_ref CHNCollection_empty(CHNCollection_ref self)
{
    return CHNCollection_become( self, CHNCollection_copyEmpty( self ) );
}


struct default_remove_an_exception_block_context {
    id             receiver;
    id             old_object
};


static id chn_collection_default_remove_an_exception_block(void* pcontext)
{
    struct default_remove_an_exception_block_context* context;

    context = (struct default_remove_an_exception_block_context *)pcontext;

    return CHNNotFoundError_class_signalOn_what( context->old_object, _S("object") );
}


/*!
 *
 */
CHN_EXPORT id CHNCollection_remove(CHNCollection_ref self, id old_object)
{
    CHNCompiledBlock_ref  a_block;
    struct default_remove_an_exception_block_context context;

    context.receiver = CHN_ASCOLLECTION(self);
    context.old_object = old_object;

    return CHNCollection_remove_ifAbsent( self, old_object, a_block );
}


CHN_EXPORT id CHNCollection_remove_ifAbsent(CHNCollection_ref self, id old_object, CHNCompiledBlock_ref a_block)
{
    return CHNObject_subclassResponsibility( CHN_ASOBJECT(self) );
}


CHN_EXPORT CHNCollection_ref CHNCollection_removeAllSuchThat(CHNCollection_ref self, CHNCompiledBlock_ref a_block)
{
    CHNCollection_ref removee;

    removee = CHNCollection_select( self, a_block );
    CHNCollection_removeAll( self, removee );

    return removee;
}



CHN_EXPORT id CHNCollection_checkIndexableBounds_ifAbsent(CHNCollection_ref self, int index, CHNCompiledBlock_ref a_block)
{
}


CHN_EXPORT id CHNCollection_copyReplaceFrom_to_with(CHNCollection_ref self, int start, int stop, CHNCollection_ref a_collection)
{
}


CHN_EXPORT CHNCollection_ref CHNCollection_firstTake(CHNCollection_ref self, int n)
{
}


CHN_EXPORT CHNBoolean CHNCollection_anySatisfy(CHNCollection_ref self, void* pcontext, CHNCompiledBlock_ref a_block)
{
}


CHN_EXPORT id CHNCollection_copyWith(CHNCollection_ref self, id value)
{
}
// Local Variables:
//   coding: utf-8
// End:
