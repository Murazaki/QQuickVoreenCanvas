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

#ifndef VRN_TEXTPORT_H
#define VRN_TEXTPORT_H

#include "tgt/shadermanager.h"
#include "voreen/core/ports/port.h"

namespace voreen {

class VRN_CORE_API TextPort : public Port {
public:
    explicit TextPort(PortDirection direction, const std::string& name, const std::string& guiName = "",
                        bool allowMultipleConnections = false,
                        Processor::InvalidationLevel invalidationLevel = Processor::INVALID_PARAMETERS);
    ~TextPort();

    virtual Port* create(PortDirection direction, const std::string& id, const std::string& guiName = "") const {return new TextPort(direction,id,guiName);}
    virtual std::string getClassName() const {return "TextPort";}
    virtual std::string getContentDescription() const;
    virtual std::string getContentDescriptionHTML() const;
    virtual void forwardData() const;

    virtual void setData(const std::string& str);

    virtual std::string getData() const;

    /// Returns true.
    virtual bool hasData() const;

    virtual std::vector<std::string> getAllData() const;

    std::vector<const TextPort* > getConnected() const;

    /**
     * Returns true, if the port is connected
     */
    virtual bool isReady() const;

    virtual void clear();

    virtual tgt::col3 getColorHint() const;

protected:
    std::string portData_;

    static const std::string loggerCat_; ///< category used in logging
};

} // namespace

#endif // VRN_TEXTPORT_H
