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

#ifndef VRN_SURFACEPLOT_H
#define VRN_SURFACEPLOT_H

#include "plotprocessor.h"

#include "voreen/core/properties/floatproperty.h"
#include "voreen/core/properties/intproperty.h"

#include "../ext/triangle/include/del_interface.hpp"

#include <vector>
#include <list>

namespace voreen {

/*
#ifndef VRN_MODULE_TRIANGLE
// forward declaration if no triangle module available
namespace tpp {
    class Delaunay;
}
#endif
*/

/**
 * This processor is able to create 3D surface plots.
 */
class VRN_CORE_API SurfacePlot : public PlotProcessor {
public:
    SurfacePlot();
    virtual Processor* create() const;

    virtual std::string getClassName() const { return "SurfacePlot";      }
    virtual CodeState getCodeState() const   { return CODE_STATE_TESTING; }

protected:
    virtual void setDescriptions() {
        setDescription("This processor is able to create 3D surfaceplots and heightmaps.");
    }

     virtual void initialize() throw (tgt::Exception);
     virtual void deinitialize() throw (tgt::Exception);

    // inherited methods
    virtual void render();
    virtual void renderData();
    virtual void renderAxes();
    virtual void setPlotStatus();
    virtual void readFromInport();
    virtual void calcDomains();
    virtual void toggleProperties();
    virtual void selectDataFromFunction();

    void domainChanged();
    virtual void generateDelaunay();

    /// clips all voronoi regions to zoomed area
    void clipVoronoiRegionsToZoom();

    /// checks whether vertex v is left of edge e, assuming e is edge of clipping rectangle
    bool insideMeshBounds(const tgt::dvec2& v, const std::pair<tgt::dvec2, tgt::dvec2>& e);

    /// calculates intersection between edge e and edge between vertices p and s
    tgt::dvec2 intersect(const tgt::dvec2& p, const tgt::dvec2& s, const std::pair<tgt::dvec2, tgt::dvec2>& e);

    int omitDelaunayTriangulation_; ///< semaphor to determine if to omit delaunay triangluation even when indexX or indexY have changed
    int currentIndexX_;             ///< column index of current x axis (local variable to notice when according setting in properties changes and delauney triangulation has to be redone)
    int currentIndexY_;             ///< column index of current x axis (local variable to notice when according setting in properties changes and delauney triangulation has to be redone)

    tpp::Delaunay* delaunay_;               ///< pointer to delaunay object which does delaunay triangulation and voronoi diagram generation
    std::vector<int> triangleEdgeIndices_;  ///< vector of edge indices of delaunay triangulation - input format for plot library
    std::vector< std::list< tgt::dvec2 > > voronoiRegions_;  ///< vector of voronoi regions each being a point list in ccw order

    static const std::string loggerCat_;

    GLuint dataList_;         ///< display list of the data
    GLuint pickingList_;      ///< display list of the picking data
};

}   //namespace

#endif // VRN_SURFACEPLOT_H
