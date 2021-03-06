//  
//  classes.h
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
#ifndef coreHezelnut_classes_h
#define coreHezelnut_classes_h


CHN_EXTERN_C_BEGIN


#define Nil ((CHNClass_ref)0)

//typedef char* CString_ref;

#define CHN_CLASSOF(_object_)  ((_object_)->prototype)


struct chn_class {
    struct chn_class*          prototype;

    struct chn_class*          super_class;

    const char*                name;

    int                        version;
    unsigned int               info;
    unsigned int               instance_size;

    struct chn_varible_list*   variables;
    struct chn_method_list*    methods;
};


typedef struct chn_class* CHNMetaClass_ref;
typedef struct chn_class* CHNClass_ref;


typedef CHNClass_ref (*_chn_class_initialize)(const char* class_name);


CHN_EXTERN_C_END


#endif  /* coreHezelnut_classes_h */
// Local Variables:
//   coding: utf-8
// End:
