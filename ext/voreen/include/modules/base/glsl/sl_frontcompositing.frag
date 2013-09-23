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

#include "modules/mod_sampler2d.frag"

uniform sampler2D previousRes_;
uniform TextureParameters previousResParams_;
uniform sampler2D currentSlice_;
uniform TextureParameters currentSliceParams_;

/***
 * The main method.
 ***/
void main() {

    vec2 p = gl_FragCoord.xy * screenDimRCP_;
    vec4 previousRes = textureLookup2Dnormalized(previousRes_, previousResParams_, p);
    vec4 currentRes = textureLookup2Dnormalized(currentSlice_, currentSliceParams_, p);

    vec4 result;
    result.rgb = previousRes.rgb + (1.0-previousRes.a) * currentRes.a*currentRes.rgb;
    result.a = previousRes.a + (1.0-previousRes.a) * currentRes.a;
    FragData0 = result;
}
