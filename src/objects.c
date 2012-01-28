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
#include "coreHezelnut/chn-internal.h"

#include "coreHezelnut/classes.h"
#include "coreHezelnut/classes/CHNIndexOutOfRangeError.h"

#include "coreHezelnut/objects.h"


CHN_EXPORT id CHN_alloc(CHNClass_ref super_class)
{
    id new = nil;

    if ( !super_class )
        return nil;

    new = (id)CHN_malloc( super_class->instance_size );
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
      self->class_pointer が存在しない場合は nil を返したいところだが、
      呼び出し側では:

          CHN_init( CHN_alloc( CHNArray ) );
      
      のように alloc を init の引数リスト内で呼び出すことが多いため、
      self を返す。
     */
    if ( !self->class_pointer )
        return self;

    return self;
}


CHN_EXPORT id CHN_basicNew(CHNClass_ref super_class)
{
    return CHN_init( CHN_alloc( super_class ) );
}


CHN_EXPORT id CHN_basicNewWithSize(CHNClass_ref super_class, int size)
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


CHN_EXPORT CHNClass_ref CHN_getclass(id self)
{
    return self->class_pointer;
}


CHN_EXPORT id CHN_retain(id self)
{
}


CHN_EXPORT CHNBoolean CHN_tryRetain(id self)
{
}


CHN_EXPORT void CHN_release(id self)
{
}


CHN_EXPORT CHNBoolean CHN_isDeallocating(id self)
{
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
    return self->class_pointer == _class || CHNClass_inheritFrom( self->class_pointer, _class );
}


CHN_EXPORT CHNBoolean CHN_isMemberOf(id self, CHNClass_ref _class)
{
    return self->class_pointer == _class;
}


CHN_EXPORT CHNBoolean CHN_isNil(id self)
{
    return self == nil;
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
    CHNClass_ref _class = CHN_getclass( self );
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
    CHNClass_ref _class = self->class_pointer;
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


CHN_EXPORT int CHN_instSize(id self)
{
    if ( !self && !self->class_pointer->variables )
        return chn_list_size( self->class_pointer->variables );
    else
        return 0;
}


CHN_EXPORT id CHN_instVarAt(id self, int index)
{
    int basic_size = CHN_basicSize( self );
    int inst_size = CHN_instSize( CHN_ASOBJECT(self->class_pointer) );

    if ( index < 0 )
        CHNIndexOutOfRangeError_signalOn_withIndex( self, index );
    else if ( index > basic_size + inst_size )
        return CHN_basicAt( self, index - inst_size );

    return nil;
}


CHN_EXPORT void CHN_instVarAt_put(id self, int index, id value)
{
    int basic_size = CHN_basicSize( self );
    int inst_size = CHN_instSize( CHN_ASOBJECT(self->class_pointer) );

    if ( index < 0 )
        CHNIndexOutOfRangeError_signalOn_withIndex( self, index );
    else if ( index > basic_size + inst_size )
        return CHN_basicAt_put( self, index - inst_size, value );
}


CHN_EXPORT id CHN_basicAt(id self, int index)
{
    return CHN_checkIndexableBounds( self, index );
}


CHN_EXPORT void CHN_basicAt_put(id self, int index, id value)
{
    CHN_checkIndexableBounds_put( self, index, value );
}


CHN_EXPORT id CHN_at(id self, int index)
{
    return CHN_basicAt( self, index );
}


CHN_EXPORT void CHN_at_put(id self, int index, id value)
{
    CHN_basicAt_put( self, index, value );
}


CHN_EXPORT id CHN_checkIndexableBounds(id self, int index)
{
    if ( CHN_isFixed( CHN_ASOBJECT(self->class_pointer) ) ) {
        CHNNotIndexableError_signalOn( self );

        return nil;
    }
}
