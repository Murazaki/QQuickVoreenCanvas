#include <GL/glew.h>

#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtGui/QGuiApplication>

#include <QDebug>

#include "fboinsgrenderer.h"

int main(int argc, char **argv)
{
    int out;

    QGuiApplication app(argc, argv);

    qmlRegisterType<FboInSGRenderer>("SceneGraphRendering", 1, 0, "Renderer");

    QQuickView view;

    view.setSurfaceType(QSurface::OpenGLSurface);

    QSurfaceFormat fmt;
    fmt.setMajorVersion(4);
    fmt.setMinorVersion(2);
    fmt.setProfile(QSurfaceFormat::CoreProfile);

    view.setFormat(fmt);

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///scenegraph/textureinsgnode/main.qml"));
    view.show();

    out = app.exec();

    return out;
}
