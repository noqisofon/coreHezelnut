//  
//  CHNError.h
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
#ifndef coreHezelnut_CHNError_h
#define coreHezelnut_CHNError_h


typedef struct chn_error* CHNError_ref;


#define CHN_ASERROR(_that_) ((CHNError_ref)_that_)


/*!
 *
 */
CHN_EXPORT id CHNError_class_alloc(void);


/*!
 *
 */
CHN_EXPORT CHNError_ref CHNError_class_new(void);


/*!
 *
 */
CHN_EXPORT CHNError_ref CHNError_class_signalOn();


/*!
 *
 */
CHN_EXPORT CHNError_ref CHNError_init(id base);


/*!
 *
 */
CHN_EXPORT void CHNError_free(CHNError_ref self);


/*!
 *
 */
CHN_EXPORT void CHNError_release(CHNError_ref self);


#endif  /* coreHezelnut_CHNError_h */
