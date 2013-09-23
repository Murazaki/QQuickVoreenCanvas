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

#ifndef VRN_PLOTDATAWIDGET_H
#define VRN_PLOTDATAWIDGET_H

#include "plotdatasimpletablemodel.h"

namespace voreen {

class PlotData;
class PlotDataSimpleTableModel;
class PlotDataProperty;
class ExtendedTable;
/**
 * \brief Qt widget granting const access to the PlotData object of a PlotDataProperty.
 *
 * PlotData content will be printed as is in a QTableView.
 **/
class PlotDataWidget : public QWidget {
    Q_OBJECT
public:

    PlotDataWidget(PlotDataProperty* prop, QWidget* parent = 0);
    ~PlotDataWidget();

    void updateFromPlotData();

public slots:
    virtual void createWidgets();

private:
    PlotDataProperty* property_;                ///< property holding the PLotData to show

    PlotDataSimpleTableModel* proxyModel;   ///< proxy model of the QTableView
    ExtendedTable* table_;                  ///< extende QTableView widget which shows the data in data_

};

} // namespace voreen

#endif //VRN_PLOTDATAWIDGET_H
