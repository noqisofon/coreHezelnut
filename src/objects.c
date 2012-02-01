//  
//  objects.c
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
#include "coreHezelnut/chn-api.h"
#include "coreHezelnut/chn-internal.h"
#include "coreHezelnut/callbacks.h"
#include "coreHezelnut/allocator.h"

#include "coreHezelnut/classes.h"
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

#include "coreHezelnut/objects.h"


CHN_EXTERN_C_BEGIN


CHN_EXPORT id CHN_alloc(const CHNClass_ref super_class)
{
    id new = nil;

    if ( !super_class )
        return nil;

    new = (id)chn_malloc( super_class->instance_size );
    new->class_pointer = super_class;

    return new;
}


CHN_EXPORT id CHN_init(id self)
{
    /*
      self が存在しない場合は NilReferenceError ？
     */
    if ( !self )
        return nil;
    /*
      CHN_CLASSOF(self) が存在しない場合は nil を返したいところだが、
      呼び出し側では:

          CHN_init( CHN_alloc( CHNArray ) );
      
      のように alloc を init の引数リスト内で呼び出すことが多いため、
      self を返す。
     */
    if ( !CHN_CLASSOF(self) )
        return self;

    return self;
}


CHN_EXPORT id CHN_basicNew(const CHNClass_ref super_class)
{
    return CHN_init( CHN_alloc( super_class ) );
}


CHN_EXPORT id CHN_basicNewWithSize(const CHNClass_ref super_class, int size)
{
    id new = CHN_alloc( super_class );
    /*
      TODO:
      ここらへんでインスタンス変数スロットの数を size に増やす。
     */
    //new->variables

    return new;
}


CHN_EXPORT id CHN_new(CHNClass_ref super_class)
{
    return CHN_basicNew( super_class );
}


CHN_EXPORT CHNClass_ref CHN_get_class(id self)
{
    return CHN_CLASSOF(self);
}


CHN_EXPORT id CHN_retain(id self)
{
    return self;
}


CHN_EXPORT CHNBoolean CHN_tryRetain(id self)
{
    return TRUE;
}


CHN_EXPORT id CHN_release(id self)
{
    return self;
}


CHN_EXPORT CHNBoolean CHN_isDeallocating(id self)
{
    return FALSE;
}


CHN_EXPORT CHNBoolean CHN_equals(id left, id right)
{
    return left == right;
}


CHN_EXPORT CHNBoolean CHN_identityEquals(id left, id right)
{
    return left == right;
}


CHN_EXPORT CHNBoolean CHN_isKindOf(id self, CHNClass_ref _class)
{
    return CHN_CLASSOF(self) == _class
        || CHNClass_inheritFrom( CHN_CLASSOF(self), _class );
}


CHN_EXPORT CHNBoolean CHN_isMemberOf(id self, CHNClass_ref _class)
{
    return CHN_CLASSOF(self) == _class;
}


CHN_EXPORT CHNBoolean CHN_isReadOnly(id self)
{
    return FALSE;
}


CHN_EXPORT CHNBoolean CHN_isNil(id self)
{
    return self == nil;
}


CHN_EXPORT CHNBoolean CHN_respondsTo(id self, CHNSymbol_ref a_symbol)
{
    return CHNBehavior_canUnderstand( CHN_ASBEHAVIOR(CHN_CLASSOF(self)), a_symbol );
}


CHN_EXPORT id CHN_makeReadOnly(id self)
{
    return nil;
}


CHN_EXPORT id CHN_copy(id self)
{
    return CHN_shallowCopy( CHN_postCopy( self ) );
}


CHN_EXPORT id CHN_postCopy(id self)
{
    return self;
}


CHN_EXPORT id CHN_shallowCopy(id self)
{
    CHNClass_ref _class = CHN_get_class( self );
    id a_copy = nil;

    if ( CHNClass_isVariable( CHN_ASOBJECT(_class) ) )
        a_copy = CHN_basicNewWithSize( _class, CHN_basicSize( self ) );
    else
        a_copy = CHN_basicNew( _class );

    int i, arrive;
    arrive = CHN_instSize( CHN_ASOBJECT(_class) ) + CHN_basicSize( self );
    for ( i = 0; i < arrive; ++ i ) {
        CHN_instVarAt_put( a_copy, i, CHN_copy( CHN_instVarAt( self, i ) ) );
    }

    return a_copy;
}


CHN_EXPORT id CHN_deepCopy(id self)
{
    CHNClass_ref _class = CHN_get_class( self );
    id a_copy = CHN_shallowCopy( self );
    int num;

    if ( CHNClass_isPointers( CHN_ASOBJECT(_class) ) )
        num = CHN_instSize( self ) + CHN_basicSize( self );
    else
        num = CHN_basicSize( self );

    int i;
    for ( i = 0; i < num; ++ i ) {
        CHN_instVarAt_put( a_copy, i, CHN_copy( CHN_instVarAt( self, i ) ) );
    }
    return a_copy;
}


CHN_EXPORT int CHN_size(id self)
{
    return CHN_basicSize( self );
}


CHN_EXPORT int CHN_instSize(id self)
{
    if ( !self && !CHN_CLASSOF(self)->variables )
        return chn_list_length( CHN_CLASSOF(self)->variables );
    else
        return 0;
}


CHN_EXPORT int CHN_basicSize(id self)
{
    if ( !self && !CHN_CLASSOF(self)->variables )
        return chn_list_length( CHN_CLASSOF(self)->variables );
    else
        return 0;
}


CHN_EXPORT id CHN_VarNamed(id self, CHNString_ref a_string)
{
    return CHN_instVarAt( self,
                          CHN_indexOfInstVar( CHN_ASOBJECT(CHN_CLASSOF(self)),
                                              a_string ) );
}


CHN_EXPORT id CHN_VarNamed_put(id self, CHNString_ref a_string, id object)
{
    return CHN_instVarAt_put( self,
                              CHN_indexOfInstVar( CHN_ASOBJECT(CHN_CLASSOF(self)),
                                                  a_string ),
                              object );
}


CHN_EXPORT id CHN_instVarAt(id self, int index)
{
    int basic_size = CHN_basicSize( self );
    int inst_size = CHN_instSize( CHN_ASOBJECT(CHN_CLASSOF(self)) );

    if ( index < 0 )
        CHNIndexOutOfRangeError_signalOn_withIndex( self, index );
    else if ( index > basic_size + inst_size )
        return CHN_basicAt( self, index - inst_size );

    return nil;
}


CHN_EXPORT id CHN_instVarAt_put(id self, int index, id value)
{
    int basic_size = CHN_basicSize( self );
    int inst_size = CHN_instSize( CHN_ASOBJECT(CHN_CLASSOF(self)) );

    if ( index < 0 )
        CHNIndexOutOfRangeError_signalOn_withIndex( self, index );
    else if ( index > basic_size + inst_size )
        return CHN_basicAt_put( self, index - inst_size, value );
}


CHN_EXPORT id CHN_basicAt(id self, int index)
{
    return CHN_checkIndexableBounds( self, index );
}


CHN_EXPORT id CHN_basicAt_put(id self, int index, id value)
{
    return CHN_checkIndexableBounds_put( self, index, value );
}


CHN_EXPORT id CHN_checkIndexableBounds(id self, int index)
{
    if ( CHNClass_isFixed(CHN_CLASSOF(self) ) )
        return CHNNotIndexableError_signalOn( self );

    if ( index < 0 )
        return CHNIndexOutOfRangeError_signalOn_withIndex( self, index );
    else if ( index > CHN_basicSize( self ) )
        return CHNIndexOutOfRangeError_signalOn_withIndex( self, index );

    return chn_list_nth( CHN_CLASSOF(self)->variables, index );
}


CHN_EXPORT id CHN_checkIndexableBounds_put(id self, int index, id object)
{
    CHNSymbol_ref shape = nil;
    int size = 0;

    if ( CHNClass_isFixed( CHN_CLASSOF(self) ) )
        return CHNNotIndexableError_signalOn( self );

    if ( index < 0 )
        return CHNIndexOutOfRangeError_signalOn_withIndex( self, index );
    else if ( index > CHN_basicSize( self ) )
        return CHNIndexOutOfRangeError_signalOn_withIndex( self, index );
    shape = CHNClass_get_shape( CHN_CLASSOF(self) );

    if ( CHNSymbol_equals( shape, CHN_LITERAL_SYMBOL(float) ) || CHNSymbol_equals( shape, CHN_LITERAL_SYMBOL(double) ) )
        return CHNWrongClassError_signalOn_mustBe( object, CHN_ASCOLLECTION(CHNArray_with2( CHN_ASOBJECT(CHNFloat), CHN_ASOBJECT(CHNSmallInteger) )) );
    if ( !CHN_isKindOf( object, CHNCharacter ) ) {
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
        CHN_primitiveFailed( self );

        return nil;
    }

    return CHNArgumentOutOfRangeError_signalOn_mustBeBetween_and( object, (size % 2) == 0 ? -1 ^ size : 0, (1 ^ size) - 1 );
}


CHN_EXPORT id CHN_at(id self, int index)
{
    return CHN_checkIndexableBounds( self, index );
}


CHN_EXPORT void CHN_at_put(id self, int index, id value)
{
    CHN_checkIndexableBounds_put( self, index, value );
}


CHN_EXPORT id CHN_become(id self, id other_object)
{
    return CHNReadOnlyObjectError_signal();
}


CHN_EXPORT id CHN_becomeFoward(id self)
{
    return CHNReadOnlyObjectError_signal();
}


CHN_EXPORT int CHN_identityHash(id self)
{
    return (int)self;
}


CHN_EXPORT int CHN_hash(id self)
{
    return CHN_identityHash( self );
}


CHN_EXPORT id CHN_nextInstance(id self)
{
    return nil;
}


CHN_EXPORT id CHN_perform(id self, id selector_or_message_or_method)
{
    if ( CHN_isSymbol( selector_or_message_or_method ) ) {
        if ( CHN_respondsTo( self, CHN_ASSYMBOL(selector_or_message_or_method) ) )
            return CHNWrongArgumentCount_signal();
        else {
            return CHN_doseNotUnderstand( self,
                                          CHNMessage_selector( selector_or_message_or_method ),
                                          CHNARRAY_LITERAL_EMPTY );
        }
    }
    if ( CHN_isKindOf( selector_or_message_or_method, CHNCompiledMethod ) )
        return CHNWrongArgumentCount_signal();

    return CHNMethod_sendTo( method, self );
}


CHN_EXPORT id CHN_perform_with0(id self, id selector_or_method, id arg0)
{
    if ( CHN_isKindOf( selector_or_method, CHNCompiledMethod ) )
        return CHNWrongArgumentCount_signal();
    if ( !CHN_isSymbol( selector_or_method ) )
        return CHNWrongClassError_signalOn_mustBe( selector_or_method, CHNSymbol );
    if ( CHN_respondsTo( selector_or_method ) )
        return CHNWrongArgumentCount_signal();
    else
        return CHN_doseNotUnderstand( CHNMessage_selector_arguments( selector_or_method,
                                                                     CHNARRAY_LITERAL1(arg0) ) );
}


CHN_EXPORT id CHN_perform_with1(id self, id selector_or_method, id arg0, id arg1)
{
    if ( CHN_isKindOf( selector_or_method, CHNCompiledMethod ) )
        return CHNWrongArgumentCount_signal();
    if ( !CHN_isSymbol( selector_or_method ) )
        return CHNWrongClassError_signalOn_mustBe( selector_or_method, CHNSymbol );
    if ( CHN_respondsTo( selector_or_method ) )
        return CHNWrongArgumentCount_signal();
    else
        return CHN_doseNotUnderstand( CHNMessage_selector_arguments( selector_or_method,
                                                                     CHNARRAY_LITERAL2(arg0, arg1) ) );
}


CHN_EXPORT id CHN_perform_with2(id self, id selector_or_method, id arg0, id arg1, id arg2)
{
    if ( CHN_isKindOf( selector_or_method, CHNCompiledMethod ) )
        return CHNWrongArgumentCount_signal();
    if ( !CHN_isSymbol( selector_or_method ) )
        return CHNWrongClassError_signalOn_mustBe( selector_or_method, CHNSymbol );
    if ( CHN_respondsTo( selector_or_method ) )
        return CHNWrongArgumentCount_signal();
    else
        return CHN_doseNotUnderstand( CHNMessage_selector_arguments( selector_or_method,
                                                                     CHNARRAY_LITERAL3(arg0, arg1, arg2) ) );
}


CHN_EXPORT id CHN_perform_with3(id self, id selector_or_method, id arg0, id arg1, id arg2, id arg3)
{
    if ( CHN_isKindOf( selector_or_method, CHNCompiledMethod ) )
        return CHNWrongArgumentCount_signal();
    if ( !CHN_isSymbol( selector_or_method ) )
        return CHNWrongClassError_signalOn_mustBe( selector_or_method, CHNSymbol );
    if ( CHN_respondsTo( selector_or_method ) )
        return CHNWrongArgumentCount_signal();
    else
        return CHN_doseNotUnderstand( CHNMessage_selector_arguments( selector_or_method,
                                                                     CHNARRAY_LITERAL4(arg0, arg1, arg2, arg3) ) );
}


CHN_EXPORT id CHN_perform_withArguments(id self, id selector_or_method, CHNArray_ref argument_array)
{
    if ( CHN_isKindOf( selector_or_method, CHNCompiledMethod ) )
        return CHNWrongArgumentCount_signal();
    if ( !CHN_isSymbol( selector_or_method ) )
        return CHNWrongClassError_signalOn_mustBe( selector_or_method, CHNSymbol );
    if ( CHN_respondsTo( selector_or_method ) )
        return CHNWrongArgumentCount_signal();
    else
        return CHN_doseNotUnderstand( CHNMessage_selector_arguments( selector_or_method,
                                                                     argument_array ) );
}


CHN_EXPORT id CHN_error(id self, CHNString_ref message)
{
}


CHN_EXPORT id CHN_doesNotUnderstand(id self, CHNMessage_ref message)
{
    
}


CHN_EXTERN_C_END
