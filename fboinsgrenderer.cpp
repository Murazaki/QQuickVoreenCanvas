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

#include "fboinsgrenderer.h"

#include <QOpenGLFramebufferObject>
#include <QtQuick/QQuickWindow>
#include <QtQuick/QSGSimpleTextureNode>
#include <QQuickItem>

#include <cstdlib>

#include "tgt/texture.h"
#include "voreen/core/utils/voreenpainter.h"
#include "modules/core/processors/output/canvasrenderer.h"

#include "qquickvoreencanvas.h"

using namespace voreen;

std::vector<CanvasRenderer*> canvasRenderer;

class TextureNode : public QObject, public QSGSimpleTextureNode
{
    Q_OBJECT

public:
    TextureNode(QQuickWindow *window, QQuickVoreenCanvas* canvas, NetworkEvaluator* networkEvaluator, ProcessorNetwork* network, VoreenPainter* painter, std::vector<CanvasRenderer*> canvasRenderer)
        : m_fbo(0)
        , m_texture(0)
        , m_window(window)
        , m_canvas(canvas)
        , m_networkEvaluator(networkEvaluator)
        , m_network(network)
        , m_painter(painter)
        , m_canvasRenderer(canvasRenderer)
    {
//        connect(m_window, SIGNAL(beforeRendering()), this, SLOT(renderFBO()));
    }

    ~TextureNode()
    {
        delete m_texture;
    }

    QQuickVoreenCanvas * getCanvas() {
        return m_canvas;
    }

    void setCanvas(QQuickVoreenCanvas * canvas) {
        this->m_canvas = canvas;
    }

public slots:
    void renderFBO()
    {
        QSize size = rect().size().toSize();

        if (!m_fbo) {
            QOpenGLFramebufferObjectFormat format;
            format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
            m_fbo = new QOpenGLFramebufferObject(size, format);
            m_texture = m_window->createTextureFromId(m_fbo->texture(), size);
            setTexture(m_texture);
        }

        m_fbo->bind();

        if(m_canvas->getSize() != tgt::ivec2(size.width(),size.height()))
            m_canvas->sizeChanged(tgt::ivec2(size.width(),size.height()));

        m_canvas->render();

        m_fbo->bindDefault();

        m_window->update();
    }

private:
    QOpenGLFramebufferObject *m_fbo;
    QSGTexture *m_texture;
    QQuickWindow *m_window;

    QQuickVoreenCanvas *m_canvas;

    NetworkEvaluator* m_networkEvaluator;
    ProcessorNetwork* m_network;
    VoreenPainter* m_painter;
    std::vector<CanvasRenderer*> m_canvasRenderer;
};

FboInSGRenderer::FboInSGRenderer()
    : m_canvas(0)
    , m_app(0)
    , m_networkEvaluator(0)
    , m_network(0)
    , m_painter(0)
{
    setFlag(ItemHasContents, true);

    m_app = new VoreenApplicationQt5("VoreenCanvas", "VoreenCanvas", "Voreen in QML", 0, 0,
        VoreenApplication::APP_ALL);
    m_app->initialize();

    m_canvas = new QQuickVoreenCanvas("",tgt::ivec2(boundingRect().width(),boundingRect().height()));
    m_canvas->init();

    if(!m_app->isInitializedGL())
        m_app->initializeGL();

    Workspace* workspace = new Workspace();
    try {
        workspace->load(m_app->getResourcePath("/workspaces/standard.vws"));
    }
    catch (SerializationException& e) {
        LERRORC("simple-glut.initialize", "Failed to load standard workspace: " << e.what());
        exit(EXIT_FAILURE);
    }

    m_networkEvaluator = new NetworkEvaluator();
    m_network = workspace->getProcessorNetwork();
    m_canvasRenderer = m_network->getProcessorsByType<CanvasRenderer>();
    if (m_canvasRenderer.empty()) {
        LERRORC("simple-glut.initialize", "Loaded standard workspace does not contain a CanvasRenderer");
        exit(EXIT_FAILURE);
    }

    // init painter and connect it to the canvas
    m_painter = new VoreenPainter(m_canvas, m_networkEvaluator, m_canvasRenderer[0]);
    m_canvas->setPainter(m_painter);
    m_canvasRenderer[0]->setCanvas(m_canvas);

    // give the network to the network evaluator
    m_networkEvaluator->setProcessorNetwork(m_network);
}

FboInSGRenderer::~FboInSGRenderer()
{
    delete m_canvas;
    delete m_painter;
    m_painter = 0;
    delete m_network;
    m_network = 0;
    delete m_networkEvaluator;
    m_networkEvaluator = 0;

    if (m_app) {
        m_app->deinitializeGL();
        m_app->deinitialize();
    }
    delete m_app;
    m_app = 0;
}


QSGNode *FboInSGRenderer::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{

    // Don't bother with resize and such, just recreate the node from scratch
    // when geometry changes.
    if (oldNode)
        delete oldNode;

    TextureNode * Node = new TextureNode(window(), m_canvas, m_networkEvaluator, m_network, m_painter, m_canvasRenderer);

    Node->setRect(boundingRect());
    Node->renderFBO();

    return Node;
}


QQuickVoreenCanvas * FboInSGRenderer::getCanvas() {
    return m_canvas;
}

void FboInSGRenderer::setCanvas(QQuickVoreenCanvas * canvas) {
    this->m_canvas = canvas;
}

#include "fboinsgrenderer.moc"
