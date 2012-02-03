//  
//  target-conditionals.h
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
#ifndef coreHezelnut_target_conditionals_h
#define coreHezelnut_target_conditionals_h


#ifdef MSC_VER
#   define CORE_HEZELNUT_TARGET_OS_WIN32 1
#endif  /* def MSC_VER */

#ifdef __LINUX__
#   define CORE_HEZELNUT_TARGET_OS_LINUX 1
#endif  /* def __LINUX__ */

#endif  /* coreHezelnut_target_conditionals_h */
