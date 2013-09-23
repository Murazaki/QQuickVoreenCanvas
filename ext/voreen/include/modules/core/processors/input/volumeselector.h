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

#ifndef VRN_VOLUMESELECTOR_H
#define VRN_VOLUMESELECTOR_H

#include "voreen/core/processors/processor.h"
#include "voreen/core/ports/volumeport.h"
#include "voreen/core/properties/intproperty.h"
#include "voreen/core/datastructures/volume/volume.h"

namespace voreen {

class Volume;
class ProcessorWidgetFactory;

/**
 * Selects a single volume out of a input list.
 */
class VRN_CORE_API VolumeSelector : public Processor {

public:
    VolumeSelector();
    virtual Processor* create() const;

    virtual std::string getClassName() const { return "VolumeSelector";  }
    virtual std::string getCategory() const  { return "Input";           }
    virtual CodeState getCodeState() const   { return CODE_STATE_STABLE; }
    virtual bool isUtility() const           { return true; }

    virtual void invalidate(int inv = INVALID_RESULT);

protected:
    virtual void setDescriptions() {
        setDescription("Selects a single volume from the input list.");
    }

    virtual void process();
    virtual void initialize() throw (tgt::Exception);

    IntProperty volumeID_;

    /// Inport for the volume list.
    VolumeListPort inport_;

    /// The volume port the selected volume is written to.
    VolumePort outport_;

    static const std::string loggerCat_;

private:
    void adjustToVolumeList();

};

} // namespace

#endif
