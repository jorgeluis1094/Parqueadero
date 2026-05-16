#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButtonRegInOut, SIGNAL(clicked()),this, SLOT(on_lineEditRegInOut_returnPressed()));
    QObject::connect(ui->actionLogin,SIGNAL(triggered(bool)), this, SLOT(on_pushButtonLogin_clicked()));
    QObject::connect(ui->actionEntrega,SIGNAL(triggered(bool)), this, SLOT(on_pushButtonEntrega_clicked()));
    QObject::connect(ui->tableViewRegVeh,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_tableInOutCar_doubleClicked(QModelIndex)) );
    QObject::connect(ui->tableViewRegPago,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_tableInOutCar_doubleClicked(QModelIndex)) );

    QSqlQuery query("SELECT id_operario, nombre FROM operarios WHERE registrado = '1' LIMIT 1");

    if(query.next()){
        int idEncontrado = query.value(0).toInt();
        QString operarioEncontrado = query.value(1).toString();

        // 1. Iniciamos la sesión en el Singleton para que todo el programa sepa quién es
        SessionManager::instance().login(idEncontrado, operarioEncontrado);

        // 2. Ajustamos la Interfaz
        ui->actionLogin->setVisible(false);
        ui->actionEntrega->setVisible(true);
    }
    else{
        ui->actionLogin->setVisible(true);
        ui->actionEntrega->setVisible(false);
        SessionManager::instance().logout(); // Aseguramos que esté limpio
    }


    // Seleccionamos la clave y el valor de la tabla
    if (query.exec("SELECT clave, valor FROM tarifas")) {
        while (query.next()) {
            QString clave = query.value(0).toString();
            int valor = query.value(1).toInt();

            if (clave == "hora_moto") {
                valorHoraMoto = valor;
            } else if (clave == "valor_maximo_moto") {
                valorMaxPagar = valor;
            } else if (clave == "lavada_1") {
                valorLavada1 = valor;
            } else if (clave == "lavada_2") {
                valorLavada2 = valor;
            }
        }
    } else {
        qDebug() << "Error al cargar tarifas:" << query.lastError().text();
    }

    ui->dateEdit->setDate(QDate::currentDate());
    //impCopia=false;

    VecTipoVeh.push_back("Moto");
    VecTipoVeh.push_back("Moto-Lavada_1");
    VecTipoVeh.push_back("Moto-Lavada_2");

    initInterfaz();

    // Cargar configuración de impresión
    PrintConfig::instance().load("../../Impresora/config/");

    //repoVehiculo = new PostgresVehiculoRepository();
    repoVehiculo = new VehiculoRepository();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete modelUno;
    delete modelDos;
    delete modelTres;
    delete modeloTablaProductos;
    delete modeloTablaCaja;
}


void MainWindow::ConectarTablas()
{
/*
    modelUno = new QSqlTableModel(0,db);
    modelUno->setTable("Mensualidades");
    modelUno->select();
    ui->tableView->setModel(modelUno);

    modelDos = new QSqlTableModel(0,db);
    modelDos->setTable("EntradaVehiculos");
    modelDos->select();
    ui->tableInOutCar->setModel(modelDos);

    modelTres = new QSqlTableModel(0,db);
    modelTres->setTable("RegVehiculos");
    modelTres->select();
    ui->tableViewRegVeh->setModel(modelTres);

    modeloTablaProductos = new QSqlTableModel(0,db);
    modeloTablaProductos->setTable("Productos");
    modeloTablaProductos->select();
    ui->tW_Producto_Sel->setModel(modeloTablaProductos);
*/

    modelUno = new QSqlTableModel(this);
    modelUno->setTable("mensualidades");
    modelUno->select();
    ui->tableView->setModel(modelUno);

    modelDos = new QSqlTableModel(this);
    modelDos->setTable("estacionamiento_activo");
    modelDos->select();
    ui->tableInOutCar->setModel(modelDos);

    modelTres = new QSqlTableModel(this);
    modelTres->setTable("registro_salidas");
    modelTres->select();
    ui->tableViewRegVeh->setModel(modelTres);

    modeloTablaProductos = new QSqlTableModel(this);
    modeloTablaProductos->setTable("productos");
    modeloTablaProductos->select();
    ui->tW_Producto_Sel->setModel(modeloTablaProductos);

    modeloTablaCaja = new QSqlTableModel(this);
    modeloTablaCaja->setTable("transacciones_caja");
    modeloTablaCaja->select();
    ui->twDetalleCaja->setModel(modeloTablaCaja);

}

void MainWindow::on_pushButtonRegistrar_clicked()//Registra una mensualidad
{
    if (SessionManager::instance().estaLogueado())
    {
            QDateTime fechaActual = QDateTime();
            QSqlQuery query;
            QString nombre,direccion, telefono, placa, fechaInicio,fechaFin, valorPago, fechapago, casillero;

            nombre = ui->lineEditNombreMensual->text();
            direccion = ui->lineEditDireccionMensual->text();
            telefono = ui->lineEditTelefonoMensual->text();
            placa = ui->lineEditPlacaMensual->text().toUpper();
            fechaInicio = ui->dateEdit->text();
            //fechaFin = ui->dateEdit_2->text();
            valorPago = ui->lineEditPagoMensual->text();
            fechapago = fechaActual.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            casillero = ui->leCasilleroMensual->text();

            if(!nombre.isEmpty() && !placa.isEmpty() && !valorPago.isEmpty() )
            {

                qDebug()<<"INSERT INTO Mensualidades "
                               "(Placa, Casillero, Nombre, Telefono, Direccion, Inicio, Fin, Fecha_Pago, Valor, Registro)"
                               "VALUES ( '"+placa+"' , '"+casillero+"' , '"+nombre+"' , '"+telefono+"' , '"+direccion+"' , '"+fechaInicio+"' , datetime('" + fechaInicio + "', '+30 days') , strftime('%Y-%m-%d %H:%M:%S', 'now','localtime') , '"+valorPago+"', '"+SessionManager::instance().usuarioActual()+"')";


                    query.exec("INSERT INTO Mensualidades "
                               "(Placa, Casillero, Nombre, Telefono, Direccion, Inicio, Fin, Fecha_Pago, Valor, Registro)"
                               "VALUES ( '"+placa+"' , '"+casillero+"' , '"+nombre+"' , '"+telefono+"' , '"+direccion+"' , '"+fechaInicio+"' , date('" + fechaInicio + "', '+1 month') , strftime('%Y-%m-%d %H:%M:%S', 'now','localtime') , '"+valorPago+"', '"+SessionManager::instance().usuarioActual()+"')");

                    query.exec("INSERT INTO RegVehiculos"
                            "(Placa,Entrada,Salida,Pago,Reg_Ingreso, Reg_Salida, Tipo,Tiempo_Total)"
                               "VALUES ( '"+placa+"' , strftime('%Y-%m-%d %H:%M:%S', 'now','localtime') , strftime('%Y-%m-%d %H:%M:%S', 'now','localtime') , '"+valorPago+"' , '"+SessionManager::instance().usuarioActual()+"', '"+SessionManager::instance().usuarioActual()+"', 'Moto','Mensualidad')");

                    vehiculo = new Vehiculo(placa,"Moto",ui->dateEdit->dateTime(),SessionManager::instance().usuarioActual());
                    //vehiculo->HoraSalida(ui->dateEdit_2->dateTime());
                    vehiculo->ValorPagado(valorPago.toInt());
                    vehiculo->NomRegOut(SessionManager::instance().usuarioActual());
                    vehiculo->TipoVehiculo("Moto");
                    vehiculo->Propietario(nombre);

                    RefrescarTablas();

                    //iMPRIMIR RECIBO
                    structMensualidad.placa = placa;
                    structMensualidad.fechaPago = fechapago;
                    structMensualidad.inicioMensualidad = fechaInicio.mid(0,10);
                    structMensualidad.finMensualidad = QDate::fromString(fechaInicio, "yyyy-MM-dd").addMonths(1).toString();//;fechaFin.mid(0,10);
                    structMensualidad.tipoVehiculo = "Moto";
                    structMensualidad.pagoRecibido = valorPago;
                    structMensualidad.operarioParqueadero = SessionManager::instance().usuarioActual();

                    pm.printReciboMensualidad(structMensualidad);


            }
            else
                QMessageBox::critical(this, NombreParqueadero,tr("<font size = 15 color = black >Datos Importantes Sin LLenar"));
     }
    else
        QMessageBox::critical(this, NombreParqueadero,tr("<font size = 15 color = black >Debe Registrarse"));
}


/*+++++++++++++++++++++*/
void MainWindow::on_lineEditRegInOut_returnPressed()
{
    QString placa = ui->lineEditRegInOut->text().toUpper().trimmed();

    // 1. Validaciones de Interfaz
    if (!SessionManager::instance().estaLogueado()) {
        QMessageBox::critical(this, "Error", "Debe iniciar sesión primero.");
        return;
    }
    if (placa.length() <= 4) {
        QMessageBox::warning(this, "Error", "La placa no es válida.");
        return;
    }

    // 2. Lógica de Decisión (¿Entra o Sale?)
    if (repoVehiculo->estaEnParqueadero(placa)) {
        qDebug()<<"Esta en el parqueadero";
        // --- LÓGICA DE SALIDA (A implementar luego) ---
        // Calculamos sin modificar la base de datos
        InfoCobro cobro = repoVehiculo->calcularCobro(placa);

        if (cobro.montoTotal == 0) {
            QMessageBox::warning(this, "Error", "No se encontró el vehículo o error en cálculo.");
            return;
        }

        // 2. Mostramos el desglose al operario
        QString mensaje = QString("Placa: %1\n"
                                  "Ingreso: %2\n"
                                  "Tiempo: %3h %4m\n\n"
                                  "TOTAL A COBRAR: $%5")
                              .arg(placa)
                              .arg(cobro.fechaIngreso.toString("hh:mm ap"))
                              .arg(cobro.horas)
                              .arg(cobro.minutos)
                              .arg(cobro.montoTotal);

        QMessageBox::StandardButton resp;
        resp = QMessageBox::question(this, "Confirmar Salida", mensaje,
                                     QMessageBox::Yes | QMessageBox::No);

        // 3. Si confirma, ejecutamos la transacción real
        if (resp == QMessageBox::Yes) {
            int idOp = SessionManager::instance().idActual();
            QString duracionStr = QString("%1:%2")
                                      .arg(cobro.horas, 2, 10, QChar('0'))
                                      .arg(cobro.minutos, 2, 10, QChar('0'));

            if (repoVehiculo->ejecutarSalida(placa, cobro.montoTotal, duracionStr, idOp)) {
                QMessageBox::information(this, "Éxito", "Venta registrada.");
                ui->lineEditRegInOut->clear();
                RefrescarTablas();
                // ImprimirRecibo(cobro);
            } else {
                QMessageBox::critical(this, "Error", "No se pudo completar la transacción.");
            }
        }

        ui->lineEditRegInOut->clear();
    }
    else if (repoVehiculo->esMensualidadVigente(placa)) {
        // --- LÓGICA DE MENSUALIDAD ---
        QMessageBox::information(this, "Mensualidad", "Vehículo reconocido como Mensualidad.");
        // Aquí podrías registrar la entrada con tarifa 0
    }
    else {
        // --- LÓGICA DE ENTRADA ---
        if (QMessageBox::question(this, "Entrada", "¿Registrar entrada de: " + placa + "?") == QMessageBox::Yes) {

            QString tipoFinal = "Moto";
            if (ui->rB_Lavada1->isChecked()) tipoFinal = tipoFinal+"-Lavada_1";
            else if (ui->rB_Lavada2->isChecked()) tipoFinal = tipoFinal+"-Lavada_2";

            Vehiculo* v = new Vehiculo(placa, tipoFinal, QDateTime::currentDateTime(), SessionManager::instance().usuarioActual());

            if (repoVehiculo->registrarEntrada(v, valorHoraMoto)) {
                // Preparar ticket e imprimir
                //enviarImpresionEntrada(v);
                ui->lineEditRegInOut->clear();
                RefrescarTablas();
            } else {
                QMessageBox::critical(this, "Error", "Error al guardar en base de datos.");
            }
            delete v;
        }
    }
}
/*---------------------*/


void MainWindow::on_pushButtonLogin_clicked()//despliega ventana para el login de los operarios
{
    WinLogin = new QDialog(this);
    QDateTime HoraEntrada =QDateTime();
    WinLogin->setWindowTitle("Login de Usuario");
    WinLogin->resize(460,60*2);

    QLabel *LabelNombre = new QLabel("Elija Su Nombre:",WinLogin);
    LabelNombre->setGeometry(20,20,200,30);

    QComboBox *ComBoxNombresOperarios = new QComboBox(WinLogin);
    ComBoxNombresOperarios->setGeometry(45,45,400,30);

    //Obtiene el numero de operarios registrados
        QSqlQuery query;
        query.exec("SELECT nombre FROM operarios Where registrado='0'");

        ComBoxNombresOperarios->addItem("");
        while(query.next()){
            ComBoxNombresOperarios->addItem(query.value(0).toString());
        }

    QObject::connect(ComBoxNombresOperarios, SIGNAL(currentTextChanged(QString)),
                this, SLOT(setUsuario(QString)) );

    WinLogin->show();
}


void MainWindow::setUsuario(QString Nombre)
{
    if(Nombre == "") return;

    QSqlQuery query;
    query.prepare("SELECT id_operario FROM operarios WHERE nombre = :nom");
    query.bindValue(":nom", Nombre);

    if(query.exec() && query.next()) {
        int id = query.value(0).toInt();

        // Iniciamos una transacción para asegurar integridad
        QSqlDatabase::database().transaction();

        bool ok = true;

        // 1. Actualizar estado del operario
        QSqlQuery upd;
        upd.prepare("UPDATE operarios SET registrado = '1' WHERE id_operario = :id");
        upd.bindValue(":id", id);
        if(!upd.exec()) ok = false;

        // 2. CREAR LA SESIÓN EN LA NUEVA TABLA
        // Esto es vital para que 'obtenerEstadisticasCierre' sepa cuándo empezó el turno
        QSqlQuery insSesion;
        insSesion.prepare("INSERT INTO sesiones_operarios (id_operario, fecha_inicio) "
                          "VALUES (:id, CURRENT_TIMESTAMP)");
        insSesion.bindValue(":id", id);
        if(!insSesion.exec()) ok = false;

        if(ok) {
            QSqlDatabase::database().commit();

            // Login en el Manager con ID y Nombre
            SessionManager::instance().login(id, Nombre);

            ui->actionLogin->setVisible(false);
            ui->actionEntrega->setVisible(true);


            WinLogin->close();
        } else {
            QSqlDatabase::database().rollback();
            QMessageBox::critical(this, "Error", "No se pudo iniciar la sesión en la base de datos.");
        }
    }
}

/*
void MainWindow::on_pushButtonEntrega_clicked()//realiza la suma del producido y genera el recibo
{
    QSqlQuery query;

    //Strings Para Cadena de Caracteres
    QString Datos;
    QString Tabla;
    QString Parametros;
    QString NombreParqueadero;

    Datos = "SUM(pago)";
    Tabla = "reg_vehiculos";
    Parametros = "id_operario_Salida='"+QString::number(SessionManager::instance().idActual())+"'";

    double dinero;

    query = RealizarConsulta(Datos,Tabla,Parametros);

    dinero = query.value(0).toDouble();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,NombreParqueadero,
                                  "Total Realizado: $"+QString::number(dinero)+'\n'+"Realizar Entrega?",
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){

//        DineroTurno = dinero;
//        QString HoraSalida = QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss");

//        query.exec("SELECT Inicio FROM Entregas ORDER BY Inicio DESC LIMIT 1");
//        query.next();
//        QDateTime Entrada=query.value(0).toDateTime();
//        QString HoraEntrada = Entrada.toString("yy-MM-dd hh:mm:ss");

//        query.exec("select Sum(Pago) from RegVehiculos where Tiempo_Total='Producto'");
//        query.next();
//        int vpProductos = query.value(0).toInt();

//        query.exec(" select Sum(Pago) from RegVehiculos where Tiempo_Total='Mensualidad'");
//        query.next();
//        int vpMensualidad = query.value(0).toInt();

//        query.exec("select Count(*) from RegVehiculos where Tiempo_Total='Mensualidad'");
//        query.next();
//        int numMensualidadesPagadas = query.value(0).toInt();

//        query.exec("select Sum(Pago) from RegVehiculos where Tipo='Moto'");
//        query.next();
//        int vpMotos = query.value(0).toInt()-vpMensualidad;

//        query.exec("select Sum(Pago) from RegVehiculos where Tipo='Moto-Lavada_1'");
//        query.next();
//        int vpMotoLavada_1 = query.value(0).toInt();

//        query.exec("select Sum(Pago) from RegVehiculos where Tipo='Moto-Lavada_2'");
//        query.next();
//        int vpMotoLavada_2 = query.value(0).toInt();

//        query.exec("select  Count(*) from EntradaVehiculos");
//        query.next();
//        int numMotosDentro = query.value(0).toInt();

//       query.exec("select  Count(*) from RegVehiculos where Tipo='Moto'");
//       query.next();
//       int numMotosFuera = query.value(0).toInt();


//        cierre.fechaHoraInicio = HoraEntrada;
//        cierre.fechaHoraFin = HoraSalida;
//        cierre.usuario = SessionManager::instance().usuarioActual();
//
//        cierre.totalEntradas = numMotosDentro;
//        cierre.totalSalidas = numMotosFuera;
//        cierre.totalMensulidadesPago = numMensualidadesPagadas;
//
//        cierre.totalesPago["Moto        "] = vpMotos;
//        cierre.totalesPago["Lavada 1    "] = vpMotoLavada_1;
//        cierre.totalesPago["Lavada 2    "] = vpMotoLavada_2;
//        cierre.totalesPago["Mensualidad "] = vpMensualidad;
//        cierre.totalesPago["Productos   "] = vpProductos;
//
//        pm.printCierreCaja(cierre);

//        Tabla="RegVehiculos";
//        Parametros = "Reg_Salida='"+SessionManager::instance().usuarioActual()+"'";
//        BorrarFilaTabla(Tabla,Parametros);
//
//        Tabla = "TablaOtrosVeh";
//        BorrarFilaTabla(Tabla,Parametros);
//
//        query.exec("UPDATE Entregas SET "
//                   "Fin='20"+HoraSalida+"', "
//                   "Entrega='"+QString::number(vpMotos+vpMotoLavada_1+vpMotoLavada_2+vpMensualidad+vpProductos)+"' "
//                   "where Inicio='20"+HoraEntrada+"' ");

        query.exec("UPDATE operarios SET registrado = '0'");



//        trabajador=new Operario(SessionManager::instance().usuarioActual());
//        trabajador->HoraEntrada(HoraEntrada);
//        trabajador->HoraSalida(HoraSalida);
//        trabajador->TotalRealizado(DineroTurno);
//        trabajador->TotalMotos(vpMotos);
//        //trabajador->TotalCarros(vpCarro);
//        trabajador->TotalMensualidades(vpMensualidad);
//        //trabajador->TotalOtrosArticulos(vpOtrosArticulos);
//        trabajador->NumMensualidadesPagadas(numMensualidadesPagadas);
//        //trabajador->TotalOtrosPagos(vpOtrosPagos);

        SessionManager::instance().logout();

        ui->actionLogin->setVisible(true);
        ui->actionEntrega->setVisible(false);

    }
    RefrescarTablas();
}
*/

// +++++++++++++++++++++++++

void MainWindow::on_pushButtonEntrega_clicked() {
    int idOp = SessionManager::instance().idActual();
    DatosCierre cierre = repoVehiculo->obtenerEstadisticasCierre(idOp);

    QString listaProductos = "";
    if (!cierre.productosVendidos.isEmpty()) {
        listaProductos = "<br><b>VENTAS VITRINA:</b><br>";
        QMapIterator<QString, int> i(cierre.productosVendidos);
        while (i.hasNext()) {
            i.next();
            listaProductos += QString("- %1 (Cant: %2)<br>").arg(i.key()).arg(i.value());
        }
    }

    QString mensaje = QString(
                          "<font color='black'>"
                          "<b>RESUMEN DE CIERRE</b><br>"
                          "Motos en Patio: %1<br>"
                          "Salidas Turno: %2<br><br>"
                          "Parqueo: $%3<br>"
                          "Lavadas_1: $%4<br>"
                          "Lavadas_2: $%5<br>"
                          "Productos: $%6<br>"
                          "%7" // Aquí se inserta la lista de productos
                          "--------------------------<br>"
                          "<b>TOTAL EFECTIVO: $%8</b></font>"
                          ).arg(cierre.totalMotosDentro)    // 1
                            .arg(cierre.totalSalidasTurno)  // 2
                            .arg(cierre.dineroMotos)        // 3
                            .arg(cierre.dineroLavadas1)     // 4
                            .arg(cierre.dineroLavadas2)     // 5
                            .arg(cierre.dineroProductos)    // 6
                            .arg(listaProductos)            // 7
                            .arg(cierre.totalEfectivo);     // 8

    if (QMessageBox::question(this, "Cierre de Turno", mensaje, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        // Ejecutar cierre y mandar a imprimir
        if (repoVehiculo->registrarCierreSesion(idOp, cierre.totalEfectivo)) {

            // Estructura para la impresora (printCierreCaja usará los datos de 'cierre')
            //pm.printCierreCaja(cierre);

            SessionManager::instance().logout();

            ui->actionLogin->setVisible(true);
            ui->actionEntrega->setVisible(false);
        }
    }
}

//-------------------------


void MainWindow::imprimirReciboTabla1(void)// imprime un recibo auxiliar de la tabla de vehiculos dentro
{
    QSqlQuery query;
    QString Placa= lineEditsRE->text();
    query.exec("SELECT * FROM EntradaVehiculos  WHERE Placa='"+Placa+"' ");
    query.next();
    vehiculo = new Vehiculo(query.value(0).toString(),query.value(3).toString(),query.value(1).toDateTime(),query.value(2).toString());
    impCopia=true;
    //imprimir(0);
    ReciboTablas->close();
}


void MainWindow::imprimirReciboTabla2(void)//imprime un recibo auxiliar de la tabla de salida
{
    QSqlQuery query;
    QString Placa= lineEditsRE->text();
    query.exec("SELECT * FROM RegVehiculos WHERE Placa='"+Placa+"' ");
    query.next();

    vehiculo = new Vehiculo(query.value(0).toString(),query.value(6).toString(),query.value(1).toDateTime(),query.value(4).toString());
    vehiculo->HoraSalida(query.value(2).toDateTime());
    vehiculo->ValorPagado(query.value(3).toInt());
    vehiculo->NomRegOut(query.value(5).toString());
    vehiculo->TiempoParqueo(query.value(7).toString());
    impCopia=true;
    //imprimir(1);

    ReciboTablas->close();
}

void MainWindow::on_pushButtonRegPago_clicked()//actualiza el pago de una mensualidad
{
    if(SessionManager::instance().estaLogueado() && !ui->lineEditRegPagoPlata->text().isEmpty() && ui->lineEditRegPagoPlata->text().toInt()>0){

            QSqlQuery query;
            QString diasPagados;
            diasPagados=ui->lineEditDiasPagados->text();
            if(ui->lineEditDiasPagados->text().toInt() > 31 || ui->lineEditDiasPagados->text() == "")
                diasPagados="30";

            QSqlQueryModel *modelCuatro= new QSqlQueryModel;
            QString placa= ui->lineEditRegPago->text().toUpper();

            query.exec("UPDATE Mensualidades SET "
                       "Inicio=DATE(Fin,'+1 days'), "
                       "Fin=DATE(Fin,'+"+diasPagados+" days'), "
                       "Fecha_Pago=strftime('%Y-%m-%d %H:%M:%S', 'now','localtime'), "
                       "Registro='"+SessionManager::instance().usuarioActual()+"', "
                       "Valor='"+ui->lineEditRegPagoPlata->text().toUpper()+"' "
                       "WHERE "
                       "Placa='"+placa+"' ");

        //Ingresa el dinero recibido en la tabla de registro de salida donde estan los datos que se sumaran

            query.exec("INSERT INTO RegVehiculos"
                "(Placa,Entrada,Salida,Pago,Reg_Ingreso, Reg_Salida, Tipo,Tiempo_Total)"
                   "VALUES ( '"+placa+"', strftime('%Y-%m-%d %H:%M:%S', 'now', 'localtime'), strftime('%Y-%m-%d %H:%M:%S', 'now', 'localtime') , '"+ui->lineEditRegPagoPlata->text()+"', '"+SessionManager::instance().usuarioActual()+"', '"+SessionManager::instance().usuarioActual()+"', 'Moto','Mensualidad')");

          /*  QString consulta =  "SELECT Placa, Nombre, Valor, Inicio, Fin, Registro FROM Mensualidades WHERE "
                                "Nombre='"+ui->lineEditRegPago->text()+"' OR "
                                "Placa='"+ui->lineEditRegPago->text().toUpper()+"' ";

*/

            query.exec("SELECT Placa, Nombre, Valor, Inicio, Fin, Registro FROM Mensualidades WHERE "
                       "Nombre='"+ui->lineEditRegPago->text()+"' OR "
                       "Placa='"+ui->lineEditRegPago->text().toUpper()+"' ");
            query.next();

            //iMPRIMIR RECIBO
            structMensualidad.placa = query.value(0).toString();
            structMensualidad.fechaPago = QDateTime::currentDateTime().toString("yyyy-MM-dd");
            structMensualidad.inicioMensualidad = query.value(3).toString();
            structMensualidad.finMensualidad = query.value(4).toString();
            structMensualidad.tipoVehiculo = "Moto";
            structMensualidad.pagoRecibido = query.value(2).toString();
            structMensualidad.operarioParqueadero = SessionManager::instance().usuarioActual();

            pm.printReciboMensualidad(structMensualidad);

        //Actualiza la tabla de mensualidades y la de ingreso
        //y salida de vehiculos donde se registra la placa y el pago para sumar a lo que debe entregar el operario
           modelUno->select();
           ui->tableView->setModel(modelUno);
           modelTres->select();
           ui->tableViewRegVeh->setModel(modelTres);


            modelCuatro->setQuery("SELECT * FROM Mensualidades WHERE Placa='"+ui->lineEditRegPago->text().toUpper()+"' ");
            ui->tableViewRegPago->setModel(modelCuatro);
            ui->lineEditRegPagoPlata->clear();
            ui->lineEditRegPago->clear();
            ui->lineEditDiasPagados->clear();

    }
    else
    {
        QMessageBox::critical(this, NombreParqueadero,tr("<font size = 15 color = black >Debe Registrarse o Ingresar el Dinero"));
    }

}


void MainWindow::on_comboBoxVerMensualidad_currentIndexChanged(int index)//muestra datos de fechas de corte en la tabla
{
    QSqlQueryModel *modelo= new QSqlQueryModel;

    switch(index)
    {
    case 0:
        modelo->setQuery("SELECT * FROM Mensualidades");
        break;
    case 1:
        modelo->setQuery("SELECT * FROM Mensualidades WHERE Fin >= strftime('%Y-%m-%d')");
        break;
    case 2:
        modelo->setQuery("SELECT * FROM Mensualidades WHERE Fin < strftime('%Y-%m-%d')");
        break;
    }

    ui->tableView->setModel(modelo);

}


void MainWindow::RefrescarTablas()//actualiza las tablas y borra los lineEdit
{

    modelUno->select();
    ui->tableView->setModel(modelUno);

    modelDos->select();
    ui->tableInOutCar->setModel(modelDos);


    modelTres->select();
    ui->tableViewRegVeh->setModel(modelTres);

    modeloTablaProductos->select();
    ui->tW_Producto_Sel->setModel(modeloTablaProductos);

    modeloTablaCaja->select();
    ui->twDetalleCaja->setModel(modeloTablaCaja);



    ui->lineEditNombreMensual->clear();
    ui->lineEditDireccionMensual->clear();
    ui->lineEditTelefonoMensual->clear();
    ui->lineEditPlacaMensual->clear();
    ui->lineEditPagoMensual->clear();
    ui->lineEditRegInOut->clear();
    ui->leCasilleroMensual->clear();
    //ui->lineEditRecibeCantidad->clear();
    //ui->lineEditrecibeDe->clear();
    //ui->lineEditOtrosVeh->clear();
    //ui->lineEditCantOtrosArt->clear();
}

void MainWindow::on_tableInOutCar_doubleClicked(const QModelIndex &index)//opciones para imprimir cópia de recibo
{

    if (index.column() == 0) {
        ReciboTablas = new QDialog(this);
        ReciboTablas->setWindowTitle("Imprimir Recibo");
        ReciboTablas->resize(400,150);


        QLabel *labelPlaca = new QLabel("Placa", ReciboTablas);
        labelPlaca->setGeometry(75,10,250,20);
        lineEditsRE = new QLineEdit(ReciboTablas);
        lineEditsRE->setGeometry(75,30,250,30);
        lineEditsRE->setText(index.data().toString());

        QPushButton *buttonT1 = new QPushButton("Tabla de Registros Entrada:",ReciboTablas);
        buttonT1->setGeometry(75,70,250,30);

        QPushButton *buttonT2 = new QPushButton("Tabla de Registros Salida:",ReciboTablas);
        buttonT2->setGeometry(75,110,250,30);

        //QPushButton *buttonT3 = new QPushButton("Tabla de Otros Articulos:",ReciboTablas);
        //buttonT3->setGeometry(100,150,250,30);

        QObject::connect(buttonT1, SIGNAL(clicked()),this, SLOT(imprimirReciboTabla1()));
        QObject::connect(buttonT2, SIGNAL(clicked()),this,SLOT(imprimirReciboTabla2()));
        //QObject::connect(buttonT3, SIGNAL(clicked()),this,SLOT(imprimirReciboTablaOtros()));
        ReciboTablas->show();
    }

}

void MainWindow::on_cB_Productos_currentTextChanged(const QString &arg1)
{
    QSqlQuery query;
    QSqlQueryModel *modelo= new QSqlQueryModel;
    QString consultaSQL;

    if (arg1=="Ver todos") {
        consultaSQL = "SELECT Nombre, "
                      "Descripcion AS Descripción, "
                      "Precio_Venta AS Precio, "
                      "Stock AS Inventario "
                      "FROM Productos";
        ui->pB_VentaOtroProducto->setEnabled(false);
    }
    else {
        consultaSQL = "SELECT "
                      "Nombre, "
                      "Descripcion AS Descripción, "
                      "Precio_Venta AS Precio, "
                      "Stock AS Inventario "
                      "FROM Productos WHERE Nombre= '"+arg1+"' AND Stock>0 ";
        ui->pB_VentaOtroProducto->setEnabled(true);
    }
    query.exec(consultaSQL);

    if (query.isActive()) {
        modelo->setQuery(query);
        ui->tW_Producto_Sel->setModel(modelo);
    }
    else {
        qDebug() << "Error al ejecutar la consulta:" << query.lastError().text();
    }
}

void MainWindow::initInterfaz()//Inicia la interfaz de la tabla de produtos de la vitrina
{

    // Inicializar la intefaz del combobox de productos
    QSqlQuery query;
    query.exec("SELECT Nombre FROM Productos WHERE Stock>0");
    ui->cB_Productos->addItem("Ver todos");

    if (query.isActive()) {
        while (query.next()) {
            QString producto = query.value(0).toString();
            ui->cB_Productos->addItem(producto);
        }
    } else {
        qDebug() << "Error al ejecutar la consulta:" << query.lastError().text();
    }

    ConectarTablas();

}

void MainWindow::on_pB_VentaOtroProducto_clicked()
{

    if(SessionManager::instance().usuarioActual()=="")
        QMessageBox::critical(this, NombreParqueadero,tr("<font size = 15 color = black >Debe Registrarse"));
    else{

        QMessageBox::StandardButton reply;
        QString NomProd=ui->cB_Productos->currentText();
        reply = QMessageBox::question(this,NombreParqueadero,
                                      "Registrar venta de "+NomProd,
                                      QMessageBox::Yes | QMessageBox::No);

        if(reply == QMessageBox::Yes){

            QSqlQuery query;
            QString consultaSQL;

            //Obtiene datos del Producto a vender
            consultaSQL = "SELECT Nombre AS Placa, "
                          "DATETIME(current_timestamp, 'localtime') AS Entrada, "
                          "DATETIME(current_timestamp, 'localtime') AS Salida, "
                          "Precio_Venta AS Precio, "
                          "Stock AS Inventario "
                          "FROM Productos WHERE Nombre= '"+NomProd+"'";
            query.exec(consultaSQL);
            query.next();

            //Inserta en la tabla de ventas para sumar total
            consultaSQL = "INSERT INTO RegVehiculos "
                          "(Placa, Entrada, Salida, Pago, Reg_Ingreso, Reg_Salida, Tipo, Tiempo_Total) "
                          "VALUES ( '"+query.value(0).toString()+"' , '"+query.value(1).toString()+"' , '"+query.value(2).toString()+"' , '"+query.value(3).toString()+"' , '"+SessionManager::instance().usuarioActual()+"', '"+SessionManager::instance().usuarioActual()+"', 'Producto','Producto')";

            structVentaProductos.nombreProducto =  query.value(0).toString();
            structVentaProductos.precioProducto =  query.value(3).toString();
            structVentaProductos.fechaVenta =   query.value(1).toString();
            structVentaProductos.operarioParqueadero    = SessionManager::instance().usuarioActual();
            structVentaProductos.inventarioRestante    = QString::number((query.value(4).toInt()-1));

            query.exec(consultaSQL);
            query.next();

            //Resta el producto del stock de productos
            consultaSQL = "UPDATE Productos SET Stock = Stock-1 WHERE Nombre='"+NomProd+"'";
            query.exec(consultaSQL);
            ui->cB_Productos->setCurrentIndex(0);



            pm.printReciboVentaProductos(structVentaProductos);

            RefrescarTablas();


        }
        else{
             qDebug()<<"Rechazado";
        }
    }
}


void MainWindow::on_lineEditRegPago_textChanged(const QString &arg1)
{

    QSqlQueryModel *modelCuatro= new QSqlQueryModel;

    modelCuatro->setQuery("SELECT * FROM Mensualidades WHERE Placa LIKE '"+arg1.toUpper()+"%' ");
    ui->tableViewRegPago->setModel(modelCuatro);
}


void MainWindow::verificarSesionActiva() {
    // 1. Agregamos id_operario a la consulta
    QSqlQuery query("SELECT id_operario, nombre FROM operarios WHERE registrado = '1' LIMIT 1");

    if (query.next()) {
        int id = query.value(0).toInt();
        QString nombre = query.value(1).toString();

        SessionManager::instance().login(id, nombre);

        ui->actionLogin->setVisible(false);
        ui->actionEntrega->setVisible(true);

    } else {
        SessionManager::instance().logout();
        ui->actionLogin->setVisible(true);
        ui->actionEntrega->setVisible(false);
    }
}
