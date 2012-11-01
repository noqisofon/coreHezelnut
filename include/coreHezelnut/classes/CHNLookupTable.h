//  
//  CHNSet.h
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
#ifndef coreHezelnut_classes_CHNLookupTable_h
#define coreHezelnut_classes_CHNLookupTable_h


CHN_EXTERN_C_BEGIN


CHN_EXPORT const CHNClass_ref CHNLookupTable;


typedef struct chn_lookup_table* CHNLookupTable_ref;


/*!
 * 
 */
CHN_EXPORT id CHNLookupTable_alloc(void);


/*!
 * 
 */
CHN_EXPORT id CHNLookupTable_init(id self);


/*!
 * 
 */
CHN_EXPORT CHNLookupTable_ref CHNLookupTable_new(void);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_classes_CHNLookupTable_h */
