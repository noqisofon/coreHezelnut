//  
//  error-handling.c
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

#ifdef HAVE_STDIO_H
#   include <stdio.h>
#endif  /* def HAVE_STDIO_H */

#ifdef HAVE_STDARG_H
#   include <stdarg.h>
#endif  /* def HAVE_STDARG_H */

#ifdef HAVE_STDLIB_H
#   include <stdlib.h>
#endif  /* def HAVE_STDLIB_H */

#include "coreHezelnut/chn_api.h"

#include "coreHezelnut/error_handling.h"


CHN_EXTERN_C_BEGIN


static chn_error_handler _chn_error_handler = NULL;


#define CHN_ERROR_HANDLE(_object_, _code_, _format_, _argument_)   (*_chn_error_handler)( _object_, _code_, _format_, _argument_ )


CHN_EXPORT void CHN_error(id object, int code, const char* format, ...)
{
    va_list argument;

    va_start(argument, format);
    CHN_verror( object, code, format, argument );
    va_end(argument);
}


CHN_EXPORT void CHN_verror(id object, int code, const char* format, va_list argument)
{
    CHNBoolean result = FALSE;

    if ( _chn_error_handler )
        result = CHN_ERROR_HANDLE(object, code, format, argument);
    else
        vfprintf( stderr, format, argument );

    if ( result )
        return ;
    else
        abort();
}


CHN_EXTERN_C_END
