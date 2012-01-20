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
#include "core-hezelnut/objects.h"


id CHN_alloc(CHNClass_ref super_class)
{
    id new = nil;

    if ( !super_class )
        return nil;

    new = (id)CHN_malloc( super_class->instance_size );
    new->class_pointer = super_class;

    return new;
}


id CHN_init(id self)
{
    /*
      self が存在しない場合は NilReferenceError ？
     */
    if ( !self )
        return nil;
    /*
      self->class_pointer が存在しない場合は 
     */
    if ( !self->class_pointer )
        return nil;

    return self;
}
