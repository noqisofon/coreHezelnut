//  
//  CHNStream.h
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
#ifndef coreHezelnut_classes_CHNStream_h
#define coreHezelnut_classes_CHNStream_h

#include "coreHezelnut/classes/CHNIteratable.h"


CHN_EXTERN_C_BEGIN


typedef struct chn_collection* CHNCollection_ref;
typedef struct chn_ordered_collection* CHNOrderedCollection_ref;
typedef struct chn_file_descriptor* CHNFileDescriptor_ref;

typedef struct chn_stream* CHNStream_ref;
CHN_EXPORT const CHNClass_ref CHNStream;


#define CHN_ASSTREAM(_that_) ((CHNStream_ref)_that_)


/*!
 * 
 */
CHN_EXPORT CHNFileDescriptor_ref CHNStream_get_file(CHNStream_ref self);


/*!
 * 
 */
CHN_EXPORT CHNString_ref CHNStream_get_name(CHNStream_ref self);


/*!
 * ストリーム内の次の要素を返します。
 */
CHN_EXPORT id CHNStream_next(CHNStream_ref self);


/*!
 * 
 */
CHN_EXPORT id CHNStream_nextTake(CHNStream_ref self, int an_integer);


/*!
 * 
 */
CHN_EXPORT int CHNStream_next_putAllOn(CHNStream_ref self, int an_integer, CHNStream_ref a_stream);


/*!
 * 
 */
CHN_EXPORT id CHNStream_next_into_startingAt(CHNStream_ref self, int an_integer, id answer, int pos);


/*!
 * 
 */
CHN_EXPORT id CHNStream_nextAvailable(CHNStream_ref self, int an_integer);


/*!
 * 
 */
CHN_EXPORT int CHNStream_nextAvailable_putAllOn(CHNStream_ref self, int an_integer, CHNStream_ref a_stream);


/*!
 * 
 */
CHN_EXPORT int CHNStream_nextAvailable_into_startingAt(CHNStream_ref self, int an_integer, CHNCollection_ref collection, int pos);


/*!
 * 
 */
CHN_EXPORT CHNBoolean CHNStream_nextMatchFor(CHNStream_ref self, id an_object);


/*!
 * 
 */
CHN_EXPORT CHNOrderedCollection_ref CHNStream_splitAt(CHNStream_ref self, id an_object);


/*!
 * 
 */
CHN_EXPORT CHNOrderedCollection_ref CHNStream_contents(CHNStream_ref self);


/*!
 * 
 */
CHN_EXPORT CHNOrderedCollection_ref CHNStream_upToEnd(CHNStream_ref self);


/*!
 * 
 */
CHN_EXPORT CHNOrderedCollection_ref CHNStream_nextLine(CHNStream_ref self);


/*!
 * 
 */
CHN_EXPORT CHNOrderedCollection_ref CHNStream_upTo(CHNStream_ref self, id an_object);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_classes_CHNStream_h */
// Local Variables:
//   coding: utf-8
// End:
