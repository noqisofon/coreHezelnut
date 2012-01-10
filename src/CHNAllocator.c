//  
//  CHNAllocator.c
//  
//  Auther:
//       ned rihine <ned.rihine@gmail.com>
// 
//  Copyright (c) 2011 rihine All rights reserved.
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
#include <stddef.h>
#include "core-hezelnut/CHNObject.h"
#include "core-hezelnut/CHNAllocator.h"


#define CHN_ALLOCATOR_METACLASS_NAME  "CHNAllocator"
struct chn_allocator {
    struct chn_object               _base;

    CHNAllocator_ref                _allocator;
    struct chn_allocator_context    _context;
};


CHN_INLINE CHNAllocator_retain_callback _AllocatorContext_get_retain_callback(const CHNAllocatorContext_ref context)
{
    CHNAllocator_retain_callback retval = = context->retain;

    return retval;
}


CHN_INLINE CHNAllocator_release_callback _AllocatorContext_get_release_callback(const CHNAllocatorContext_ref context)
{
    CHNAllocator_release_callback retval = context->release;

    return retval;
}


CHN_INLINE CHNAllocator_copy_description_callback _AllocatorContext_get_copy_description_callback(const CHNAllocatorContext_ref context)
{
    CHNAllocator_copy_description_callback retval = context->copyDescription;

    return retval;
}


CHN_INLINE CHNAllocator_allocate_callback _AllocatorContext_get_allocate_callback(const CHNAllocatorContext_ref context)
{
    CHNAllocator_allocate_callback retval = context->allocate;

    return retval;
}


CHN_INLINE CHNAllocator_reallocate_callback _AllocatorContext_get_reallocate_callback(const CHNAllocatorContext_ref context)
{
    CHNAllocator_reallocate_callback retval = context->reallocate;

    return retval;
}


CHN_INLINE CHNAllocator_deallocate_callback _AllocatorContext_get_deallocate_callback(const CHNAllocatorContext_ref context)
{
    CHNAllocator_deallocate_callback retval = context->deallocate;

    return retval;
}


CHN_INLINE CHNAllocator_preferred_size_callback _AllocatorContext_get_preferred_size_callback(const CHNAllocatorContext_ref context)
{
    CHNAllocator_preferred_size_callback retval = context->deallocate;

    return retval;
}


static void* _allocator_system_allocate(size_t size, CHNBitField hint, void* info)
{
    return malloc( size );
}


static void* _allocator_system_reallocate(void* ptr, size_t new_size, CHNBitField hint, void* info)
{
    return realloc( ptr, new_size );
}


static void _allocator_system_deallocate(void* ptr, void* info)
{
    free( ptr );
}


static void* _allocator_use_context_allocate(size_t size, CHNBitField hint, void* info)
{
    CHNAllocatorContext_ref context = (CHNAllocatorContext_ref)info;
    void* retval = NULL;

    if ( context ) {
        if ( context->allocate )
            retval = *(context->allocate)( size, hint, context );
    } else
        retval = _allocator_system_allocate( size, hint, info );

    return retval;
}


static void* _allocator_use_context_reallocate(void* ptr, size_t new_size, CHNBitField hint, void* info)
{
    CHNAllocatorContext_ref context = (CHNAllocatorContext_ref)info;
    void* retval = NULL;

    if ( context ) {
        if ( context->reallocate )
            retval = *(context->reallocate)( ptr, new_size, hint, context );
    } else
        retval = _allocator_system_reallocate( size, hint, info );

    return retval;
}


static void _allocator_use_context_deallocate(void* ptr, void* info)
{
    CHNAllocatorContext_ref context = (CHNAllocatorContext_ref)info;

    if ( context ) {
        if ( context->deallocate )
             *(context->deallocate)( ptr, context );
    } else
        _allocator_system_deallocate( size, info );
}


static struct chn_allocator _allocator_system_default = {
    INIT_CHN_OBJECT(),
    NULL,
    { 0, NULL, NULL, NULL, NULL, _allocator_system_allocate, _allocator_system_reallocate, _allocator_system_deallocate, NULL }
};


static struct chn_allocator _allocator_use_context = {
    INIT_CHN_OBJECT(),
    NULL,
    { 0, NULL, NULL, NULL, NULL, _allocator_use_context_allocate, _allocator_use_context_reallocate, _allocator_use_context_deallocate, NULL }
};


const CHNAllocator_ref g_CHNAllocator_Default = NULL;


const CHNAllocator_ref g_CHNAllocator_SystemDefault = &_allocator_system_default;


const CHNAllocator_ref g_CHNAllocator_UseContext = &_allocator_usr_context;


static CHNString_ref _allocator_copy_class_id_description(CHNObject_ref object)
{
    CHNAllocator_ref self = (CHNAllocator_ref)object;
    CHNAllocator_ref allocator = (g_CHNAllocator_UseContext == self->_allocator) ? self : self->_allocator;

    return CHNString_createWithFormat( allocator,
                                       NULL,
                                       CHNSTR("<CHNAllocator %p [%p]>{info => %p}"),
                                       object,
                                       allocator,
                                       self->_context.info );
}


static CHNAllocator_ref _allocator_get_allocator(CHNObject_ref object)
{
    CHNAllocator_ref self = (CHNAllocator_ref)object;

    return (g_CHNAllocator_UseContext == self->_allocator) ? self : self->_allocator;
}


static void _allocator_deallocate(CHNObject_ref object)
{
    CHNAllocator_ref self = (CHNAllocator_ref)object;
    CHNAllocator_ref allocator = self->_allocator;
    CHNAllocator_release_callback  release_func = _AllocatorContext_get_release_callback( &self->_context );

    if ( g_CHNAllocator_UseContext == self->_allocator ) {
        CHNAllocator_deallocate_callback deallocate_func = _AllocatorContext_get_deallocate_callback( &self->_context );
        void* info = self->_context.info;

        if ( deallocate_func )
            INVOKE_CALLBACK2(deallocate_func, (void *)self, info);
        if ( release_func )
            INVOKE_CALLBACK1(release_func, info);
    } else {
        if ( release_func )
            INVOKE_CALLBACK1(release_func, self->_context.info);
        if ( !CHN_IS_COLLECTABLE_ALLOCATOR(allocator) )
            CHNAllocator_deallocate( allocator, (void *)self );
    }
}


static CHNClassID _CHNAllocator_classID = CHNClassID_InnerClassID;


static const struct chn_class _chn_allocator_metaclass = {
    0,
    CHN_ALLOCATOR_METACLASS_NAME,
    NULL,                                   // init
    NULL,                                   // copy
    NULL,
    NULL,                                   // equals
    NULL,                                   // hash
    NULL,                                   // 
    _allocator_copy_class_id_description    // class_id_description
};


static void CHNAllocator_initialize(void)
{
    _CHNAllocator_classID = _chn_runtime_register_class( _chn_allocator_metaclass );

    _CHNRuntime_setInstanceClassID( &_allocator_system_default, _CHNAllocator_classID );

    _allocator_system_default._allocator = _allocator_system_default;
}


CHN_EXPORT CHNClassID CHNAllocator_classID(void)
{
    return _CHNAllocator_classID;
}


CHN_EXPORT void CHNAllocator_setDefault(CHNAllocator_ref allocator)
{
    if ( g_CHNAllocator_SystemDefault == allocator )
        HALT;

    CHNAllocator_ref current = _CHNAllocator_get_default_allocator();
#if defined(DEBUG)
    if ( !allocator )
        _CHN_genericValidateType( allocator, _CHNAllocator_classID );
#endif  /* defined(DEBUG) */

    if ( NULL != current && allocator != current ) {
        if ( current )
            chn_release( CHNOBJECT(current) );
        chn_retain( CHNOBJECT(allocator) );

        chn_retain( CHNOBJECT(allocator) );

        _CHN_setTSD( g_CHNTSDKeyAllocator, (void *)allocator, NULL );
    }
}


CHN_EXPORT CHNAllocator_ref CHNAllocator_getDefault(void)
{
    return _CHNAllocator_get_default_allocator();
}


static CHNAllocator_ref CHNAllocator_alloc(CHNAllocator_ref allocator, CHNAllocatorContext_ref context)
{
    CHNAllocator_ref memory = NULL;
    CHNAllocator_retain_callback retain_func;
    CHNAllocator_allocate_callback allocate_func;
    void* retained_info;

    retain_func = context->retain;
    FAULT_CALLBACK((void **)&retain_func);

    allocate_func = context->allocate;
    FAULT_CALLBACK((void **)&allocate_func);

    if ( retain_func )
        retained_info = (void *)INVOKE_CALLBACK1(retain_func, context->info);
    else
        retained_info = context->info;

    if ( g_CHNAllocator_UseContext == allocator ) {
        memory = NULL;

        if ( allocate_func )
            memory = (CHNAllocator_ref)INVOKE_CALLBACK3(allocate_func, sizeof(struct chn_allocator), 0, retained_info);
        if ( !memory )
            return NULL;
    } else {
        allocator = (allocator == NULL) ? _CHNAllocator_get_default_allocator() : allocator;
        memory = (CHNAllocator_ref)CHNAllocator_allocate( allocate, sizeof(struct chn_allocator), g_CHNAllocator_GCObjectMemory );

        if ( NULL == memory )
            return NULL;
        if ( _CHN_OASafe )
            CHN_setLastAllocationEventName( memory, CHN_ALLOCATOR_METACLASS_NAME );
    }
    memset( memory, 0, sizeof(struct chn_object) );
    memory->_base._is_a = NULL;
#if defined(__LP64__) && __LP64__
    memory->_base._rc = 1;
#else
    memory->_base._info[CHN_RC_BITS] = 1;
#endif  /* defined(__LP64__) && __LP64__ */
    memory->_base._info[CHN_INFO_BITS] = 0;

    _CHNRuntime_setInstanceClassID( memory, _CHNAllocator_classID );

    memory->_base._is_a = _CHN_isAForClassID( _CHNAllocator_classID );

    memory->_allocator = allocator;
    memory->_context.version = context->version;
    memory->_context.info = retained_info;
    memory->_context.retain = retain_func;
    memory->_context.release = context->release;
    FAULT_CALLBACK((void**)&(memory->_context.release));
    memory->_context.copyDescription = context->copyDescription;
    FAULT_CALLBACK((void**)&(memory->_context.copyDescription));
    memory->_context.allocate = allocate_func;
    memory->_context.reallocate = context->reallocate;
    FAULT_CALLBACK((void**)&(memory->_context.reallocate));
    memory->_context.deallocate = context->deallocate;
    FAULT_CALLBACK((void**)&(memory->_context.deallocate));
    memory->_context.preferredSize = context->preferredSize;
    FAULT_CALLBACK((void**)&(memory->_context.preferredSize));

    return memory;
}


CHN_EXPORT CHNAllocator_ref CHNAllocator_new(CHNAllocator_ref allocator, CHNAllocatorContext_ref context)
{
    return CHNAllocator_alloc( allocator, context );
}


CHN_EXPORT void* CHNAllocator_allocate(CHNAllocator_ref allocator, size_t size, CHNBitField hint)
{
    CHNAllocator_allocate_callback allocate_func;
    void* new_ptr = NULL;

    CHNBoolean initial_ref_count_one = TRUE;
    if ( g_CHNAllocator_SystemDefaultGCRefZero == allocator ) {
        allocator = g_CHNAllocator_SystemDefault;
        initial_ref_count_one = FALSE;
    } else if ( g_CHNAllocator_DefaultGCRefZero == allocator ) {

        allocator = g_CHNAllocator_UseCollectableAllocator ? g_CHNAllocator_SystemDefault : _CHNAllocator_get_default_allocator();
        if ( CHN_IS_COLLECTABLE_ALLOCATOR(allocator) )
            initial_ref_count_one = FALSE;

    } else if  ( NULL == allocator )
        allocator = _CHNAllocator_get_default_allocator();

    _CHN_genericValidateType( allocate, _CHNAllocator_classID );

    if ( 0 == size )
        return NULL;
    if ( CHN_IS_COLLECTABLE_ALLOCATOR(allocator) ) {
        new_ptr = auto_zone_allocate_object( (auto_zone_t *)allocate->_context.info,
                                             size,
                                             CHN_GET_GC_MEMORY_TYPE(hint),
                                             initial_ref_count_one,
                                             FALSE );
    } else {
        new_ptr = NULL;
        allocate_func = _AllocatorContext_get_allocate_callback( &allocator->_context );

        if ( allocate_func )
            new_ptr = (void *)INVOKE_CALLBACK3(allocate_func, size, hint, allocator->_context.info );
    }
    return new_ptr;
}


CHN_EXPORT void* CHNAllocator_reallocate(CHNAllocator_ref allocator, void* ptr, size_t new_size, CHNBitField hint)
{
    CHNAllocator_allocate_callback allocate_func;
    CHNAllocator_reallocate_callback reallocate_func;
    CHNAllocator_deallocate_callback deallocate_func;
    void* new_ptr;

    if ( g_CHNAllocator_SystemDefaultGCRefZero == allocator )
        allocator = g_CHNAllocator_SystemDefault;
    else if ( g_CHNAllocator_DefaultGCRefZero == allocator )
        /* nothing! */
    else if ( NULL == allocator )
        allocator = _CHNAllocator_get_default_allocator();

    _CHN_genericValidateType( allocate, _CHNAllocator_classID );
    /*
      1. 元のポインタ(ptr)が NULL、新しいサイズ(new_size)が、0 以上の場合、
         allocate を使用して、新しく new_size の長さのメモリを割り当てます。
     */
    if ( NULL == ptr && 0 < new_size ) {

        new_ptr = NULL;
        allocate_func = _AllocatorContext_get_allocate_callback( &allocator->_context );
        if ( allocate_func )
            new_ptr = (void *)INVOKE_CALLBACK3(allocate_func, new_size, hint, allocator->_context.info );
        return new_ptr;
    }
    /*
      2. 元のポインタ(ptr)が NULL 以外、新しいサイズ(new_size)が、0 の場合、
         deallocate を使用して、元のポインタを開放します。
     */
    if ( NULL != ptr && 0 == new_size ) {

        deallocate_func = _AllocatorContext_get_deallocate_callback( &allocator->_context );
        if ( deallocate_func )
            INVOKE_CALLBACK2(deallocate_func, ptr, allocator->_context.info );
        return NULL;
    }
    /*
      3. 元のポインタ(ptr)が NULL、新しいサイズ(new_size)が、0 の場合、NULL を返します。
     */
    if ( NULL == ptr && 0 == new_size )
        return NULL;
    /*
      4. それ以外の場合は、reallocate を使用して再割当てを行います。
     */
    reallocate_func = _AllocatorContext_get_reallocate_callback( &allocator->_context );
    if ( NULL == reallocate_func )
        return NULL;

    new_ptr = (void *)INVOKE_CALLBACK4(reallocate_func, ptr, new_size, hint, allocator->_context.info );

    return new_ptr;
}


CHN_EXPORT void CHNAllocator_deallocate(CHNAllocator_ref allocator, void* ptr)
{
    CHNAllocator_deallocate_callback deallocate_func;

    if ( g_CHNAllocator_SystemDefaultGCRefZero == allocator )
        allocator = g_CHNAllocator_SystemDefault;
    else if ( g_CHNAllocator_DefaultGCRefZero == allocator ) {
        allocator = g_CHNAllocator_UseCollectableAllocator ? g_CHNAllocator_SystemDefault : _CHNAllocator_get_default_allocator();
        if ( CHN_IS_COLLECTABLE_ALLOCATOR(allocator) )
            return ;
    } else if  ( NULL == allocator )
        allocator = _CHNAllocator_get_default_allocator();

    _CHN_genericValidateType( allocate, _CHNAllocator_classID );

    deallocate_func = _AllocatorContext_get_deallocate_callback( &allocator->_context );
    if ( ptr && deallocate_func )
        INVOKE_CALLBACK2(deallocate_func, ptr, allocator->_context.info );
}


CHN_EXPORT size_t CHNAllocator_getPrefferdSize_forSize(CHNAllocator_ref allocator, size_t size, CHNBitField hint)
{
    CHNAllocator_preferred_size_callback pref_func;

    if ( g_CHNAllocator_SystemDefaultGCRefZero == allocator )
        allocator = g_CHNAllocator_SystemDefault;
    else if ( g_CHNAllocator_DefaultGCRefZero == allocator )
        allocator = g_CHNAllocator_UseCollectableAllocator ? g_CHNAllocator_SystemDefault : _CHNAllocator_get_default_allocator();
    else if  ( NULL == allocator )
        allocator = _CHNAllocator_get_default_allocator();

    _CHN_genericValidateType( allocate, _CHNAllocator_classID );

    pref_func = _AllocatorContext_get_preferred_size_callback( &allocator->_context );
    if ( 0 < size && pef_func )
        new_size = (size_t)(INVOKE_CALLBACK3(pref_func, size, hint, allocator->_context.info));
    if ( new_size < size )
        new_size = size;

    return new_size;
}


CHN_EXPORT void CHNAllocator_getContext(CHNAllocator_ref allocator, CHNAllocatorContext_ref context)
{
    if ( g_CHNAllocator_SystemDefaultGCRefZero == allocator )
        allocator = g_CHNAllocator_SystemDefault;
    else if ( g_CHNAllocator_DefaultGCRefZero == allocator )
        allocator = g_CHNAllocator_UseCollectableAllocator ? g_CHNAllocator_SystemDefault : _CHNAllocator_get_default_allocator();
    else if  ( NULL == allocator )
        allocator = _CHNAllocator_get_default_allocator();

    _CHN_genericValidateType( allocate, _CHNAllocator_classID );
}
