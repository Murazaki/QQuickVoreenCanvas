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

#ifndef VRN_GRADIENTVECTORFLOW_H
#define VRN_GRADIENTVECTORFLOW_H

#include "itkprocessor.h"
#include "voreen/core/properties/floatproperty.h"
#include "voreen/core/properties/intproperty.h"

#include "voreen/core/ports/volumeport.h"

#include <string>

namespace voreen {

class Volume;

class GradientVectorFlow : public ITKProcessor {
public:
    GradientVectorFlow();
    virtual Processor* create() const;

    virtual std::string getCategory() const   { return "Volume Processing"; }
    virtual std::string getClassName() const  { return "GradientVectorFlow";  }
    virtual CodeState getCodeState() const    { return CODE_STATE_EXPERIMENTAL; }
    virtual std::string getProcessorInfo() const;

protected:
    virtual void setDescriptions() {
        setDescription("");
    }

    virtual void process();

    template<class T>
    Volume* gradientvectorflow(const VolumeBase* inputVolume);

private:
    VolumePort inport_;
    VolumePort outport_;

    FloatProperty noiseLevel_;
    FloatProperty timeStep_;
    IntProperty numSteps_;
    BoolProperty normalize_;

    static const std::string loggerCat_; ///< category used in logging
};

}   //namespace

#endif
