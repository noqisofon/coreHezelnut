//  
//  CHNBihavior.h
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
#ifndef coreHezelnut_CHNBihavior_h
#define coreHezelnut_CHNBihavior_h


/*!
 * 
 */
CHN_EXPORT id CHNBihavior_addInstVarName(CHNBihavior_ref self, CHNString_ref a_string);


/*!
 * 
 */
CHN_EXPORT id CHNBihavior_removeInstVarName(CHNBihavior_ref self, CHNString_ref a_string);


/*!
 * 
 */
CHN_EXPORT id CHNBihavior_set_instanceVariableNames(CHNBihavior_ref self, CHNCollection_ref inst_var_names);


/*!
 *
 */
CHN_EXPORT CHNCollection_ref CHNBihavior_parseVariableString(CHNBihavior_ref self, CHNString_ref variable_string);


/*!
 *
 */
CHN_EXPORT CHNCollection_ref CHNBihavior_parseInstanceVariableString(CHNBihavior_ref self, CHNString_ref variable_string);


/*!
 * 
 */
CHN_EXPORT id CHNBihavior_set_methodDictionary(CHNBihavior_ref self, CHNSet_ref a_dictionary);


/*!
 * 
 */
CHN_EXPORT id CHNBihavior_addSelector_withMethod(CHNBihavior_ref self, CHNSymbol_ref selector, CHNCompiledMethod_ref compiled_method);


/*!
 * 
 */
CHN_EXPORT id CHNBihavior_removeSelector(CHNBihavior_ref self, CHNSymbol_ref selector);


/*!
 * 
 */
CHN_EXPORT id CHNBihavior_removeSelector_ifAbsent(CHNBihavior_ref self, CHNSymbol_ref selector, chn_if_absent_callback a_block);


/*!
 * 
 */
CHN_EXPORT id CHNBihavior_formattedSourceStringAt(CHNBihavior_ref self, CHNSymbol_ref selector);


/*!
 * 
 */
CHN_EXPORT id CHNBihavior_formattedSourceStringAt_ifAbsent(CHNBihavior_ref self, CHNSymbol_ref selector, chn_if_absent_callback a_block);


/*!
 * 
 */
CHN_EXPORT id CHNBihavior_compile(CHNBihavior_ref self, id code);


/*!
 * 
 */
CHN_EXPORT id CHNBihavior_compile_ifError(CHNBihavior_ref self, id code, chn_if_error_callback a_block);


/*!
 * 
 */
CHN_EXPORT id CHNBihavior_compile_notifying(CHNBihavior_ref self, id code, id requestor);


/*!
 * 
 */
CHN_EXPORT id CHNBihavior_compileAllSubclasses(CHNBihavior_ref self);


/*!
 * 
 */
CHN_EXPORT CHNBoolean CHNBihavior_inheritsFrom(CHNBihavior_ref self, CHNBihavior_ref a_class);


/*!
 * 
 */
CHN_EXPORT CHNSymbol_ref CHNBihavior_get_shape(CHNBihavior_ref self);


/*!
 * 
 */
CHN_EXPORT CHNClass_ref CHNBihavior_set_superclass(CHNBihavior_ref self, CHNBihavior_ref a_class);


/*!
 * self にサブクラスとして a_class を追加します。
 */
CHN_EXPORT id CHNBihavior_addSubclass(CHNBihavior_ref self, CHNClass_ref a_class);


/*!
 * self に含まれているサブクラスの a_class を削除します。
 */
CHN_EXPORT id CHNBihavior_removeSubclass(CHNBihavior_ref self, CHNClass_ref a_class);


/*!
 * 
 */
CHN_EXPORT CHNSet_ref CHNBihavior_get_selectors(CHNBihavior_ref self);


/*!
 * 
 */
CHN_EXPORT CHNSet_ref CHNBihavior_get_allSelectors(CHNBihavior_ref self);


/*!
 * 
 */
CHN_EXPORT id CHNBihavior_allSubclassesDo(CHNBihavior_ref self, void* pcontext, chn_doing_callback a_block);


/*!
 * 
 */
CHN_EXPORT id CHNBihavior_allSuperclassesDo(CHNBihavior_ref self, void* pcontext, chn_doing_callback a_block);


/*!
 * 
 */
CHN_EXPORT id CHNBihavior_withAllSubclassesDo(CHNBihavior_ref self, void* pcontext, chn_doing_callback a_block);


/*!
 * 
 */
CHN_EXPORT id CHNBihavior_withAllSuperclassesDo(CHNBihavior_ref self, void* pcontext, chn_doing_callback a_block);


#endif  /* coreHezelnut_CHNBihavior_h */
// Local Variables:
//   coding: utf-8
// End:
