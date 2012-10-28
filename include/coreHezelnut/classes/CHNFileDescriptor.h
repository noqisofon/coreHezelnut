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


typedef struct chn_file_descriptor*  CHNFileDescriptor_ref;


/*!
 *
 */
CHN_EXTERN void CHNFileDescriptor_class_initialize(void);


/*!
 *
 */
CHN_EXTERN id CHNFileDescriptor_class_alloc(void);


/*!
 *
 */
CHN_EXTERN CHNFileDescriptor_ref CHNFileDescriptor_class_open(const char* filename);


/*!
 *
 */
CHN_EXTERN CHNFileDescriptor_ref CHNFileDescriptor_class_open_mode(const char* filename, int32_t file_mode);


/*!
 *
 */
CHN_EXTERN CHNFileDescriptor_ref CHNFileDescriptor_class_open_mode_ifFail(const char* filename, int32_t file_mode, fail_func a_block);


/*!
 * base_name から一時ファイルを作成します。
 */
CHN_EXTERN CHNFileDescriptor_ref CHNFileDescriptor_class_openTemporaryFile(const char* base_name);


/*!
 *
 */
CHN_EXTERN id CHNFileDescriptor_init(id base);


/*!
 * ファイルディスクリプターを閉じます。
 */
CHN_EXTERN CHNFileDescriptor_ref CHNFileDescriptor_close(CHNFileDescriptor_ref self);


/*!
 *
 */
CHN_EXTERN void CHNFileDescriptor_free(CHNFileDescriptor_ref self);


/*!
 *
 */
CHN_EXTERN void CHNFileDescriptor_release(CHNFileDescriptor_ref self);



CHN_EXTERN_C_END


#endif  /* coreHezelnut_classes_CHNFileDescriptor_h */
// Local Variables:
//   coding: utf-8
// End:
