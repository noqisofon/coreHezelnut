//  
//  CHNArray.c
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
#include <stddef.h>

#include "coreHezelnut/chn_api.h"
#include "coreHezelnut/chn_class.h"
#include "coreHezelnut/callbacks.h"
#include "coreHezelnut/error_handling.h"

#include "coreHezelnut/classes/CHNIterator.h"
#include "coreHezelnut/classes/CHNCompiledBlock.h"
#include "coreHezelnut/classes/CHNOrderedCollection.h"
#include "coreHezelnut/classes/CHNIODescriptor.h"
#include "coreHezelnut/classes/CHNStream.h"
#include "coreHezelnut/classes/CHNByteArray.h"

#include "coreHezelnut/classes/CHNArray.h"


CHN_EXTERN_C_BEGIN


struct chn_array {
    CHNClass_ref prototype;

    size_t _capacity;
    size_t _size;

    CHNObject_ref* _contents;
};


CHN_EXPORT id CHNArray_class_alloc(void)
{
    return CHNObject_class_alloc( CHNArray );
}


CHN_EXPORT CHNArray_ref CHNArray_class_new(void)
{
    return CHNArray_initWithSize( CHNArray_class_alloc(), 32 );
}


CHN_EXPORT CHNArray_ref CHNArray_class_from(CHNArray_ref an_array)
{
    return an_array;
}


static CHNArray_ref super_init(id base)
{
    return (CHNArray_ref)CHNArrayedCollection_init( CHN_ASARRAYED_COLLECTION(base) );
}


static CHNArray_ref super_free(id base)
{
    CHNArrayedCollection_free( CHN_ASARRAYED_COLLECTION(base) );
}


CHN_EXPORT CHNArray_ref CHNArray_initWithSize(id base, size_t size)
{
    CHNArray_ref self;

    if ( self = super_init( base ) ) {
        if ( size == 0 )
            self->_capacity = size + 1;
        else
            self->_capacity = size;
        self->_size = 0;
        self->_contents = CHN_malloc( sizeof(CHNObject_ref*) * self->_capacity );
    }
    return self;
}


CHN_EXPORT id CHNArray_free(CHNArray_ref self)
{
    int i;
    int stop = (int)self->_capacity;
    id that;

    for ( i = 0; i < stop; ++ i ) {
        that = self->_contents[i];
        if ( that )
            CHNObject_relase( that );
    }
    CHN_free( self->_contents );
    super_free( self );
}


CHN_EXPORT id CHNArray_release(CHNArray_ref self)
{
    super_release(  );
    CHNArray_free( self );
}


CHN_EXPORT id CHNArray_at(CHNArray_ref self, int an_index)
{
    return self->_contents[an_index];
}


CHN_EXPORT id CHNArray_at_ifAbsent(CHNArray_ref self, int an_index, CHNCompiledBlock_ref a_block)
{
    return CHNCollection_checkIndexableBounds_ifAbsent( CHN_ASCOLLECTION(self),
                                                        an_index,
                                                        a_block );
}


CHN_EXPORT id CHNArray_printOn(CHNArray_ref self, CHNStream_ref a_stream)
{
    CHNIterator_ref   it;
    id                element;

    CHNStream_nextPutCh( a_stream, '(' );

    it = CHNCollection_get_iterator( CHN_ASCOLLECTION(self) );
    for ( ; CHNIterator_finished( it ); CHNIterator_next( it ) ) {
        element = CHNIterator_current( it );

        CHNObject_printOn( element, a_stream );
        CHNStream_space( a_stream );
    }
    CHNIterator_release( it );

    CHNStream_nextPutCh( a_stream, ')' );

    return CHN_ASOBJECT(self);
}


CHN_EXPORT CHNBoolean CHNArray_isLiteralObject(CHNArray_ref self)
{
    return !CHNArray_isReadOnly( self );
}


CHN_EXPORT id CHNArray_replaceFrom_to_with_startingAt(CHNArray_ref self, int start, int stop, CHNByteArray_ref byte_array, int replace_start)
{
    return CHNArrayCollection_replaceFrom_to_with_startingAt( CHN_ASARRAYED_COLLECTION(self),
                                                              start,
                                                              stop,
                                                              CHN_ASARRAYED_COLLECTION(byte_array),
                                                              replace_start );
}


CHN_EXPORT id CHNArray_storeLiteralOn(CHNArray_ref self, CHNStream_ref a_stream)
{
    CHNIterator_ref   it;
    id                element;

    if ( CHNClass_equals( CHNObject_get_class( CHN_ASOBJECT(self) ), CHNArray ) )
        return CHNArrayCollection_storeLiteralOn( CHN_ASARRAYED_COLLECTION(self), a_stream );

    CHNStream_nextPutCh( a_stream, '#' );
    CHNStream_nextPutCh( a_stream, '(' );

    it = CHNCollection_get_iterator( CHN_ASCOLLECTION(self) );
    for ( ; CHNIterator_finished( it ); CHNIterator_next( it ) ) {
        element = CHNIterator_current( it );

        CHNObject_storeLiteralOn( element, a_stream );
        CHNStream_space( a_stream );
    }
    CHNIterator_release( it );

    CHNStream_nextPutCh( a_stream, ')' );

    return CHN_ASOBJECT(self);
}


CHN_EXPORT id CHNArray_storeOn(CHNArray_ref self, CHNStream_ref a_stream)
{
    CHNIterator_ref   it;
    id                element;

    if ( CHNClass_equals( CHNObject_get_class( CHN_ASOBJECT(self) ), CHNArray ) )
        return CHNArrayCollection_storeOn( CHN_ASARRAYED_COLLECTION(self), a_stream );

    CHNStream_nextPutCh( a_stream, '#' );
    CHNStream_nextPutCh( a_stream, '(' );

    it = CHNCollection_get_iterator( CHN_ASCOLLECTION(self) );
    for ( ; CHNIterator_finished( it ); CHNIterator_next( it ) ) {
        element = CHNIterator_current( it );

        CHNObject_storeOn( element, a_stream );
        CHNStream_space( a_stream );
    }
    CHNIterator_release( it );

    CHNStream_nextPutCh( a_stream, ')' );

    return CHN_ASOBJECT(self);
}


CHN_EXPORT id CHNArray_multiBecome(CHNArray_ref self, CHNArray_ref an_array)
{
    int   index = 0;
    id    object;
#if 0
    return CHNCollection_collect( self,  );
#else
    CHNIterator_ref it;
    CHNArray_ref prev_self = CHNArray_copy( self );

    it = CHNCollection_get_iterator( CHN_ASCOLLECTION(self) );
    for ( ; CHNIterator_finished( it ); CHNIterator_next( it ) ) {
        object = CHNIterator_current( it );

        CHNObject_become( object, CHNArray_at( an_array, index ) );
        ++ index;
    }
    CHNIterator_release( it );
    /*
      an_array は引数リスト内で動的に作成されたものかもしれない。
     */
    CHNArray_release( an_array );

    return CHN_ASOBJECT(prev_self);
#endif 
}


CHN_EXTERN_C_END
// Local Variables:
//   coding: utf-8
// End:
