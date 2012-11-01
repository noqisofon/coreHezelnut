//  
//  CHNFileDescriptor.h
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
#ifndef coreHezelnut_classes_CHNFileDescriptor_h
#define coreHezelnut_classes_CHNFileDescriptor_h

#include "coreHezelnut/classes/CHNStream.h"


CHN_EXTERN_C_BEGIN


CHN_EXPORT const CHNClass_ref CHNFileDescriptor;


typedef struct chn_file_descriptor*  CHNFileDescriptor_ref;


#define CHN_ASFILE_DESCRIPTOR(_that_) ((CHNFileDescriptor_ref)_that_)


/*!
 *
 */
CHN_EXPORT void CHNFileDescriptor_class_initialize(void);


/*!
 *
 */
CHN_EXPORT id CHNFileDescriptor_class_alloc(void);


/*!
 *
 */
CHN_EXPORT CHNFileDescriptor_ref CHNFileDescriptor_class_open(CHNString_ref filename);


/*!
 *
 */
CHN_EXPORT CHNFileDescriptor_ref CHNFileDescriptor_class_open_mode(CHNString_ref filename, int32_t file_mode);


/*!
 *
 */
CHN_EXPORT CHNFileDescriptor_ref CHNFileDescriptor_class_open_mode_ifFail(CHNString_ref filename, int32_t file_mode, CHNCompiledBlock_ref a_block);


/*!
 * base_name から一時ファイルを作成します。
 */
CHN_EXPORT CHNFileDescriptor_ref CHNFileDescriptor_class_openTemporaryFile(CHNString_ref base_name);


/*!
 *
 */
CHN_EXPORT CHNFileDescriptor_ref CHNFileDescriptor_init(id base);


/*!
 * ファイルディスクリプターを閉じます。
 */
CHN_EXPORT CHNFileDescriptor_ref CHNFileDescriptor_close(CHNFileDescriptor_ref self);


/*!
 *
 */
CHN_EXPORT void CHNFileDescriptor_free(CHNFileDescriptor_ref self);


/*!
 *
 */
CHN_EXPORT void CHNFileDescriptor_release(CHNFileDescriptor_ref self);



CHN_EXTERN_C_END


#endif  /* coreHezelnut_classes_CHNFileDescriptor_h */
// Local Variables:
//   coding: utf-8
// End:
