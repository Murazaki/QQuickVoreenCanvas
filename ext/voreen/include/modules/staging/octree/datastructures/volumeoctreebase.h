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

#ifndef VRN_VOLUMEOCTREEBASE_H
#define VRN_VOLUMEOCTREEBASE_H

#include "voreen/core/voreencoreapi.h"
#include "voreen/core/utils/exception.h"
#include "voreen/core/datastructures/meta/realworldmappingmetadata.h"
#include "voreen/core/voreenobject.h"
#include "voreen/core/datastructures/volume/volumerepresentation.h"

#include "voreen/core/datastructures/volume/volumeslicehelper.h"

#include "tgt/vector.h"
#include "tgt/matrix.h"
#include "tgt/types.h"

#include <vector>
#include <string>

namespace voreen {

class VolumeOctreeBase;
class Volume;
class VolumeBase;

/**
 * Base class for octree nodes that represent a certain region of a volume.
 * Each node has up to eight child nodes and stores one average, min, and max
 * value per channel.
 *
 * In addition, each node is associated with one brick that stores
 * the actual volume data of the represented volume region. All nodes of a
 * single octree have the same cubic power-of-two dimensions. The brick
 * voxels are stored in a uint16_t buffer in ZYX order, like voxels in a volume.
 * In case of a multi-channel octree, the channel bricks are stored consecutively
 * in the brick buffer. If the octree is optimized, bricks of homogeneous nodes
 * are discarded.
 *
 * @note In order to reduce the memory footprint of the tree structure,
 *  the nodes do not store data that is constant or can be obtained
 *  during tree traversal, such as the brick dimensions or the
 *  LLF and URB of the represented region. This information
 *  is provided by the octree.
 */
class VRN_CORE_API VolumeOctreeNode {

    friend class VolumeOctreeBase;

public:
    virtual ~VolumeOctreeNode();

    virtual size_t getNumChannels() const = 0;
    virtual uint16_t getAvgValue(size_t channel = 0) const = 0;
    virtual uint16_t getMinValue(size_t channel = 0) const = 0;
    virtual uint16_t getMaxValue(size_t channel = 0) const = 0;

    bool hasBrick() const;
    uint64_t getBrickAddress() const;

    bool isLeaf() const;
    bool isHomogeneous() const;

    /// Returns the actual depth of the sub-tree below the node.
    size_t getDepth() const;
    /// Returns the number of nodes of the sub-tree below the node.
    size_t getNodeCount() const;
    /// Returns the number of bricks the sub-tree below the node contains.
    size_t getNumBricks() const;

    // serialization (do not call directly)
    virtual void serializeContentToBinaryBuffer(char* buffer) const;
    virtual void deserializeContentFromBinaryBuffer(const char* buffer);
    virtual size_t getContentSize() const { return sizeof(uint64_t); }  ///< brickAddress

    VolumeOctreeNode* children_[8];     ///< The node's child nodes in ZYX order (like voxels in a volume).

protected:
    /// Default constructor used for serialization only.
    VolumeOctreeNode();

    /**
      * Byte offset of the corresponding brick in the virtual memory, or UINT64_MAX if node has no brick.
      * Use VolumeOctree::getNodeBrick(VolumeOctreeNode*) to obtain a pointer to the brick buffer.
      */
    uint64_t brickAddress_;
};

//-------------------------------------------------------------------------------------------------

/**
 * Base class for octrees that are used for handling single- or multi-channel volume data, which does not fit
 * into the GPU memory and possibly not even into the main memory.
 *
 * The octree data structure consists of two parts:
 *   - a spatial tree whose nodes represent certain regions of the volume and only store derived information,
 *     such as average and min/max values (@see VolumeOctreeNode)
 *   - a pool of bricks that are associated with the tree nodes and contain the actually volume data
 *     a different resolutions. Each tree node usually references exactly one brick via a virtual memory address,
 *     Homogeneous nodes, however, might not have a brick. All bricks of a single octree have the same cubic dimension.
 *     The brick pool may either be hold in the CPU RAM or managed on the disk (@see OctreeBrickPoolManagerBase).
 *
 * The octree can be used in several ways:
 *   - as a mipmap that allows to extract the entire volume or an axis-aligned slice at a desired resolution.
 *   - by retrieving an octree node that encloses a certain sampling point at a desired resolution.
 *   - by traversing the octree from the root node (mainly for renderers).
 *
 * Internally the octree has cubic power-of-two dimensions, even for NPOT volumes. However, all node access
 * functions expect sampling/voxel positions in normalized coordinates with respect to the dimensions
 * of the represented volume.
 */
class VRN_CORE_API VolumeOctreeBase : public VoreenSerializableObject, public VolumeRepresentation {

public:
    virtual ~VolumeOctreeBase() {}

    /// Returns the voxel format of the volume/octree as string (e.g., "uint16" or "Vector3(uint16t)", @see VolumeFactory).
    virtual std::string getFormat() const;

    /// Returns the base data type.
    virtual std::string getBaseType() const;

    /// Returns the dimensions of the volume(s) the octree has been constructed from (same as getDimensions()).
    tgt::svec3 getVolumeDim() const;

    /// Returns the number of channels stored in each volume/octree voxel.
    virtual size_t getNumChannels() const;

    /// Returns the number of bytes of one volume/octree voxel.
    virtual size_t getBytesPerVoxel() const;

    /// Returns the cubic power-of-two dimensions of the octree (octreeDim >= volumeDim).
    tgt::svec3 getOctreeDim() const;

    /// Returns the dimensions of one brick. Must be cubic and power-of-two.
    tgt::svec3 getBrickDim() const;

    /// Helper function returning the number of voxel per brick and channel, i.e. hmul(brickDim).
    size_t getNumVoxelsPerBrick() const;

    /// Helper function returning the memory size of brick in bytes, i.e. getNumVoxelsPerBrick()*getBytesPerVoxel()*getNumChannels().
    size_t getBrickMemorySize() const;

    /**
     * Returns the theoretical depth of an complete octree with the given volume and brick dimensions.
     * Note that the actual depth of the optimized octree might be lower.
     *
     * @see getActualTreeDepth
     */
    size_t getNumLevels() const;


    /// Returns the actual depth of the optimized octree.
    virtual size_t getActualTreeDepth() const = 0;

    /// Returns the octree's total number of nodes.
    virtual size_t getNumNodes() const = 0;

    /// Returns the number of node bricks stored by the octree. May be lower but not higher than the node count.
    virtual size_t getNumBricks() const = 0;

    /// Returns the amount of memory in bytes that has been allocated for the brick pool.
    virtual uint64_t getBrickPoolMemoryAllocated() const = 0;

    /// Returns the amount of memory in bytes that is actually used for storing the node bricks.
    virtual uint64_t getBrickPoolMemoryUsed() const = 0;

    /// Returns a multi-line string containing the major properties of the octree.
    virtual std::string getDescription() const = 0;


    /// Returns the tree's root node, i.e,. the node that represents the entire volume at the coarsest resolution.
    virtual const VolumeOctreeNode* getRootNode() const = 0;

    /**
     * Returns the node containing the passed coordinates at the specified level.
     *
     * @param point point in normalized (texture) coordinates for which the node is to be retrieved.
     *      The coordinates are normalized with respect to the volume's dimensions (not octree dimensions),
     *      i.e., (1,1,1) refers to the volume's upper-right-back.
     * @param level level of the node to be retrieved, with level 0 being the level with the highest (full) resolution.
     *      This is an in/out parameter that will hold the actual level of the returned node after the function call.
     * @param voxelLLF Out parameter returning the lower-left-front of the returned node in voxel coordinates.
     * @param voxelURB Out parameter returning the upper-right-back of the returned node in voxel coordinates.
     * @param normLLF Out parameter returning the lower-left-front of the returned node in normalized (texture) coordinates.
     * @param normURB Out parameter returning the upper-right-back of the returned node in normalized (texture) coordinates.
     *
     * @return the octree node
     */
    virtual const VolumeOctreeNode* getNode(const tgt::vec3& point, size_t& level,
        tgt::svec3& voxelLLF, tgt::svec3& voxelURB, tgt::vec3& normLLF, tgt::vec3& normURB) const = 0;

    /**
     * Returns a pointer to the brick buffer of the passed octree node.
     * If the passed node does not have a brick, the null pointer is returned.
     *
     * @param node The node whose brick buffer is to be returned. Must not be null.
     *
     * @throws VoreenException If the brick could not be loaded into RAM.
     */
    virtual const uint16_t* getNodeBrick(const VolumeOctreeNode* node) const
        throw (VoreenException) = 0;

    /**
     * Releases the brick of the passed node in order to indicate that the brick
     * is not used right now and can therefore be removed from the RAM.
     *
     * It is strongly recommended to release bricks as soon as possible!
     *
     * @param node the node, whose brick will be released
     */
    virtual void releaseNodeBrick(const VolumeOctreeNode* node) const = 0;

    /**
     * Returns a RAM volume composed from the octree nodes at the specified mipmap level.
     * The caller is responsible for deleting the returned object.
     *
     * @param level the mipmap level to create, with level 0 being the level with the highest (full) resolution.
     *      The resulting volume dimension is: VolumeDimension / (1 << level)
     * @param channel the channel to extract
     *
     * @return A single-channel RAM volume storing the selected channel.
     *      Its data type equals the data type of the octree.
     *
     * @throw VoreenException If the volume could not be created, usually due to insufficient RAM.
     */
    virtual VolumeRAM* createVolume(size_t level = 0, size_t channel = 0) const
        throw (VoreenException) = 0;

    /**
     * Returns an axis-aligned single-channel slice composed from a selectable octree level.
     * The caller is responsible for deleting the returned object.
     *
     * @param sliceAlignment Alignment of the slice to create
     * @param sliceIndex slice number of the slice to create. Must be within range [0;VolumeDim(AlignmentAxis)-1].
     * @param level mipmap level at which the slice should be created, with level 0 being the level with the
     *      highest (full) resolution. The resulting slice dimension is: VolumeSliceDimension / (1 << level)
     * @param channel Volume channel of the slice to create.
     *
     * @return A single-channel RAM volume storing the selected slice and channel.
     *      Its data type equals the data type of the octree.
     *
     * @throw VoreenException If the slice could not be created
     */
    virtual VolumeRAM* createSlice(SliceAlignment sliceAlignment, size_t sliceIndex, size_t level, size_t channel = 0) const
        throw (VoreenException) = 0;

    /// Logs the string retrieved from getDescription(), one log entry per line.
    void logDescription() const;

    /// @see Serializer::serialize
    virtual void serialize(XmlSerializer& s) const;

    /// @see Deserializer::deserialize
    virtual void deserialize(XmlDeserializer& s);

    /// Returns the number of nodes of a complete octree with the specified depth.
    static size_t getCompleteTreeNodeCount(size_t treeDepth);

protected:
    /**
     * @param brickDim Dimensions of one brick. Must be cubic and power-of-two.
     * @param volumeDim Volume dimensions. Must be larger than the brick dimensions.
     * @param numChannels Number of channels per voxel. Must be between 1 and 4.
     */
    VolumeOctreeBase(const tgt::svec3& brickDim, const tgt::svec3& volumeDim, size_t numChannels) throw (std::exception);
    VolumeOctreeBase(); ///< default constructor for serialization only
    
    /// Creates an empty octree node without brick. All avg/min/max values are set to 0.
    static VolumeOctreeNode* createNode(size_t numChannels);

    /**
     * Creates an octree node without a brick and with the passed avg/min/max values. The passed arrays must store one
     * value per channel each. All values are copied.
     */
    static VolumeOctreeNode* createNode(size_t numChannels, uint16_t* avgValues, uint16_t* minValues, uint16_t* maxValues);

    /// Creates an octree node with a brick and the passed avg/min/max values.
    static VolumeOctreeNode* createNode(size_t numChannels, uint16_t* avgValues, uint16_t* minValues, uint16_t* maxValues,
                                        uint64_t brickAdress);

    /// Creates an octree node with a brick, the passed avg/min/max values and the passed eight child nodes.
    static VolumeOctreeNode* createNode(size_t numChannels, uint16_t* avgValues, uint16_t* minValues, uint16_t* maxValues,
                                        uint64_t brickAddress, VolumeOctreeNode* children[8]);

    static const std::string loggerCat_;

private:
    size_t numLevels_;      ///< theoretical tree depth
    size_t numChannels_;    ///< number of channels per voxel
    size_t bytesPerVoxel_;  ///< number of bytes per voxel and channel

    tgt::svec3 octreeDim_;  ///< cubic, power-of-two dimensions of the octree
    tgt::svec3 brickDim_;   ///< cubic, power-of-two dimensions of one brick
};

} // namespace

#endif
