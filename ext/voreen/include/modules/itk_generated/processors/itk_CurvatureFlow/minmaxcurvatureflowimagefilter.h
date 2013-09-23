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

#ifndef VRN_MINMAXCURVATUREFLOWIMAGEFILTER_H
#define VRN_MINMAXCURVATUREFLOWIMAGEFILTER_H

#include "modules/itk/processors/itkprocessor.h"
#include "voreen/core/processors/volumeprocessor.h"
#include "voreen/core/ports/volumeport.h"
#include "voreen/core/ports/geometryport.h"

#include <string>

#include "voreen/core/properties/boolproperty.h"
#include "voreen/core/properties/intproperty.h"


namespace voreen {

class VolumeBase;

class MinMaxCurvatureFlowImageFilterITK : public ITKProcessor {
public:
    MinMaxCurvatureFlowImageFilterITK();

    virtual Processor* create() const;

    virtual std::string getCategory() const   { return "Volume Processing/Filtering/CurvatureFlow"; }
    virtual std::string getClassName() const  { return "MinMaxCurvatureFlowImageFilterITK";  }
    virtual CodeState getCodeState() const    { return CODE_STATE_STABLE; }

protected:
    virtual void setDescriptions() {
        setDescription("<a href=\"http://www.itk.org/Doxygen/html/classitk_1_1MinMaxCurvatureFlowImageFilter.html\">Go to ITK-Doxygen-Description</a>");
    }
    template<class T>
    void minMaxCurvatureFlowImageFilterITK();


    virtual void process();


private:
    VolumePort inport1_;
    VolumePort outport1_;


    BoolProperty enableProcessing_;
    IntProperty stencilRadius_;


    static const std::string loggerCat_;
};
}
#endif
