//  
//  CHNCompiledBlock.h
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
#ifndef coreHezelnut_classes_CHNCompiledBlock_h
#define coreHezelnut_classes_CHNCompiledBlock_h

#include "coreHezelnut/classes/CHNObject.h"


CHN_EXTERN_C_BEGIN


typedef struct chn_compiled_method* CHNCompiledMethod_ref;

typedef struct chn_compiled_block* CHNCompiledBlock_ref;
CHN_EXPORT const CHNClass_ref CHNCompiledBlock;


/*!
 * 
 */
CHN_EXPORT id CHNCompiledBlock_class_alloc(void);


/*!
 * 
 */
CHN_EXPORT CHNCompiledBlock_ref CHNCompiledBlock_class_new(void);


/*!
 * 
 */
CHN_EXPORT CHNCompiledBlock_ref CHNCompiledBlock_init(id self);


/*!
 * 
 */
CHN_EXPORT CHNString_ref CHNCompiledBlock_get_methodCategory(CHNCompiledBlock_ref self);


/*!
 * 
 */
CHN_EXPORT CHNString_ref CHNCompiledBlock_set_methodCategory(CHNCompiledBlock_ref self, CHNString_ref a_category);


/*!
 * 
 */
CHN_EXPORT CHNCompiledMethod_ref CHNCompiledBlock_get_method(CHNCompiledBlock_ref self);


/*!
 * 
 */
CHN_EXPORT CHNCompiledMethod_ref CHNCompiledBlock_set_method(CHNCompiledBlock_ref self, CHNCompiledMethod_ref a_method);


/*!
 *
 */
CHN_EXPORT CHNSymbol_ref CHNCompiledBlock_get_selector(CHNCompiledBlock_ref self);


/*!
 *
 */
CHN_EXPORT int CHNCompiledBlock_get_numArgs(CHNCompiledBlock_ref self);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_classes_CHNCompiledBlock_h */
// Local Variables:
//   coding: utf-8
// End:
