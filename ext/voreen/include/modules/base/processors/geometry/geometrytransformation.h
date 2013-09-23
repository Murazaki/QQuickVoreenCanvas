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

#ifndef VRN_GEOMETRYTRANSFORMATION_H
#define VRN_GEOMETRYTRANSFORMATION_H

#include "voreen/core/processors/processor.h"

#include "voreen/core/ports/geometryport.h"
#include "voreen/core/properties/boolproperty.h"
#include "voreen/core/properties/matrixproperty.h"

namespace voreen {

class VRN_CORE_API GeometryTransformation : public Processor {
public:
    GeometryTransformation();
    virtual ~GeometryTransformation();
    virtual Processor* create() const;

    virtual std::string getCategory() const   { return "Geometry";               }
    virtual std::string getClassName() const  { return "GeometryTransformation"; }
    virtual CodeState getCodeState() const    { return CODE_STATE_STABLE;        }

protected:
    virtual void setDescriptions() {
        setDescription("Transform the input geometry by a transformation matrix.");
    }

    virtual void process();

private:
    GeometryPort inport_;
    GeometryPort outport_;

    BoolProperty enableProcessing_;
    FloatMat4Property transformMatrix_;

    static const std::string loggerCat_; ///< category used in logging
};

}   //namespace

#endif // VRN_GEOMETRYTRANSFORMATION_H
