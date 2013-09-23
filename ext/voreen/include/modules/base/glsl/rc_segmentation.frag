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
#include "modules/mod_sampler3d.frag"
#include "modules/mod_transfunc.frag"

#include "modules/mod_raysetup.frag"

#include "modules/mod_depth.frag"
#include "modules/mod_compositing.frag"
#include "modules/mod_gradients.frag"
#include "modules/mod_shading.frag"

// variables for storing compositing results
vec4 result = vec4(0.0);
vec4 result1 = vec4(0.0);
vec4 result2 = vec4(0.0);

uniform float samplingStepSize_;

// declare entry and exit parameters
uniform sampler2D entryPoints_;                // ray entry points
uniform sampler2D entryPointsDepth_;           // ray entry points depth
uniform TextureParameters entryParameters_;

uniform sampler2D exitPoints_;                 // ray exit points
uniform sampler2D exitPointsDepth_;            // ray exit points depth
uniform TextureParameters exitParameters_;

// declare volumes
uniform VolumeParameters volumeStruct_;
uniform sampler3D volume_;        // volume data set

uniform VolumeParameters segmentationParameters_;
uniform sampler3D segmentation_;  // segmentation data set

#ifndef MOD_APPLY_SEGMENTATION
uniform TransFuncParameters transferFunc_;
uniform TF_SAMPLER_TYPE transferFuncTex_;
#endif

#ifdef MOD_APPLY_SEGMENTATION

uniform sampler2D segmentationTransferFunc_;

vec4 applySegmentationClassification(vec3 sampleVal, vec4 voxel, VolumeParameters segmentationParameters) {

    // Determine segment id and perform transfer function lookup within corresponding segmentation transfer function.
    // The 1D transfer function of a segment is stored in the 2D segmentation tf texture as a 3-row wide stripe which is centered around the row 3*i+1.

    float segmentScaleFactor = 255.0;
    if (segmentationParameters.bitDepth_ == 12)
        segmentScaleFactor = 4095.0;
    else if (segmentationParameters.bitDepth_ == 16)
        segmentScaleFactor = 65535.0;

    float segValue = getVoxel(segmentation_, segmentationParameters, sampleVal).a;
    float segment = segValue * segmentScaleFactor;

    #ifdef GLSL_VERSION_130
        return texture(segmentationTransferFunc_, vec2(voxel.a, (segment*3.0+1.0)/float(SEGMENTATION_TRANSFUNC_HEIGHT)) );
    #else
        return texture2D(segmentationTransferFunc_, vec2(voxel.a, (segment*3.0+1.0)/float(SEGMENTATION_TRANSFUNC_HEIGHT)) );
    #endif
}

#endif


/***
 * Performs the ray traversal
 * returns the final fragment color.
 ***/
void rayTraversal(in vec3 first, in vec3 last, float entryDepth, float exitDepth) {

    // calculate the required ray parameters
    float t     = 0.0;
    float tIncr = 0.0;
    float tEnd  = 1.0;
    float lastIntensity = 0.0f; //used for pre-integrated transfer-functions
    vec3 rayDirection;
    raySetup(first, last, samplingStepSize_, rayDirection, tIncr, tEnd);

    float tDepth = -1.0f;
    bool finished = false;
    WHILE(!finished) {
        vec3 samplePos = first + t * rayDirection;
        vec4 voxel = getVoxel(volume_, volumeStruct_, samplePos);

        #ifdef MOD_APPLY_SEGMENTATION
            // apply segmentation
            vec4 color = applySegmentationClassification(samplePos, voxel, segmentationParameters_);
        #else
            // apply classification
            vec4 color = RC_APPLY_CLASSIFICATION(transferFunc_, transferFuncTex_, voxel, lastIntensity);
        #endif

        // if opacity greater zero, apply compositing
        if (color.a > 0.0) {
            // calculate gradients
            if(t == 0.0)
                voxel.xyz = fixClipBorderGradient(samplePos, rayDirection, entryPoints_, entryParameters_);
            else
                voxel.xyz = CALC_GRADIENT(volume_, volumeStruct_, samplePos);

            // apply standard shading
            color.rgb = APPLY_SHADING(voxel.xyz, texToPhysical(samplePos, volumeStruct_), volumeStruct_.lightPositionPhysical_, volumeStruct_.cameraPositionPhysical_, color.rgb, color.rgb, color.rgb);

            result = RC_APPLY_COMPOSITING(result, color, samplePos, voxel.xyz, t, samplingStepSize_, tDepth);
            result1 = RC_APPLY_COMPOSITING_1(result1, color, samplePos, voxel.xyz, t, samplingStepSize_, tDepth);
            result2 = RC_APPLY_COMPOSITING_2(result2, color, samplePos, voxel.xyz, t, samplingStepSize_, tDepth);
        }
        lastIntensity = voxel.a;

        finished = earlyRayTermination(result.a, EARLY_RAY_TERMINATION_OPACITY);
        t += tIncr;
        finished = finished || (t > tEnd);
    } END_WHILE
    gl_FragDepth = getDepthValue(tDepth, tEnd, entryDepth, exitDepth);
}

/***
 * The main method.
 ***/
void main() {
    // fetch entry/exit points
    vec2 p = gl_FragCoord.xy * screenDimRCP_;
    vec3 frontPos = textureLookup2Dnormalized(entryPoints_, entryParameters_, p).rgb;
    vec3 backPos = textureLookup2Dnormalized(exitPoints_, exitParameters_, p).rgb;
    float entryDepth = textureLookup2Dnormalized(entryPointsDepth_, entryParameters_, p).z;
    float exitDepth = textureLookup2Dnormalized(exitPointsDepth_, exitParameters_, p).z;

    // determine whether the ray has to be casted
    if (frontPos == backPos)
        // background needs no raycasting
        discard;
    else
        // fragCoords are lying inside the bounding box
        rayTraversal(frontPos, backPos, entryDepth, exitDepth);

    #ifdef OP0
        FragData0 = result;
    #endif
    #ifdef OP1
        FragData1 = result1;
    #endif
    #ifdef OP2
        FragData2 = result2;
    #endif
}
