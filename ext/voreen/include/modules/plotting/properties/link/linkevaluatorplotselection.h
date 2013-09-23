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

#ifndef VRN_LINKEVALUATORPLOTSELECTION_H
#define VRN_LINKEVALUATORPLOTSELECTION_H

#include "voreen/core/properties/link/linkevaluatorbase.h"

namespace voreen {

/**
 * This is a LinkEvaluator only for PlotSelectionProperty. It links only the selections and not the flags specifying how the selections are used.
 */
class VRN_CORE_API LinkEvaluatorPlotSelection : public LinkEvaluatorBase {
public:

    virtual void eval(Property* src, Property* dest) throw (VoreenException);

    virtual std::string getGuiName() const { return "Plot Selection"; }

    virtual std::string getClassName() const { return "LinkEvaluatorPlotSelection"; }

    virtual bool arePropertiesLinkable(const Property* p1, const Property* p2) const;

    virtual LinkEvaluatorBase* create() const { return new LinkEvaluatorPlotSelection(); }
};

} // namespace

#endif // VRN_LINKEVALUATORPLOTSELECTION_H
