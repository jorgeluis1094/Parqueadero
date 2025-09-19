#include "factura.h"

Factura::Factura()
{


    NombreParqueadero="El Guadual de Armenia";
    direccionParqueadero="Carrera 18 calle 20";
    telefonoParqueadero ="Tel: 3128251598";
    propietarioParqueadero = "Jorge Evelio Enriquez ";
    nITParquieadero ="NIT:16.247.560-5";
    reglamentoParqueadero =
            "1. El Vehiculo se entrega al portador de este recibo.\n En caso de perdida presentar la matricula.\n"
            "2. No aceptamos ordenes escritas o telefonicas.\n"
            "3. Retirado el vehiculo no aceptamos reclamos por danos,\n faltas o averias. Revise el vehiculo antes de salir.\n"
            "4. No respondemos por objetos dejados en el vehiculo.\n"
            "5. No somos responsables por dano o perdidas causadas\n en el parqueadero, siempre y cuando el vehiculo\n no sea entregado personalmente.\n"
            "6. No respondemos por perdidas, deterioros o danos\n ocurridos como consecuencia de incendio, terremoto,\n revolucion u otros eventos que impliquen fuerza mayor.\n"
            "7. El valor minimo se cobra por hora o fraccion.\n"
            "8. No deje llaves.\n"
            "Nota: Todo dano causado por su vehiculo,\n el responsable es el mismo.\n";
    imagenDerecha="/opt/Parqueadero/Imagenes/moto.png";
    imagenIzquierda="/opt/Parqueadero/Imagenes/bandera.png";
}


void Factura::setVehiculo(Vehiculo *vehiculo)
{
    this->vehiculo=vehiculo;
}

void Factura::setTrabajador(Operario *trabajador)
{
    this->trabajador=trabajador;
}

void Factura::Imprimir(QPrinter *printer, int tipoRecibo)
{

    QPainter painter;
    painter.begin(printer);


    int derecho, superior,izquierdo;
    derecho = printer->pageRect().right(); //tomo el valor de los márgenes
    superior = printer->pageRect().top();
    izquierdo = printer->pageRect().left();

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


    //DATOS DEL VEHICULO, DEL OPERARIO Y DE LA HORA//
    rect.translate(0, tamPropietario.lineSpacing());

    QFont ftInfo("Helvetica", 8, QFont::Bold);
    QFontMetrics tamInfo(ftInfo, printer);
    rect.setHeight(tamInfo.lineSpacing());
    rect.translate(0, rect.height());


    //REGLAMENTO DEL PARQUEADERO//
    QFont ftReglas("Arial", 6,QFont::Bold);
    QFontMetrics tamReglas(ftReglas, printer);

    //PLACA

    QFont ftPlaca("Arial", 20, QFont::Bold);
    QFontMetrics tamPlaca(ftPlaca, printer);

    //Placa codigo de barras

    QFont ftCodigoB("Free 3 of 9 Extended", 40);
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
    painter.drawText(rect, Qt::AlignCenter, vehiculo->getPlaca());
    rect.translate(0, rect.height());

    delete vehiculo;
    //FIN DATOS DEL VEHICULO, DEL OPERARIO Y DE LA HORA//

    //REGLAMENTO DEL PARQUEADERO//
    painter.setFont(ftReglas);
    rect.setHeight(tamReglas.lineSpacing()*3);
    painter.drawText(rect, Qt::AlignCenter, "Servicio de Parqueadero:\n Reglamento \n");
    rect.translate(0, rect.height());
    rect.setHeight(tamReglas.lineSpacing()*17);
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
        rect.setHeight(tamReglas.lineSpacing()*17);
        painter.drawText(rect, Qt::AlignCenter, reglamentoParqueadero);
        //FIN DEL REGLAMENTO DEL PARQUEADERO//

        painter.setFont(ftReglas);
        rect.translate(0, rect.height());
        rect.setHeight(tamReglas.lineSpacing()*2);
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
