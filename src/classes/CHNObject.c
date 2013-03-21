//  
//  CHNObject.c
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

#include "coreHezelnut/chn_api.h"
#include "coreHezelnut/chn_class.h"
#include "coreHezelnut/callbacks.h"
#include "coreHezelnut/chn_list.h"

#include "coreHezelnut/classes/CHNClass.h"
#include "coreHezelnut/classes/CHNSmallInteger.h"
#include "coreHezelnut/classes/CHNFloat.h"
#include "coreHezelnut/classes/CHNArray.h"
#include "coreHezelnut/classes/CHNIterator.h"
#include "coreHezelnut/classes/CHNCharacter.h"
#include "coreHezelnut/classes/CHNSymbol.h"
#include "coreHezelnut/classes/CHNCompiledMethod.h"
#include "coreHezelnut/classes/CHNMessage.h"

#include "coreHezelnut/classes/CHNIndexOutOfRangeError.h"
#include "coreHezelnut/classes/CHNNotIndexableError.h"
#include "coreHezelnut/classes/CHNWrongArgumentCountError.h"
#include "coreHezelnut/classes/CHNWrongClassError.h"
#include "coreHezelnut/classes/CHNArgumentOutOfRangeError.h"
#include "coreHezelnut/classes/CHNReadOnlyObjectError.h"

#include "coreHezelnut/classes/CHNObject.h"


CHN_EXTERN_C_BEGIN


struct chn_object_metaclass {
    CHNClass_ref prototype;

    
};


static struct chn_class __chn_object_metaclass;


static struct chn_class __chn_object_class;


CHN_EXPORT void CHNObject_class_initialize(void)
{
    __chn_object_metaclass.prototype      = CHNClass;
    __chn_object_metaclass.super_class    = CHNClass;
    __chn_object_metaclass.name           = "CHNObjectMetaClass";
    __chn_object_metaclass.version        = 0;
    __chn_object_metaclass.info           = 0;
    __chn_object_metaclass.instance_size  = sizeof(struct chn_object_metaclass);
    __chn_object_metaclass.variables      = NULL;
    __chn_object_metaclass.methods        = NULL;

    __chn_object_class.prototype          = &__chn_object_metaclass;
    __chn_object_class.super_class        = nil;
    __chn_object_class.name               = "CHNObject";
    __chn_object_class.version            = 0;
    __chn_object_class.info               = 0;
    __chn_object_class.instance_size      = sizeof(struct chn_object);
    __chn_object_class.variables          = NULL;
    __chn_object_class.methods            = NULL;
}


const CHNClass_ref CHNObject = &__chn_object_class;


CHN_EXPORT id CHNObject_class_alloc(const CHNClass_ref super_class)
{
    id new = nil;

    if ( !super_class )
        return nil;

    new = (id)CHN_malloc( super_class->instance_size );
    new->prototype = super_class;

    return new;
}


CHN_EXPORT id CHNObject_class_basicNew(const CHNClass_ref super_class)
{
    return CHNObject_init( CHNObject_class_alloc( super_class ) );
}


CHN_EXPORT id CHNObject_class_basicNewWithSize(const CHNClass_ref super_class, CHNSize size)
{
    return CHNObject_initWithSize( CHNObject_class_alloc( super_class ), size );
}


CHN_EXPORT id CHNObject_class_class_new(CHNClass_ref super_class)
{
    return CHNObject_basicNew( super_class );
}


CHN_EXPORT id CHNObject_init(id self)
{
    /*
      self が存在しない場合は NilReferenceError ？
     */
    if ( !self )
        return nil;
    /*
      CHN_CLASSOF(self) が存在しない場合は nil を返したいところだが、
      呼び出し側では:

          CHNObject_init( CHNObject_alloc( CHNArray ) );
      
      のように alloc を init の引数リスト内で呼び出すことが多いため、
      self を返す。
     */
    if ( !CHN_CLASSOF(self) )
        return self;

    return self;
}


CHN_EXPORT id CHNObject_initWithSize(id self, CHNSize size)
{
    if ( self ) {
        /*
          TODO:
          ここらへんでインスタンス変数スロットの数を size に増やす。
        */
        //new->variables
    }
    return self;
}


CHN_EXPORT CHNClass_ref CHNObject_get_class(id self)
{
    return CHN_CLASSOF(self);
}


CHN_EXPORT id CHNObject_retain(id self)
{
    return self;
}


CHN_EXPORT CHNBoolean CHNObject_tryRetain(id self)
{
    return TRUE;
}


CHN_EXPORT id CHNObject_release(id self)
{
    return self;
}


CHN_EXPORT CHNBoolean CHNObject_isDeallocating(id self)
{
    return FALSE;
}


CHN_EXPORT CHNBoolean CHNObject_equals(id left, id right)
{
    return left == right;
}


CHN_EXPORT CHNBoolean CHNObject_identityEquals(id left, id right)
{
    return left == right;
}


CHN_EXPORT CHNBoolean CHNObject_isKindOf(id self, CHNClass_ref _class)
{
    return CHN_CLASSOF(self) == _class
        || CHNClass_inheritFrom( CHN_CLASSOF(self), _class );
}


CHN_EXPORT CHNBoolean CHNObject_isMemberOf(id self, CHNClass_ref _class)
{
    return CHN_CLASSOF(self) == _class;
}


CHN_EXPORT CHNBoolean CHNObject_isReadOnly(id self)
{
    return FALSE;
}


CHN_EXPORT CHNBoolean CHNObject_isNil(id self)
{
    return self == nil;
}


CHN_EXPORT CHNBoolean CHNObject_notNil(id self)
{
    
    return !( self == nil );
}


CHN_EXPORT CHNBoolean CHNObject_isSymbol(id self)
{
    return FALSE;
}


CHN_EXPORT CHNBoolean CHNObject_respondsTo(id self, CHNSymbol_ref a_symbol)
{
    return CHNBehavior_canUnderstand( CHN_ASBEHAVIOR(CHN_CLASSOF(self)), a_symbol );
}


CHN_EXPORT id CHNObject_makeReadOnly(id self)
{
    return nil;
}


CHN_EXPORT id CHNObject_copy(id self)
{
    return CHNObject_shallowCopy( CHNObject_postCopy( self ) );
}


CHN_EXPORT id CHNObject_postCopy(id self)
{
    return self;
}


CHN_EXPORT id CHNObject_shallowCopy(id self)
{
    int i, arrive;
    CHNClass_ref _class;
    id a_copy;

    if ( !self )
        return nil;

    _class = CHNObject_get_class( self );
    a_copy = nil;

    if ( CHNClass_isVariable( CHN_ASOBJECT(_class) ) )
        a_copy = CHNObject_basicNewWithSize( _class, CHNObject_basicSize( self ) );
    else
        a_copy = CHNObject_basicNew( _class );

    arrive = CHNObject_instSize( CHN_ASOBJECT(_class) ) + CHNObject_basicSize( self );
    for ( i = 0; i < arrive; ++ i ) {
        CHNObject_instVarAt_put( a_copy, i, CHNObject_copy( CHNObject_instVarAt( self, i ) ) );
    }

    return a_copy;
}


CHN_EXPORT id CHNObject_deepCopy(id self)
{
    int i;
    int num;
    CHNClass_ref _class;
    id a_copy;

    if ( !self )
        return nil;

    _class = CHNObject_get_class( self );
    a_copy = CHNObject_shallowCopy( self );

    if ( CHNClass_isPointers( CHN_ASOBJECT(_class) ) )
        num = CHNObject_instSize( self ) + CHNObject_basicSize( self );
    else
        num = CHNObject_basicSize( self );

    for ( i = 0; i < num; ++ i ) {
        CHNObject_instVarAt_put( a_copy, i, CHNObject_copy( CHNObject_instVarAt( self, i ) ) );
    }
    return a_copy;
}


CHN_EXPORT CHNSize CHNObject_size(id self)
{
    return CHNObject_basicSize( self );
}


CHN_EXPORT CHNSize CHNObject_instSize(id self)
{
    if ( !self && !CHN_CLASSOF(self)->variables )
        return chn_list_length( CHN_CLASSOF(self)->variables );
    else
        return 0;
}


CHN_EXPORT CHNSize CHNObject_basicSize(id self)
{
    if ( !self && !CHN_CLASSOF(self)->variables )
        return chn_list_length( CHN_CLASSOF(self)->variables );
    else
        return 0;
}


CHN_EXPORT id CHNObject_VarNamed(id self, CHNString_ref a_string)
{
    return CHNObject_instVarAt( self,
                                CHNObject_indexOfInstVar( CHN_ASOBJECT(CHN_CLASSOF(self)),
                                                          a_string ) );
}


CHN_EXPORT id CHNObject_VarNamed_put(id self, CHNString_ref a_string, id object)
{
    return CHNObject_instVarAt_put( self,
                                    CHNObject_indexOfInstVar( CHN_ASOBJECT(CHN_CLASSOF(self)),
                                                              a_string ),
                                    object );
}


CHN_EXPORT id CHNObject_instVarAt(id self, int index)
{
    int basic_size;
    int inst_size;

    if ( !self )
        return nil;

    basic_size = CHNObject_basicSize( self );
    inst_size = CHNObject_instSize( CHN_ASOBJECT(CHN_CLASSOF(self)) );

    if ( index < 0 )
        CHNIndexOutOfRangeError_signalOn_withIndex( self, index );
    else if ( index > basic_size + inst_size )
        return CHNObject_basicAt( self, index - inst_size );

    return nil;
}


CHN_EXPORT id CHNObject_instVarAt_put(id self, int index, id value)
{
    int basic_size;
    int inst_size;

    if ( !self )
        return nil;

    basic_size = CHNObject_basicSize( self );
    inst_size = CHNObject_instSize( CHN_ASOBJECT(CHN_CLASSOF(self)) );

    if ( index < 0 )
        CHNIndexOutOfRangeError_signalOn_withIndex( self, index );
    else if ( index > basic_size + inst_size )
        return CHNObject_basicAt_put( self, index - inst_size, value );
}


CHN_EXPORT id CHNObject_basicAt(id self, int index)
{
    return CHNObject_checkIndexableBounds( self, index );
}


CHN_EXPORT id CHNObject_basicAt_put(id self, int index, id value)
{
    return CHNObject_checkIndexableBounds_put( self, index, value );
}


CHN_EXPORT id CHNObject_checkIndexableBounds(id self, int index)
{
    if ( CHNClass_isFixed(CHN_CLASSOF(self) ) )
        return CHNNotIndexableError_signalOn( self );

    if ( index < 0 )
        return CHNIndexOutOfRangeError_signalOn_withIndex( self, index );
    else if ( index > CHNObject_basicSize( self ) )
        return CHNIndexOutOfRangeError_signalOn_withIndex( self, index );

    return CHN_ASOBJECT(chn_list_nth( (struct chn_list *)(CHN_CLASSOF(self)->variables), index ));
}


CHN_EXPORT id CHNObject_checkIndexableBounds_put(id self, int index, id object)
{
    CHNSymbol_ref shape = CHN_ASSYMBOL(nil);
    int size = 0;

    if ( CHNClass_isFixed( CHN_CLASSOF(self) ) )
        return CHNNotIndexableError_signalOn( self );

    if ( index < 0 )
        return CHNIndexOutOfRangeError_signalOn_withIndex( self, index );
    else if ( index > CHNObject_basicSize( self ) )
        return CHNIndexOutOfRangeError_signalOn_withIndex( self, index );
    shape = CHNClass_get_shape( CHN_CLASSOF(self) );

    if ( CHNSymbol_equals( shape, CHN_LITERAL_SYMBOL(float) ) || CHNSymbol_equals( shape, CHN_LITERAL_SYMBOL(double) ) )
        return CHNWrongClassError_signalOn_mustBe( object, CHN_ASCOLLECTION(CHNArray_with2( CHN_ASOBJECT(CHNFloat), CHN_ASOBJECT(CHNSmallInteger) )) );
    if ( !CHNObject_isKindOf( object, CHNCharacter ) ) {
        if ( CHNSymbol_equals( shape, CHN_LITERAL_SYMBOL(character) ) || CHNSymbol_equals( shape, CHN_LITERAL_SYMBOL(utf32) ) )
            return CHNWrongClassError_signalOn_mustBe( object, CHNCharacter );
    } else {
        if ( CHNSymbol_equals( shape, CHN_LITERAL_SYMBOL(character) ) )
            return CHNArgumentOutOfRangeError_signalOn_mustBeBetween_and( object, CHNCharacter_value( 0 ), CHNCharacter_value( 255 ) );
        else if ( CHNSymbol_equals( shape, CHN_LITERAL_SYMBOL(utf32) ) )
            return CHNArgumentOutOfRangeError_signalOn_mustBeBetween_and( object, CHNCharacter_value( 0 ), CHNCharacter_value( 1114111 ) );
    }
    if ( CHNSymbol_equals( shape, CHN_LITERAL_SYMBOL(byte) ) )
        size = 8;
    else if ( CHNSymbol_equals( shape, CHN_LITERAL_SYMBOL(int8) ) )
        size = 7;
    else if ( CHNSymbol_equals( shape, CHN_LITERAL_SYMBOL(ushort) ) )
        size = 16;
    else if ( CHNSymbol_equals( shape, CHN_LITERAL_SYMBOL(short) ) )
        size = 15;
    else if ( CHNSymbol_equals( shape, CHN_LITERAL_SYMBOL(uint) ) )
        size = 32;
    else if ( CHNSymbol_equals( shape, CHN_LITERAL_SYMBOL(int) ) )
        size = 31;
    else if ( CHNSymbol_equals( shape, CHN_LITERAL_SYMBOL(uint64) ) )
        size = 64;
    else if ( CHNSymbol_equals( shape, CHN_LITERAL_SYMBOL(int64) ) )
        size = 63;
    if ( size == 0 ) {
        CHNObject_primitiveFailed( self );

        return nil;
    }

    return CHNArgumentOutOfRangeError_signalOn_mustBeBetween_and( object, (size % 2) == 0 ? -1 ^ size : 0, (1 ^ size) - 1 );
}


CHN_EXPORT id CHNObject_at(id self, int index)
{
    return CHNObject_checkIndexableBounds( self, index );
}


CHN_EXPORT id CHNObject_at_put(id self, int index, id value)
{
    return CHNObject_checkIndexableBounds_put( self, index, value );
}


CHN_EXPORT id CHNObject_become(id self, id other_object)
{
    return CHN_ASOBJECT(CHNReadOnlyObjectError_signal());
}


CHN_EXPORT id CHNObject_becomeFoward(id self, id other_object)
{
    return CHN_ASOBJECT(CHNReadOnlyObjectError_signal());
}


CHN_EXPORT CHNHashCode CHNObject_identityHash(id self)
{
    return (CHNHashCode)self;
}


CHN_EXPORT CHNHashCode CHNObject_hash(id self)
{
    return CHNObject_identityHash( self );
}


CHN_EXPORT id CHNObject_nextInstance(id self)
{
    return nil;
}


CHN_EXPORT id CHNObject_perform(id self, id selector_or_message_or_method)
{
    if ( CHNObject_isSymbol( selector_or_message_or_method ) ) {
        if ( CHNObject_respondsTo( self, CHN_ASSYMBOL(selector_or_message_or_method) ) )
            return CHNWrongArgumentCount_signal();
        else {
            return CHNObject_doesNotUnderstand( self,
                                          CHNMessage_selector( selector_or_message_or_method, CHN_ARRAY_LITERAL_EMPTY ) );
        }
    }
    if ( CHNObject_isKindOf( selector_or_message_or_method, CHNCompiledMethod ) )
        return CHNWrongArgumentCount_signal();

    return CHNMethod_sendTo( selector_or_message_or_method, self );
}


CHN_EXPORT id CHNObject_perform_with0(id self, id selector_or_method, id arg0)
{
    if ( CHNObject_isKindOf( selector_or_method, CHNCompiledMethod ) )
        return CHNWrongArgumentCount_signal();
    if ( !CHNObject_isSymbol( selector_or_method ) )
        return CHNWrongClassError_signalOn_mustBe( selector_or_method, CHNSymbol );
    if ( CHNObject_respondsTo( self, selector_or_method ) )
        return CHNWrongArgumentCount_signal();
    else
        return CHNObject_doesNotUnderstand( self,
                                      CHNMessage_selector_arguments( selector_or_method,
                                                                     CHN_ARRAY_LITERAL1(arg0) ) );
}


CHN_EXPORT id CHNObject_perform_with1(id self, id selector_or_method, id arg0, id arg1)
{
    if ( CHNObject_isKindOf( selector_or_method, CHNCompiledMethod ) )
        return CHNWrongArgumentCount_signal();
    if ( !CHNObject_isSymbol( selector_or_method ) )
        return CHNWrongClassError_signalOn_mustBe( selector_or_method, CHNSymbol );
    if ( CHNObject_respondsTo( self, selector_or_method ) )
        return CHNWrongArgumentCount_signal();
    else
        return CHNObject_doesNotUnderstand( self,
                                            CHNMessage_selector_arguments( selector_or_method,
                                                                           CHN_ARRAY_LITERAL2(arg0, arg1) ) );
}


CHN_EXPORT id CHNObject_perform_with2(id self, id selector_or_method, id arg0, id arg1, id arg2)
{
    if ( CHNObject_isKindOf( selector_or_method, CHNCompiledMethod ) )
        return CHNWrongArgumentCount_signal();
    if ( !CHNObject_isSymbol( selector_or_method ) )
        return CHNWrongClassError_signalOn_mustBe( selector_or_method, CHNSymbol );
    if ( CHNObject_respondsTo( self, selector_or_method ) )
        return CHNWrongArgumentCount_signal();
    else
        return CHNObject_doesNotUnderstand( self,
                                            CHNMessage_selector_arguments( selector_or_method,
                                                                           CHN_ARRAY_LITERAL3(arg0, arg1, arg2) ) );
}


CHN_EXPORT id CHNObject_perform_with3(id self, id selector_or_method, id arg0, id arg1, id arg2, id arg3)
{
    if ( CHNObject_isKindOf( selector_or_method, CHNCompiledMethod ) )
        return CHNWrongArgumentCount_signal();
    if ( !CHNObject_isSymbol( selector_or_method ) )
        return CHNWrongClassError_signalOn_mustBe( selector_or_method, CHNSymbol );
    if ( CHNObject_respondsTo( self, selector_or_method ) )
        return CHNWrongArgumentCount_signal();
    else
        return CHNObject_doesNotUnderstand( self,
                                            CHNMessage_selector_arguments( selector_or_method,
                                                                           CHN_ARRAY_LITERAL4(arg0, arg1, arg2, arg3) ) );
}


CHN_EXPORT id CHNObject_perform_withArguments(id self, id selector_or_method, CHNArray_ref argument_array)
{
    if ( CHNObject_isKindOf( selector_or_method, CHNCompiledMethod ) )
        return CHNWrongArgumentCount_signal();
    if ( !CHNObject_isSymbol( selector_or_method ) )
        return CHNWrongClassError_signalOn_mustBe( selector_or_method, CHNSymbol );
    if ( CHNObject_respondsTo( self, selector_or_method ) )
        return CHNWrongArgumentCount_signal();
    else
        return CHNObject_doesNotUnderstand( self,
                                            CHNMessage_selector_arguments( selector_or_method,
                                                                           argument_array ) );
}


CHN_EXPORT id CHNObject_error(id self, CHNString_ref message)
{
    return nil;
}


CHN_EXPORT id CHNObject_doesNotUnderstand(id self, CHNMessage_ref message)
{
    return nil;
}


CHN_EXTERN_C_END
// Local Variables:
//   coding: utf-8
// End:
