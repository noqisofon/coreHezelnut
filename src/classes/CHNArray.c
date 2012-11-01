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
#include "coreHezelnut/coreHezelnut.h"
#include "coreHezelnut/classes.h"
#include "coreHezelnut/callbacks.h"

#include "coreHezelnut/classes/CHNIterator.h"
#include "coreHezelnut/classes/CHNCompiledBlock.h"
#include "coreHezelnut/classes/CHNOrderedCollection.h"
#include "coreHezelnut/classes/CHNIODescriptor.h"
#include "coreHezelnut/classes/CHNStream.h"
#include "coreHezelnut/classes/CHNByteArray.h"

#include "coreHezelnut/classes/CHNArray.h"


CHN_EXTERN_C_BEGIN


CHN_EXPORT CHNArray_ref CHNArray_class_from(CHNArray_ref an_array)
{
    return an_array;
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
