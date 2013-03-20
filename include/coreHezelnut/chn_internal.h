//  
//  chn-internal.h
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
#ifndef coreHezelnut_chn_internal_h
#define coreHezelnut_chn_internal_h

#include "coreHezelnut/target_conditionals.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif  /* def HAVE_STDDEF_H */

#if defined(__GNU__) || defined(CORE_HEZELNUT_TARGET_OS_WIN32)
#   ifdef HAVE_STDINT_H
#       include <stdint.h>
#   endif  /* def HAVE_STDINT_H */
#endif  /* defined(__GNU__) || defined(CORE_HEZELNUT_TARGET_OS_WIN32) */

#if !defined(CHN_EXTERN_C_BEGIN)
#   ifdef __cplusplus
#       define CHN_EXTERN_C_BEGIN extern "C" {
#       define CHN_EXTERN_C_END   }
#   else
#       define CHN_EXTERN_C_BEGIN
#       define CHN_EXTERN_C_END
#   endif   /* def __cplusplus */
#endif  /* !defined(CHN_EXTERN_C_BEGIN) */

#if defined(CORE_HEZELNUT_TARGET_OS_WIN32)
#   if !defined(CHN_EXPORT)
#       if defined(CORE_HEZELNUT_BUILDING) && defined(__cplusplus)
#           define CHN_EXPORT extern "C" __declspec(dllexport)
#       elif defined(CORE_HEZELNUT_BUILDING) && !defined(__cplusplus)
#           define CHN_EXPORT extern __declspec(dllexport)
#       elif defined(__cplusplus)
#           define CHN_EXPORT extern "C" __declspec(dllimport)
#       elif !defined(__cplusplus)
#           define CHN_EXPORT extern __declspec(dllimport)
#       else
#           define CHN_EXPORT
#       endif  /* defined(CORE_HEZELNUT_BUILDING) && defined(__cplusplus) */
#   endif  /* not defined(CHN_EXPORT) */
#else
#   define CHN_EXPORT extern
#endif  /* defined(CORE_HEZELNUT_TARGET_OS_WIN32) */

CHN_EXTERN_C_BEGIN

#if !defined(NULL)
#   if defined(__GNUG__)
#       define NULL __null
#   elif defined(__cplusplus)
#       define NULL 0
#   else
#       define NULL ((void *)0)
#   endif  /* defined(__GNUG__) */
#endif  /* !defined(NULL) */

/*!
 * @typedef CHNBoolean
 * 真偽値の型として利用します。
 */
typedef unsigned char CHNBoolean;


#ifndef TRUE
#   define TRUE 1
#endif  /* ndef TRUE */

#ifndef FALSE
#   define FALSE 0
#endif  /* ndef FALSE */

#if !defined(CHN_INLINE)
#   if defined(__GNUC__) && ( __GNUC__ == 4 ) && !defined(DEBUG)
#       define CHN_INLINE static __inline__ __attribute__((always_inline))
#   elif defined(__GNUC__)
#       define CHN_INLINE static __inline__
#   elif defined(__MWERKS__) || defined(__cplusplus)
#       define CHN_INLINE static inline
#   elif defined(CORE_HEZELNUT_TARGET_OS_WIN32)
#       define CHN_INLINE static __inline__
#   endif  /* defined(__GNUC__) && ( __GNUC__ == 4 ) && !defined(DEBUG) */
#endif  /* !defined(CHN_INLINE) */


typedef void* retval_t;
typedef void (*apply_t)(void);

typedef unsigned int CHNClassID;
typedef unsigned int CHNBitField;
typedef unsigned int CHNIndex;
typedef unsigned int CHNCount;
typedef unsigned int CHNSize;
typedef unsigned int CHNHashCode;


typedef const void* CHNValue_ref;


typedef struct chn_object {
    struct chn_class* prototype;
} *id;


#define nil ((id)0)

typedef const struct chn_string*       CHNConstantString_ref;
typedef       struct chn_string*       CHNMutableString_ref;


#define CHNString_ref CHNConstantString_ref


typedef struct chn_ordered_collection* CHNOrderedCollection_ref;
typedef struct chn_set*                CHNSet_ref;
typedef struct chn_stream*             CHNStream_ref;
typedef struct chn_write_stream*       CHNWriteStream_ref;
typedef struct chn_symbol*             CHNSymbol_ref;
typedef struct chn_character*          CHNCharacter_ref;
typedef struct chn_array*              CHNArray_ref;
typedef struct chn_iterator*           CHNIterator_ref;
typedef struct chn_integer_array*      CHNIntegerArray_ref;
typedef struct chn_byte_array*         CHNByteArray_ref;
typedef struct chn_message*            CHNMessage_ref;
typedef struct chn_block_context*      CHNBlockContext_ref;
typedef struct chn_context_part*       CHNContextPart_ref;
typedef struct chn_block_closure*      CHNBlockClosure_ref;
typedef struct chn_compiled_block*     CHNCompiledBlock_ref;
typedef struct chn_compiled_method*    CHNCompiledMethod_ref;
typedef struct chn_bihavior*           CHNBihavior_ref;


enum __CHNComparisonResults {
    CHNComparisonResults_LessThan    = -1,  //!< left が right より小さい時に返されます。
    CHNComparisonResults_SameAs      =  0,  //!< left が right と等しい時に返されます。
    CHNComparisonResults_GreaterThan =  1,  //!< left が right より大きい時に返されます。
};
typedef int CHNComparisonResult;


typedef CHNComparisonResult (*chn_comparison_func)(id left, id right);


enum __CHNAccessResults {
    CHNAccessResults_NotFound = -1
};


typedef struct _chn_range {
    int first;
    int last;
} CHNRange;


#ifdef CHN_INLINE
CHN_INLINE CHNRange CHNRange_new(int first, int last)
{
    CHNRange new;

    new.first = first;
    new.last = last;

    return new;
}


CHN_INLINE CHNBoolean CHNRange_isInclude(CHNRange range, int x)
{
    return range.first <= x && x < range.last;
}
#else
#   define  CHNRange_new(_first_, _last_)  __CHNRange_new( _first_, _last_ )
#   define  CHNRange_isInclude(_range_, _x_)  __CHNRange_between( _range_, _x_ )
#endif  /* def CHN_INLINE */


/*!
 *
 */
CHN_EXPORT CHNRange __CHNRange_new(int first, int last);


/*!
 *
 */
CHN_EXPORT CHNBoolean __CHNRange_between(CHNRange range, int x);


#define INVOKE_CALLBACK0(_func_)                                           (*_func_)()
#define INVOKE_CALLBACK1(_func_, _arg0_)                                   (*_func_)( _arg0_ )
#define INVOKE_CALLBACK2(_func_, _arg0_, _arg1_)                           (*_func_)( _arg0_, _arg1_ )
#define INVOKE_CALLBACK3(_func_, _arg0_, _arg1_, _arg2_)                   (*_func_)( _arg0_, _arg1_, _arg2_ )
#define INVOKE_CALLBACK4(_func_, _arg0_, _arg1_, _arg2_, _arg3_)           (*_func_)( _arg0_, _arg1_, _arg2_, _arg3_ )
#define INVOKE_CALLBACK5(_func_, _arg0_, _arg1_, _arg2_, _arg3_, _arg4_)   (*_func_)( _arg0_, _arg1_, _arg2_, _arg3_, _arg4_ )



CHN_EXTERN_C_END


#endif  /* coreHezelnut_chn_internal_h */
