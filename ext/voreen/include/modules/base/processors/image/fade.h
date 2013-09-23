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

#ifndef VRN_FADE_H
#define VRN_FADE_H

#include "voreen/core/processors/imageprocessorbypassable.h"

#include "voreen/core/properties/floatproperty.h"
#include "voreen/core/properties/vectorproperty.h"

namespace voreen {

/**
 * Performs a fading.
 */
class VRN_CORE_API Fade : public ImageProcessorBypassable {
public:
    Fade();

    virtual std::string getCategory() const { return "Image Processing"; }
    virtual std::string getClassName() const { return "Fade"; }
    virtual Processor::CodeState getCodeState() const { return CODE_STATE_STABLE; } ///2.0
    virtual Processor* create() const {return new Fade();}

    void process();

protected:
    virtual void setDescriptions() {
        setDescription("Performs a fading of the input image towards the specified color.");
    }

    FloatProperty fading_;
    FloatVec4Property color_;

    RenderPort inport_;
    RenderPort outport_;
};


} // namespace voreen

#endif //VRN_FADE_H
