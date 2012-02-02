//  
//  CHNContextPart.c
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

#include "coreHezelnut/classes/CHNClass.h"
#include "coreHezelnut/classes/CHNIterator.h"
#include "coreHezelnut/classes/CHNCollection.h"
#include "coreHezelnut/classes/CHNIODescriptor.h"
#include "coreHezelnut/classes/CHNStream.h"
#include "coreHezelnut/classes/CHNTranscript.h"

#include "coreHezelnut/classes/CHNContextPart.h"


CHN_EXTERN_C_BEGIN


struct chn_context_part {
    CHNClass_ref class_pointer;

    CHNContextPart_ref parent;
    id native_ip;
    id ip;
    id sp;
    id receiver;
    id method;
};


static struct chn_class __chn_context_part_metaclass;


static struct chn_class __chn_context_part_class;


CHN_EXPORT void CHNContextPart_class_initialize(void)
{
    __chn_context_part_metaclass.class_pointer = CHNClass;
    __chn_context_part_metaclass.super_class = CHNClass;
    __chn_context_part_metaclass.name = "CHNContextPartMetaClass";
    __chn_context_part_metaclass.version = 0;
    __chn_context_part_metaclass.info = 0;
    __chn_context_part_metaclass.instance_size = sizeof(struct chn_object);
    __chn_context_part_metaclass.variables = NULL;
    __chn_context_part_metaclass.methods = NULL;

    __chn_context_part_class.class_pointer = &__chn_context_part_metaclass;
    __chn_context_part_class.super_class = CHNObject;
    __chn_context_part_class.name = "CHNContextPart";
    __chn_context_part_class.version = 0;
    __chn_context_part_class.info = 0;
    __chn_context_part_class.instance_size = sizeof(struct chn_context_part);
    __chn_context_part_class.variables = NULL;
    __chn_context_part_class.methods = NULL;
}


const CHNClass_ref CHNContextPart = &__chn_context_part_class;


CHN_EXPORT int CHNContextPart_class_spindex(void)
{
    return 4;
}


CHN_EXPORT id CHNContextPart_class_backtrace(void)
{
    CHNContextPart_ref this_context = CHNContextPart_class_thisContext();

    CHNContextPart_backtraceOn( CHNContextPart_get_parentContext( this_context ),
                                CHNTranscript_class_get_instance() );

    CHN_release( CHN_ASOBJECT(this_context) );

    return CHNContextPart;
}


CHN_EXPORT id CHNContextPart_class_backtraceOn(CHNStream_ref a_stream)
{
    CHNContextPart_ref this_context = CHNContextPart_class_thisContext();

    CHNContextPart_backtraceOn( CHNContextPart_get_parentContext( this_context ),
                                a_stream );

    CHN_release( CHN_ASOBJECT(this_context) );

    return CHNContextPart;
}


CHN_EXPORT CHNContextPart_ref CHNContextPart_class_thisContext(void)
{
    /*
      TODO:
      現在のコンテキストを返す。
     */
    return nil;
}


CHN_EXPORT id CHNContextPart_backtrace(CHNContextPart_ref self)
{
    return CHNContextPart_backtraceOn( self,
                                       CHNTranscript_class_get_instance() );
}


CHN_EXPORT id CHNContextPart_backtraceOn(CHNContextPart_ref self, CHNStream_ref a_stream)
{
    CHNContextPart_ref other_context = self;
    CHNContextPart_ref temp_context;

    while ( !( CHN_isNil( CHN_ASOBJECT(other_context) ) || CHNContextPart_isEnvironment( other_context ) ) ) {
        if ( !CHNContextPart_isDisabled( other_context ) ) {
            CHN_printOn( other_context, a_stream );
            CHNStream_nl( a_stream );
        }
        temp_context = other_context;
        other_context = CHNContextPart_get_parentContext( other_context );
        CHN_release( CHN_ASOBJECT(temp_context) );
    }
    return self;
}


CHN_EXPORT id CHNContextPart_get_client(CHNContextPart_ref self)
{
    return CHNContextPart_get_parentContext( self )->receiver;
}


CHN_EXPORT id CHNContextPart_get_environment(CHNContextPart_ref self)
{
    CHNContextPart_ref context = self;
    CHNContextPart_ref next;

    while ( !( CHNContextPart_isEnvironment( context ) ) ) {
        next = CHNContextPart_get_parentContext( context );
        context = next;
    }
    return CHN_ASOBJECT(context);
}


CHN_EXPORT int CHNContextPart_get_initialIP(CHNContextPart_ref self)
{
    return 0;
}


CHN_EXPORT CHNBoolean CHNContextPart_isDisabled(CHNContextPart_ref self)
{
    CHN_subclassResponsibility( CHN_ASOBJECT(self) );

    return FALSE;
}


CHN_EXPORT CHNBoolean CHNContextPart_isUnwind(CHNContextPart_ref self)
{
    CHN_subclassResponsibility( CHN_ASOBJECT(self) );

    return FALSE;
}


CHN_EXPORT CHNBoolean CHNContextPart_isEnvironment(CHNContextPart_ref self)
{
    CHN_subclassResponsibility( CHN_ASOBJECT(self) );

    return FALSE;
}


CHN_EXPORT CHNBoolean CHNContextPart_isProcess(CHNContextPart_ref self)
{
    return CHN_isNil( CHN_ASOBJECT(CHNContextPart_get_parentContext( self )) )
        && !CHNContextPart_isEnvironment( self );
}


CHN_EXPORT CHNContextPart_ref CHNContextPart_get_parentContext(CHNContextPart_ref self)
{
    return self->parent;
}


CHN_EXPORT id CHNContextPart_set_parentContext(CHNContextPart_ref self, CHNContextPart_ref a_context)
{
    id retval = CHN_ASOBJECT(self->parent);

    if ( CHNClass_equals( CHN_get_superclass( CHN_ASOBJECT(CHN_get_class( CHN_ASOBJECT(self) )) ), CHNContextPart )
         || CHN_isNil( CHN_ASOBJECT(a_context) ) )
        return CHNWrongClassError_signalOn_mustBe( CHN_ASOBJECT(a_context), CHNContextPart );

    self->parent = a_context;

    return retval;
}


CHN_EXTERN_C_END
// Local Variables:
//   coding: utf-8
// End:
