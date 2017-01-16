#include "ventanavisualizacion.hpp"
#include <QTime>
#include <QDebug>
#include <QOpenGLShaderProgram>
#include <cstring>


VentanaVisualizacion::VentanaVisualizacion(QWidget* parent)
    :QOpenGLWidget(parent)
{

    qsrand(QTime::currentTime().msec());

    const int numeroDatosPrueba = 1024;
    vertices.reserveForAtLeastNVertexs( numeroDatosPrueba );


    for(auto& muestra: vertices.vertices){
        muestra = qrand()%65536U;
    }
    timerAnimacion.setInterval(16);
    timerAnimacion.setSingleShot(false);
    connect(
        &timerAnimacion,
        SIGNAL(timeout()),
        this,
        SLOT(update())
    );
    timerAnimacion.start();

}

QOpenGLShaderProgram* VentanaVisualizacion::cargarShader(
    const QString &archivoVS,
    const QString &archivoGS,
    const QString &archivoFS,
    QObject* parent
){
    auto shader = new QOpenGLShaderProgram(parent);
    bool resultA = shader->addShaderFromSourceFile( QOpenGLShader::Vertex, archivoVS );
    if(!resultA){
        qWarning() << shader->log();
        return nullptr;
    }
    bool resultB = shader->addShaderFromSourceFile( QOpenGLShader::Geometry, archivoGS );
    if(!resultB){
        qWarning() << shader->log();
        return nullptr;
    }
    bool resultC = shader->addShaderFromSourceFile( QOpenGLShader::Fragment, archivoFS );
    if(!resultC){
        qWarning() << shader->log();
        return nullptr;
    }
    bool resultD = shader->link();
    if(!resultD){
        qWarning() << shader->log();
        return nullptr;
    }

    return shader;
}

void VentanaVisualizacion::initializeGL(){
    initializeOpenGLFunctions();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
    qDebug() << "Widget OpenGl: " << format().majorVersion() << "." << format().minorVersion();
    qDebug() << "Context valid: " << context()->isValid();
    qDebug() << "Really used OpenGl: " << context()->format().majorVersion() << "." << context()->format().minorVersion();
    qDebug() << "OpenGl information: VENDOR:       " << (const char*)glGetString(GL_VENDOR);
    qDebug() << "                    RENDERDER:    " << (const char*)glGetString(GL_RENDERER);
    qDebug() << "                    VERSION:      " << (const char*)glGetString(GL_VERSION);
    qDebug() << "                    GLSL VERSION: " << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
    shader = cargarShader("scope.vs", "scope.gs", "scope.fs", this);
    if(shader==nullptr){
        return;
    }
    //cargar las vertices de muestra
    vertices.initGL(*this);
    vertices.addIndexesVBOs(1, *this);

    #ifdef QT_DEBUG
    auto glErroCode = glGetError();
    if(glErroCode!=GL_NO_ERROR){
        qDebug("error opengl cargando las muestras");
        return;
    }
    #endif //QT_DEBUG
//    std::memcpy(
//        vertices.vertices.data(),
//        muestras.data(),
//        muestras.size()*sizeof(GLushort)
//    );

    shader->bind();
    shader->setAttributeBuffer( "vertex", GL_UNSIGNED_SHORT, 0, 1 );
    shader->enableAttributeArray( "vertex" );


    recursosCargados = true;
}

void VentanaVisualizacion::paintGL(){
    //Revisar que se hayan cargado de forma correcta los recurss
    if(!recursosCargados){
        return;
    }
    //realizar dibujo


    glViewport( 0, 0, anchoPantalla, altoPantalla );
    shader->bind();
    vertices.updateVertexData(*this);
    glBindVertexArray(vertices.objecto_VBOArray);
    vertices.setVertexPointer(*this,0);
    glDrawArraysInstanced(
        GL_POINTS,
        0,
        vertices.vertices.size(),
        1
    );
    #ifdef QT_DEBUG
    auto glErroCode = glGetError();
    if(glErroCode!=GL_NO_ERROR){
        qDebug("error opengl dibujo");
        return;
    }
    #endif //QT_DEBUG

}

void VentanaVisualizacion::resizeGL(int w, int h){
    auto dpiFactor = this->devicePixelRatioF();
    anchoPantalla = w*dpiFactor;
    altoPantalla = h*dpiFactor;
}
