#include "ventanavisualizacion.hpp"
#include "vistaosciloscopio.hpp"
#include <QHostAddress>
#include <QByteArray>
#include <QDebug>

void VistaOsciloscopio::prepararSocket(){
    if(socket!=nullptr){
        socket->close();
    }
    socket = nullptr;
    socket = std::make_unique<QUdpSocket>(this);
    connect(
        socket.get(),
        &QUdpSocket::readyRead,
        this,
        &VistaOsciloscopio::hayDatosLecturaPendientes
    );
    socket->bind(
        QHostAddress(config->ip),
        config->puerto
    );


}

void VistaOsciloscopio::hayDatosLecturaPendientes(){
    if(socket==nullptr){
        return;
    }
    while(socket->hasPendingDatagrams()){
        int numeroDatosALeer = socket->pendingDatagramSize();
        if((numeroDatosALeer%2)!=0){
            QByteArray datosAIgnorar;
            datosAIgnorar.resize(numeroDatosALeer);
            socket->read(datosAIgnorar.data(), numeroDatosALeer);
        }
        auto nMuestras = numeroDatosALeer/2;
        ventana->vertices.resizeForNVertexs(nMuestras);
        QHostAddress sender;
        quint16 senderPort;
        auto valorRetRed = socket->readDatagram(
            (char*)ventana->vertices.vertices.data(),
            numeroDatosALeer,
            &sender, &senderPort
        );
        //update();
        if(valorRetRed<=0){
            #ifdef QT_DEBUG
            qDebug()<<"Error leyendo datos UDP";
            #endif //QT_DEBUG
        }
    }
}
