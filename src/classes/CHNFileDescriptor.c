//  
//  CHNFileDescriptor.c
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

#include "coreHezelnut/classes/CHNSymbol.h"
#include "coreHezelnut/classes/CHNWeakIdentitySet.h"

#include "coreHezelnut/classes/CHNFileDescriptor.h"


struct chn_file_descriptor {
    int         _fd;
    uint32_t    _access;
    char*       _filename;
    CHNBoolean  _is_pipe;
    CHNBoolean  _at_end;
    int         _peek;
};


static CHNFileDescriptor_ref super_init(id base);
static void super_free(id base);


CHN_EXTERN void CHNFileDescriptor_class_initialize(void)
{
    GarbageCollector_class_addDependent( CHNFileDescriptor );
    _AllOpenFiles = CHNWeakIdentitySet_class_new();
}


CHN_EXTERN id CHNFileDescriptor_class_alloc(void)
{
    return CHNObject_class_alloc( CHNFileDescriptor );
}


CHN_EXTERN CHNFileDescriptor_ref CHNFileDescriptor_class_open(const char* filename)
{
    return CHNFileDescriptor_class_open( filename, FileStream_class_readWrite() );
}


CHN_EXTERN CHNFileDescriptor_ref CHNFileDescriptor_class_open_mode(const char* filename, int32_t file_mode)
{
    return CHNFileDescriptor_class_open_ifFail( filename, FileStream_class_readWrite(), chn_file_descriptor_open_mode_if_fail );
}


CHN_EXTERN CHNFileDescriptor_ref CHNFileDescriptor_class_open_mode_ifFail(const char* filename, int32_t file_mode, fail_func a_block)
{
}


CHN_EXTERN CHNFileDescriptor_ref CHNFileDescriptor_class_openTemporaryFile(const char* base_name)
{
    CHNFileDescriptor_ref new;

    new = CHNFileDescriptor_class_basicNew();
}


static CHNFileDescriptor_ref super_init(id base)
{
    return (CHNFileDescriptor_ref)base;
}


static void super_free(id base)
{
    CHNObject_free( base );
}


CHN_EXTERN CHNFileDescriptor_ref CHNFileDescriptor_init(id base)
{
    CHNFileDescriptor_ref self;

    if ( self = super_init( base ) ) {
        self->_fd          = 0;
        self->_access      = 0;
        self->_filename    = NULL;
        self->_is_pipe     = FALSE;
        self->_at_end      = FALSE;
        self->_peek        = -1;
    }
    return self;
}


CHN_EXTERN CHNFileDescriptor_ref CHNFileDescriptor_close(CHNFileDescriptor_ref self)
{
    if ( !CHNFileDescriptor_isOpen( self ) )
        return self;

    CHNFileDescriptor_flush( self );
    CHNFileDescriptor_changed( self, CHN_LITERAL_SYMBOL(beforeClosing) );
    CHNFileDescriptor_fileOption( self, 1 );
    CHNFileDescriptor_removeToBeFinalized( self );
    CHNFileDescriptor_invalidate( self );
    CHNFileDescriptor_changed( self, CHN_LITERAL_SYMBOL(afterClosing) );

    return self;
}


CHN_EXTERN void CHNFileDescriptor_free(CHNFileDescriptor_ref self)
{
    super_free( CHN_OBJECT(self) );
}


CHN_EXTERN void CHNFileDescriptor_release(CHNFileDescriptor_ref self)
{
}
// Local Variables:
//   coding: utf-8
// End:
