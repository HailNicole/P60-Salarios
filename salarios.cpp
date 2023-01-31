#include "salarios.h"
#include "ui_salarios.h"


Salarios::Salarios(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salarios)
{
    ui->setupUi(this);
    m_contolador = new Controlador();
}

Salarios::~Salarios()
{
    delete ui;
}


void Salarios::on_btnCalcular_clicked()
{
    calcular();
}


void Salarios::on_actionNuevo_triggered()
{
    QString datos = ui->outCalculos->toPlainText();

    if(datos.isEmpty()){
        // Limpiar widgets´
        limpiar();
        // Limpiar el texto de los calculos
        ui->outCalculos->clear();
        // Mostrar mensaje en la barra de estado
        ui->statusbar->showMessage(tr("Nuevos cálculos de salario."), 3000);
    }else{
        // Crear un objeto del cuadro de diálogo
        Dialog *dialog = new Dialog(this);
        // Mostrar la venta en modo MODAL
        //dialog->exec();
        if(dialog->exec() == QDialog::Accepted){
            on_actionGuardar_triggered();
            limpiar();
            ui->outCalculos->clear();
            ui->statusbar->showMessage(tr("Nuevos cálculos de salario."), 3000);
        }
        else{
            QMessageBox::warning(this,
                                 tr("Guardar archivo"),
                                 tr("No se ha guardado el archivo."));

            // Limpiar widgets´
            limpiar();
            // Limpiar el texto de los calculos
            ui->outCalculos->clear();
            // Mostrar mensaje en la barra de estado
            ui->statusbar->showMessage(tr("Nuevos cálculos de salario."), 3000);
        }

    }

}

void Salarios::limpiar()
{
    // Limpiar widgets
    ui->inNombre->setText("");
    ui->inHoras->setValue(0);
    ui->inMatutina->setChecked(true);
    ui->inNombre->setFocus();
}

void Salarios::calcular()
{
    // Obtener datos de la GUI
    QString nombre = ui->inNombre->text();
    int horas = ui->inHoras->value();
    TipoJornada jornada;
    if(ui->inMatutina->isChecked()){
        jornada = TipoJornada::Matituna;
    }else if (ui->inVespertina->isChecked()){
        jornada = TipoJornada::Vespertina;
    }else{
        jornada = TipoJornada::Nocturna;
    }
    // Validacion de datos
    if(nombre == "" || horas == 0){
        QMessageBox::warning(this,tr("Advertencia"),tr("El nombre y/o el número de horas es incorrecto"));
        return;
    }

    // Establecer datos al controlador
    m_contolador->setDatos(nombre, horas, jornada);
    // Calcular salarios
    if (m_contolador->calcular()) {
        // Muestra los resultados
        ui->outCalculos->appendPlainText(m_contolador->getDatos());
    } else {
        QMessageBox::critical(
                    this,
                    tr("Error"),
                    tr("No se puede calcular el salario."));
    }
    // Limpiar widgets
    limpiar();
    // Mostrar mensaje en la barra de estado
    ui->statusbar->showMessage(tr("Salario de ") + nombre + tr(" calculado."),5000);

}


void Salarios::on_actionCalcular_triggered()
{
    calcular();
}


void Salarios::on_actionSalir_triggered()
{
    this->close();
}


void Salarios::on_actionGuardar_triggered()
{
    QString datos = ui->outCalculos->toPlainText();
    if(datos.isEmpty()){
        QMessageBox::information(this, tr("Advertencia") , tr("No se han ingresado datos para guardar :|"));
        return;
    }
    // Abrir un cuadro de diálogo para seleccionar el path y archivo a guardar
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                   tr("Guardar calculos de salarios"),
                                                   QDir::home().absolutePath() + "/salarios.txt",
                                                   tr("Archivos de texto (*.txt)"));
    // Crear un objeto File
    QFile archivo(nombreArchivo);
    // Tartar de abrir para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        // cRear un objeto 'stream' de texto
        QTextStream salida(&archivo);
        // Enviar los datos del resultado a la salida
        salida << ui->outCalculos->toPlainText();
        // Mostrar mensaje en la barra de estados
        QMessageBox::information(this, " ", tr("Datos guardados con éxito!"));
        ui->statusbar->showMessage(tr("Datos guardados en: ") + nombreArchivo, 5000);
        // Cerrar el archivo
        archivo.close();
    }else {
        // Mensaje de error
        QMessageBox::warning(this,
                             tr("Guardar archivo"),
                             tr("No se puede acceder al archivo para guardar los datos."));
    }


}


void Salarios::on_actionAcerca_de_triggered()
{
    // Crear un objeto del cuadro de diálogo
    Acerca *dialog = new Acerca(this);
    // Enviar datos a la otra ventana
    dialog->setVersion(VERSION);
    // Mostrar la venta en modo MODAL
    dialog->exec();
    // Luego de cerrar la ventana, se acceden a los datos de la misma
    qDebug() << dialog->valor();
}


void Salarios::on_actionAbrir_triggered()
{
    QString texto="";
    QFile file(QFileDialog::getOpenFileName(this,tr("Abrir Archivo"),QDir::home().absolutePath(),tr("Archivo de Texto(*.txt)")));

           if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
              QMessageBox::warning(this, tr("Salarios"), tr("No se puede abrir el archivo"));
           }else{
               QTextStream entrada(&file);
               while (!entrada.atEnd()) {
                   texto += entrada.readLine()+'\n';
               }
            ui->outCalculos->appendPlainText(texto);
               file.close();
           }
}

