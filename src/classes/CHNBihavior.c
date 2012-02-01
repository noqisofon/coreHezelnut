//  
//  CHNBihavior.c
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

#include "coreHezelnut/classes/CHNIterator.h"
#include "coreHezelnut/classes/CHNIODescriptor.h"
#include "coreHezelnut/classes/CHNCollection.h"
#include "coreHezelnut/classes/CHNDictionary.h"
#include "coreHezelnut/classes/CHNStream.h"
#include "coreHezelnut/classes/CHNWriteStream.h"
#include "coreHezelnut/classes/CHNByteArray.h"
#include "coreHezelnut/classes/CHNArray.h"
#include "coreHezelnut/classes/CHNOrderedCollection.h"
#include "coreHezelnut/classes/CHNString.h"
#include "coreHezelnut/classes/CHNCompiledMethod.h"
#include "coreHezelnut/classes/CHNSymbol.h"

#include "coreHezelnut/classes/CHNNotFoundError.h"

#include "coreHezelnut/classes/CHNBihavior.h"


struct chn_bihavior {
    CHNClass_ref              class_pointer;

    CHNClass_ref              super_class;
    CHNDictionary_ref         method_dictionary;
    unsigned int              instance_spec;
    CHNOrderedCollection_ref  sub_classes;
    CHNOrderedCollection_ref  instance_variables;
};


CHN_EXPORT id CHNBihavior_addInstVarName(CHNBihavior_ref self, CHNString_ref a_string)
{
    CHNCollection_ref new_instance_variables;
    CHNBoolean duplicated;
    CHNSymbol_ref symbol;

    CHNOrderedCollection_ref instance_variables = self->instance_variables;
    CHNCollection_ref temp_inst_names;

    CHNBihavior_validateIdentifier( self, a_string );
    symbol = CHNString_asSymbol( a_string );

    if ( CHN_isNil( CHN_ASOBJECT(symbol) ) )
        new_instance_variables = CHN_ASCOLLECTION(CHN_ARRAY_LITERAL1(symbol));
    else
        new_instance_variables = CHN_ASCOLLECTION(CHNCollection_copyWith( CHN_ASCOLLECTION(instance_variables), CHN_ASOBJECT(symbol) ));

    CHN_release( CHN_ASOBJECT(symbol) );

    temp_inst_names = CHN_ASCOLLECTION(CHN_allInstVarNames( CHN_ASOBJECT(CHN_get_superclass( self )) ));
    duplicated = CHNCollection_includes( temp_inst_names );

    CHN_release( CHN_ASOBJECT(temp_inst_names) );

    CHNBihavior_updateInstanceVars( CHN_ASOBJECT(self),
                                    new_instance_variables,
                                    CHNBihavior_get_shape(self) );
    CHN_release( CHN_ASOBJECT(new_instance_variables) );

    if ( duplicated )
        CHNBihavior_compileAll( self );
    CHNBihavior_compileAllSubclasses( self );

    return CHN_ASOBJECT(self);
}


struct temp_find_last_context0 {
    id receiver;  /*! 関数の第一引数が渡されます。 */
    CHNSymbol_ref symbol;
};


static CHNBoolean __remove_inst_var_name_find_last(void* pcontext, id each)
{
    struct temp_find_last_context0* context = (struct temp_find_last_context0 *)pcontext;

    return CHN_equals( each, CHN_ASOBJECT(context->symbol) );
}


CHN_EXPORT id CHNBihavior_removeInstVarName(CHNBihavior_ref self, CHNString_ref a_string)
{
    CHNCollection_ref new_instance_variables;
    CHNSymbol_ref symbol = CHNString_asSymbol( a_string );
    int index = 0;

    CHNCollection_ref instance_variables = CHN_ASCOLLECTION(self->instance_variables);

    struct temp_find_last_context0 context;
    context.symbol = symbol;

    index = CHNOrderedCollection_findLast( instance_variables,
                                           __remove_inst_var_name_find_last,
                                           &context );

    if ( index == 0 ) {
        CHN_release( CHN_ASOBJECT(new_instance_variables) );
        /*
          symbol は CHNNotFoundError_signalOn_what 内で release されると思う。
         */
        return CHNNotFoundError_signalOn_what( CHN_ASOBJECT(symbol), _S("instance variable") );
    }
    CHN_release( CHN_ASOBJECT(symbol) );

    new_instance_variables = CHN_ASCOLLECTION(CHNCollection_copyReplaceFrom_to_with( CHN_ASCOLLECTION(instance_variables),
                                                                                     index,
                                                                                     index,
                                                                                     CHN_ARRAY_LITERAL_EMPTY ));
    CHNBihavior_updateInstanceVars_shape( self,
                                          new_instance_variables,
                                          CHNBihavior_get_shape( self ) );

    CHN_release( CHN_ASOBJECT(new_instance_variables) );

    CHNBihavior_compileAll( self );
    CHNBihavior_compileAllSubclasses( self );
}


struct temp_any_satisfy_context0 {
    id receiver;  /*! 関数の第一引数が渡されます。 */
    CHNCollection_ref other;
};


static CHNBoolean __setinst_var_names_any_satisfy0(void* pcontext, id each)
{
    struct temp_any_satisfy_context0* context = (struct temp_any_satisfy_context0 *)pcontext;
    CHNCollection_ref variable_array = CHN_ASCOLLECTION(context->other);

    return !CHNCollection_includes( variable_array, each );
}


static CHNBoolean __setinst_var_names_any_satisfy1(void* pcontext, id each)
{
    struct temp_any_satisfy_context0* context = (struct temp_any_satisfy_context0 *)pcontext;
    CHNCollection_ref old_inst_var_names = CHN_ASCOLLECTION(context->other);

    return !CHNCollection_includes( old_inst_var_names, each );
}


CHN_EXPORT id CHNBihavior_set_instanceVariableNames(CHNBihavior_ref self, CHNCollection_ref inst_var_names)
{
    CHNCollection_ref variable_array = CHNBihavior_parseInstanceVariableString( self, CHN_ASSTRING(inst_var_names) );
    CHNCollection_ref old_inst_var_names = CHNBihavior_allInstVarNames( self );

    variable_array = CHN_concat( CHNBihavior_subclassInstVarNames( self ), variable_array );

    if ( CHN_equals( CHN_ASOBJECT(variable_array), CHN_ASOBJECT(old_inst_var_names) ) ) {
        CHN_release( variable_array );
        CHN_release( old_inst_var_names );

        return self;
    }
    CHNBihavior_updateInstanceVars_shape( self,
                                          variable_array,
                                          CHNBehabior_get_shape( self ) );

    CHNBoolean changed, removed, added;
    CHNCollection_ref temp0, temp1;
    int old_size = CHN_size( CHN_ASOBJECT(old_inst_var_names) );
    
    if ( CHN_size( CHN_ASOBJECT(variable_array) ) < old_size
         || CHNCollection_equals( temp0 = CHNCollection_first_take( CHN_ASCOLLECTION(variable_array), old_size ),
                                  temp1 = CHNCollection_first_take( CHN_ASCOLLECTION(old_inst_var_names), old_size ) ) )
        changed = TRUE;
    else
        changed = FALSE;
    CHN_release( CHN_ASOBJECT(temp0) );
    CHN_release( CHN_ASOBJECT(temp1) );

    struct temp_any_satisfy_context0 context;
    context.other = old_inst_var_names;
    if ( CHNCollection_anySatisfy( CHN_ASCOLLECTION(variable_array),
                                   &context,
                                   __setinst_var_names_any_satisfy0 ) )
        removed = TRUE;
    else
        removed = FALSE;

    context.other = variable_array;
    if ( CHNCollection_anySatisfy( CHN_ASCOLLECTION(old_inst_var_names),
                                   &context,
                                   __setinst_var_names_any_satisfy1 ) )
        added = TRUE;
    else
        added = FALSE;

    CHN_release( variable_array );
    CHN_release( old_inst_var_names );

    if ( !(changed | removed | added) ) return self;
    if ( changed | removed ) CHNBihavior_compileAll( self );
    CHNBihavior_compileAllSubclasses( self );

    return self;
}


struct temp_simple_context0 {
    id receiver;
};


static id __parse_var_str_collect(void* pcontext, id each)
{
    CHNString_ref each_text = CHN_ASSTRING(each);

    return CHN_ASOBJECT(CHNString_asSymbol( each_text ));
}


CHN_EXPORT CHNCollection_ref CHNBihavior_parseInstanceVariableString(CHNBihavior_ref self, CHNString_ref variable_string)
{
    CHNCollection_ref variable_array = CHNBihavior_parseVariableString( self, variable_string );
    CHNCollection_ref retval;
    struct temp_simple_context0 context;

    retval = CHNCollection_collect( variable_array,
                                    &context,
                                    __parse_var_str_collect );

    CHN_release( CHN_ASOBJECT(variable_array) );

    return retval;
}


CHN_EXPORT CHNCollection_ref CHNBihavior_parseVariableString(CHNBihavior_ref self, CHNString_ref a_string)
{
    CHNCollection_ref temp = CHNString_subStrings( a_string );
    CHNArray_ref tokens = CHNCollection_asArray( temp );
    CHNIterator_ref it = CHNCollection_get_iterator( tokens );

    CHN_release( CHN_ASOBJECT(temp) );

    for ( ; CHNIterator_finished( it ); CHNIterator_next( it ) ) {
        id token = CHNIterator_current( it );

        CHNBihavior_validateIdentifier( self, token );
    }
    CHN_release( CHN_ASOBJECT(it) );
    CHN_release( CHN_ASOBJECT(tokens) );

    return tokens;
}


static id __method_dict_collect0(void* pcontext, id each)
{
    struct temp_simple_context0* context = (struct temp_simple_context0 *)pcontext;
    CHNCompiledMethod_ref temp_method = CHN_ASCOMPILED_METHOD(each);

    return CHNCompiledMethod_withNewMethodClass( temp_method, context->receiver );
}


CHN_EXPORT id CHNBihavior_methodDictionary(CHNBihavior_ref self, CHNDictionary_ref a_dictionary)
{
    CHNDictionary_ref new_dictionary;

    if ( !CHN_isNil( CHN_ASOBJECT(a_dictionary) ) ) {
        struct temp_simple_context0 context;

        new_dictionary = CHNDictionary_collect( a_dictionary,
                                                &context,
                                                __method_dict_collect0 );
        CHNDictionary_become( a_dictionary, new_dictionary );
    }
    CHNBihavior_flushCache();
    chn_var_named_put( self, "methodDictionary", a_dictionary );

    return self;
}


CHN_EXPORT id CHNBihavior_addSelector_withMethod(CHNBihavior_ref self, CHNSymbol_ref selector, CHNCompiledMethod_ref compiled_method)
{
    if ( CHN_isNil( CHN_ASOBJECT(self->method_dictionary) ) )
        self->method_dictionary = CHNDictionary_new();

    return CHNDirectionary_at_put( self->method_dictionary,
                                   selector,
                                   CHNCompiledMethod_withNewMethodClass_selector( self,
                                                                                  selector ) );
}


struct tmp_remove_selector_context0 {
    id receiver;
    CHNSymbol_ref selector;
};



static id __remove_selector0(void* pcontext)
{
    struct tmp_remove_selector_context0* context = (struct tmp_remove_selector_context0 *)pcontext;

    return CHNNotFoundError_signalOn_what( context->selector, _S("method") );
}


CHN_EXPORT id CHNBihavior_removeSelector(CHNBihavior_ref self, CHNSymbol_ref selector)
{
    return CHNBihavior_removeSelector_ifAbsent( self,
                                                selector,
                                                __remove_selector0 );
}


static id __remove_selector_ifAbsent0(void* pcontext)
{
    struct tmp_remove_selector_context0* context = (struct tmp_remove_selector_context0 *)pcontext;

    CHN_error( context->receiver, _S("huh?!?") );

    return nil;
}


CHN_EXPORT id CHNBihavior_removeSelector_ifAbsent(CHNBihavior_ref self, CHNSymbol_ref selector, chn_if_abesent_callback a_block)
{
    CHNDictionary_ref self_method_dictionary = chn_var_named( self, "methodDictionary" );
    
    struct tmp_remove_selector_context0 context;
    context.receiver = self;
    context.selector = selector;

    if ( CHN_isNil( CHN_ASOBJECT(self_method_dictionary) ) )
        return INVOKE_CALLBACK1(a_block, &context);
    if ( !CHNDictionary_includesKey( self_method_dictionary, selector ) )
        return INVOKE_CALLBACK1(a_block, &context);

    return CHNDictionary_removeKey( self_method_dictionary,
                                    selector,
                                    __remove_selector_ifAbsent0 );
}


static id __formatted_source_string_at0(void* pcontext)
{
    return _S(" *** SOURCE CODE NOT AVAILABLE *** ");
}


CHN_EXPORT id CHNBihavior_formattedSourceStringAt(CHNBihavior_ref self, CHNSymbol_ref selector)
{
    return CHNBihavior_formattedSourceStringAt_ifAbsent( self,
                                                         selector,
                                                         __formatted_source_string_at0 );
}


CHN_EXPORT id CHNBihavior_formattedSourceStringAt_ifAbsent(CHNBihavior_ref self, CHNSymbol_ref selector, chn_if_abesent_callback a_block)
{
    return CHN_notYetImplemented( CHN_ASOBJECT(self) );
}


CHN_EXPORT id CHNBihavior_compile(CHNBihavior_ref self, id code)
{
    if ( CHN_isKindOf( code, CHNWriteStream ) )
        return CHNBihavior_primCompile( self, CHNStream_get_readStream( CHN_ASREAD_STREAM(code) ) );
    if ( CHN_isKindOf( code, CHNStream ) )
        return CHNBihavior_primCompile( self, CHN_ASSTREAM(code) );

    return CHNBihavior_primCompile( self, CHN_asString( code ) );
}


CHN_EXPORT id CHNBihavior_compile_ifError(CHNBihavior_ref self, id code, chn_if_error_callback a_block)
{
    if ( CHN_isKindOf( code, CHNWriteStream ) )
        return CHNBihavior_primCompile_ifError( self, CHNStream_get_readStream( CHN_ASREAD_STREAM(code) ), a_block );
    if ( CHN_isKindOf( code, CHNStream ) )
        return CHNBihavior_primCompile_ifError( self, CHN_ASSTREAM(code), a_block );

    return CHNBihavior_primCompile_ifError( self, CHN_asString( code ), a_block );
}


CHN_EXPORT id CHNBihavior_compile_notifying(CHNBihavior_ref self, id code, id requestor)
{
    id method = CHNBihavior_compile( self, code );

    if ( CHN_isNil( method ) )
        return CHN_error( method, _S("compilation failed") );

    return method;
}


static id __compile_all_subclasses0(void* pcontext, CHNBihavior_ref subclass)
{
    return CHNBihavior_compileAll( subclass );
}


CHN_EXPORT id CHNBihavior_compileAllSubclasses(CHNBihavior_ref self)
{
    return CHNBihavior_allSubclassesDo( self, __compile_all_subclasses0 );
}


CHN_EXPORT CHNBoolean CHNBihavior_inheritsFrom(CHNBihavior_ref self, CHNBihavior_ref a_class)
{
    CHNBihavior_ref super_class;

    if ( CHN_isNil( CHN_ASOBJECT(a_class) ) )
        return TRUE;

    super_class = self;
    super_class = CHN_get_superclass( CHN_ASOBJECT(super_class) );
    while ( !CHN_isNil( CHN_ASOBJECT(super_class) ) ) {
        if ( CHN_equals( CHN_ASOBJECT(super_class), a_class ) )
            return TRUE;
        super_class = CHN_get_superclass( CHN_ASOBJECT(super_class) );
    }
    return FALSE;
}


CHN_EXPORT CHNSymbol_ref CHNBihavior_get_shape(CHNBihavior_ref self)
{
    if ( !CHNBihavior_isVariable( self ) )
        return nil;

    CHNCollection_ref self_shapes = CHNBihavior_get_shapes( self );

    return CHNCollection_at( self_shapes, (self->instance_spec & 15) + 1 );
}


CHN_EXPORT id CHNBihavior_allSubclassesDo(CHNBihavior_ref self, chn_doing_callback a_block)
{
    if ( CHN_isNil( CHN_ASOBJECT(self->sub_classes) ) )
        return self;

    CHNIterator_ref it = CHNCollection_get_iterator( CHN_ASCOLLECTION(self->sub_classes) );
    for ( ; CHNIterator_finished( it ); CHNIterator_next( it ) ) {
        CHNBihavior_ref klass = CHN_ASBIHAVIOR(CHNIterator_current( it ));

        INVOKE_CALLBACK2(a_block, NULL, CHN_ASOBJECT(klass));
        CHNBihavior_allSubclassesDo( klass, a_block );
    }
    CHN_release( CHN_ASOBJECT(it) );

    return self;
}


CHN_EXPORT id CHNBihavior_allSuperclassesDo(CHNBihavior_ref self, chn_doing_callback a_block)
{
    CHNBihavior_ref klass = self;
    CHNBihavior_ref super_class;

    do {
        super_class = CHN_get_superclass( CHN_ASOBJECT(klass) );
        klass = super_class;

        if ( CHN_isNil( CHN_ASOBJECT(super_class) ) )
            break;
    } while ( INVOKE_CALLBACK2(a_block, NULL, CHN_ASOBJECT(super_class)) );

    return self;
}


CHN_EXPORT id CHNBihavior_withAllSubclassesDo(CHNBihavior_ref self, chn_doing_callback a_block)
{
    INVOKE_CALLBACK2(a_block, NULL, CHN_ASOBJECT(self));

    return CHNBihavior_allSubclassesDo( self, a_block );
}


CHN_EXPORT id CHNBihavior_withAllSuperclassesDo(CHNBihavior_ref self, chn_doing_callback a_block)
{
    CHNBihavior_ref klass = self;

    while ( CHN_isNil( CHN_ASOBJECT(klass) ) ) {
        INVOKE_CALLBACK2(a_block, NULL, CHN_ASOBJECT(klass));
        klass = CHN_get_superclass( CHN_ASOBJECT(klass) );
    }
    return self;
}
