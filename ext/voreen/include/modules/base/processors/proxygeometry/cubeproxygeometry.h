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

#ifndef VRN_CUBEPROXYGEOMETRY_H
#define VRN_CUBEPROXYGEOMETRY_H

#include "voreen/core/processors/processor.h"

#include "voreen/core/ports/volumeport.h"
#include "voreen/core/ports/geometryport.h"

#include "voreen/core/properties/boolproperty.h"
#include "voreen/core/properties/floatproperty.h"
#include "voreen/core/properties/buttonproperty.h"

namespace voreen {

class MeshListGeometry;

/**
 * Provides a cube proxy geometry as mesh with axis-aligned clipping.
 *
 * @see EntryExitPoints
 * @see MeshClipping
 */
class VRN_CORE_API CubeProxyGeometry : public Processor {
public:
    CubeProxyGeometry();
    virtual ~CubeProxyGeometry();
    virtual Processor* create() const;

    virtual std::string getClassName() const { return "CubeProxyGeometry"; }
    virtual std::string getCategory() const  { return "Volume Proxy Geometry"; }
    virtual CodeState getCodeState() const   { return CODE_STATE_STABLE; }

protected:
    virtual void setDescriptions() {
        setDescription("Provides a mesh representing a cubic proxy geometry that can be passed to a MeshEntryExitPoints processor. The proxy geometry can be manipulated by axis-aligned clipping. Clipping against an arbitrarily oriented plane is provided by the MeshClipping processor.");
    }

    virtual void process();

private:
    /// Ensure useful clipping planes on clip right property change.
    void onClipRightChange();

    /// Ensure useful clipping planes on clip left property change.
    void onClipLeftChange();

    /// Ensure useful clipping planes on clip front property change.
    void onClipFrontChange();

    /// Ensure useful clipping planes on clip back property change.
    void onClipBackChange();

    /// Ensure useful clipping planes on clip bottom property change.
    void onClipBottomChange();

    /// Ensure useful clipping planes on clip top property change.
    void onClipTopChange();

    /// Resets clipping plane parameters to extremal values.
    void resetClipPlanes();

    /// Adapt ranges of clip plane properties to the input volume's dimensions.
    void adjustClipPropertiesRanges();

    /// Adjust visibility of the clipping plane properties according to enableClipping_ property.
    void adjustClipPropertiesVisibility();

    /// Extracts ROI from volume (if present) and adjusts clipping slider accordingly.
    void adjustClippingToVolumeROI();

    VolumePort inport_;              ///< Inport for the dataset the proxy is generated for.
    GeometryPort outport_;           ///< Outport for the generated cube proxy geometry.

    BoolProperty enableClipping_;    ///< Clipping enable / disable property.
    FloatProperty clipRight_;        ///< Right clipping plane position (x).
    FloatProperty clipLeft_;         ///< Left clipping plane position (-x).
    FloatProperty clipFront_;        ///< Front clipping plane position (y).
    FloatProperty clipBack_;         ///< Back clipping plane position property (-y).
    FloatProperty clipBottom_;       ///< Bottom clipping plane position property (z).
    FloatProperty clipTop_;          ///< Top clipping plane position property (-z).
    ButtonProperty resetClipPlanes_; ///< Reset clipping plane parameters to extremal values.

    tgt::ivec3 oldVolumeDimensions_;

    /// Cube proxy geometry generated by this processor.
    MeshListGeometry* geometry_;

    /// Category used for logging.
    static const std::string loggerCat_;
};

} // namespace

#endif // VRN_CUBEPROXYGEOMETRY_H
