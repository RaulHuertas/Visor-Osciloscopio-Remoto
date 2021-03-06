#ifndef VISTAOSCILOSCOPIO_HPP
#define VISTAOSCILOSCOPIO_HPP

#include <QWidget>
#include <memory>
#include <QSettings>
#include "configuraacionred.hpp"
#include <QUdpSocket>
#include <QDateTime>

class VentanaVisualizacion;
namespace Ui {
class VistaOsciloscopio;
}

struct ConfiguracionOsc{
    QString ip;
    quint16 puerto;

    quint32 periodoTotal_ms = 16000U;
    double periodo_salto = 0.0;
    double periodo_ventana = 1.0;
    void cargarDesde(const QSettings& conf);
    void guardarEn(QSettings& conf)const;
};

class VistaOsciloscopio : public QWidget
{
    Q_OBJECT

public:
    explicit VistaOsciloscopio(std::shared_ptr<QSettings>& settings, QWidget *parent = 0);
    ~VistaOsciloscopio();

    std::unique_ptr<ConfiguracionOsc> config = nullptr;
    std::shared_ptr<QSettings> settings = nullptr;
public slots:
    void nuevoSaltoPeriodo(int newValue);
    void nuevaVentanaPeriodo(int newValue);
    void guardarIPYPuerto(
        const QString& ip,
        const quint16 puerto
    );
    void cambiarConfiguracionRed();
private:
    Ui::VistaOsciloscopio *ui;
    ConfiguraacionRed* dialogoConfigRed = nullptr;
    VentanaVisualizacion* ventana = nullptr;
    //COMUNICACION UDP
    private:
        std::unique_ptr<QUdpSocket> socket = nullptr;
        void prepararSocket();

        std::vector<std::uint16_t> muetrasAMostrar;
        std::vector<std::uint8_t> bufferLectura;
        std::uint32_t ultimoPaqueteValido = 0;
        std::uint32_t paqueteInicialVentanaActual = 0;

        int muestrasCapturadas  = 0;
        std::uint64_t ultimoTiempoDeCaptura = 0;

        bool debeActualizar()const{
            auto tiempoActual = QDateTime::currentMSecsSinceEpoch();
            return ((tiempoActual-ultimoTiempoDeCaptura)>(16));
        }


    public slots:
        void hayDatosLecturaPendientes();
};

#endif // VISTAOSCILOSCOPIO_HPP
