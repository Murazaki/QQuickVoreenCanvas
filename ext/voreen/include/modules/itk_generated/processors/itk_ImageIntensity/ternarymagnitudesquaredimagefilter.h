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

#ifndef VRN_TERNARYMAGNITUDESQUAREDIMAGEFILTER_H
#define VRN_TERNARYMAGNITUDESQUAREDIMAGEFILTER_H

#include "modules/itk/processors/itkprocessor.h"
#include "voreen/core/processors/volumeprocessor.h"
#include "voreen/core/ports/volumeport.h"
#include "voreen/core/ports/geometryport.h"

#include <string>



namespace voreen {

class VolumeBase;

class TernaryMagnitudeSquaredImageFilterITK : public ITKProcessor {
public:
    TernaryMagnitudeSquaredImageFilterITK();

    virtual Processor* create() const;

    virtual std::string getCategory() const   { return "Volume Processing/Filtering/ImageIntensity"; }
    virtual std::string getClassName() const  { return "TernaryMagnitudeSquaredImageFilterITK";  }
    virtual CodeState getCodeState() const    { return CODE_STATE_STABLE; }

protected:
    virtual void setDescriptions() {
        setDescription("<a href=\"http://www.itk.org/Doxygen/html/classitk_1_1TernaryMagnitudeSquaredImageFilter.html\">Go to ITK-Doxygen-Description</a>");
    }
    template<class T, class S, class R>
    void ternaryMagnitudeSquaredImageFilterITK();


    virtual void process();
    template<class T>
    void volumeTypeSwitch1();

    template<class T, class S>
    void volumeTypeSwitch2();


private:
    VolumePort inport1_;
    VolumePort inport2_;
    VolumePort inport3_;
    VolumePort outport1_;




    static const std::string loggerCat_;
};
}
#endif
