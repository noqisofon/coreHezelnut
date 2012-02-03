//  
//  CHNBlockClosure.c
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
#include "coreHezelnut/coreHezelnut.h"
#include "coreHezelnut/classes.h"
#include "coreHezelnut/callbacks.h"

#include "coreHezelnut/classes/CHNInteger.h"
#include "coreHezelnut/classes/CHNBlockContext.h"
#include "coreHezelnut/classes/CHNCompiledBlock.h"

#include "coreHezelnut/classes/CHNBlockClosure.h"


struct chn_block_closure {
    CHNClass_ref class_pointer;

    CHNBlockContext_ref other_context;
    CHNCompiledBlock_ref block;
    id receiver;
};


CHN_EXPORT id CHNBlockClosure_class_alloc(void)
{
    id new  = CHN_alloc( CHNBlockClosure );

    return new;
}


CHN_EXPORT CHNBlockClosure_ref CHNBlockClosure_class_new(void)
{
    return CHNBlockClosure_init( CHNBlockClosure_class_alloc() );
}


CHN_EXPORT CHNBlockClosure_ref CHNBlockClosure_init(id self)
{
    return CHN_ASBLOCK_CLOSURE( self );
}


static id __exception_handler_reset(id context)
{
    return CHN_at_put( context, CHNContextPart_numArgs( context ) + 1, CHNInteger_class_value( 0 ) );
}


CHN_EXPORT CHNBlockClosure_ref CHNBlockClosure_class_exceptionHandlerResetBlock(void)
{
    CHNBlockClosure_ref exception_handler_reset = CHNBlockClosure_new();

    exception_handler_reset->other_context = NULL;
    exception_handler_reset->block = __exception_handler_reset;
    exception_handler_reset->receiver = nil;

    return exception_handler_reset;
}


CHN_EXPORT int CHNBlockClosure_argumentCount(CHNBlockClosure_ref self)
{
    return CHNCompiledBlock_get_numArgs( self->block );
}
