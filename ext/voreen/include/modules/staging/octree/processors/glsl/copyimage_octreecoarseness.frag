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

uniform sampler2D colorTex_;
uniform TextureParameters texParams_;

#ifndef NO_DEPTH_TEX
uniform sampler2D depthTex_;

uniform sampler2D depthTexEntry_; //< full resolution
uniform sampler2D depthTexExit_;
uniform TextureParameters texParamsEEP_;
#endif

void main() {
    vec2 fragCoord = gl_FragCoord.xy * screenDimRCP_;
    vec4 fragColor = textureLookup2Dnormalized(colorTex_, texParams_, fragCoord);
    FragData0 = fragColor;

#ifndef NO_DEPTH_TEX
    // ray parameter t of first-hit-point, i.e. depthRay=0.0 => entrypoint, depthRay=1.0 => exitpoint
    float depthRay = textureLookup2Dnormalized(depthTex_, texParams_, fragCoord).z;

    // entry/exit point depth values
    float depthEntry = textureLookup2Dnormalized(depthTexEntry_, texParamsEEP_, fragCoord).z;
    float depthExit = textureLookup2Dnormalized(depthTexExit_, texParamsEEP_, fragCoord).z;

    // scale ray depth value linearly between entry/exit depth values
    if (depthRay < 1.0) {
        gl_FragDepth = depthEntry + depthRay*(depthExit-depthEntry);
    }
    else {
        gl_FragDepth = 1.0;
    }
#endif
}
