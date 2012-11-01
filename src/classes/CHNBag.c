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

#include "coreHezelnut/runtime.h"

#include "coreHezelnut/classes/CHNClass.h"
#include "coreHezelnut/classes/CHNInteger.h"
#include "coreHezelnut/classes/CHNString.h"
#include "coreHezelnut/classes/CHNKeyAndValueIterator.h"
#include "coreHezelnut/classes/CHNHashedCollection.h"
#include "coreHezelnut/classes/CHNSortedCollection.h"
#include "coreHezelnut/classes/CHNMappedCollection.h"
#include "coreHezelnut/classes/CHNLookupTable.h"

#include "coreHezelnut/classes/CHNBag.h"


CHN_EXTERN_C_BEGIN


struct chn_bag {
    CHNMappedCollection_ref _contents;
};


CHN_EXPORT id CHNBag_class_alloc(void)
{
    return CHNObject_class_alloc( CHNBag );
}


CHN_EXPORT CHNBag_ref CHNBag_class_new(void)
{
    return CHNBag_initContents( CHNBag_class_alloc()/* CHNBag_class_basicNew() */, 31 );
}


CHN_EXPORT CHNBag_ref CHNBag_class_new_(size_t size)
{
    return CHNBag_initContents( CHNBag_class_alloc()/* CHNBag_class_basicNew() */, chn_int_max(7, size) );
}


CHN_EXPORT CHNBag_ref CHNBag_class_basicNew(void)
{
    return CHNBag_initContents( CHNBag_class_alloc(), 31 );
}


static CHNBag_ref super_init(id base)
{
    return CHN_ASBag(base);
}


CHN_EXPORT CHNBag_ref CHNBag_initContents(id base, size_t size)
{
    CHNBag_ref self;
    
    if ( self = super_init( base ) ) {
        self->_contents = CHN_ASMAPPED_COLLECTION(CHNObject_newWithSize( CHNBag_dictionaryClass( self ), size ));
    }
    return self;
}


CHN_EXPORT CHNClass_ref CHNBag_dictionaryClass(CHNBag_ref self)
{
    return CHNLookupTable;
}


CHN_EXPORT CHNBag_ref CHNBag_add(CHNBag_ref self, id new_object)
{
    return CHNBag_add_withOccurrences( self, new_object, 1 );
}


CHN_EXPORT CHNBag_ref CHNBag_add_withOccurrences(CHNBag_ref self, id new_object, int an_integer)
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


CHN_EXPORT id CHNBag_remove_ifAbsent(CHNBag_ref self, id old_object, CHNCompiledBlock_ref an_exception_block)
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


CHN_EXPORT CHNArray_ref CHNBag_sortedByCount(CHNBag_ref self)
{
    CHNArray_ref                ret;
    CHNSortedCollection_ref     counts;
    CHNKeyAndValueIterator_ref  it;

    counts  = CHNSortedCollection_class_sortBlock( chn_bag_sorted_by_count_block );
    it      = CHNMappedCollection_keyAndValuesIterator( self->_contents );

    for ( ; CHNKeyAndValueIterator_finished( it ); CHNKeyAndValueIterator_next( it ) ) {
        id  key    = CHNKeyAndValueIterator_currentKey( it );
        id  count  = CHNKeyAndValueIterator_currentValue( it );

        CHNSortedCollection_add( counts, CHNAssociation_class_new( count, key ) );
    }
    CHNKeyAndValueIterator_release( it );

    ret = CHNSortedCollection_asArray( counts );
    CHNSortedCollection_release( counts );
    
    return ret;
}


static CHNInteger_ref chn_bag_occurrences_of_block(void)
{
    return CHNInteger_class_value( 0 );
}


CHN_EXPORT int CHNBag_occurrencesOf(CHNBag_ref self, id an_object)
{
    CHNInteger_ref ret = CHNMappedCollection_at_put_ifAbsent( self,
                                                              an_object,
                                                              CHNCompiledBlock_class_block( chn_bag_occurrences_of_block ) );

    return CHNInteger_asInt32( ret );
}


CHN_EXPORT CHNBoolean CHNBag_includes(CHNBag_ref self, id an_object)
{
    return CHNMappedCollection_includesKey( self, an_object );
}


CHN_EXPORT size_t CHNBag_size(CHNBag_ref self)
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


CHN_EXPORT CHNHashCode CHNBag_hash(CHNBag_ref self)
{
    return CHNMappedCollection_hash( self->_contents );
}


CHN_EXPORT int CHNBag_equals(CHNBag_ref self, CHNBag_ref other)
{
    return CHNMappedCollection_equals( self->_contents, other->_contents );
}


CHN_EXPORT CHNSet_ref CHNBag_asSet(CHNBag_ref self)
{
    return CHNSet_get_keys( self->_contents );
}


CHN_EXPORT CHNClass_ref CHNBag_class(CHNBag_ref self)
{
    return CHNBag;
}


CHN_EXPORT CHNIterator_ref CHNSet_iterator(CHNBag_ref self)
{
    return CHNMappedCollection_iterator( self->_contents );
}


CHN_EXPORT CHNBag_ref CHNBag_storeOn(CHNBag_ref self, CHNStream_ref a_stream)
{
    CHNBoolean                  no_elements;
    CHNKeyAndValueIterator_ref  it;
    id                          key;
    id                          count;

    CHNStream_nextPut( a_stream, '(' );
    CHNStream_nextPutAll( a_stream, CHNClass_storeString( CHNBag_class( self ) ) );
    CHNStream_nextPutAll( a_stream, _S(" new") );

    no_elements = TRUE;
    it = CHNBag_keyAndValueIterator( self );
    for ( ; CHNKeyAndValueIterator_finished( it ); CHNKeyAndValueIterator_next( it ) ) {
        key    = CHNKeyAndValueIterator_currentKey( it );
        count  = CHNKeyAndValueIterator_currentValue( it );

        CHNStream_nextPutAll( a_stream, _S(" add: ") );
        CHNStream_store( a_stream, key );
        CHNStream_nextPutAll( a_stream, _S(" withOccurrences: ") );
        CHNStream_store( a_stream, count );
        CHNStream_nextPut( a_stream, ';' );

        no_elements = FALSE;
    }

    if ( !no_elements )
        CHNStream_nextPutAll( a_stream, _S("; yourself") );
    CHNStream_nextPut( a_stream, ')' );

    return self;
}


CHN_EXPORT CHNBag_ref CHNBag_printOn(CHNBag_ref self, CHNStream_ref a_stream)
{
    CHNBoolean                  no_elements;
    CHNKeyAndValueIterator_ref  it;
    id                          key;
    id                          count;

    CHNStream_nextPutAll( a_stream, CHNClass_storeString( CHNBag_class( self ) ) );
    CHNStream_nextPut( a_stream, '(' );

    it = CHNBag_keyAndValueIterator( self );
    for ( ; CHNKeyAndValueIterator_finished( it ); CHNKeyAndValueIterator_next( it ) ) {
        key    = CHNKeyAndValueIterator_currentKey( it );
        count  = CHNKeyAndValueIterator_currentValue( it );

        CHNStream_print( a_stream, key );
        CHNStream_nextPut( a_stream, ':' );
        CHNStream_print( a_stream, count );
        CHNStream_space( a_stream );
    }
    CHNStream_nextPut( a_stream, ')' );
}


CHN_EXPORT CHNMappedCollection_ref CHNBag_keyAndValues(CHNBag_ref self)
{
    return CHNMappedCollection_copy( self->_contents );
}


CHN_EXPORT CHNMappedCollection_ref CHNBag_contents(CHNBag_ref self)
{
    return CHNMappedCollection_retain( self->_contents );
}


CHN_EXTERN_C_END


// Local Variables:
//   coding: utf-8
// End:
