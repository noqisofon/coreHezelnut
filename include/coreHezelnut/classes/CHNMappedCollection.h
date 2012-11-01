//  
//  CHNMappedCollection.h
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
#ifndef coreHezelnut_classes_CHNMappedCollection_h
#define coreHezelnut_classes_CHNMappedCollection_h

#include "coreHezelnut/classes/CHNCollection.h"


CHN_EXTERN_C_BEGIN


CHN_EXPORT const CHNClass_ref CHNMappedCollection;


typedef struct chn_mapped_collection* CHNMappedCollection_ref;


#define CHN_ASMAPPED_COLLECTION(_that_)    ((CHNMappedCollection_ref)_that_)


/*!
 * 
 */
CHN_EXPORT id CHNMappedCollection_class_alloc(void);


/*!
 * 
 */
CHN_EXPORT CHNMappedCollection_ref CHNMappedCollection_class_collection_map(CHNHashedCollection_ref a_collection, CHNHashedCollection_ref a_map);


/*!
 * 
 */
CHN_EXPORT CHNMappedCollection_ref CHNMappedCollection_class_new(void);


/*!
 * 
 */
CHN_EXPORT CHNMappedCollection_ref CHNMappedCollection_class_basicNew(void);


/*!
 * 
 */
CHN_EXPORT CHNMappedCollection_ref CHNMappedCollection_init(id base);


/*!
 * 
 */
CHN_EXPORT id CHNMappedCollection_at(CHNMappedCollection_ref self, id key);


/*!
 *
 */
CHN_EXPORT CHNMappedCollection_ref CHNMappedCollection_setCollection_andMap( CHNMappedCollection_ref self,
                                                                             CHNHashedCollection_ref a_collection,
                                                                             CHNHashedCollection_ref a_map);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_classes_CHNMappedCollection_h */
// Local Variables:
//   coding: utf-8
// End:
