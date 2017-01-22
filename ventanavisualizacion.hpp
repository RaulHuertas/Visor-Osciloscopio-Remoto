#ifndef VENTANAVISUALIZACION_H
#define VENTANAVISUALIZACION_H
#include <vector>
#include <cstdint>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include "glchunk.hpp"
#include <QTimer>

class QOpenGLShaderProgram;
class QOpenGLBuffer;
class VentanaVisualizacion : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
Q_OBJECT
public:
    //std::vector<std::uint16_t> muestras;
    std::uint16_t minValue = 0U;
    std::uint16_t maxValue = 65535U;

public:
    VentanaVisualizacion(QWidget* parent = nullptr);
    ~VentanaVisualizacion();

protected:
    virtual void initializeGL();
    virtual void resizeGL( int w, int h );
    virtual void paintGL();

public:
    //vertices para OpenGL
    GLChunk<1, 0, 0, 0, GLushort, GL_UNSIGNED_SHORT> vertices;
private:
    static QOpenGLShaderProgram* cargarShader(
        const QString& archivoVS,
        const QString& archivoGS,
        const QString& archivoFS,
        QObject* parent = nullptr
    );

    QOpenGLShaderProgram* shader = nullptr;

    bool recursosCargados=false;
    int anchoPantalla = 0;
    int altoPantalla = 0;

    QTimer timerAnimacion;
};

#endif // VENTANAVISUALIZACION_H
