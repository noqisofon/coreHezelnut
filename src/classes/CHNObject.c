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
#include "coreHezelnut/chn_internal.h"
#include "coreHezelnut/classes.h"
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
    CHNClass_ref class_pointer;

    
};


static struct chn_class __chn_object_metaclass;


static struct chn_class __chn_object_class;


CHN_EXPORT void CHNObject_class_initialize(void)
{
    __chn_object_metaclass.class_pointer = CHNClass;
    __chn_object_metaclass.super_class = CHNClass;
    __chn_object_metaclass.name = "CHNObjectMetaClass";
    __chn_object_metaclass.version = 0;
    __chn_object_metaclass.info = 0;
    __chn_object_metaclass.instance_size = sizeof(struct chn_object_metaclass);
    __chn_object_metaclass.variables = NULL;
    __chn_object_metaclass.methods = NULL;

    __chn_object_class.class_pointer = &__chn_object_metaclass;
    __chn_object_class.super_class = nil;
    __chn_object_class.name = "CHNObject";
    __chn_object_class.version = 0;
    __chn_object_class.info = 0;
    __chn_object_class.instance_size = sizeof(struct chn_object);
    __chn_object_class.variables = NULL;
    __chn_object_class.methods = NULL;
}


const CHNClass_ref CHNObject = &__chn_object_class;



CHN_EXPORT id CHNObject_class_alloc(void)
{
    id new = CHN_alloc( CHNObject );

    return new;
}

CHN_EXPORT id CHNObject_class_new(void)
{
    return CHNObject_init( CHNObject_class_alloc() );
}


CHN_EXPORT id CHNObject_init(id self)
{
    return self;
}






CHN_EXTERN_C_END
// Local Variables:
//   coding: utf-8
// End:
