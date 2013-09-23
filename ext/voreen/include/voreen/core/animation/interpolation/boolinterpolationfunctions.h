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

#ifndef VRN_BOOLINTERPOLATIONFUNCTIONS_H
#define VRN_BOOLINTERPOLATIONFUNCTIONS_H

#include "voreen/core/animation/interpolationfunction.h"

namespace voreen {

#ifdef DLL_TEMPLATE_INST
template class VRN_CORE_API InterpolationFunction<bool>;
#endif

/**
 * This class offers an interpolation function for bool-values. Interpolation: focus on startvalue.
 */
class VRN_CORE_API BoolStartInterpolationFunction : public InterpolationFunction<bool> {
public:
    BoolStartInterpolationFunction();
    virtual std::string getClassName() const { return "BoolStartInterpolationFunction"; }
    InterpolationFunction<bool>* create() const;
    bool interpolate(bool startvalue, bool endvalue, float time) const;

    std::string getGuiName() const;
    std::string getCategory() const;
};

/**
 * This class offers an interpolation function for bool-values. Interpolation: focus on endvalue.
 */
class VRN_CORE_API BoolEndInterpolationFunction : public InterpolationFunction<bool> {
public:
    BoolEndInterpolationFunction();
    virtual std::string getClassName() const { return "BoolEndInterpolationFunction"; }
    InterpolationFunction<bool>* create() const;
    bool interpolate(bool startvalue, bool endvalue, float time) const;

    std::string getGuiName() const;
    std::string getCategory() const;
};

/**
 * This class offers an interpolation function for bool-values. Interpolation: bisection.
 */
class VRN_CORE_API BoolStartEndInterpolationFunction : public InterpolationFunction<bool> {
public:
    BoolStartEndInterpolationFunction();
    virtual std::string getClassName() const { return "BoolStartEndInterpolationFunction"; }
    InterpolationFunction<bool>* create() const;
    bool interpolate(bool startvalue, bool endvalue, float time) const;

    std::string getGuiName() const;
    std::string getCategory() const;
};

} // namespace voreen

#endif
