//  
//  CHNHashedCollection.c
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


CHN_EXTERN_C_BEGIN


struct chn_hashed_collection {
    
};


CHN_EXPORT id CHNHashedCollection_class_alloc(void)
{
    return CHNClass_createInstance( CHNHashedCollection );
}


CHN_EXPORT CHNHashedCollection_ref CHNHashedCollection_class_new(void)
{
    return CHNHashedCollection_class_newWithSize( 0 );
}


CHN_EXPORT CHNHashedCollection_ref CHNHashedCollection_class_newWithSize(size_t an_integer)
{
    return CHNHashedCollection_initWithSize( CHNHashedCollection_class_alloc(), an_integer );
}


CHN_EXPORT CHNHashedCollection_ref CHNHashedCollection_init(id base)
{
}


CHN_EXPORT id CHNHashedCollection_at(CHNHashedCollection_ref self, id key)
{
}


CHN_EXPORT void CHNHashedCollection_free(CHNHashedCollection_ref self)
{
}


CHN_EXTERN_C_END


// Local Variables:
//   coding: utf-8
// End:
