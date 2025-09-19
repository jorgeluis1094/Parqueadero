#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    QString nombreDB;
    nombreDB.append("/opt/Parqueadero/DB/dbParqueadero.sqlite");

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(nombreDB);

    if( db.open() )
    {
       qDebug()<<"se ha conectado a la DB";
       CrearTablas();
       ConectarTablas();
    }
    else
    {
        qDebug()<<"Error no se a conectado a la DB";
    }

    QObject::connect(ui->pushButtonRegInOut, SIGNAL(clicked()),this, SLOT(on_lineEditRegInOut_returnPressed()));
    //QObject::connect(ui->lineEditCantOtrosArt,SIGNAL(returnPressed()), this, SLOT(on_lineEditOtrosVeh_returnPressed()));
    QObject::connect(ui->actionLogin,SIGNAL(triggered(bool)), this, SLOT(on_pushButtonLogin_clicked()));
    QObject::connect(ui->actionEntrega,SIGNAL(triggered(bool)), this, SLOT(on_pushButtonEntrega_clicked()));
    QObject::connect(ui->tableViewRegVeh,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_tableInOutCar_doubleClicked(QModelIndex)) );
    //QObject::connect(ui->tableViewOtros,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_tableInOutCar_doubleClicked(QModelIndex)) );
    QObject::connect(ui->tableViewRegPago,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_tableInOutCar_doubleClicked(QModelIndex)) );


//verifica si hay operario trabajando para registrar
    QSqlQuery query;
    query.exec("SELECT Nombre FROM Operarios WHERE Registrado ='1'");
    query.next();
    OperarioTurno = query.value(0).toString();
    if( OperarioTurno != "")
    {
        ui->actionLogin->setVisible(false);
        ui->actionEntrega->setVisible(true);

    }
    else
    {
        ui->actionLogin->setVisible(true);
        ui->actionEntrega->setVisible(false);
    }
    query.exec("SELECT Moto, `Valor Maximo Moto`, `Moto-Lavada-1`, `Moto-Lavada-2` FROM Precios");
    query.next();
    valorHoraMoto=query.value(0).toInt();
    valorMaxPagar=query.value(1).toInt();
    valorLavada1=query.value(2).toInt();
    valorLavada2=query.value(3).toInt();
    //valorNocheOtro=query.value(3).toInt();


    query.exec("SELECT * FROM TiemposLimites");
    query.next();
    hhUmbralD=query.value(0).toInt();
    MMUmbralD=query.value(1).toInt();
    ssUmbralD=0;

    hhUmbralN=query.value(2).toInt();
    MMUmbralN=query.value(3).toInt();
    ssUmbralN=0;

    QStringList rutasArchivos, cadenas;
    rutasArchivos<<"/opt/Parqueadero/Archivos/NombreParqueadero.txt"
                 <<"/opt/Parqueadero/Archivos/DireccionParqueadero.txt"
                 <<"/opt/Parqueadero/Archivos/TelParqueadero.txt"
                 <<"/opt/Parqueadero/Archivos/PropietarioParqueadero.txt"
                 <<"/opt/Parqueadero/Archivos/NitParqueadero.txt"
                 <<"/opt/Parqueadero/Archivos/ReglamentoParqueadero.txt"
                 <<"/opt/Parqueadero/Imagenes/moto.png"
                 <<"/opt/Parqueadero/Imagenes/bandera.png";

    QFile file("");
    QTextStream stream(&file);

    for(int iter=0;iter<rutasArchivos.size();iter++)
    {
        file.setFileName(rutasArchivos.at(iter));
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        stream.setDevice(&file);
        cadenas<<stream.readLine();
        file.close();
    }
    NombreParqueadero=cadenas.at(0);
    direccionParqueadero=cadenas.at(1);
    telefonoParqueadero=cadenas.at(2);
    propietarioParqueadero=cadenas.at(3);
    nITParquieadero=cadenas.at(4);

    file.setFileName(rutasArchivos.at(5));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    stream.setDevice(&file);
    while (!stream.atEnd())
    {
                 reglamentoParqueadero += stream.readLine();
                 reglamentoParqueadero +='\n';
    }

    file.close();
    imagenDerecha=rutasArchivos.at(6);
    imagenIzquierda=rutasArchivos.at(7);
    //ui->tableInOutCar->setVisible(false);
    //ui->tableViewOtros->setVisible(false);
    //ui->tableViewRegVeh->setVisible(false);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    impCopia=false;

    VecTipoVeh.push_back("Moto");
    VecTipoVeh.push_back("Moto-Lavada_1");
    VecTipoVeh.push_back("Moto-Lavada_2");


    initInterfaz();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete modelUno;
    delete modelDos;
    delete modelTres;
    delete modeloTablaProductos;
}

void MainWindow::CrearTablas()
{
 /*       QSqlQuery query;
        //Se crean las Tablas
        query.exec("CREATE TABLE IF NOT EXISTS Mensualidades (`Nombre Cliente` VARCHAR(30), Direccion  VARCHAR(30), telefono VARCHAR(15),`Placa Vehiculo` VARCHAR(8), Pago INT, `Inicio Mensualida` DATE, `Fin Mensualidad` DATE, `Fecha de Pago` DATE, `Registrado Por:` VARCHAR(30));");
        query.exec("CREATE TABLE IF NOT EXISTS EntradaVehiculos (Placa VARCHAR(30), Entrada DATETIME, Reg_Ingreso VARCHAR(30),Tipo VARCHAR(30),`Valor Hora` INT);");
        query.exec("CREATE TABLE IF NOT EXISTS RegVehiculos (Placa VARCHAR(20),Entrada DATETIME,Salida DATETIME, Pago INT, Reg_Ingreso VARCHAR(30), Reg_Salida VARCHAR(30),Tipo VARCHAR(30), Tiempo_Total VARCHAR(30));");
        query.exec("CREATE TABLE IF NOT EXISTS TablaOtrosVeh (`Propietario del Articulo` VARCHAR(30),Entrada DATETIME, `Recargo Entrada` INT, Salida DATETIME,`Recargo Salida` INT,Pago INT, Reg_Ingreso VARCHAR(30),Reg_Salida VARCHAR(30),Tipo VARCHAR(20),Tiempo_Total VARCHAR(11) ,Cantidad DECIMAL(5,2));");
        query.exec("CREATE TABLE IF NOT EXISTS Entregas(Operario VARCHAR(30),Entrada DATETIME ,Salida DATETIME, Entrega INT);");
        query.exec("CREATE TABLE IF NOT EXISTS Operarios(Nombre VARCHAR(30), Registrado tinyint);");
        query.exec("CREATE TABLE IF NOT EXISTS TiemposLimites(`Hora Dia` INT, `Minuto Dia` INT, `Hora Noche` INT, `Minuto Noche` INT);");
        query.exec("CREATE TABLE IF NOT EXISTS Precios(Moto VARCHAR(10), Carro VARCHAR(10), `Otra cosa` VARCHAR(10), `Noche Puesto` VARCHAR(10), `Valor Maximo Moto` VARCHAR(10));");

        query.exec("SELECT count(*) FROM Operarios");
        query.next();
        if(query.value(0).toInt() == 0 )
        {
            query.exec("INSERT INTO Precios VALUES (500,1500,1500,1500,2000); ");
            query.exec("INSERT INTO TiemposLimites VALUES (10,30,19,00);");
            query.exec("INSERT INTO Operarios VALUES ('Jorge',0);");
        }
*/
}

void MainWindow::ConectarTablas()
{

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

}

void MainWindow::imprimir(int tipoRecibo)
{

    // Crear una QPageLayout
    QPageLayout pageLayout;

    // Definir un tamaño de papel personalizado para la impresora térmica Epson T20
    // Supongamos que el tamaño del papel es 80 mm de ancho y 200 mm de alto
    QPageSize customPageSize(QSizeF(80, 200), QPageSize::Millimeter);
    pageLayout.setPageSize(customPageSize);

    // Establecer las márgenes de la página
    QMarginsF margins(1.0, 1.0, 1.0, 1.0); // Márgenes en puntos (10 puntos en cada lado)
    pageLayout.setMargins(margins);


    QPrinter printer(printer.HighResolution);
    printer.setColorMode(printer.Color);
    QSizeF tamPaper(70,150);

    // Aplicar la configuración de la página al QPrinter
    printer.setPageLayout(pageLayout);

    //printer.setPageMargins(1,1,1,1,QPrinter::Millimeter); //Modificar
    //printer.setPaperSize(tamPaper,QPrinter::Millimeter);  //Modificar
    printDocument(&printer, tipoRecibo);
}



void MainWindow::printDocument(QPrinter *printer, int tipoRecibo)
{
    QPainter painter;
    painter.begin(printer);


    //int derecho, superior,izquierdo;
    //derecho = printer->pageRect().right(); //tomo el valor de los márgenes
    //superior = printer->pageRect().top();
    //izquierdo = printer->pageRect().left();


    // Obtener los márgenes de la página
    //QMarginsF currentMargins = printer->pageLayout.margins();
    int derecho = printer->pageLayout().fullRect().right();
    int superior = printer->pageLayout().fullRect().top();
    int izquierdo = printer->pageLayout().fullRect().left();

    //SE REALIZA ENCABEZADO
    QFont ftTitulo("Arial", 11, QFont::Bold);
    QFontMetrics tamTitulo(ftTitulo, printer);
    QRect rect(izquierdo, superior, derecho, tamTitulo.lineSpacing());

    QRectF target= rect;
    target.setHeight(500);

    target.setWidth(derecho/2);
    QImage image(imagenIzquierda);
    painter.drawImage(target, image);

    target.translate(derecho/2,0);
    QImage image2(imagenDerecha);
    painter.drawImage(target, image2);
    rect.translate(0,target.height());


    painter.setFont(ftTitulo);
    painter.drawText(rect, Qt::AlignCenter, "***Parqueadero***");
    //rect.translate(0, rect.height());
    rect.translate(0, tamTitulo.lineSpacing());

    painter.drawText(rect, Qt::AlignCenter, NombreParqueadero);
    //rect.translate(0, rect.height());
    rect.translate(0, tamTitulo.lineSpacing());

    QFont ftDireccion("Arial", 7, QFont::Black);
    painter.setFont(ftDireccion);
    QFontMetrics tamDireccion(ftDireccion, printer);
    painter.drawText(rect, Qt::AlignCenter, direccionParqueadero);
    rect.translate(0, tamDireccion.lineSpacing());

    QFont ftTelefono("Arial", 7, QFont::Black);
    painter.setFont(ftTelefono);
    QFontMetrics tamTelefono(ftTelefono, printer);
    painter.drawText(rect, Qt::AlignCenter, telefonoParqueadero);
    rect.translate(0, tamTelefono.lineSpacing());

    QFont ftPropietrario("Arial", 7, QFont::Black);
    painter.setFont(ftPropietrario);
    QFontMetrics tamPropietario(ftPropietrario, printer);
    painter.drawText(rect, Qt::AlignCenter, propietarioParqueadero+nITParquieadero);


    //TERMINA ENCABEZADO//
    if(impCopia)
    {   painter.setFont(ftTitulo);
        rect.translate(0, tamPropietario.lineSpacing());
        painter.drawText(rect, Qt::AlignCenter, "Este Recibo Es Una Copia!!!");
        impCopia=false;
    }

    //DATOS DEL VEHICULO, DEL OPERARIO Y DE LA HORA//
    rect.translate(0, tamPropietario.lineSpacing());

    QFont ftInfo("Helvetica", 8, QFont::Bold);
    QFontMetrics tamInfo(ftInfo, printer);
    rect.setHeight(tamInfo.lineSpacing());
    rect.translate(0, rect.height());


    //REGLAMENTO DEL PARQUEADERO//
    QFont ftReglas("Arial",6,QFont::Bold);
    QFontMetrics tamReglas(ftReglas, printer);

    //PLACA
    QFont ftPlaca("Arial", 20, QFont::Bold);
    QFontMetrics tamPlaca(ftPlaca, printer);

    //Placa codigo de barras
    QFont ftCodigoB("New", 40);
    QFontMetrics tamCodigoB(ftCodigoB, printer);

    switch(tipoRecibo){

    case 0://para vehiculos que entran al parqueadero

            painter.setFont(ftInfo);

            painter.drawText(rect, Qt::AlignJustify, "Atendido Por: "+OperarioTurno);
            rect.translate(0, rect.height());

            painter.drawText(rect, Qt::AlignJustify, "Fecha: "+vehiculo->getHoraEntrada().toString("dd-MM-yyyy"));
            rect.translate(0, rect.height());

            painter.drawText(rect, Qt::AlignJustify, "Hora de Entrada: "+vehiculo->getHoraEntrada().toString("hh:mm:ss"));
            rect.translate(0, rect.height());

            painter.drawText(rect, Qt::AlignJustify, "Tipo de Vehiculo: "+vehiculo->getTipoVehiculo());
            rect.translate(0, rect.height());

            painter.drawText(rect, Qt::AlignJustify, "Cantidad: "+QString::number(vehiculo->getCantidad() ));
            rect.translate(0, rect.height());

            painter.drawText(rect, Qt::AlignJustify, "Placa: ");
            rect.translate(0, rect.height());

            painter.setFont(ftPlaca);
            rect.setHeight(tamPlaca.lineSpacing());
            painter.drawText(rect, Qt::AlignHCenter, "***  "+vehiculo->getPlaca()+"  ***");
            rect.translate(0, rect.height());

            painter.setFont(ftCodigoB);
            painter.drawText(rect, Qt::AlignCenter, "*"+vehiculo->getPlaca()+"*");
            rect.translate(0, rect.height());

            delete vehiculo;
            //FIN DATOS DEL VEHICULO, DEL OPERARIO Y DE LA HORA//

            //REGLAMENTO DEL PARQUEADERO//
            painter.setFont(ftReglas);
            rect.setHeight(tamReglas.lineSpacing()*3);
            painter.drawText(rect, Qt::AlignCenter, "Servicio de Parqueadero:\n Reglamento \n");
            rect.translate(0, rect.height());
            rect.setHeight(tamReglas.lineSpacing()*18);
            painter.drawText(rect, Qt::AlignCenter, reglamentoParqueadero);
            //FIN DEL REGLAMENTO DEL PARQUEADERO//

            painter.setFont(ftReglas);
            rect.translate(0, rect.height());
            rect.setHeight(tamReglas.lineSpacing()*2);
            painter.drawText(rect, Qt::AlignJustify, "Ing. Jorge Luis Enriquez Gonzalez.\n Tel: 3113718421");

        break;

    case 1: //imprime recibos para vehiculos que salen del parqueadero

        painter.setFont(ftInfo);

        painter.drawText(rect, Qt::AlignJustify, "Placa: "+vehiculo->getPlaca());
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Tipo de Vehiculo: "+vehiculo->getTipoVehiculo());
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Registro la entrada: "+vehiculo->getNomRegIn());
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Registro la salida: "+vehiculo->getNomRegOut());
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Entrada: "+vehiculo->getHoraEntrada().toString("hh:mm:ss dd-MM-yyyy"));
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Salida: "+vehiculo->getHoraSalida().toString("hh:mm:ss  dd-MM-yyyy"));
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Tiempo de Parqueo: "+vehiculo->getTiempoParqueo());
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Total Pagado: "+QString::number(vehiculo->getValorPagado()));
        rect.translate(0, rect.height());

        painter.setFont(ftReglas);
        rect.translate(0, rect.height());
        rect.setHeight(tamReglas.lineSpacing()*2);
        painter.drawText(rect, Qt::AlignJustify, "Ing. Jorge Luis Enriquez Gonzalez.\n Tel: 3113718421");

        delete vehiculo;
        //FIN DATOS DEL VEHICULO, DEL OPERARIO Y DE LA HORA//
            break;
    case 2://Impresion para Mensualidades

        painter.setFont(ftInfo);

        painter.drawText(rect, Qt::AlignCenter, "Mensualidad");
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Tipo Vehiculo: "+vehiculo->getTipoVehiculo());
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Placa: "+vehiculo->getPlaca());
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Propietario: "+vehiculo->getPropietario());
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Pago Por: $"+QString::number(vehiculo->getValorPagado()));
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Fecha Inicio: "+vehiculo->getHoraEntrada().toString("dd-MM-yyyy"));
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Fecha Finalizacion: "+vehiculo->getHoraSalida().toString("dd-MM-yyyy"));
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Atendido Por: "+vehiculo->getNomRegIn());
        rect.translate(0, rect.height());

        delete vehiculo;

        //REGLAMENTO DEL PARQUEADERO//
        painter.setFont(ftReglas);
        rect.setHeight(tamReglas.lineSpacing()*3);
        painter.drawText(rect, Qt::AlignCenter, "Servicio de Parqueadero:\n Reglamento \n");
        rect.translate(0, rect.height());
        rect.setHeight(tamReglas.lineSpacing()*18);//17
        painter.drawText(rect, Qt::AlignCenter, reglamentoParqueadero);
        //FIN DEL REGLAMENTO DEL PARQUEADERO//

        painter.setFont(ftReglas);
        rect.translate(0, rect.height());
        rect.setHeight(tamReglas.lineSpacing()*2);//2
        painter.drawText(rect, Qt::AlignJustify, "Ing. Jorge Luis Enriquez Gonzalez.\n Tel: 3113718421");
            break;
    case 3:
//impresion de recibo de salida con la totalidad realizado

        painter.setFont(ftInfo);

        painter.drawText(rect, Qt::AlignJustify, "Operario: "+trabajador->getNombre());
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Hora Inicio: "+trabajador->getHoraEntrada());
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Hora Salida: "+trabajador->getHoraSalida());
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Total Mensualidades: $"+QString::number(trabajador->getTotalMensualidades()));
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Numero Mensualidades: "+QString::number(trabajador->getNumMensualidadesPagadas()));
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Total Motos: $"+QString::number(trabajador->getTotalMotos()));
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Total Carros: $"+QString::number(trabajador->getTotalCarros()));
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Total Otros Articulos: $"+QString::number(trabajador->getTotalOtrosArticulos()));
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Total Otros Pagos: $"+QString::number(trabajador->getTotalOtrosPagos()));
        rect.translate(0, rect.height());

        painter.drawText(rect, Qt::AlignJustify, "Entrega Total: $"+QString::number(trabajador->getTotalRealizado()));
        rect.translate(0, rect.height());

        painter.setFont(ftReglas);
        rect.translate(0, rect.height());
        rect.setHeight(tamReglas.lineSpacing()*2);
        painter.drawText(rect, Qt::AlignJustify, "Ing. Jorge Luis Enriquez Gonzalez.\n Tel: 3113718421");

        delete trabajador;

        break;
    }
    painter.end();
}

void MainWindow::on_pushButtonRegistrar_clicked()//Registra una mensualidad
{
    if (OperarioTurno != "")
    {
            QDateTime fechaActual = QDateTime();
            QSqlQuery query;
            QString nombre,direccion, telefono, placa, fechaInicio,fechaFin, valorPago, fechapago;

            nombre = ui->lineEditNombre->text();
            direccion = ui->lineEditDireccion->text();
            telefono = ui->lineEditTelefono->text();
            placa = ui->lineEditPlaca->text().toUpper();
            fechaInicio = ui->dateEdit->text();
            fechaFin = ui->dateEdit_2->text();
            valorPago = ui->lineEditPago->text();
            fechapago = fechaActual.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

            if(!nombre.isEmpty() && !placa.isEmpty() && !valorPago.isEmpty() )
            {
                    query.exec("INSERT INTO Mensualidades "
                               "(Placa, Nombre, Telefono, Direccion, Inicio, Fin, Fecha_Pago, Valor, Registro)"
                               "VALUES ( '"+placa+"' , '"+nombre+"' , '"+telefono+"' , '"+direccion+"' , '"+fechaInicio+"' , '"+fechaFin+"' , '"+fechapago+"','"+valorPago+"', '"+OperarioTurno+"')");

                    query.exec("INSERT INTO RegVehiculos"
                            "(Placa,Entrada,Salida,Pago,Reg_Ingreso, Reg_Salida, Tipo,Tiempo_Total)"
                               "VALUES ( '"+placa+"' , '"+fechapago+"' , '"+fechapago+"' , '"+valorPago+"' , '"+OperarioTurno+"', '"+OperarioTurno+"', 'Moto','Mensualidad')");

                    vehiculo = new Vehiculo(placa,"Moto",ui->dateEdit->dateTime(),OperarioTurno);
                    vehiculo->HoraSalida(ui->dateEdit_2->dateTime());
                    vehiculo->ValorPagado(valorPago.toInt());
                    vehiculo->NomRegOut(OperarioTurno);
                    vehiculo->TipoVehiculo("Moto");
                    vehiculo->Propietario(nombre);

                    RefrescarTablas();

                    imprimir(2);//imprimir mensualidad
            }
            else
                QMessageBox::critical(this, NombreParqueadero,tr("<font size = 15 color = black >Datos Importantes Sin LLenar"));
     }
    else
        QMessageBox::critical(this, NombreParqueadero,tr("<font size = 15 color = black >Debe Registrarse"));
}

void MainWindow::on_lineEditRegInOut_returnPressed()//registra la entrada de un usuario de moto o carro
{

    if(OperarioTurno=="")
    {
        QMessageBox::critical(this, NombreParqueadero,tr("<font size = 15 color = black >Debe Registrarse"));
    }
    else  if(ui->lineEditRegInOut->text().length() <= 4 ){
        QMessageBox::warning(this, NombreParqueadero,tr("<font size = 15 color = black >No es placa de moto"));
    }
    else
    {
        QSqlQuery query;
        //Obtiene el dato que esta en el widget de  ingreso de la placa
        QString Placa = ui->lineEditRegInOut->text().toUpper();
        QString TipoVeh = "Moto"; //ui->comboBoxVehiculos->currentText();

        //Strings Para Cadena de Caracteres
        QString Datos;
        QString Tabla;
        QString Parametros;

        QDateTime dateNow;
        QDateTime horaEntrada;
        QDateTime horaSalida;
        QString OpeRegIn;
        //QString OpeRegOut;
        QString tim;
        int valorHora=0;
        int segT=0;
        int valoraPagar=0;
        int Hora=0, Min=0;
        int consMotoCarro = 0;
        int consMen = 0;

        //Verificar Si está o No en la Tabla EntradaVehiculos
        Datos = "count(*)";
        Tabla = "EntradaVehiculos";
        Parametros = "Placa='"+Placa+"'";
        query = RealizarConsulta(Datos,Tabla,Parametros);
        consMotoCarro = query.value(0).toInt();

        //Verificar Si esta o No en la Tabla Mensualidades
        Datos = "count(*)";
        Tabla = "Mensualidades";
        Parametros = "`Placa Vehiculo`='"+Placa+"'";
        query = RealizarConsulta(Datos,Tabla,Parametros);
        consMen = query.value(0).toInt();

        if( consMotoCarro && !consMen) {
            valorHora=valorHoraMoto;

            //CobrarMoto(valorHora,Placa);
            //Está Registrado. Se Debe Cobrar
            Datos="Placa, Ingreso, Operario, Tipo";
            Tabla="EntradaVehiculos";
            Parametros="Placa='"+Placa+"'";

            query=RealizarConsulta(Datos,Tabla,Parametros);
            Placa = query.value(0).toString();
            horaEntrada = query.value(1).toDateTime();
            OpeRegIn = query.value(2).toString();
            TipoVeh = query.value(3).toString();
            segT = DiferenciaHora(query.value(1).toDateTime(),dateNow);
            tim= HMS2seg(Hora,Min,segT);
            valoraPagar=CobroXMotos(Hora,Min,5,valorHora);

            vehiculo = new Vehiculo(Placa,TipoVeh,horaEntrada,OpeRegIn);
            vehiculo->HoraSalida(horaSalida.currentDateTime());
            vehiculo->NomRegOut(OperarioTurno);
            vehiculo->TiempoParqueo(tim);
            vehiculo->ValorPagado(valoraPagar);

            if (valoraPagar > valorMaxPagar)
            {
                int dias = Hora/12;//para cobrar los dias que ha estado guardado
                Hora=Hora%12;

                if(Hora < valorMaxPagar/valorHora)
                    vehiculo->ValorPagado(valorMaxPagar*dias+Hora*valorHora);
                else
                    vehiculo->ValorPagado(valorMaxPagar*dias);
            }

            switch (VecTipoVeh.indexOf(TipoVeh)) {
            case 1:
                if(Hora < valorMaxPagar/valorHora)
                    vehiculo->ValorPagado(valoraPagar+valorLavada1-valorHora);
                else
                    vehiculo->ValorPagado(valoraPagar+valorLavada1);
                qDebug()<<"Esto es lavada 1";
                break;
            case 2:
                if(Hora < valorMaxPagar/valorHora)
                    vehiculo->ValorPagado(valoraPagar+valorLavada2-valorHora);
                else
                    vehiculo->ValorPagado(valoraPagar+valorLavada2);
                qDebug()<<"Esto es lavada 2";
                break;
            default:
                break;
            }

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this,NombreParqueadero,"<font size = 15 color = black >"+Placa+" debe pagar: $" +QString::number(vehiculo->getValorPagado()),
                                          QMessageBox::Yes | QMessageBox::No);


                if (reply == QMessageBox::Yes && consMotoCarro){
                    //realizar el cobro
                    IngresarFilaTabla(1,vehiculo,QString::number(valorHoraMoto));
                    Tabla="EntradaVehiculos";
                    Parametros="Placa='"+Placa+"'";
                    BorrarFilaTabla(Tabla,Parametros);
                }


        }
        else if(consMen){
            QMessageBox::warning(this, NombreParqueadero,tr("<font size = 15 color = black >Usuario de Mensualidad"));
        }
        else
        {
            //No esta Registrado. Se Debe Registrar(Listo)
            QMessageBox::StandardButton QuesImprRec;
            QuesImprRec = QMessageBox::question(this,NombreParqueadero,"Registrar Entrada de Vehiculo?",
                                                   QMessageBox::Yes | QMessageBox::No);

                if (QuesImprRec == QMessageBox::Yes){

                if (ui->rB_Normal->isChecked()){
                        vehiculo = new Vehiculo(Placa,TipoVeh,dateNow.currentDateTime(),OperarioTurno);
                        IngresarFilaTabla(0,vehiculo,QString::number(valorHoraMoto));
                    }
                else if(ui->rB_Lavada1->isChecked()){
                    vehiculo = new Vehiculo(Placa,TipoVeh+"-Lavada_1",dateNow.currentDateTime(),OperarioTurno);
                    IngresarFilaTabla(0,vehiculo,QString::number(valorHoraMoto));
                }
                else if(ui->rB_Lavada2->isChecked()){
                    vehiculo = new Vehiculo(Placa,TipoVeh+"-Lavada_2",dateNow.currentDateTime(),OperarioTurno);
                    IngresarFilaTabla(0,vehiculo,QString::number(valorHoraMoto));
                }
                else
                    qDebug()<<"Error al ingresar vehiculo";

                ui->rB_Normal->setChecked(true);
                imprimir(0);//imprimir recibo de entrada
                }
              }

    }

    RefrescarTablas();

}

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
        query.exec("SELECT * FROM Operarios Where Registrado='0'");

        ComBoxNombresOperarios->addItem("");
        while(query.next()){
            ComBoxNombresOperarios->addItem(query.value(0).toString());
        }

    QObject::connect(ComBoxNombresOperarios, SIGNAL(currentTextChanged(QString)),
                this, SLOT(setUsuario(QString)) );

    WinLogin->show();
}


void MainWindow::setUsuario(QString Nombre)//actualida los datos para el operario en turno
{

    if(Nombre != ""){

        QSqlQuery query;
        query.exec("Update Operarios Set Registrado = '1' where  Nombre= '"+Nombre+"'");
        OperarioTurno=Nombre;
        QString HoraEntrada = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        WinLogin->close();

        ui->actionLogin->setVisible(false);
        ui->actionEntrega->setVisible(true);

        query.exec("INSERT INTO Entregas"
                   "(Operario, Entrada, Salida, Entrega)"
                   "VALUES('"+OperarioTurno+"','"+HoraEntrada+"','NULL','NULL') ");
    }
}


void MainWindow::on_pushButtonEntrega_clicked()//realiza la suma del producido y genera el recibo
{
    QSqlQuery query;

    //Strings Para Cadena de Caracteres
    QString Datos;
    QString Tabla;
    QString Parametros;
    QString NombreParqueadero;

    Datos = "SUM(Pago)";
    Tabla = "RegVehiculos";
    Parametros = "Reg_Salida = '"+OperarioTurno+"'";

    double dinero;

    query = RealizarConsulta(Datos,Tabla,Parametros);

    dinero = query.value(0).toDouble();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,NombreParqueadero,
                                  "Total Realizado: $"+QString::number(dinero)+'\n'+"Realizar Entrega?",
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){

        DineroTurno = dinero;
        QString HoraSalida = QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss");

        query.exec("SELECT Entrada FROM Entregas ORDER BY Entrada DESC LIMIT 1 ");
        query.next();
        QDateTime Entrada=query.value(0).toDateTime();
        QString HoraEntrada = Entrada.toString("yy-MM-dd hh:mm:ss");

        query.exec("select Sum(Pago) from RegVehiculos where Tipo='Otro Articulo'");
        query.next();
        int vpOtrosArticulos = query.value(0).toInt();

        query.exec(" select Sum(Pago) from RegVehiculos where Tiempo_Total='Mensualidad'");
        query.next();
        int vpMensualidad = query.value(0).toInt();

        query.exec("select Count(*) from RegVehiculos where Tiempo_Total='Mensualidad'");
        query.next();
        int numMensualidadesPagadas = query.value(0).toInt();

        query.exec("select Sum(Pago) from RegVehiculos where Tipo='Moto'");
        query.next();
        int vpMotos = query.value(0).toInt()-vpMensualidad;

        query.exec("select Sum(Pago) from RegVehiculos where Tipo='Carro'");
        query.next();
        int vpCarro = query.value(0).toInt();

        query.exec("select Sum(Pago) from RegVehiculos where Tipo='Otro Pago'");
        query.next();
        int vpOtrosPagos = query.value(0).toInt();


        Tabla="RegVehiculos";
        Parametros = "Reg_Salida='"+OperarioTurno+"'";
        BorrarFilaTabla(Tabla,Parametros);

        Tabla = "TablaOtrosVeh";
        BorrarFilaTabla(Tabla,Parametros);

        query.exec("UPDATE Entregas SET"
                   "Salida='"+HoraSalida+"',"
                   "Entrega='"+QString::number(DineroTurno)+"' "
                   "where Entrada='"+HoraEntrada+"' ");

        query.exec("Update Operarios Set Registrado = '0'");

        trabajador=new Operario(OperarioTurno);
        trabajador->HoraEntrada(HoraEntrada);
        trabajador->HoraSalida(HoraSalida);
        trabajador->TotalRealizado(DineroTurno);
        trabajador->TotalMotos(vpMotos);
        trabajador->TotalCarros(vpCarro);
        trabajador->TotalMensualidades(vpMensualidad);
        trabajador->TotalOtrosArticulos(vpOtrosArticulos);
        trabajador->NumMensualidadesPagadas(numMensualidadesPagadas);
        trabajador->TotalOtrosPagos(vpOtrosPagos);
        OperarioTurno="";
        imprimir(3);//imprimir recibo de entrega

        ui->actionLogin->setVisible(true);
        ui->actionEntrega->setVisible(false);

        //Generar Resivo De Salida Con el Valor total del Dia

    }
    RefrescarTablas();
}


void MainWindow::imprimirReciboTabla1(void)// imprime un recibo auxiliar de la tabla de vehiculos dentro
{
    QSqlQuery query;
    QString Placa= lineEditsRE->text();
    query.exec("SELECT * FROM EntradaVehiculos  WHERE Placa='"+Placa+"' ");
    query.next();
    vehiculo = new Vehiculo(query.value(0).toString(),query.value(3).toString(),query.value(1).toDateTime(),query.value(2).toString());
    impCopia=true;
    imprimir(0);
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
    imprimir(1);

    ReciboTablas->close();
}

void MainWindow::imprimirReciboTablaOtros(void)//imprime un recibo auxiliar de la tabla de Otras Cosas
{
    QSqlQuery query;
    QString Placa= lineEditsRE->text();
    query.exec("SELECT * FROM TablaOtrosVeh WHERE `Propietario del Articulo`='"+Placa+"' ");
    query.next();
    vehiculo = new Vehiculo(query.value(0).toString(),query.value(8).toString(),query.value(1).toDateTime(),query.value(6).toString());
    impCopia=true;
    imprimir(0);
    ReciboTablas->close();

}

void MainWindow::on_lineEditRegPago_editingFinished()//busca y muestra en tabla los usuarios registrados en mensalidad
{

    QString PlacaPago="";
    QSqlQueryModel *modelCuatro= new QSqlQueryModel;

    ui->tableViewRegPago->setModel(modelCuatro);
    PlacaPago=ui->lineEditRegPago->text().toUpper();

    modelCuatro->setQuery("SELECT * FROM Mensualidades WHERE Placa ='"+PlacaPago+"' ");
    ui->tableViewRegPago->setModel(modelCuatro);
}


void MainWindow::on_pushButtonRegPago_clicked()//actualiza el pago de una mensualidad
{
    if(OperarioTurno != "" && !ui->lineEditRegPagoPlata->text().isEmpty() && ui->lineEditRegPagoPlata->text().toInt()>0){

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
                       "Fecha_Pago=strftime('%Y-%m-%d %H:%M:%S', 'now'), "
                       "Registro='"+OperarioTurno+"', "
                       "Valor='"+ui->lineEditRegPagoPlata->text().toUpper()+"' "
                       "WHERE "
                       "Placa='"+placa+"' ");

        //Inbresa el dinero recibido en la tabla de registro de salida donde estan los datos que se sumaran

            query.exec("INSERT INTO RegVehiculos"
                "(Placa,Entrada,Salida,Pago,Reg_Ingreso, Reg_Salida, Tipo,Tiempo_Total)"
                   "VALUES ( '"+placa+"', strftime('%Y-%m-%d %H:%M:%S', 'now'), strftime('%Y-%m-%d %H:%M:%S', 'now') , '"+ui->lineEditRegPagoPlata->text()+"', '"+OperarioTurno+"', '"+OperarioTurno+"', 'Moto','Mensualidad')");

            query.exec("SELECT Placa, Nombre, Valor, Inicio, Fin, Registro: FROM Mensualidades WHERE "
                       "Nombre='"+ui->lineEditRegPago->text()+"' "
                       "Placa='"+ui->lineEditRegPago->text().toUpper()+"' ");
            query.next();
            vehiculo = new Vehiculo(query.value(0).toString(), "Moto", query.value(3).toDateTime(), query.value(5).toString());
            vehiculo->Propietario(query.value(1).toString());
            vehiculo->ValorPagado(query.value(2).toInt());
            vehiculo->HoraSalida(query.value(4).toDateTime());
            imprimir(2);//imprime un recibo para mensualidad

        //Actualiza la tabla de mensualidades y la de ingreso
        //y salida de veiculos donde se registra la placa y el pago para sumar a lo que debe entregar el operario
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

    //modeloTablaOtros->select();
    //ui->tableViewOtros->setModel(modeloTablaOtros);


    ui->lineEditNombre->clear();
    ui->lineEditDireccion->clear();
    ui->lineEditTelefono->clear();
    ui->lineEditPlaca->clear();
    ui->lineEditPago->clear();
    ui->lineEditRegInOut->clear();
    //ui->lineEditRecibeCantidad->clear();
    //ui->lineEditrecibeDe->clear();
    //ui->lineEditOtrosVeh->clear();
    //ui->lineEditCantOtrosArt->clear();
}

void MainWindow::on_tableInOutCar_doubleClicked(const QModelIndex &index)
{

    ReciboTablas = new QDialog(this);
    ReciboTablas->setWindowTitle("Imprimir Recibo");
    ReciboTablas->resize(450,200);


    QLabel *labelPlaca = new QLabel("Ingrese La Placa", ReciboTablas);
    labelPlaca->setGeometry(100,10,250,20);
    lineEditsRE = new QLineEdit(ReciboTablas);
    lineEditsRE->setGeometry(100,30,250,30);

    QPushButton *buttonT1 = new QPushButton("Tabla de Registros Entrada:",ReciboTablas);
    buttonT1->setGeometry(100,70,250,30);

    QPushButton *buttonT2 = new QPushButton("Tabla de Registros Salida:",ReciboTablas);
    buttonT2->setGeometry(100,110,250,30);

    QPushButton *buttonT3 = new QPushButton("Tabla de Otros Articulos:",ReciboTablas);
    buttonT3->setGeometry(100,150,250,30);

    QObject::connect(buttonT1, SIGNAL(clicked()),this, SLOT(imprimirReciboTabla1()));
    QObject::connect(buttonT2, SIGNAL(clicked()),this,SLOT(imprimirReciboTabla2()));
    QObject::connect(buttonT3, SIGNAL(clicked()),this,SLOT(imprimirReciboTablaOtros()));
    ReciboTablas->show();

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

void MainWindow::initInterfaz()
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

}

void MainWindow::on_pB_VentaOtroProducto_clicked()
{

    if(OperarioTurno=="")
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
                          "VALUES ( '"+query.value(0).toString()+"' , '"+query.value(1).toString()+"' , '"+query.value(2).toString()+"' , '"+query.value(3).toString()+"' , '"+OperarioTurno+"', '"+OperarioTurno+"', 'Producto','Producto')";

            query.exec(consultaSQL);
            query.next();

            //Resta el producto del stock de productos
            consultaSQL = "UPDATE Productos SET Stock = Stock-1 WHERE Nombre='"+NomProd+"'";
            query.exec(consultaSQL);
            ui->cB_Productos->setCurrentIndex(0);

            RefrescarTablas();


        }
        else{
             qDebug()<<"Rechazado";
        }
    }
}


void MainWindow::on_lineEditFiltarmensualidad_textChanged(const QString &arg1)
{
    QSqlQueryModel *modelCuatro= new QSqlQueryModel;


    modelCuatro->setQuery("SELECT * FROM Mensualidades WHERE Placa='"+ui->lineEditRegPago->text().toUpper()+"' ");
    ui->tableViewRegPago->setModel(modelCuatro);
}

