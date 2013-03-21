//  
//  CHNCompiledMethod.h
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
#ifndef coreHezelnut_classes_CHNCompiledMethod_h
#define coreHezelnut_classes_CHNCompiledMethod_h


CHN_EXTERN_C_BEGIN


typedef struct chn_bihavior* CHNBihavior_ref;
typedef struct chn_symbol* CHNSymbol_ref;

typedef struct chn_compiled_method* CHNCompiledMethod_ref;
CHN_EXPORT const CHNClass_ref CHNCompiledMethod;


#define CHN_ASCOMPILED_METHOD(_that_) ((CHNCompiledMethod_ref)_that_)


/*!
 *
 */
CHN_EXPORT id CHNCompiledMethod_withNewMethodClass(CHNCompiledMethod_ref self, CHNBihavior_ref klass);


/*!
 *
 */
CHN_EXPORT CHNString_ref CHNCompiledMethod_get_methodCategory(CHNCompiledMethod_ref self);


/*!
 *
 */
CHN_EXPORT CHNString_ref CHNCompiledMethod_set_methodCategory(CHNCompiledMethod_ref self, CHNString_ref a_string);


/*!
 *
 */
CHN_EXPORT CHNSymbol_ref CHNCompiledMethod_get_selector(CHNCompiledMethod_ref self);


/*!
 *
 */
CHN_EXPORT CHNSymbol_ref CHNCompiledMethod_set_selector(CHNCompiledMethod_ref self, CHNSymbol_ref a_symbol);


/*!
 *
 */
CHN_EXPORT int CHNCompiledMethod_get_argumentCount(CHNCompiledMethod_ref self);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_classes_CHNCompiledMethod_h */
