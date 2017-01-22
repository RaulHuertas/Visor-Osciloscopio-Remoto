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

constexpr int nMuestrasAMostrar = 512;

void VistaOsciloscopio::hayDatosLecturaPendientes(){
    if(socket==nullptr){
        return;
    }
    bool seDebeActualizar = debeActualizar();
    while(socket->hasPendingDatagrams()){
        int numeroDatosALeer = socket->pendingDatagramSize();
        //Ignorar apquetses que no tienen la longitud adecuada
        if(
            ((numeroDatosALeer%2)!=0) ||
            (!seDebeActualizar)
        ){
            if(bufferLectura.size()<numeroDatosALeer){
                bufferLectura.resize(numeroDatosALeer);
            }
            //socket->readDatagram(nullptr, numeroDatosALeer, nullptr, nullptr);
            socket->readDatagram((char*)bufferLectura.data(), numeroDatosALeer, nullptr, nullptr);
            //socket->readDatagram((char*)bufferLectura.data(), 0, nullptr, nullptr);
            muestrasCapturadas = 0;
            continue;
        }
        auto nMuestrasRecibidas = (numeroDatosALeer-4)/2;
        //QHostAddress sender;
        //quint16 senderPort;
//        auto valorRetRed = socket->readDatagram(
//            (char*)bufferLectura.data(),
//            numeroDatosALeer,
//            &sender, &senderPort
//        );
        auto valorRetRed = socket->readDatagram(
            (char*)bufferLectura.data(),
            numeroDatosALeer,
            nullptr, nullptr
        );
        if(valorRetRed<=0){
            #ifdef QT_DEBUG
            qDebug()<<"Error leyendo datos UDP";
            #endif //QT_DEBUG
            continue;
        }
        //update();
        std::uint32_t nuevoContador = *((std::uint32_t*)bufferLectura.data());
        if(nuevoContador!=(ultimoPaqueteValido+1)){
            //Desincronizado
            muestrasCapturadas = 0;
            ultimoPaqueteValido = nuevoContador;
            //continue;
        }
        ultimoPaqueteValido = nuevoContador;
        if(muetrasAMostrar.size()<nMuestrasAMostrar){
            muetrasAMostrar.resize(nMuestrasAMostrar);
        }
        int nMuestrasRestantes = std::max(
            nMuestrasAMostrar-muestrasCapturadas,
            0
        );
        int nMuestrasAdjuntar = std::min(
            nMuestrasRecibidas,
            nMuestrasRestantes
        );
        memcpy(
            muetrasAMostrar.data()+sizeof(std::uint16_t)*muestrasCapturadas,
            bufferLectura.data()+sizeof(std::uint32_t),
            nMuestrasAdjuntar*sizeof(std::uint16_t)
        );
        muestrasCapturadas+=nMuestrasAdjuntar;
        if(muestrasCapturadas>=nMuestrasAMostrar){
            if(ventana->vertices.vertices.size()<nMuestrasAMostrar){
                ventana->vertices.reserveForAtLeastNVertexs(nMuestrasAMostrar);
            }
            memcpy(
                (char*)ventana->vertices.vertices.data(),
                muetrasAMostrar.data(),
                nMuestrasAMostrar*sizeof(std::uint16_t)
            );
            muestrasCapturadas = 0;
            ultimoTiempoDeCaptura = QDateTime::currentMSecsSinceEpoch();
            continue;
        }



    }
}
