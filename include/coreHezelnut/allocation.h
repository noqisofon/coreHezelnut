//  
//  allocation.h
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
#ifndef coreHezelnut_allocation_h
#define coreHezelnut_allocation_h


CHN_EXTERN_C_BEGIN


/*!
 *
 */
CHN_EXPORT void* CHN_malloc(size_t size);


/*!
 *
 */
CHN_EXPORT void* CHN_atomic_malloc(size_t size);


/*!
 *
 */
CHN_EXPORT void* CHN_vmalloc(size_t size);


/*!
 *
 */
CHN_EXPORT void* CHN_realloc(void* ptr, size_t new_size);


/*!
 *
 */
CHN_EXPORT void* CHN_calloc(size_t nelem, size_t size);


/*!
 *
 */
CHN_EXPORT void CHN_free(void* memp);


CHN_EXPORT void* (*_chn_malloc)(size_t);
CHN_EXPORT void* (*_chn_atomic_malloc)(size_t);
CHN_EXPORT void* (*_chn_valloc)(size_t);
CHN_EXPORT void* (*_chn_realloc)(void*, size_t);
CHN_EXPORT void* (*_chn_calloc)(size_t, size_t);
CHN_EXPORT void  (*_chn_free)(void *);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_allocation.h */
