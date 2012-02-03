//  
//  allocation.c
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
#include "config.h"

#ifdef HAVE_STDLIB_H
#   include <stdlib.h>
#endif  /* def HAVE_STDLIB_H */

#ifdef HAVE_STDARG_H
#   include <stdarg.h>
#endif  /* def HAVE_STDARG_H */

#ifdef HAVE_STRING_H
#   include <string.h>
#endif  /* def HAVE_STRING_H */

#ifdef HAVE_MEMORY_H
#   include <memory.h>
#endif  /* def HAVE_MEMORY_H */

#include "coreHezelnut/coreHezelnut.h"
#include "coreHezelnut/objects.h"
#include "coreHezelnut/error-handling.h"

#include "coreHezelnut/allocation.h"


CHN_EXTERN_C_BEGIN


#define CHN_MALLOC(_size_)            (*_chn_malloc)( _size_ )
#define CHN_ATOMIC_MALLOC(_size_)     (*_chn_atomic_malloc)( _size_ )
#define CHN_VALLOC(_size_)            (*_chn_valloc)( _size_ )
#define CHN_REALLOC(_ptr_, _size_)    (*_chn_realloc)( _ptr_, _size_ )
#define CHN_CALLOC(_nelem_, _size_)   (*_chn_calloc)(_nelem_, _size_)
#define CHN_FREE(_ptr_)               (*_chn_free)(_ptr_)


void* chn_malloc(size_t size)
{
    void* res = CHN_MALLOC(size);

    if ( !res )
        chn_error( nil, CHN_ERR_MEMORY, "virtual memory exhaustend\n" );
    return res;
}


void* chn_atomic_malloc(size_t size)
{
    void* res = CHN_ATOMIC_MALLOC(size);

    if ( !res )
        chn_error( nil, CHN_ERR_MEMORY, "virtual memory exhaustend\n" );
    return res;
}


void* chn_valloc(size_t size)
{
    void* res = CHN_VALLOC(size);

    if ( !res )
        chn_error( nil, CHN_ERR_MEMORY, "virtual memory exhaustend\n" );
    return res;
}


void* chn_realloc(void * ptr, size_t new_size)
{
    void* res = CHN_REALLOC(ptr, new_size);

    if ( !res )
        chn_error( nil, CHN_ERR_MEMORY, "virtual memory exhaustend\n" );
    return res;
}


void* chn_calloc(size_t nelem, size_t size)
{
    void* res = CHN_CALLOC(nelem, size);

    if ( !res )
        chn_error( nil, CHN_ERR_MEMORY, "virtual memory exhaustend\n" );
    return res;
}


void chn_free(void* memp)
{
    CHN_FREE(memp);
}


CHN_EXTERN_C_END
