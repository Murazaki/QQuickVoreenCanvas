#include "qquickvoreencanvas.h"

using namespace tgt;

QQuickVoreenCanvas::QQuickVoreenCanvas(const std::string& title,
                                       const ivec2& size,
                                       const Buffers buffers)
    : GLCanvas(title, size, buffers)
{
}

QQuickVoreenCanvas::~QQuickVoreenCanvas() {}

void QQuickVoreenCanvas::init()
{
    GLCanvas::init();
}

void QQuickVoreenCanvas::render()
{
    GLCanvas::paint();
}

void QQuickVoreenCanvas::repaint() {
//    updateGL();
}

void QQuickVoreenCanvas::update() {
//    QWidget::update();
}

void QQuickVoreenCanvas::swap() {
//    QGLWidget::swapBuffers();
}

void QQuickVoreenCanvas::getGLFocus() {
//    QGLWidget::doneCurrent();
//    QGLWidget::makeCurrent();
}

void QQuickVoreenCanvas::toggleFullScreen() {
//    if (fullscreen_) {
//        fullscreen_ = false;
//        showNormal();
//    }
//    else {
//        showFullScreen();
//        fullscreen_ = !fullscreen_;
//    }
}

QSurfaceFormat QQuickVoreenCanvas::getQSurfaceFormat(const Buffers buffers) {
    QSurfaceFormat::FormatOption stereobuffer =
            (buffers & GLCanvas::STEREO_VIEWING)?QSurfaceFormat::StereoBuffers : (QSurfaceFormat::FormatOption)0;
    QSurfaceFormat::SwapBehavior swapbehavior =
            (buffers & GLCanvas::DOUBLE_BUFFER)?QSurfaceFormat::DoubleBuffer : QSurfaceFormat::DefaultSwapBehavior;


    QSurfaceFormat format = QSurfaceFormat(stereobuffer);
    format.setSwapBehavior(swapbehavior);

    return format;
}
