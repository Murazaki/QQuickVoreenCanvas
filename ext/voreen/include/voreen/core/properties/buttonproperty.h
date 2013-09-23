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

#ifndef VRN_BUTTONPROPERTY_H
#define VRN_BUTTONPROPERTY_H

#include "voreen/core/properties/property.h"
#include "voreen/core/properties/action.h"

namespace voreen {

class VRN_CORE_API ButtonProperty : public Property {
public:
    ButtonProperty(const std::string& id, const std::string& guiText, int invalidationLevel=Processor::VALID);
    ButtonProperty();
    virtual ~ButtonProperty();

    virtual Property* create() const;

    virtual std::string getClassName() const       { return "ButtonProperty"; }
    virtual std::string getTypeDescription() const { return "Button"; }
    virtual void reset(){}

    void onChange(const Action& action = NoAction());

    /// Convenience function delegating calls to onChange().
    void onClick(const Action& action);

    void clicked();

protected:
    std::vector<Action*> actions_;
};

}   // namespace

#endif
