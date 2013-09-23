/***********************************************************************************
 *                                                                                 *
 * Voreen - The Volume Rendering Engine                                            *
 *                                                                                 *
 * Copyright (C) 2005-2013 University of Muenster, Germany.                        *
 * Visualization and Computer Graphics Group <http://viscg.uni-muenster.de>        *
 * For a list of authors please refer to the file "CREDITS.txt".                   *
 *                                                                                 *
 * This file is part of the Voreen software package. Voreen is free software:      *
 * you can redistribute it and/or modify it under the terms of the GNU General     *
 * Public License version 2 as published by the Free Software Foundation.          *
 *                                                                                 *
 * Voreen is distributed in the hope that it will be useful, but WITHOUT ANY       *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR   *
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.      *
 *                                                                                 *
 * You should have received a copy of the GNU General Public License in the file   *
 * "LICENSE.txt" along with this file. If not, see <http://www.gnu.org/licenses/>. *
 *                                                                                 *
 * For non-commercial academic use see the license exception specified in the file *
 * "LICENSE-academic.txt". To get information about commercial licensing please    *
 * contact the authors.                                                            *
 *                                                                                 *
 ***********************************************************************************/

#ifndef VRN_VOREENCOREAPI_H
#define VRN_VOREENCOREAPI_H

#ifdef VRN_SHARED_LIBS
    #ifdef VRN_CORE_BUILD_DLL
        // building library -> export symbols
        #ifdef WIN32
            #define VRN_CORE_API __declspec(dllexport)
        #else
            #define VRN_CORE_API
        #endif
    #else
        // including library -> import symbols
        #ifdef WIN32
            #define VRN_CORE_API __declspec(dllimport)
        #else
            #define VRN_CORE_API
        #endif
    #endif
#else
    // building/including static library -> do nothing
    #define VRN_CORE_API
#endif

#endif // VRN_VOREENCOREAPI_H
