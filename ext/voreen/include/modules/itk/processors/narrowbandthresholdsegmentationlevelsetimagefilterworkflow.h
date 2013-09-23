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

#ifndef VRN_NARROWBANDTHRESHOLDSEGMENTATIONLEVELSETIMAGEFILTERWORKFLOW_H
#define VRN_NARROWBANDTHRESHOLDSEGMENTATIONLEVELSETIMAGEFILTERWORKFLOW_H

#include "modules/itk/processors/itkprocessor.h"
#include "voreen/core/processors/volumeprocessor.h"
#include "voreen/core/ports/volumeport.h"
#include "voreen/core/ports/geometryport.h"
#include <string>

#include "voreen/core/datastructures/geometry/pointlistgeometry.h"
#include "voreen/core/properties/boolproperty.h"
#include "voreen/core/properties/floatproperty.h"
#include "voreen/core/properties/vectorproperty.h"
#include "voreen/core/properties/intproperty.h"
#include "voreen/core/properties/optionproperty.h"

namespace voreen {

class VolumeBase;

class NarrowBandThresholdSegmentationLevelSetImageFilterWorkflowITK : public ITKProcessor {
public:
    NarrowBandThresholdSegmentationLevelSetImageFilterWorkflowITK();

    virtual Processor* create() const;

    virtual std::string getCategory() const   { return "Volume Processing/Segmentation/LevelSetWorkflows"; }
    virtual std::string getClassName() const  { return "NarrowBandThresholdSegmentationLevelSetImageFilterWorkflowITK";  }
    virtual CodeState getCodeState() const    { return CODE_STATE_EXPERIMENTAL; }

protected:
    virtual void setDescriptions() {
        setDescription("");
    }
    template<class T>
    void narrowBandThresholdSegmentationLevelSetImageFilterWorkflowITK();


    virtual void process();


private:
    VolumePort inport1_;
    VolumePort outport1_;
    GeometryPort seedPointPort_;

    BoolProperty enableProcessing_;
    StringOptionProperty initLevelSet_;

    // seed point
    IntProperty numSeedPoint_;
    FloatVec3Property seedPoint_;

    std::vector<tgt::vec3> seedPoints;

    //properties for DanielsonSignedDistance
    BoolProperty inputIsBinary_;
    BoolProperty squaredDistance_;
    BoolProperty useImageSpacing_;
    //properties for smoothing filter
    FloatProperty timestep_;
    IntProperty numberofiterations_;
    FloatProperty conductanceparameter_;
    //properties for sigmoid filter
    FloatProperty alpha_;
    FloatProperty beta_;
    FloatProperty sigma_;
    //properties for fast marching
    FloatProperty stoptime_;
    FloatProperty initialDistance_;
    //segmentation
    FloatProperty propagationScaling_;


    static const std::string loggerCat_;
};
}
#endif
