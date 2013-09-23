/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <GL/glew.h>

#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtGui/QGuiApplication>

#include "fboinsgrenderer.h"

#ifdef WIN32
#include <windows.h>
#endif

#include <cstdlib>

#include "tgt/shadermanager.h"
#include "tgt/logmanager.h"

#include "voreen/core/voreenapplication.h"
#include "voreen/core/utils/voreenpainter.h"
#include "voreen/core/io/serialization/serialization.h"
#include "voreen/core/network/networkevaluator.h"
#include "voreen/core/network/workspace.h"
#include "voreen/core/network/processornetwork.h"

#include "modules/core/processors/output/canvasrenderer.h"

const std::string description =
    "This is a small program that demonstrates a little of what the Voreen core library can do: \n"
    "We load the standard.vws workspace, which shows a volume rendering of the nucleon dataset \n"
    "that can be rotated and zoomed using the mouse.\n\n"
    "This is the GLUT-version of this sample, there are others in the simple/-folder, like a Qt-version.";

using namespace voreen;

//---------------------------------------------------------------------------

VoreenApplication* app = 0;

NetworkEvaluator* networkEvaluator = 0;
ProcessorNetwork* network = 0;
VoreenPainter* painter = 0;

//---------------------------------------------------------------------------

void initialize() {
    QQuickVoreenCanvas * canvas = FboInSGRenderer::getCanvas();

    Workspace* workspace = new Workspace();
    try {
        workspace->load(VoreenApplication::app()->getResourcePath("/workspaces/standard.vws"));
    }
    catch (SerializationException& e) {
        LERRORC("simple-glut.initialize", "Failed to load standard workspace: " << e.what());
        exit(EXIT_FAILURE);
    }

    // initialize the network evaluator and retrieve CanvasRenderer processors from the loaded network
    networkEvaluator = new NetworkEvaluator();
    network = workspace->getProcessorNetwork();
    std::vector<CanvasRenderer*> canvasRenderer = network->getProcessorsByType<CanvasRenderer>();
    if (canvasRenderer.empty()) {
        LERRORC("simple-glut.initialize", "Loaded standard workspace does not contain a CanvasRenderer");
        exit(EXIT_FAILURE);
    }

    // init painter and connect it to the canvas
    painter = new VoreenPainter(canvas, networkEvaluator, canvasRenderer[0]);
    canvas->setPainter(painter);
    canvasRenderer[0]->setCanvas(canvas);
    // give the network to the network evaluator
    networkEvaluator->setProcessorNetwork(network);
}

void finalize() {
    delete painter;
    painter = 0;
    delete network;
    network = 0;
    delete networkEvaluator;
    networkEvaluator = 0;

    if (app) {
        app->deinitializeGL();
        app->deinitialize();
    }
    delete app;
    app = 0;
}

//void keyPressed(unsigned char key, int /*x*/, int /*y*/) {
//    switch (key) {
//        case '\033': // = ESC
//            finalize();
//            exit(0);
//            break;
//        case '1':
//            glutReshapeWindow(128,128);
//            break;
//        case '2':
//            glutReshapeWindow(256,256);
//            break;
//        case '3':
//            glutReshapeWindow(512,512);
//            break;
//        case '4':
//            glutReshapeWindow(1024, 1024);
//            break;
//    }
//}

int main(int argc, char **argv)
{
    int out;

//    QGuiApplication app(argc, argv);

    VoreenApplication* VoreenApp = new VoreenApplication("VoreenCanvas", "VoreenCanvas", description, argc, argv,
        VoreenApplication::APP_ALL);
    VoreenApp->initialize();

//    qmlRegisterType<FboInSGRenderer>("SceneGraphRendering", 1, 0, "Renderer");

//    QQuickView view;
//    view.setResizeMode(QQuickView::SizeRootObjectToView);
//    view.setSource(QUrl("qrc:///scenegraph/textureinsgnode/main.qml"));
//    view.show();

    VoreenApp->initializeGL();

    initialize();

//    out = app.exec();

    finalize();

    return out;
}
