#include <QApplication>
#include "vistaosciloscopio.hpp"
#include <memory>
#include <QSettings>
#include <QSurfaceFormat>
#include <QOpenGLContext>

char* OrgName = "Raul Huertas Inc";
char* AppName = "Visor Osciloscopio";

using namespace std;

int main(int argc, char *argv[])
{




    QApplication a(argc, argv);

    //Preparar OpenGL
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    fmt.setVersion(4, 1);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        #ifdef QT_DEBUG
        qDebug("Requesting 4.1 core context");
        #endif //QT_DEBUG
        fmt.setVersion(4, 1);
        fmt.setProfile(QSurfaceFormat::CoreProfile);
    } else {
        #ifdef QT_DEBUG
        qDebug("Requesting 3.0 context");
        #endif //QT_DEBUG
        fmt.setVersion(3, 0);
    }
    QSurfaceFormat::setDefaultFormat(fmt);


    auto settings = std::make_shared<QSettings>(OrgName, AppName);
    auto osc = std::make_unique<VistaOsciloscopio>(settings);
    osc->showFullScreen();



    return a.exec();
}
