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

#ifndef VRN_STATISTICS_H
#define VRN_STATISTICS_H

#include "voreen/core/voreencoreapi.h"
#include <vector>
#include <cstddef>
#include <cmath>

namespace voreen {

/// Computes some statistics on a set of float values.
class VRN_CORE_API Statistics {
public:
    /// Enable collectSamples to calculate median, q1, q3 later on.
    Statistics(bool collectSamples);
    void reset();

    void addSample(float v);

    float getMin() const;
    float getMax() const;
    float getSum() const;
    float getMean() const;
    size_t getNumSamples() const;

    float getVariance() const;
    // Algorithm by B. P. Welford (1962), presented in Donald Knuth's Art of Computer Programming, Vol 2, page 232, 3rd edition
    float getStdDev() const;
    float getRelStdDev() const;

    // collectSamples needs to be true!
    float getMedian() const;
    // collectSamples needs to be true!
    float getQ1() const;
    // collectSamples needs to be true!
    float getQ3() const;

private:
    float min_;
    float max_;

    // for std dev:
    double runningMean_;
    double m2_;
    double sum_;

    bool collectSamples_;
    mutable std::vector<float> samples_; //used for median
    size_t numSamples_;
};


} // namespace

#endif
