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

uniform sampler2D colorTex0_;
uniform sampler2D depthTex0_;
uniform TextureParameters textureParameters0_;
uniform sampler2D colorTex1_;
uniform sampler2D depthTex1_;
uniform TextureParameters textureParameters1_;

void main() {
    vec2 p = gl_FragCoord.xy;
    vec4 color0 = textureLookup2Dnormalized(colorTex0_, textureParameters0_, p*screenDimRCP_);
    float depth0 = textureLookup2Dnormalized(depthTex0_, textureParameters0_, p*screenDimRCP_).z;
    vec4 color1 = textureLookup2Dnormalized(colorTex1_, textureParameters1_, p*screenDimRCP_);
    float depth1 = textureLookup2Dnormalized(depthTex1_, textureParameters1_, p*screenDimRCP_).z;

    vec4 fragColor;
    fragColor.rgb = color1.rgb * color1.a + color0.rgb * color0.a * (1.0 - color1.a);
    // If working with soft-rendered fonts, this version should be preferred if possible, otherwise the blending leads to artefacts
    //fragColor.rgb = color1.a > 0.0 ? color1.rgb : color0.rgb;
    fragColor.a = color1.a + color0.a * (1.0 - color1.a);
    float fragDepth = min(depth0, depth1);

    FragData0 = fragColor;
    gl_FragDepth = fragDepth;
}
