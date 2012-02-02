//  
//  CHNBlockContext.c
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

#include "coreHezelnut/classes/CHNBlockClosure.h"

#include "coreHezelnut/classes/CHNContextPart.h"


CHN_EXTERN_C_BEGIN


CHN_EXPORT id CHNBlockContext_class_fromClosure_parent(CHNBlockClosure_ref a_block_closure, CHNContextPart_ref parent_context)
{
    CHNContextPart_ref context = CHN_copy( CHN_ASOBJECT(CHNContextPart_get_parentContext( CHN_THIS_CONTEXT )) );

    CHNContextPart_set_parentContext( context, parent_context );

    return CHNBlockClosure_value_with( a_block_closure, context );
}


CHN_EXTERN_C_END
// Local Variables:
//   coding: utf-8
// End:
