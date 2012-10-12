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
#include "coreHezelnut/classes/CHNSet.h"
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
    CHNClass_ref              prototype;

    CHNClass_ref              super_class;
    CHNSet_ref                method_dictionary;
    unsigned int              instance_spec;
    CHNOrderedCollection_ref  sub_classes;
    CHNOrderedCollection_ref  instance_variables;
};


CHN_EXPORT id CHNBihavior_addInstVarName(CHNBihavior_ref self, CHNString_ref a_string)
{
    CHNCollection_ref           new_instance_variables;
    CHNBoolean                  duplicated;
    CHNSymbol_ref               symbol;

    CHNOrderedCollection_ref    instance_variables;
    CHNCollection_ref           temp_inst_names;

    instance_variables = self->instance_variables;

    CHNBihavior_validateIdentifier( self, a_string );

    symbol             = CHNString_asSymbol( a_string );

    if ( CHNObject_isNil( CHN_ASOBJECT(symbol) ) )
        new_instance_variables = CHN_ASCOLLECTION(CHN_ARRAY_LITERAL1(symbol));
    else
        new_instance_variables = CHN_ASCOLLECTION(CHNCollection_copyWith( CHN_ASCOLLECTION(instance_variables),
                                                                          CHN_ASOBJECT(symbol) ));

    CHNSymbol_release( symbol );

    temp_inst_names  = CHN_ASCOLLECTION(CHNClass_allInstVarNames( CHNObject_get_superclass( self ) ));
    duplicated       = CHNCollection_includes( temp_inst_names );

    CHNCollection_release( temp_inst_names );

    CHNBihavior_updateInstanceVars( CHN_ASOBJECT(self),
                                    new_instance_variables,
                                    CHNBihavior_get_shape(self) );
    CHNCollection_release( new_instance_variables );

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

    return CHNObject_equals( each, CHN_ASOBJECT(context->symbol) );
}


CHN_EXPORT id CHNBihavior_removeInstVarName(CHNBihavior_ref self, CHNString_ref a_string)
{
    struct temp_find_last_context0    context;

    int                               index;

    CHNCollection_ref                 new_instance_variables;
    CHNSymbol_ref                     symbol;

    CHNCollection_ref                 instance_variables;


    symbol             = CHNString_asSymbol( a_string );
    instance_variables = CHN_ASCOLLECTION(self->instance_variables);
    context.symbol     = symbol;

    index              = CHNOrderedCollection_findLast( instance_variables,
                                                        __remove_inst_var_name_find_last,
                                                        &context );

    if ( index == 0 ) {
        CHNSymbol_release( symbol );
        /*
          symbol は CHNNotFoundError_signalOn_what 内で release されると思う。
         */
        return CHNNotFoundError_signalOn_what( CHN_ASOBJECT(symbol), _S("instance variable") );
    }
    CHNSymbol_release( symbol );

    new_instance_variables = CHN_ASCOLLECTION(CHNCollection_copyReplaceFrom_to_with( CHN_ASCOLLECTION(instance_variables),
                                                                                     index,
                                                                                     index,
                                                                                     CHN_ARRAY_LITERAL_EMPTY ));
    CHNBihavior_updateInstanceVars_shape( self,
                                          new_instance_variables,
                                          CHNBihavior_get_shape( self ) );

    CHNCollection_release( new_instance_variables );

    CHNBihavior_compileAll( self );
    CHNBihavior_compileAllSubclasses( self );
}


struct temp_any_satisfy_context0 {
    id                   receiver;  /*! 関数の第一引数が渡されます。 */
    CHNCollection_ref    other;
};


static CHNBoolean __setinst_var_names_any_satisfy0(void* pcontext, id each)
{
    struct temp_any_satisfy_context0*  context;
    CHNCollection_ref                  variable_array;

    context          = (struct temp_any_satisfy_context0 *)pcontext;
    variable_array   = CHN_ASCOLLECTION(context->other);

    return !CHNCollection_includes( variable_array, each );
}


static CHNBoolean __setinst_var_names_any_satisfy1(void* pcontext, id each)
{
    struct temp_any_satisfy_context0*  context;
    CHNCollection_ref                  variable_array;

    context          = (struct temp_any_satisfy_context0 *)pcontext;
    variable_array   = CHN_ASCOLLECTION(context->other);

    return !CHNCollection_includes( variable_array, each );
}


CHN_EXPORT id CHNBihavior_set_instanceVariableNames(CHNBihavior_ref self, CHNCollection_ref inst_var_names)
{
    struct temp_any_satisfy_context0  context;

    CHNCollection_ref                 variable_array;
    CHNCollection_ref                 old_inst_var_names;

    CHNBoolean                        changed, removed, added;
    CHNCollection_ref                 temp0, temp1;

    int                               old_size;

    variable_array         = CHNBihavior_parseInstanceVariableString( self, CHN_ASSTRING(inst_var_names) );
    old_inst_var_names     = CHNBihavior_allInstVarNames( self );

    variable_array         = CHNSequenceableCollection_concat( CHNBihavior_subclassInstVarNames( self ), variable_array );

    if ( CHNObject_equals( CHN_ASOBJECT(variable_array), CHN_ASOBJECT(old_inst_var_names) ) ) {
        CHNCollection_release( variable_array );
        CHNCollection_release( old_inst_var_names );

        return self;
    }
    CHNBihavior_updateInstanceVars_shape( self,
                                          variable_array,
                                          CHNBehabior_get_shape( self ) );

    old_size = CHN_size( CHN_ASOBJECT(old_inst_var_names) );
    
    if ( CHN_size( CHN_ASOBJECT(variable_array) ) < old_size
         || CHNCollection_equals( temp0 = CHNCollection_firstTake( CHN_ASCOLLECTION(variable_array), old_size ),
                                  temp1 = CHNCollection_firstTake( CHN_ASCOLLECTION(old_inst_var_names), old_size ) ) )
        changed = TRUE;
    else
        changed = FALSE;
    CHNCollection_release( temp0 );
    CHNCollection_release(temp1 );

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

    CHNCollection_release( variable_array );
    CHNCollection_release( old_inst_var_names );

    if ( !(changed | removed | added) ) return self;
    if ( changed | removed ) CHNBihavior_compileAll( self );
    CHNBihavior_compileAllSubclasses( self );

    return self;
}


struct temp_simple_context0 {
    id       receiver;
};


static id __parse_var_str_collect(void* pcontext, id each)
{
    CHNString_ref each_text = CHN_ASSTRING(each);

    return CHN_ASOBJECT(CHNString_asSymbol( each_text ));
}


CHN_EXPORT CHNCollection_ref CHNBihavior_parseInstanceVariableString(CHNBihavior_ref self, CHNString_ref variable_string)
{
    CHNCollection_ref             variable_array;
    CHNCollection_ref             retval;

    struct temp_simple_context0   context;

    variable_array = CHNBihavior_parseVariableString( self, variable_string );
    retval         = CHNCollection_collect( variable_array,
                                            &context,
                                            __parse_var_str_collect );

    CHNCollection_release( variable_array );

    return retval;
}


CHN_EXPORT CHNCollection_ref CHNBihavior_parseVariableString(CHNBihavior_ref self, CHNString_ref a_string)
{
    CHNCollection_ref  temp;
    CHNArray_ref       tokens;

    CHNIterator_ref    it;
    id                 token;

    temp    = CHNString_subStrings( a_string );
    tokens  = CHNCollection_asArray( temp );
    it      = CHNCollection_get_iterator( tokens );

    CHNCollection_release( temp );

    for ( ; CHNIterator_finished( it ); CHNIterator_next( it ) ) {
        token = CHNIterator_current( it );

        CHNBihavior_validateIdentifier( self, token );
    }
    CHNIterator_release( it );
    CHNArray_release( tokens );

    return tokens;
}


static id __method_dict_collect0(void* pcontext, id each)
{
    struct temp_simple_context0* context = (struct temp_simple_context0 *)pcontext;
    CHNCompiledMethod_ref temp_method = CHN_ASCOMPILED_METHOD(each);

    return CHNCompiledMethod_withNewMethodClass( temp_method, context->receiver );
}


CHN_EXPORT id CHNBihavior_set_methodDictionary(CHNBihavior_ref self, CHNSet_ref a_dictionary)
{
    struct temp_simple_context0 context;

    CHNSet_ref new_dictionary;

    if ( !CHNObject_isNil( CHN_ASOBJECT(a_dictionary) ) ) {

        new_dictionary = CHNSet_collect( a_dictionary,
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
    if ( CHNObject_isNil( CHN_ASOBJECT(self->method_dictionary) ) )
        self->method_dictionary = CHNDictionary_new();

    return CHNDirectionary_at_put( self->method_dictionary,
                                   selector,
                                   CHNCompiledMethod_withNewMethodClass_selector( self,
                                                                                  selector ) );
}


struct tmp_remove_selector_context0 {
    id                receiver;
    CHNSymbol_ref     selector;
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

    CHNObject_error( context->receiver, _S("huh?!?") );

    return nil;
}


CHN_EXPORT id CHNBihavior_removeSelector_ifAbsent(CHNBihavior_ref self, CHNSymbol_ref selector, chn_if_abesent_callback a_block)
{
    struct tmp_remove_selector_context0 context;

    CHNSet_ref self_method_dictionary;

    self_method_dictionary = self->method_dictionary;

    context.receiver = self;
    context.selector = selector;

    if ( CHNObject_isNil( CHN_ASOBJECT(self_method_dictionary) ) )
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
    if ( CHNObject_isKindOf( code, CHNWriteStream ) )
        return CHNBihavior_primCompile( self, CHNStream_get_readStream( CHN_ASREAD_STREAM(code) ) );
    if ( CHNObject_isKindOf( code, CHNStream ) )
        return CHNBihavior_primCompile( self, CHN_ASSTREAM(code) );

    return CHNBihavior_primCompile( self, CHN_asString( code ) );
}


CHN_EXPORT id CHNBihavior_compile_ifError(CHNBihavior_ref self, id code, chn_if_error_callback a_block)
{
    if ( CHNObject_isKindOf( code, CHNWriteStream ) )
        return CHNBihavior_primCompile_ifError( self, CHNStream_get_readStream( CHN_ASREAD_STREAM(code) ), a_block );
    if ( CHNObject_isKindOf( code, CHNStream ) )
        return CHNBihavior_primCompile_ifError( self, CHN_ASSTREAM(code), a_block );

    return CHNBihavior_primCompile_ifError( self, CHN_asString( code ), a_block );
}


CHN_EXPORT id CHNBihavior_compile_notifying(CHNBihavior_ref self, id code, id requestor)
{
    id method;

    method = CHNBihavior_compile( self, code );

    if ( CHNObject_isNil( method ) )
        return CHN_error( method, _S("compilation failed") );

    return method;
}


static id __compile_all_subclasses0(void* pcontext, CHNBihavior_ref subclass)
{
    return CHNBihavior_compileAll( subclass );
}


CHN_EXPORT id CHNBihavior_compileAllSubclasses(CHNBihavior_ref self)
{
    return CHNBihavior_allSubclassesDo( self, NULL, __compile_all_subclasses0 );
}


CHN_EXPORT CHNBoolean CHNBihavior_inheritsFrom(CHNBihavior_ref self, CHNBihavior_ref a_class)
{
    CHNBihavior_ref super_class;

    if ( CHNObject_isNil( CHN_ASOBJECT(a_class) ) )
        return TRUE;

    super_class = self;
    super_class = CHNObject_get_superclass( CHN_ASOBJECT(super_class) );
    while ( !CHNObject_isNil( CHN_ASOBJECT(super_class) ) ) {

        if ( CHNObject_equals( CHN_ASOBJECT(super_class), a_class ) )
            return TRUE;

        super_class = CHNObject_get_superclass( CHN_ASOBJECT(super_class) );
    }
    return FALSE;
}


CHN_EXPORT CHNSymbol_ref CHNBihavior_get_shape(CHNBihavior_ref self)
{
    CHNCollection_ref self_shapes;

    if ( !CHNBihavior_isVariable( self ) )
        return nil;

    self_shapes = CHNBihavior_get_shapes( self );

    return CHNCollection_at( self_shapes, (self->instance_spec & 15) + 1 );
}


CHN_EXPORT CHNClass_ref CHNBihavior_set_superclass(CHNBihavior_ref self, CHNBihavior_ref a_class)
{
    CHNClass_ref prev_super_class = self->super_class;

    self->super_class = a_class;

    if ( CHNObject_isNil( CHN_ASOBJECT(a_class) ) )
        self->instance_spec = 0;
    else
        self->instance_spec = a_class->instance_spec;

    return prev_super_class;
}


CHN_EXPORT id CHNBihavior_addSubclass(CHNBihavior_ref self, CHNClass_ref a_class)
{
    /*
      Smalltalk のソースでは Array だけど、OrderedCollection にしてる。
     */
    if ( CHNObject_isNil( CHN_ASOBJECT(self->sub_classes) ) )
        self->sub_classes = CHNOrderedCollection_new();

    CHNOrderedCollection_addLast( self->sub_classes, a_class );

    return CHN_ASOBJECT(self);
}


CHN_EXPORT id CHNBihavior_removeSubclass(CHNBihavior_ref self, CHNClass_ref a_class)
{
    CHNOrderedCollection_remove( self->sub_classes, a_class );

    return CHN_ASOBJECT(self);
}


CHN_EXPORT CHNSet_ref CHNBihavior_get_selectors(CHNBihavior_ref self)
{
    if ( CHNObject_isNil( CHN_ASOBJECT(self->method_dictionary) ) )
        return CHNSet_new();
    else
        return CHNSet_get_keys( self->method_dictionary );
        
}


struct tmp_get_all_selectors_context0 {
    id receiver;
    id other;
};


static id __all_selectors_superclasses_do(void* pcontext, id each)
{
    struct tmp_get_all_selectors_context0*    context;
    CHNSet_ref                                a_set;
    CHNBihavior_ref                           klass;

    context  = (struct tmp_get_all_selectors_context0 *)context;
    a_set    = CHN_ASSET(context->other);
    klass    = CHN_ASBIHAVIOR(each);

    CHNSet_add( a_set, CHNBihavior_get_selectors( klass ) );

    return nil;
}


CHN_EXPORT CHNSet_ref CHNBihavior_get_allSelectors(CHNBihavior_ref self)
{
    struct tmp_get_all_selectors_context0   context;

    CHNSet_ref                              a_result_set;

    a_result_set = CHNBihavior_get_selectors( self );

    context.receiver = self;
    context.other = CHN_ASOBJECT(a_result_set);

    CHNBihavior_allSuperclassesDo( self, a_result_set, __all_selectors_superclasses_do );

    return a_result_set;
}


CHN_EXPORT id CHNBihavior_allSubclassesDo(CHNBihavior_ref self, void* pcontext, chn_doing_callback a_block)
{
    CHNIterator_ref  it;
    CHNBihavior_ref  klass;

    if ( CHNObject_isNil( CHN_ASOBJECT(self->sub_classes) ) )
        return self;

    it = CHNCollection_get_iterator( CHN_ASCOLLECTION(self->sub_classes) );
    for ( ; CHNIterator_finished( it ); CHNIterator_next( it ) ) {
        klass = CHN_ASBIHAVIOR(CHNIterator_current( it ));

        INVOKE_CALLBACK2(a_block, pcontext, CHN_ASOBJECT(klass));
        CHNBihavior_allSubclassesDo( klass, pcontext, a_block );
    }
    CHNIterator_release( it );

    return self;
}


CHN_EXPORT id CHNBihavior_allSuperclassesDo(CHNBihavior_ref self, void* pcontext, chn_doing_callback a_block)
{
    CHNBihavior_ref klass = self;
    CHNBihavior_ref super_class;

    do {
        super_class = CHNObject_get_superclass( CHN_ASOBJECT(klass) );
        klass = super_class;

        if ( CHNObject_isNil( CHN_ASOBJECT(super_class) ) )
            break;
    } while ( INVOKE_CALLBACK2(a_block, pcontext, CHN_ASOBJECT(super_class)) );

    return self;
}


CHN_EXPORT id CHNBihavior_withAllSubclassesDo(CHNBihavior_ref self, void* pcontext, chn_doing_callback a_block)
{
    INVOKE_CALLBACK2(a_block, pcontext, CHN_ASOBJECT(self));

    return CHNBihavior_allSubclassesDo( self, pcontext, a_block );
}


CHN_EXPORT id CHNBihavior_withAllSuperclassesDo(CHNBihavior_ref self, void* pcontext, chn_doing_callback a_block)
{
    CHNBihavior_ref klass = self;

    while ( CHNObject_isNil( CHN_ASOBJECT(klass) ) ) {
        INVOKE_CALLBACK2(a_block, pcontext, CHN_ASOBJECT(klass));
        klass = CHNObject_get_superclass( CHN_ASOBJECT(klass) );
    }
    return self;
}
