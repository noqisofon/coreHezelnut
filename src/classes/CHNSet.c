//  
//  CHNSet.c
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

#include "coreHezelnut/coreHezelnut.h"
#include "coreHezelnut/classes.h"
#include "coreHezelnut/callbacks.h"

#include "coreHezelnut/classes/CHNInteger.h"
#include "coreHezelnut/classes/CHNString.h"
#include "coreHezelnut/classes/CHNKeyAndValueIterator.h"
#include "coreHezelnut/classes/CHNSortedCollection.h"
#include "coreHezelnut/classes/CHNMappedCollection.h"
#include "coreHezelnut/classes/CHNLookupTable.h"

#include "coreHezelnut/classes/CHNSet.h"


CHN_EXTERN_C_BEGIN


CHN_EXPORT id CHNSet_class_alloc(void)
{
    return CHNObject_class_basicNew( CHNSet );
}


CHN_EXPORT CHNSet_ref CHNSet_class_new(void)
{
    return CHNSet_init( CHNSet_class_alloc() );
}


CHN_EXPORT id CHNSet_init(id base)
{
if () {

}
}


CHN_EXTERN_C_END


// Local Variables:
//   coding: utf-8
// End:
