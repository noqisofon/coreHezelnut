//  
//  CHNString.h
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
#ifndef coreHezelnut_classes_CHNString_h
#define coreHezelnut_classes_CHNString_h


CHN_EXTERN_C_BEGIN


CHN_EXPORT const CHNClass_ref CHNString;


#define CHN_ASSTRING(_that_) ((CHNString_ref)_that_)

#define _S(_cstring_) CHNString_newWithCString( _cstring_ )


/*!
 *
 */
CHN_EXPORT CHNString_ref CHNString_class_alloc(CHNClass_ref self);


/*!
 *
 */
CHN_EXPORT CHNString_ref CHNString_initWithCString(CHNString_ref self, const char* cstring);


/*!
 *
 */
CHN_EXPORT CHNSymbol_ref CHNString_asSymbol(CHNString_ref self);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_classes_CHNString_h */
