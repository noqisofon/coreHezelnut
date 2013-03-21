//  
//  CHNCompiledBlock.c
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

#include "coreHezelnut/runtime.h"
#include "coreHezelnut/chn_class.h"
#include "coreHezelnut/callbacks.h"

#include "coreHezelnut/classes/CHNCompiledMethod.h"

#include "coreHezelnut/classes/CHNCompiledBlock.h"


CHN_EXTERN_C_BEGIN


struct chn_compiled_block {
    CHNClass_ref            prototype;

    CHNCompiledMethod_ref   method;
};


CHN_EXPORT id CHNCompiledBlock_class_alloc(void)
{
    return CHNObject_class_alloc( CHNCompiledBlock );
}


CHN_EXPORT CHNCompiledBlock_ref CHNCompiledBlock_class_new(void)
{
    return CHNCompiledBlock_init( CHNCompiledBlock_class_alloc() );
}


CHN_EXPORT CHNCompiledBlock_ref CHNCompiledBlock_init(id self)
{
    return CHN_ASBLOCK_CLOSURE( self );
}


CHN_EXPORT CHNString_ref CHNCompiledBlock_get_methodCategory(CHNCompiledBlock_ref self)
{
    return CHNCompiledMethod_get_methodCategory( self->method );
}


CHN_EXPORT CHNString_ref CHNCompiledBlock_set_methodCategory(CHNCompiledBlock_ref self, CHNString_ref a_category)
{
    return CHNCompiledMethod_set_methodCategory( self->method, a_category );
}


CHN_EXPORT CHNCompiledMethod_ref CHNCompiledBlock_get_method(CHNCompiledBlock_ref self)
{
    return self->method;
}


CHN_EXPORT CHNCompiledMethod_ref CHNCompiledBlock_set_method(CHNCompiledBlock_ref self, CHNCompiledMethod_ref a_method)
{
    CHNCompiledMethod_ref retval;

    retval = self->method;
    self->method = a_method;

    return retval;
}


CHN_EXPORT CHNSymbol_ref CHNCompiledBlock_get_selector(CHNCompiledBlock_ref self)
{
    return CHNCompiledMethod_get_selector( self );
}


CHN_EXPORT CHNSymbol_ref CHNCompiledBlock_set_selector(CHNCompiledBlock_ref self, CHNSymbol_ref a_symbol)
{
    return CHNCompiledMethod_set_selector( self, a_symbol );
}


CHN_EXPORT int CHNCompiledBlock_get_numArgs(CHNCompiledBlock_ref self)
{
    return CHNCompiledMethod_get_argumentCount( self->method );
}


CHN_EXTERN_C_END
// Local Variables:
//   coding: utf-8
// End:
