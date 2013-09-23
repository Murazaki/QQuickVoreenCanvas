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

#ifndef VRN_COREMODULE_H
#define VRN_COREMODULE_H

#include "voreen/core/voreenmodule.h"

namespace voreen {

/**
 * Registers core resources at runtime.
 *
 * This is actually a pseudo module, since it is an integral part
 * of the Voreen core and cannot be excluded from the build process.
 * It has been introduced to handle runtime resources of the core and
 * the modules in a consistent manner.
 */
class VRN_CORE_API CoreModule : public VoreenModule {

public:
    CoreModule(const std::string& modulePath);
    ~CoreModule(); ///< deletes the Animation's serializer factories

    virtual std::string getDescription() const { return "Provides the most basic components necessary for every network."; }
protected:
    static const std::string loggerCat_;
};

} // namespace

#endif // VRN_COREMODULE_H
