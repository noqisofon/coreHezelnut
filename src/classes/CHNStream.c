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

#include "coreHezelnut/classes/CHNClass.h"
#include "coreHezelnut/classes/CHNIterator.h"
#include "coreHezelnut/classes/CHNCollection.h"
#include "coreHezelnut/classes/CHNIODescriptor.h"
#include "coreHezelnut/classes/CHNString.h"
#include "coreHezelnut/classes/CHNWriteStream.h"

#include "coreHezelnut/classes/CHNNotEnoughElementsError.h"

#include "coreHezelnut/classes/CHNStream.h"


CHN_EXTERN_C_BEGIN


CHN_EXPORT CHNIODescriptor_ref CHNStream_get_file(CHNStream_ref self)
{
    return CHN_ASIO_DESCRIPTOR(nil);
}


CHN_EXPORT CHNString_ref CHNStream_get_name(CHNStream_ref self)
{
    return CHN_ASSTRING(nil);
}


CHN_EXPORT id CHNStream_next(CHNStream_ref self)
{
    return CHNObject_subclassResponsibility( CHN_ASOBJECT(self) );
}


CHN_EXPORT id CHNStream_nextTake(CHNStream_ref self, int an_integer)
{
    id answer = CHNObject_class_newWithSize( CHNStream_species( self ), an_integer );

    CHNStream_next_into_startingAt( self, an_integer, answer, 0 );

    return answer;
}


CHN_EXPORT int CHNStream_next_putAllOn(CHNStream_ref self, int an_integer, CHNStream_ref a_stream)
{
    int read = 0;

    while ( !(read == an_integer) ) {
        if ( CHNStream_atEnd( self ) ) {
            CHNNotEnoughElementsError_signalOn( an_integer - read );

            return -1;
        }
        read += CHNStream_nextAvailable_putAllOn( self,
                                                  an_integer - read,
                                                  a_stream );
    }
    return read;
}


CHN_EXPORT id CHNStream_next_into_startingAt(CHNStream_ref self, int an_integer, id answer, int pos)
{
    int read = 0;

    while ( !(read == an_integer) ) {
        if ( CHNStream_atEnd( self ) )
            return CHNNotEnoughElementsError_signalOn( an_integer - read );
        /*
          answer は、空のコレクションであり、関数が中身を詰めることになる。
         */
        read += CHNStream_nextAvailable_into_startingAt( self,
                                                         an_integer - read,
                                                         answer,
                                                         read + pos );
    }
    return read;
}


CHN_EXPORT id CHNStream_nextAvailable(CHNStream_ref self, int an_integer)
{
    int n;
    id answer;
    id temp;

    answer = CHNObject_class_newWithSize( CHNStream_species( self ), an_integer );
    n = CHNStream_nextAvailable_into_startingAt( self, an_integer, answer, 0 );

    if ( n < an_integer ) {
        temp = answer;

        answer = CHNCollection_copyFrom( CHN_ASCOLLECTION(answer), 0, n );

        CHNObject_release( temp );
    }
    return answer;
}


CHN_EXPORT int CHNStream_nextAvailable_putAllOn(CHNStream_ref self, int an_integer, CHNStream_ref a_stream)
{
    int n = chn_int_min( an_integer, 1024 );
    id collection;

    collection = CHNObject_class_newWithSize( CHNStream_species( self ), an_integer );
    n = CHNStream_nextAvailable_into_startingAt( n,
                                                 an_integer,
                                                 collection,
                                                 0 );

    CHNStream_next_putAll_startingAt( a_stream, n, collection , 0 );
    CHNObject_release( collection );

    return n;
}


CHN_EXPORT int CHNStream_nextAvailable_into_startingAt(CHNStream_ref self, int an_integer, CHNCollection_ref collection, int pos)
{
    int i = 0;

    while ( i != an_integer ) {
        if ( CHNStream_atEnd( self ) )
            return i;

        CHNCollection_at_put( collection, i + pos, CHNStream_next( self ) );

        ++ i;
    }
    return an_integer;
}


CHN_EXPORT CHNBoolean CHNStream_nextMatchFor(CHNStream_ref self, id an_object)
{
    return CHNObject_equals( an_object, CHNStream_next( self ) );
}


CHN_EXPORT CHNOrderedCollection_ref CHNStream_splitAt(CHNStream_ref self, id an_object)
{
    CHNOrderedCollection_ref result = CHNOrderedCollection_newWithSize( 10 );

    while ( !CHNStream_atEnd( self ) ) {
        CHNOrderedCollection_addLast( result, CHNStream_upTo( self, an_object ) );
    }
    return result;
}


/*!
 * 
 */
CHN_EXPORT CHNOrderedCollection_ref CHNStream_contents(CHNStream_ref self)
{
    return CHNStream_upToEnd( self );
}


CHN_EXPORT CHNOrderedCollection_ref CHNStream_upToEnd(CHNStream_ref self)
{
    CHNOrderedCollection_ref result;
    CHNWriteStream_ref write_stream = CHNWriteStream_on( CHNObject_class_newWithSize( CHNStream_species( self ), 8 ) );

    CHNStream_nextPutAllOn( self, write_stream );

    result = CHNStream_contents( write_stream );
    CHNWriteStream_release( write_stream );

    return result;
}


CHN_EXPORT CHNOrderedCollection_ref CHNStream_nextLine(CHNStream_ref self)
{
    CHNOrderedCollection_ref result;

    id next;
    CHNWriteStream_ref write_stream = CHNWriteStream_on( CHNObject_class_newWithSize( CHNStream_species( self ), 40 ) );

    while ( !( CHNStream_atEnd( self )
               || CHNObject_equals( next = CHNStream_next( self ), CHNCharacter_cr() )
               || CHNObject_equals( next = CHNStream_next( self ), CHNCharacter_nl() )
               || CHN_isNil( next ) ) ) {
        CHNWriteStream_nextPut( write_stream, next );
    }
    result = CHNStream_contents( write_stream );
    CHNWriteStream_release( write_stream );

    return result;
}


CHN_EXPORT CHNOrderedCollection_ref CHNStream_upTo(CHNStream_ref self, id an_object)
{
    id next;
    CHNOrderedCollection_ref result;
    CHNWriteStream_ref write_stream = CHNWriteStream_on( CHNObject_class_newWithSize( CHNStream_species( self ), 8 ) );

    while ( !( CHNStream_atEnd( self ) || CHNObject_equals( ( next = CHNStream_next( self ) ), an_object ) ) ) {
        CHNWriteStream_nextPut( write_stream, next );
    }

    result = CHNStream_contents( write_stream );
    CHNWriteStream_release( write_stream );

    return result;
}


CHN_EXPORT CHNOrderedCollection_ref CHNStream_upToAll(CHNStream_ref self, CHNCollection_ref a_collection)
{
    CHNWriteStream_ref result_stream;
    CHNIntegerArray_ref prefix;
    id ch;
    CHNOrderedCollection_ref result;
    int j;

    if ( CHNStream_atEnd( self ) )
        return CHNObject_class_new( CHNStream_species( self ) );
    if ( CHNCollection_isEmpty( a_collection ) )
        return CHNObject_class_new( CHNStream_species( self ) );

    result_stream = CHNWriteStream_on( CHNObject_class_newWithSize( CHNStream_species( self ), 20 ) );
    /*
      prefix の型は CHNIntegerArray で、プリミティブの int 型の要素で成り立っている…ことにしておく。
     */
    prefix = CHNStream_prefixTableFor( self, a_collection );
    ch     = CHNStream_next( self );

    CHNCollection_release( a_collection );

    CHNStream_nextPut( result_stream, ch );

    j = 0;
    for ( ; ; ) {
        if ( ( CHNObject_equals( ch, CHNCollection_at( a_collection, j ) )
               || ( j = CHNIntegerArray_at( prefix, j ) ) == 0 ) ) {
            ++ j;

            if ( j > CHNIntegerArray_size( prefix ) ) {
                CHNWriteStream_skip( result_stream, chn_int_negated( CHNCollection_size( a_collection ) ) );

                result = CHNWriteStream_contents( result_stream );
                CHNObject_release( CHN_ASOBJECT(result_stream) );
                CHNObject_release( CHN_ASOBJECT(prefix) );

                return result;
            }

            if ( CHNStream_atEnd( self ) ) {
                result = CHNWriteStream_contents( result_stream );
                CHNObject_release( CHN_ASOBJECT(result_stream) );
                CHNObject_release( CHN_ASOBJECT(prefix) );

                return result;
            }

            ch = CHNStream_next( self );
            CHNStream_nextPut( result_stream, ch );
        }
    }
    return nil;
}


CHN_EXTERN_C_END
// Local Variables:
//   coding: utf-8
// End:
