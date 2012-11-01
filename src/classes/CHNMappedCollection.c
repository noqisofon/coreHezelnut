//  
//  CHNMappedCollection.c
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

#include "coreHezelnut/classes/CHNClass.h"
#include "coreHezelnut/classes/CHNString.h"
#include "coreHezelnut/classes/CHNSymbol.h"
#include "coreHezelnut/classes/CHNHashedCollection.h"
#include "coreHezelnut/classes/CHNWrongMessageSentError.h"

#include "coreHezelnut/classes/CHNMappedCollection.h"


CHN_EXTERN_C_BEGIN


struct chn_mapped_collection {
    CHNHashedCollection_ref     _domain;
    CHNHashedCollection_ref     _map;
};


CHN_EXPORT id CHNMappedCollection_class_alloc(void)
{
    return CHNObject_class_alloc( CHNMappedCollection );
}


CHN_EXPORT CHNMappedCollection_ref CHNMappedCollection_class_collection_map(CHNHashedCollection_ref a_collection, CHNHashedCollection_ref a_map)
{
    return CHNMappedCollection_setCollection_andMap( CHNMappedCollection_class_basicNew(), a_collection, a_map );
}


CHN_EXPORT CHNMappedCollection_ref CHNMappedCollection_class_new(void)
{
    CHNWrongMessageSentError_class_signalOn_useInsted( CHN_LITERAL_SYMBOL(new), CHN_LITERAL_SYMBOL(collction:map) );

    return nil;
}


CHN_EXPORT CHNMappedCollection_ref CHNMappedCollection_class_basicNew(void)
{

}


static CHNMappedCollection_ref super_init(id base)
{
    return CHN_ASMAPPED_COLLECTION(CHNCollection_init( CHN_ASCOLLECTION(base) ));
}


static void super_free(CHNMappedCollection_ref self)
{
    if ( self->_domain )
        CHNHashedCollection_release( self->_domain );
    if ( self->_map )
        CHNHashedCollection_release( self->_map );

    CHNCollection_free( CHN_ASCOLLECTION(self) );
}


CHN_EXPORT CHNMappedCollection_ref CHNMappedCollection_init(id base)
{
    CHNMappedCollection_ref self;
    
    if ( self = super_init( base ) ) {
        self->_domain = nil;
        self->_map = nil;
    }
    return self;
}


CHN_EXPORT id CHNMappedCollection_at(CHNMappedCollection_ref self, id key)
{
    return CHNHashCollection_at( self->_domain, CHNHashedCollection_at( self->_map, key ) );
}


CHN_EXPORT CHNMappedCollection_ref CHNMappedCollection_setCollection_andMap( CHNMappedCollection_ref self,
                                                                             CHNHashedCollection_ref a_collection,
                                                                             CHNHashedCollection_ref a_map)
{
    self->_domain = a_collection;
    self->_map = a_map;

    return self;
}


CHN_EXTERN_C_END


// Local Variables:
//   coding: utf-8
// End:
