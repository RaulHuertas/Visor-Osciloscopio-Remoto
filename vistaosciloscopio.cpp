#include "vistaosciloscopio.hpp"
#include "ui_vistaosciloscopio.h"
#include "ui_configuraacionred.h"
#include "ventanavisualizacion.hpp"
#include <QGridLayout>

VistaOsciloscopio::VistaOsciloscopio(
    std::shared_ptr<QSettings>& settings,
    QWidget *parent
) :
    QWidget(parent),
    ui(new Ui::VistaOsciloscopio)
{
    this->settings = settings;
    config = std::make_unique<ConfiguracionOsc>();
    config->cargarDesde(*settings.get());
    ui->setupUi(this);
    dialogoConfigRed = new ConfiguraacionRed(this);
    connect(
        ui->slider_saltoPeriodo,
        &QSlider::valueChanged,
        this,
        &VistaOsciloscopio::nuevoSaltoPeriodo
    );
    connect(
        ui->slider_saltoVisible,
        &QSlider::valueChanged,
        this,
        &VistaOsciloscopio::nuevaVentanaPeriodo
    );
    connect(
        ui->botonOpciones,
        &QPushButton::clicked,
        this,
        &VistaOsciloscopio::cambiarConfiguracionRed
    );
    //mostrar lso valores actuales de configuracion
    //en la GUI
    ui->slider_saltoPeriodo->setValue(config->periodo_salto*100);
    ui->slider_saltoVisible->setValue(config->periodo_ventana*100);
    dialogoConfigRed->ui->line_ip->setText(config->ip);
    dialogoConfigRed->ui->line_puerto->setValue(config->puerto);

    ventana = new VentanaVisualizacion(ui->vistaOSC);
    auto* ly = new QGridLayout();
    ly->setMargin(0);
    ly->addWidget(ventana);
    ui->vistaOSC->setLayout(ly);

    bufferLectura.resize(2048);
    muestrasCapturadas = 0;
}

VistaOsciloscopio::~VistaOsciloscopio()
{
    delete ui;
}

void VistaOsciloscopio::cambiarConfiguracionRed(){
    auto ret = dialogoConfigRed->exec();
    if(ret==QDialog::Rejected){
        return;
    }
    guardarIPYPuerto(
        dialogoConfigRed->ui->line_ip->text(),
        dialogoConfigRed->ui->line_puerto->value()
    );
    prepararSocket();
}
