#ifndef QQUICKVOREENCANVAS_H
#define QQUICKVOREENCANVAS_H

#include "tgt/include/tgt/glcanvas.h"

class QQuickVoreenCanvas : public tgt::GLCanvas
{
public:
    QQuickVoreenCanvas(const std::string& title = "",
                       const tgt::ivec2& size = tgt::ivec2(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT),
                       const Buffers buffers = RGBADD);
    ~QQuickVoreenCanvas();

    void render();

    /// initialize canvas
    virtual void init();

//    /**
//     * Called by the Qt framework once at the beginning, before rendering starts.
//     * This function calls the corresponding GLCanvas method \a initialize.
//     */
//    virtual void initializeGL();

//    /**
//     * This is called by the Qt framework every time the canvas is resized.
//     * This function calls the corresponding GLCanvas method \a sizeChanged.
//     *
//     * @param w The new width of the canvas.
//     * @param h The new height of the canvas.
//     */
//    virtual void resizeGL(int w, int h);

//    /**
//     * Called by Qt if there is a paint event; it uses the \a painter_ to paint() something.
//     */
//    virtual void paintGL();

    /**
     * If you manually want to cause a paint-event, use this function. It will call paintGL()
     * via updateGL(). This will cause immediate repainting.
     */
    virtual void repaint();

    /**
     * If you manually want to cause a paint-event, use this function. It will call QWidget::update()
     * and repaint when entering main loop next time.
     */
    virtual void update();

    /// swap buffers
    virtual void swap();

    /**
     * If we use several GLCanvases, we have to switch the OpenGL context when we switch between
     * canvases; this method sets the context of this canvas as the current one.
     */
    virtual void getGLFocus();
    virtual void toggleFullScreen();
};

#endif // QQUICKVOREENCANVAS_H
