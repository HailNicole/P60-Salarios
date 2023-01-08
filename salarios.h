#ifndef SALARIOS_H
#define SALARIOS_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

#include "obrero.h"
#include "controlador.h"
#include "acerca.h"
#include "dialog.h"

#define VERSION "0.2"

QT_BEGIN_NAMESPACE
namespace Ui { class Salarios; }
QT_END_NAMESPACE

class Salarios : public QMainWindow
{
    Q_OBJECT

public:
    Salarios(QWidget *parent = nullptr);
    ~Salarios();

private slots:
    void on_btnCalcular_clicked();

    void on_actionNuevo_triggered();

    void on_actionCalcular_triggered();

    void on_actionSalir_triggered();

    void on_actionGuardar_triggered();

    void on_actionAcerca_de_triggered();

    void on_actionAbrir_triggered();

private:
    Ui::Salarios *ui;
    Controlador *m_contolador;
    void limpiar();
    void calcular();
};
#endif // SALARIOS_H
