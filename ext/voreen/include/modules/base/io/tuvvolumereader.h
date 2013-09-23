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

#ifndef VRN_TUVVOLUMEREADER_H
#define VRN_TUVVOLUMEREADER_H

#include "voreen/core/io/volumereader.h"

#include "tgt/vector.h"

namespace voreen {

/**
 * This is a reader for the dat files provided by TU Vienna.
 * To avoid confusion the file extension of the file to be read
 * has to be renamed from '.dat' to '.tuv'.
 *
 * @see http://www.cg.tuwien.ac.at/research/datasets/
 */
class VRN_CORE_API TUVVolumeReader : public VolumeReader {
public:
    TUVVolumeReader() {
         extensions_.push_back("tuv");
    }

    virtual std::string getClassName() const { return "TUVVolumeReader"; }
    virtual std::string getFormatDescription() const { return "TU Vienna dat format"; }

    virtual VolumeReader* create(ProgressBar* progress = 0) const;

    virtual VolumeList* read(const std::string& url)
        throw (tgt::CorruptedFileException, tgt::IOException, std::bad_alloc);

private:
    static const std::string loggerCat_;
};

} // namespace voreen

#endif // VRN_TUVVOLUMEREADER_H
