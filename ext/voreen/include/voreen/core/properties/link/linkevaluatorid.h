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

#ifndef VRN_LINKEVALUATORID_H
#define VRN_LINKEVALUATORID_H

#include "voreen/core/properties/link/linkevaluatoridgeneric.h"

#include "voreen/core/properties/shaderproperty.h"
#include "voreen/core/properties/cameraproperty.h"
#include "voreen/core/properties/lightsourceproperty.h"
#include "voreen/core/properties/volumeurlproperty.h"

namespace voreen {

///just a dummy class to enable auto conversion:
class VRN_CORE_API LinkEvaluatorId : public LinkEvaluatorBase {
public:
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorId(); }
    virtual std::string getClassName() const  { return "LinkEvaluatorId"; }
    virtual std::string getGuiName() const    { return "Identity"; }

    virtual void eval(Property*, Property*) throw (VoreenException) {}
    virtual bool arePropertiesLinkable(const Property*, const Property*) const { return true; }
};

///just a dummy class to enable auto conversion:
class VRN_CORE_API LinkEvaluatorIdNormalized : public LinkEvaluatorBase {
public:
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorIdNormalized(); }
    virtual std::string getClassName() const  { return "LinkEvaluatorIdNormalized"; }
    virtual std::string getGuiName() const     { return "Normalization"; }

    virtual void eval(Property*, Property*) throw (VoreenException) {}
    virtual bool arePropertiesLinkable(const Property*, const Property*) const { return true; }
};

//-------------------------------------------------------------------------------------------------------
//Bool, Int, Float, Double:

class VRN_CORE_API LinkEvaluatorBoolId : public LinkEvaluatorIdGeneric<bool> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorBoolId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorBoolId(); }
};

class VRN_CORE_API LinkEvaluatorIntId : public LinkEvaluatorIdGeneric<int> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorIntId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorIntId(); }
};

class VRN_CORE_API LinkEvaluatorFloatId : public LinkEvaluatorIdGeneric<float> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorFloatId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorFloatId(); }
};

class VRN_CORE_API LinkEvaluatorDoubleId : public LinkEvaluatorIdGeneric<double> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDoubleId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDoubleId(); }
};

// id conversion
class VRN_CORE_API LinkEvaluatorDoubleFloatId : public LinkEvaluatorIdGenericConversion<double, float> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDoubleFloatId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDoubleFloatId(); }
};

class VRN_CORE_API LinkEvaluatorDoubleIntId : public LinkEvaluatorIdGenericConversion<double, int> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDoubleIntId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDoubleIntId(); }
};

class VRN_CORE_API LinkEvaluatorDoubleBoolId : public LinkEvaluatorIdGenericConversion<double, bool> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDoubleBoolId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDoubleBoolId(); }
};

class VRN_CORE_API LinkEvaluatorFloatIntId : public LinkEvaluatorIdGenericConversion<float, int> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorFloatIntId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorFloatIntId(); }
};

class VRN_CORE_API LinkEvaluatorFloatBoolId : public LinkEvaluatorIdGenericConversion<float, bool> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorFloatBoolId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorFloatBoolId(); }
};

class VRN_CORE_API LinkEvaluatorIntBoolId : public LinkEvaluatorIdGenericConversion<int, bool> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorIntBoolId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorIntBoolId(); }
};

// id normalized
class VRN_CORE_API LinkEvaluatorIntIdNormalized : public LinkEvaluatorIdNormalizedGeneric<int> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorIntIdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorIntIdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorFloatIdNormalized : public LinkEvaluatorIdNormalizedGeneric<float> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorFloatIdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorFloatIdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorDoubleIdNormalized : public LinkEvaluatorIdNormalizedGeneric<double> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDoubleIdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDoubleIdNormalized(); }
};

// id normalized conversion
class VRN_CORE_API LinkEvaluatorDoubleFloatIdNormalized : public LinkEvaluatorIdNormalizedGenericConversion<double, float> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDoubleFloatIdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDoubleFloatIdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorDoubleIntIdNormalized : public LinkEvaluatorIdNormalizedGenericConversion<double, int> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDoubleIntIdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDoubleIntIdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorFloatIntIdNormalized : public LinkEvaluatorIdNormalizedGenericConversion<float, int> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorFloatIntIdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorFloatIntIdNormalized(); }
};

//-------------------------------------------------------------------------------------------------------
// Vector properties:

// id
class VRN_CORE_API LinkEvaluatorIVec2Id : public LinkEvaluatorIdGeneric<tgt::ivec2> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorIVec2Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorIVec2Id(); }
};

class VRN_CORE_API LinkEvaluatorIVec3Id : public LinkEvaluatorIdGeneric<tgt::ivec3> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorIVec3Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorIVec3Id(); }
};

class VRN_CORE_API LinkEvaluatorIVec4Id : public LinkEvaluatorIdGeneric<tgt::ivec4> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorIVec4Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorIVec4Id(); }
};

class VRN_CORE_API LinkEvaluatorVec2Id : public LinkEvaluatorIdGeneric<tgt::vec2> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorVec2Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorVec2Id(); }
};

class VRN_CORE_API LinkEvaluatorVec3Id : public LinkEvaluatorIdGeneric<tgt::vec3> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorVec3Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorVec3Id(); }
};

class VRN_CORE_API LinkEvaluatorVec4Id : public LinkEvaluatorIdGeneric<tgt::vec4> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorVec4Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorVec4Id(); }
};

class VRN_CORE_API LinkEvaluatorDVec2Id : public LinkEvaluatorIdGeneric<tgt::dvec2> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec2Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec2Id(); }
};

class VRN_CORE_API LinkEvaluatorDVec3Id : public LinkEvaluatorIdGeneric<tgt::dvec3> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec3Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec3Id(); }
};

class VRN_CORE_API LinkEvaluatorDVec4Id : public LinkEvaluatorIdGeneric<tgt::dvec4> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec4Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec4Id(); }
};

// id conversion
class VRN_CORE_API LinkEvaluatorDVec2Vec2Id : public LinkEvaluatorIdGenericConversion<tgt::dvec2, tgt::vec2> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec2Vec2Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec2Vec2Id(); }
};

class VRN_CORE_API LinkEvaluatorDVec3Vec3Id : public LinkEvaluatorIdGenericConversion<tgt::dvec3, tgt::vec3> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec3Vec3Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec3Vec3Id(); }
};

class VRN_CORE_API LinkEvaluatorDVec4Vec4Id : public LinkEvaluatorIdGenericConversion<tgt::dvec4, tgt::vec4> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec4Vec4Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec4Vec4Id(); }
};

class VRN_CORE_API LinkEvaluatorDVec2IVec2Id : public LinkEvaluatorIdGenericConversion<tgt::dvec2, tgt::ivec2> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec2IVec2Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec2IVec2Id(); }
};

class VRN_CORE_API LinkEvaluatorDVec3IVec3Id : public LinkEvaluatorIdGenericConversion<tgt::dvec3, tgt::ivec3> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec3IVec3Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec3IVec3Id(); }
};

class VRN_CORE_API LinkEvaluatorDVec4IVec4Id : public LinkEvaluatorIdGenericConversion<tgt::dvec4, tgt::ivec4> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec4IVec4Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec4IVec4Id(); }
};

class VRN_CORE_API LinkEvaluatorVec2IVec2Id : public LinkEvaluatorIdGenericConversion<tgt::vec2, tgt::ivec2> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorVec2IVec2Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorVec2IVec2Id(); }
};

class VRN_CORE_API LinkEvaluatorVec3IVec3Id : public LinkEvaluatorIdGenericConversion<tgt::vec3, tgt::ivec3> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorVec3IVec3Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorVec3IVec3Id(); }
};

class VRN_CORE_API LinkEvaluatorVec4IVec4Id : public LinkEvaluatorIdGenericConversion<tgt::vec4, tgt::ivec4> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorVec4IVec4Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorVec4IVec4Id(); }
};

// id normalized
class VRN_CORE_API LinkEvaluatorIVec2IdNormalized : public LinkEvaluatorIdNormalizedGeneric<tgt::ivec2> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorIVec2IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorIVec2IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorIVec3IdNormalized : public LinkEvaluatorIdNormalizedGeneric<tgt::ivec3> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorIVec3IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorIVec3IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorIVec4IdNormalized : public LinkEvaluatorIdNormalizedGeneric<tgt::ivec4> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorIVec4IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorIVec4IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorVec2IdNormalized : public LinkEvaluatorIdNormalizedGeneric<tgt::vec2> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorVec2IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorVec2IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorVec3IdNormalized : public LinkEvaluatorIdNormalizedGeneric<tgt::vec3> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorVec3IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorVec3IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorVec4IdNormalized : public LinkEvaluatorIdNormalizedGeneric<tgt::vec4> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorVec4IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorVec4IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorDVec2IdNormalized : public LinkEvaluatorIdNormalizedGeneric<tgt::dvec2> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec2IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec2IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorDVec3IdNormalized : public LinkEvaluatorIdNormalizedGeneric<tgt::dvec3> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec3IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec3IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorDVec4IdNormalized : public LinkEvaluatorIdNormalizedGeneric<tgt::dvec4> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec4IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec4IdNormalized(); }
};

// id normalized conversion
class VRN_CORE_API LinkEvaluatorDVec2Vec2IdNormalized : public LinkEvaluatorIdNormalizedGenericConversion<tgt::dvec2, tgt::vec2> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec2Vec2IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec2Vec2IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorDVec3Vec3IdNormalized : public LinkEvaluatorIdNormalizedGenericConversion<tgt::dvec3, tgt::vec3> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec3Vec3IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec3Vec3IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorDVec4Vec4IdNormalized : public LinkEvaluatorIdNormalizedGenericConversion<tgt::dvec4, tgt::vec4> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec4Vec4IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec4Vec4IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorDVec2IVec2IdNormalized : public LinkEvaluatorIdNormalizedGenericConversion<tgt::dvec2, tgt::ivec2> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec2IVec2IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec2IVec2IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorDVec3IVec3IdNormalized : public LinkEvaluatorIdNormalizedGenericConversion<tgt::dvec3, tgt::ivec3> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec3IVec3IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec3IVec3IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorDVec4IVec4IdNormalized : public LinkEvaluatorIdNormalizedGenericConversion<tgt::dvec4, tgt::ivec4> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorDVec4IVec4IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorDVec4IVec4IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorVec2IVec2IdNormalized : public LinkEvaluatorIdNormalizedGenericConversion<tgt::vec2, tgt::ivec2> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorVec2IVec2IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorVec2IVec2IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorVec3IVec3IdNormalized : public LinkEvaluatorIdNormalizedGenericConversion<tgt::vec3, tgt::ivec3> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorVec3IVec3IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorVec3IVec3IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorVec4IVec4IdNormalized : public LinkEvaluatorIdNormalizedGenericConversion<tgt::vec4, tgt::ivec4> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorVec4IVec4IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorVec4IVec4IdNormalized(); }
};


//-------------------------------------------------------------------------------------------------------
//Matrix properties:

class VRN_CORE_API LinkEvaluatorMat2Id : public LinkEvaluatorIdGeneric<tgt::mat2> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorMat2Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorMat2Id(); }
};

class VRN_CORE_API LinkEvaluatorMat3Id : public LinkEvaluatorIdGeneric<tgt::mat3> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorMat3Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorMat3Id(); }
};

class VRN_CORE_API LinkEvaluatorMat4Id : public LinkEvaluatorIdGeneric<tgt::mat4> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorMat4Id"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorMat4Id(); }
};

// id normalized
class VRN_CORE_API LinkEvaluatorMat2IdNormalized : public LinkEvaluatorIdNormalizedGeneric<tgt::mat2> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorMat2IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorMat2IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorMat3IdNormalized : public LinkEvaluatorIdNormalizedGeneric<tgt::mat3> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorMat3IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorMat3IdNormalized(); }
};

class VRN_CORE_API LinkEvaluatorMat4IdNormalized : public LinkEvaluatorIdNormalizedGeneric<tgt::mat4> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorMat4IdNormalized"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorMat4IdNormalized(); }
};

//-------------------------------------------------------------------------------------------------------
//String (+FileDialog)

class VRN_CORE_API LinkEvaluatorStringId : public LinkEvaluatorIdGeneric<std::string> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorStringId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorStringId(); }
};

//-------------------------------------------------------------------------------------------------------

class VRN_CORE_API LinkEvaluatorShaderId : public LinkEvaluatorIdGeneric<ShaderSource> {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorShaderId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorShaderId(); }
};

//-------------------------------------------------------------------------------------------------------

class VRN_CORE_API LinkEvaluatorCameraId : public LinkEvaluatorBase {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorCameraId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorCameraId(); }
    virtual std::string getGuiName() const { return "Camera Identity"; }

    ///Special implementation to only link position focus and up vector
    virtual void eval(Property* src, Property* dst) throw (VoreenException);

    bool arePropertiesLinkable(const Property* p1, const Property* p2) const;
};

//-------------------------------------------------------------------------------------------------------

class VRN_CORE_API LinkEvaluatorCameraOrientationId : public LinkEvaluatorBase {
public:
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorCameraOrientationId(); }
    virtual std::string getClassName() const { return "LinkEvaluatorCameraOrientationId"; }
    virtual std::string getGuiName() const { return "Camera Orientation Identity"; }

    ///Special implementation to only link position focus and up vector
    virtual void eval(Property* src, Property* dst) throw (VoreenException);

    bool arePropertiesLinkable(const Property* p1, const Property* p2) const;
};

//------------------------------------------------------------------------------------------------------
//
class VRN_CORE_API LinkEvaluatorCameraPosId : public LinkEvaluatorBase {
public:
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorCameraPosId(); }
    virtual std::string getClassName() const { return "LinkEvaluatorCameraPosId"; }
    virtual std::string getGuiName() const { return "Camera Position Identity"; }

    ///Special implementation to only link position with FloatVec3Property
    virtual void eval(Property* src, Property* dst) throw (VoreenException);

    bool arePropertiesLinkable(const Property* p1, const Property* p2) const;
};

//------------------------------------------------------------------------------------------------------
//
class VRN_CORE_API LinkEvaluatorCameraLookId : public LinkEvaluatorBase {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorCameraLookId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorCameraLookId(); }
    virtual std::string getGuiName() const { return "Camera Look Identity"; }

    ///Special implementation to only link look vector with FloatVec3Property
    virtual void eval(Property* src, Property* dst) throw (VoreenException);

    bool arePropertiesLinkable(const Property* p1, const Property* p2) const;
};

//------------------------------------------------------------------------------------------------------

class VRN_CORE_API LinkEvaluatorCameraFocusId : public LinkEvaluatorBase {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorCameraFocusId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorCameraFocusId(); }
    virtual std::string getGuiName() const { return "Camera Focus Identity"; }

    ///Special implementation to only link focus vector with FloatVec3Property
    virtual void eval(Property* src, Property* dst) throw (VoreenException);

    bool arePropertiesLinkable(const Property* p1, const Property* p2) const;
};

//------------------------------------------------------------------------------------------------------

class VRN_CORE_API LinkEvaluatorCameraFrustumId : public LinkEvaluatorBase {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorCameraFrustumId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorCameraFrustumId(); }
    virtual std::string getGuiName() const { return "Camera Frustum Identity"; }

    ///Special implementation to only link focus vector with FloatVec3Property
    virtual void eval(Property* src, Property* dst) throw (VoreenException);

    bool arePropertiesLinkable(const Property* p1, const Property* p2) const;
};

//-------------------------------------------------------------------------------------------------------

class VRN_CORE_API LinkEvaluatorTransFuncId : public LinkEvaluatorBase {
public:
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorTransFuncId(); }
    virtual std::string getClassName() const  { return "LinkEvaluatorTransFuncId"; }
    virtual std::string getGuiName() const    { return "Identity"; }

    virtual void eval(Property* src, Property* dst) throw (VoreenException);

    bool arePropertiesLinkable(const Property* p1, const Property* p2) const;
};

//-------------------------------------------------------------------------------------------------------

class VRN_CORE_API LinkEvaluatorButtonId : public LinkEvaluatorBase {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorButtonId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorButtonId(); }
    virtual std::string getGuiName() const { return "Button"; }

    ///Special implementation to only link position focus and up vector
    virtual void eval(Property* src, Property* dst) throw (VoreenException);

    bool arePropertiesLinkable(const Property* p1, const Property* p2) const;
};

//-------------------------------------------------------------------------------------------------------

class VRN_CORE_API LinkEvaluatorLightSourceId : public LinkEvaluatorBase {
public:
    virtual std::string getClassName() const { return "LinkEvaluatorLightSourceId"; }
    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorLightSourceId(); }
    virtual std::string getGuiName() const { return "LightSource"; }

    ///Special implementation to make sure light source property widgets are updated
    virtual void eval(Property* src, Property* dst) throw (VoreenException);

    bool arePropertiesLinkable(const Property* p1, const Property* p2) const;
};

} // namespace

#endif // VRN_LINKEVALUATORID_H
