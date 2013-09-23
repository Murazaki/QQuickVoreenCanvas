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

#ifndef VRN_VVDVOLUMEREADER_H
#define VRN_VVDVOLUMEREADER_H

#include "voreen/core/io/volumereader.h"
#include "voreen/core/voreencoreapi.h"

namespace voreen {

class VRN_CORE_API VvdVolumeReader : public VolumeReader {
public:
    VvdVolumeReader(ProgressBar* progress = 0);
    virtual VolumeReader* create(ProgressBar* progress = 0) const;

    virtual std::string getClassName() const   { return "VvdVolumeReader"; }
    virtual std::string getFormatDescription() const { return "Voreen Volume Data (new Voreen format)"; }

    virtual VolumeList* read(const std::string& url)
        throw (tgt::FileException, std::bad_alloc);

private:
    static const std::string loggerCat_;
};

} // namespace voreen

#endif
