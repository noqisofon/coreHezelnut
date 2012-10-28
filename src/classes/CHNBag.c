//  
//  CHNBag.c
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
#include "config.h"

#include "coreHezelnut/classes/CHNKeyAndValueIterator.h"
#include "coreHezelnut/classes/CHNSortedCollection.h"
#include "coreHezelnut/classes/CHNMappedCollection.h"

#include "coreHezelnut/classes/CHNBag.h"


CHN_EXTERN id CHNBag_class_alloc(void)
{
    return CHNObject_class_alloc( CHNBag );
}


CHN_EXTERN CHNBag_ref CHNBag_class_new(void)
{
    return CHNBag_initContents( CHNBag_class_basicNew(), 31 );
}


CHN_EXTERN CHNBag_ref CHNBag_class_new_(size_t size)
{
    return CHNBag_initContents( CHNBag_class_basicNew(), chn_max(7, size) );
}


CHN_EXTERN CHNBag_ref CHNBag_add(CHNBag_ref self, id new_object)
{
    return CHNBag_add_withOccurrences( self, new_object, 1 );
}


CHN_EXTERN CHNBag_ref CHNBag_add_withOccurrences(CHNBag_ref self, id new_object, int an_integer)
{
    int new_occurrences;

    if ( CHNObject_isNil( new_object ) ) {
        CHNInvalidArgumentError_class_signalOn_reason( new_object, _S("bag elements cannot be nil") );

        return self;
    }

    new_occurrences = CHNMappedCollection_at_put( self->_contents,
                                                  new_object,
                                                  CHNBag_occurrencesOf( self, new_object ) + an_integer );

    if ( new_occurrences <= 0 )
        CHNMappedCollection_removeKey( self->_contents, new_object );

    return self;
}


CHN_EXTERN id CHNBag_remove_ifAbsent(CHNBag_ref self, id old_object, CHNCompiledBlock_ref an_exception_block)
{
    int count;

    count = CHNBag_occurrencesOf( self, old_object );

    if ( count == 0 )
        return CHNCompiledBlock_value0( an_exception_block );

    if ( count == 1 )
        CHNMappedCollection_removeKey( self->_contents, old_object );
    else
        CHNMappedCollection_at_put( self->_contents, count - 1 );

    return old_object;
}


static CHNBoolean chn_bag_sorted_by_count_block(int x, int y)
{
    return x >= y;
}


CHN_EXTERN CHNArray_ref CHNBag_sortedByCount(CHNBag_ref self)
{
    CHNArray_ref                ret;
    CHNSortedCollection_ref     counts;
    CHNKeyAndValueIterator_ref  it;

    counts  = CHNSortedCollection_class_sortBlock( sorted_by_count_block );
    it      = CHNMappedCollection_keyAndValuesIterator( self->contents );

    for ( ; CHNKeyAndValueIterator_finished( it ); CHNKeyAndValueIterator_next( it ) ) {
        id key    = CHNKeyAndValueIterator_currentKey( id );
        id count  = CHNKeyAndValueIterator_currentValue( id );

        CHNSortedCollection_add( counts, CHNAssociation_class_new( count, key ) );
    }
    CHNKeyAndValueIterator_release( it );

    ret = CHNSortedCollection_asArray( counts );
    CHNSortedCollection_release( counts );
    
    return ret;
}


static CHNInteger chn_bag_occurrences_of_block(void)
{
    return 0;
}


CHN_EXTERN int CHNBag_occurrencesOf(CHNBag_ref self, id an_object)
{
    return CHNMappedCollection_at_put_ifAbsent( self,
                                                an_object,
                                                CHNCompiledBlock_class_block( chn_bag_occurrences_of_block ) );
}


CHN_EXTERN CHNBoolean CHNBag_includes(CHNBag_ref self, id an_object)
{
    return CHNMappedCollection_includesKey( self, an_object );
}


CHN_EXTERN size_t CHNBag_size(CHNBag_ref self)
{
    size_t            count;
    CHNIterator_ref   it;

    it = CHNMappedCollection_iterator( self->_contents );
    for ( ; CHNIterator_finished( it ); CHNIterator_next( it ) ) {
        CHNInteger_ref element = (CHNInteger_ref)CHNIterator_current( it );

        count += CHNInteger_asInt32( element );
    }
    CHNIterator_release( it );

    return count;
}


CHN_EXTERN CHNHashCode CHNBag_hash(CHNBag_ref self)
{
    return CHNMappedCollection_hash( self->_contents );
}


CHN_EXTERN int CHNBag_equals(CHNBag_ref self, CHNBag_ref other)
{
    return CHNMappedCollection_equals( self->_contents, other->_contents );
}


CHN_EXTERN CHNSet_ref CHNBag_asSet(CHNBag_ref self)
{
    return CHNSet_get_keys( self->_contents );
}


CHN_EXTERN CHNIterator_ref CHNSet_iterator(CHNBag_ref self)
{
    
}
// Local Variables:
//   coding: utf-8
// End:
