#include "vistaosciloscopio.hpp"
#include <QSettings>
#include <QDebug>

void ConfiguracionOsc::cargarDesde(const QSettings &conf){
    ip = conf.value("ip", "localhost").toString();
    puerto = conf.value("puerto", 2799).toUInt();
    periodoTotal_ms = conf.value("periodoTotal_ms", "1600").toString().toULongLong();
    periodo_salto  = conf.value("periodo_salto", 0.0).toDouble();
    periodo_ventana  = conf.value("periodo_ventana", 1.0).toDouble();
}

void ConfiguracionOsc::guardarEn(QSettings& conf)const{
    conf.setValue("ip", ip);
    conf.setValue("puerto", QString::number(puerto));
    conf.setValue("periodoTotal_ms", QString::number(periodoTotal_ms));
    conf.setValue("periodo_salto", periodo_salto);
    conf.setValue("periodo_ventana", periodo_ventana);
    #ifdef QT_DEBUG
    qDebug()<<"periodo_salto: "<<periodo_salto;
    #endif;
}
