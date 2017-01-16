#include "vistaosciloscopio.hpp"

void VistaOsciloscopio::nuevoSaltoPeriodo(int newValue){
    config->periodo_salto = newValue/100.0;
    config->guardarEn(*settings.get());
}

void VistaOsciloscopio::nuevaVentanaPeriodo(int newValue){
    config->periodo_ventana = newValue/100.0;
    config->guardarEn(*settings.get());
}

void VistaOsciloscopio::guardarIPYPuerto(
    const QString& ip,
    const quint16 puerto
){
    config->ip = ip;
    config->puerto = puerto;
    config->guardarEn(*settings.get());
}
