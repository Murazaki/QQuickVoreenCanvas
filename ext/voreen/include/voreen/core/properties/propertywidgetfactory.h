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

#ifndef VRN_PROPERTYWIDGETFACTORY_H
#define VRN_PROPERTYWIDGETFACTORY_H

namespace voreen {

class Property;
class PropertyWidget;

/**
 * Interface for factories that create GUI representations for properties.
 *
 * If a module contains custom properties, it is also expected to provide
 * a suitable PropertyWidgetFactory for these properties.
 *
 * @see VoreenModule::registerPropertyWidgetFactory
 */
class PropertyWidgetFactory {
public:
    virtual ~PropertyWidgetFactory() {}

    virtual PropertyWidget* createWidget(Property*) const = 0;

    virtual bool lazyInstantiation(Property*) const {
        return true;
    }
};

} // namespace

#endif // VRN_PROPERTYWIDGETFACTORY_H
