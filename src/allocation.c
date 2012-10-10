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

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif  /* def HAVE_STDDEF_H */

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

#include "coreHezelnut/chn_api.h"
#include "coreHezelnut/error_handling.h"

#include "coreHezelnut/allocation.h"


CHN_EXTERN_C_BEGIN


void* __chn_malloc(size_t size);
void* __chn_atomic_malloc(size_t size);
void* __chn_valloc(size_t size);
void* __chn_realloc(void * ptr, size_t new_size);
void* __chn_calloc(size_t nelem, size_t size);
void  __chn_free(void* memp);


CHN_EXPORT void* (*_chn_malloc)(size_t)            = __chn_malloc;
CHN_EXPORT void* (*_chn_atomic_malloc)(size_t)     = __chn_atomic_malloc;
CHN_EXPORT void* (*_chn_valloc)(size_t)            = __chn_valloc;
CHN_EXPORT void* (*_chn_realloc)(void*, size_t)    = __chn_realloc;
CHN_EXPORT void* (*_chn_calloc)(size_t, size_t)    = __chn_calloc;
CHN_EXPORT void  (*_chn_free)(void *)              = __chn_free;


#define CHN_MALLOC(_size_)            (*_chn_malloc)( _size_ )
#define CHN_ATOMIC_MALLOC(_size_)     (*_chn_atomic_malloc)( _size_ )
#define CHN_VALLOC(_size_)            (*_chn_valloc)( _size_ )
#define CHN_REALLOC(_ptr_, _size_)    (*_chn_realloc)( _ptr_, _size_ )
#define CHN_CALLOC(_nelem_, _size_)   (*_chn_calloc)( _nelem_, _size_ )
#define CHN_FREE(_ptr_)               (*_chn_free)( _ptr_ )


CHN_EXPORT void* CHN_malloc(size_t size)
{
    void* memp = CHN_MALLOC(size);

    if ( !memp )
        CHN_error( nil, CHN_ERR_MEMORY, "virtual memory exhaustend\n" );
    return memp;
}


CHN_EXPORT void* CHN_atomic_malloc(size_t size)
{
    void* memp = CHN_ATOMIC_MALLOC(size);

    if ( !memp )
        CHN_error( nil, CHN_ERR_MEMORY, "virtual memory exhaustend\n" );
    return memp;
}


CHN_EXPORT void* CHN_valloc(size_t size)
{
    void* memp = CHN_VALLOC(size);

    if ( !memp )
        CHN_error( nil, CHN_ERR_MEMORY, "virtual memory exhaustend\n" );
    return memp;
}


CHN_EXPORT void* CHN_realloc(void * ptr, size_t new_size)
{
    void* memp = CHN_REALLOC(ptr, new_size);

    if ( !memp )
        CHN_error( nil, CHN_ERR_MEMORY, "virtual memory exhaustend\n" );
    return memp;
}


CHN_EXPORT void* CHN_calloc(size_t nelem, size_t size)
{
    void* memp = CHN_CALLOC(nelem, size);

    if ( !memp )
        CHN_error( nil, CHN_ERR_MEMORY, "virtual memory exhaustend\n" );
    return memp;
}


CHN_EXPORT void CHN_free(void* memp)
{
    CHN_FREE(memp);
}


void* __chn_malloc(size_t size)
{
    if ( size == 0 )
        size = 1;

    return malloc( size );
}


void* __chn_atomic_malloc(size_t size)
{
    if ( size == 0 )
        size = 1;

    return malloc( size );
}


void* __chn_valloc(size_t size)
{
    if ( size == 0 )
        size = 1;

    return malloc( size );
}


void* __chn_realloc(void* ptr, size_t new_size)
{
    if ( new_size == 0 )
        new_size = 1;

    return realloc( ptr, new_size );
}


void* __chn_calloc(size_t nelem, size_t size)
{
    if ( nelem == 0 )
        nelem = 1;
    if ( size == 0 )
        size = 1;

    return calloc( nelem, size );
}


void  __chn_free(void* memp)
{
    free( memp );
}


CHN_EXTERN_C_END
// Local Variables:
//   coding: utf-8
// End:
