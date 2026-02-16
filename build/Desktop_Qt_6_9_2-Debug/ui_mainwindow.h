/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "relojdigital.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionGuardar;
    QAction *actionGuardar_2;
    QAction *actionGuardar_3;
    QAction *actionSalir;
    QAction *actionAgregar_Operario;
    QAction *actionLogin;
    QAction *actionEntrega;
    QAction *actionIngresar_Productos;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_19;
    QTabWidget *tabWidget;
    QWidget *Ingreso;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_14;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_13;
    QVBoxLayout *verticalLayout_6;
    QLabel *labelPlaca;
    QHBoxLayout *horizontalLayout_22;
    QLineEdit *lineEditRegInOut;
    QPushButton *pushButtonRegInOut;
    QVBoxLayout *verticalLayout_12;
    QSpacerItem *verticalSpacer_4;
    QRadioButton *rB_Normal;
    QRadioButton *rB_Lavada1;
    QRadioButton *rB_Lavada2;
    QSpacerItem *verticalSpacer_6;
    QVBoxLayout *verticalLayout_3;
    relojdigital *lcdNumber;
    QFrame *line;
    QVBoxLayout *verticalLayout_9;
    QCheckBox *cbRegEntrada;
    QTableView *tableInOutCar;
    QVBoxLayout *verticalLayout_13;
    QCheckBox *cbRegSalida;
    QTableView *tableViewRegVeh;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_3;
    QTabWidget *tabWidgetRegPago;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_15;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_10;
    QLineEdit *lineEditRegPago;
    QSpacerItem *horizontalSpacer_4;
    QFrame *line_5;
    QTableView *tableViewRegPago;
    QFrame *line_6;
    QHBoxLayout *horizontalLayout_21;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_12;
    QLineEdit *lineEditRegPagoPlata;
    QSpacerItem *horizontalSpacer_12;
    QVBoxLayout *verticalLayout_17;
    QLabel *label_16;
    QLineEdit *lineEditDiasPagados;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_19;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *pushButtonRegPago;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout;
    QFrame *line_4;
    QHBoxLayout *horizontalLayout_16;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *lineEditPlacaMensual;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label;
    QLineEdit *leCasilleroMensual;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_6;
    QLineEdit *lineEditPagoMensual;
    QFrame *line_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QLineEdit *lineEditNombreMensual;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *lineEditDireccionMensual;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *lineEditTelefonoMensual;
    QFrame *line_3;
    QLabel *labelFechaInicio;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_6;
    QDateEdit *dateEdit;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonRegistrar;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_21;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_7;
    QComboBox *comboBoxVerMensualidad;
    QVBoxLayout *verticalLayout_20;
    QLabel *lbBuscarMensualidad;
    QLineEdit *lineEditFiltarmensualidad;
    QSpacerItem *horizontalSpacer;
    QTableView *tableView;
    QWidget *OtrosPagos;
    QVBoxLayout *verticalLayout_18;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout;
    QLabel *lb_Producto;
    QComboBox *cB_Productos;
    QSpacerItem *horizontalSpacer_3;
    QLabel *lb_ValorProducto;
    QPushButton *pB_VentaOtroProducto;
    QTableView *tW_Producto_Sel;
    QMenuBar *menuBar;
    QMenu *menuMenu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setWindowModality(Qt::WindowModality::ApplicationModal);
        MainWindow->resize(786, 620);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamilies({QString::fromUtf8("Liberation Serif")});
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        font.setStyleStrategy(QFont::PreferAntialias);
        MainWindow->setFont(font);
        MainWindow->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        actionGuardar = new QAction(MainWindow);
        actionGuardar->setObjectName("actionGuardar");
        actionGuardar_2 = new QAction(MainWindow);
        actionGuardar_2->setObjectName("actionGuardar_2");
        actionGuardar_3 = new QAction(MainWindow);
        actionGuardar_3->setObjectName("actionGuardar_3");
        actionSalir = new QAction(MainWindow);
        actionSalir->setObjectName("actionSalir");
        actionAgregar_Operario = new QAction(MainWindow);
        actionAgregar_Operario->setObjectName("actionAgregar_Operario");
        actionLogin = new QAction(MainWindow);
        actionLogin->setObjectName("actionLogin");
        actionEntrega = new QAction(MainWindow);
        actionEntrega->setObjectName("actionEntrega");
        actionIngresar_Productos = new QAction(MainWindow);
        actionIngresar_Productos->setObjectName("actionIngresar_Productos");
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        verticalLayout_19 = new QVBoxLayout(centralWidget);
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setContentsMargins(11, 11, 11, 11);
        verticalLayout_19->setObjectName("verticalLayout_19");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        Ingreso = new QWidget();
        Ingreso->setObjectName("Ingreso");
        verticalLayout_14 = new QVBoxLayout(Ingreso);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName("verticalLayout_14");
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName("verticalLayout_6");
        labelPlaca = new QLabel(Ingreso);
        labelPlaca->setObjectName("labelPlaca");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Liberation Serif")});
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setStrikeOut(false);
        font1.setStyleStrategy(QFont::PreferAntialias);
        labelPlaca->setFont(font1);

        verticalLayout_6->addWidget(labelPlaca);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName("horizontalLayout_22");
        lineEditRegInOut = new QLineEdit(Ingreso);
        lineEditRegInOut->setObjectName("lineEditRegInOut");
        lineEditRegInOut->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEditRegInOut->sizePolicy().hasHeightForWidth());
        lineEditRegInOut->setSizePolicy(sizePolicy2);
        lineEditRegInOut->setMinimumSize(QSize(0, 0));
        lineEditRegInOut->setMaximumSize(QSize(16777215, 16777215));
        lineEditRegInOut->setSizeIncrement(QSize(0, 0));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Cantarell")});
        font2.setPointSize(20);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setStyleStrategy(QFont::PreferAntialias);
        lineEditRegInOut->setFont(font2);
        lineEditRegInOut->setInputMethodHints(Qt::InputMethodHint::ImhUppercaseOnly);
        lineEditRegInOut->setMaxLength(12694);
        lineEditRegInOut->setEchoMode(QLineEdit::EchoMode::Normal);

        horizontalLayout_22->addWidget(lineEditRegInOut);


        verticalLayout_6->addLayout(horizontalLayout_22);

        pushButtonRegInOut = new QPushButton(Ingreso);
        pushButtonRegInOut->setObjectName("pushButtonRegInOut");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButtonRegInOut->sizePolicy().hasHeightForWidth());
        pushButtonRegInOut->setSizePolicy(sizePolicy3);

        verticalLayout_6->addWidget(pushButtonRegInOut);


        horizontalLayout_13->addLayout(verticalLayout_6);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName("verticalLayout_12");
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_12->addItem(verticalSpacer_4);

        rB_Normal = new QRadioButton(Ingreso);
        rB_Normal->setObjectName("rB_Normal");
        rB_Normal->setCheckable(true);
        rB_Normal->setChecked(true);
        rB_Normal->setAutoExclusive(true);

        verticalLayout_12->addWidget(rB_Normal);

        rB_Lavada1 = new QRadioButton(Ingreso);
        rB_Lavada1->setObjectName("rB_Lavada1");

        verticalLayout_12->addWidget(rB_Lavada1);

        rB_Lavada2 = new QRadioButton(Ingreso);
        rB_Lavada2->setObjectName("rB_Lavada2");

        verticalLayout_12->addWidget(rB_Lavada2);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_12->addItem(verticalSpacer_6);


        horizontalLayout_13->addLayout(verticalLayout_12);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        lcdNumber = new relojdigital(Ingreso);
        lcdNumber->setObjectName("lcdNumber");
        sizePolicy2.setHeightForWidth(lcdNumber->sizePolicy().hasHeightForWidth());
        lcdNumber->setSizePolicy(sizePolicy2);

        verticalLayout_3->addWidget(lcdNumber);


        horizontalLayout_13->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_13);

        line = new QFrame(Ingreso);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_4->addWidget(line);


        horizontalLayout_14->addLayout(verticalLayout_4);


        verticalLayout_14->addLayout(horizontalLayout_14);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName("verticalLayout_9");
        cbRegEntrada = new QCheckBox(Ingreso);
        cbRegEntrada->setObjectName("cbRegEntrada");
        cbRegEntrada->setChecked(true);

        verticalLayout_9->addWidget(cbRegEntrada);

        tableInOutCar = new QTableView(Ingreso);
        tableInOutCar->setObjectName("tableInOutCar");
        tableInOutCar->setEnabled(true);
        sizePolicy2.setHeightForWidth(tableInOutCar->sizePolicy().hasHeightForWidth());
        tableInOutCar->setSizePolicy(sizePolicy2);
        tableInOutCar->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tableInOutCar->setDragEnabled(false);
        tableInOutCar->setShowGrid(true);
        tableInOutCar->setGridStyle(Qt::PenStyle::SolidLine);
        tableInOutCar->setSortingEnabled(false);
        tableInOutCar->horizontalHeader()->setDefaultSectionSize(160);

        verticalLayout_9->addWidget(tableInOutCar);


        verticalLayout_14->addLayout(verticalLayout_9);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName("verticalLayout_13");
        cbRegSalida = new QCheckBox(Ingreso);
        cbRegSalida->setObjectName("cbRegSalida");
        cbRegSalida->setChecked(true);

        verticalLayout_13->addWidget(cbRegSalida);

        tableViewRegVeh = new QTableView(Ingreso);
        tableViewRegVeh->setObjectName("tableViewRegVeh");
        sizePolicy2.setHeightForWidth(tableViewRegVeh->sizePolicy().hasHeightForWidth());
        tableViewRegVeh->setSizePolicy(sizePolicy2);
        tableViewRegVeh->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tableViewRegVeh->horizontalHeader()->setCascadingSectionResizes(false);
        tableViewRegVeh->horizontalHeader()->setDefaultSectionSize(160);

        verticalLayout_13->addWidget(tableViewRegVeh);


        verticalLayout_14->addLayout(verticalLayout_13);

        tabWidget->addTab(Ingreso, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        horizontalLayout_3 = new QHBoxLayout(tab_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        tabWidgetRegPago = new QTabWidget(tab_2);
        tabWidgetRegPago->setObjectName("tabWidgetRegPago");
        tabWidgetRegPago->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        tabWidgetRegPago->setAutoFillBackground(false);
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        verticalLayout_15 = new QVBoxLayout(tab_6);
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName("verticalLayout_15");
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName("verticalLayout_10");
        label_10 = new QLabel(tab_6);
        label_10->setObjectName("label_10");

        verticalLayout_10->addWidget(label_10);

        lineEditRegPago = new QLineEdit(tab_6);
        lineEditRegPago->setObjectName("lineEditRegPago");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lineEditRegPago->sizePolicy().hasHeightForWidth());
        lineEditRegPago->setSizePolicy(sizePolicy4);
        lineEditRegPago->setMinimumSize(QSize(120, 0));

        verticalLayout_10->addWidget(lineEditRegPago);


        horizontalLayout_9->addLayout(verticalLayout_10);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_4);


        verticalLayout_15->addLayout(horizontalLayout_9);

        line_5 = new QFrame(tab_6);
        line_5->setObjectName("line_5");
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_15->addWidget(line_5);

        tableViewRegPago = new QTableView(tab_6);
        tableViewRegPago->setObjectName("tableViewRegPago");
        tableViewRegPago->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tableViewRegPago->horizontalHeader()->setDefaultSectionSize(160);

        verticalLayout_15->addWidget(tableViewRegPago);

        line_6 = new QFrame(tab_6);
        line_6->setObjectName("line_6");
        line_6->setFrameShape(QFrame::Shape::HLine);
        line_6->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_15->addWidget(line_6);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName("horizontalLayout_21");
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName("verticalLayout_11");
        label_12 = new QLabel(tab_6);
        label_12->setObjectName("label_12");

        verticalLayout_11->addWidget(label_12);

        lineEditRegPagoPlata = new QLineEdit(tab_6);
        lineEditRegPagoPlata->setObjectName("lineEditRegPagoPlata");

        verticalLayout_11->addWidget(lineEditRegPagoPlata);


        horizontalLayout_21->addLayout(verticalLayout_11);

        horizontalSpacer_12 = new QSpacerItem(348, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_12);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setObjectName("verticalLayout_17");
        label_16 = new QLabel(tab_6);
        label_16->setObjectName("label_16");

        verticalLayout_17->addWidget(label_16);

        lineEditDiasPagados = new QLineEdit(tab_6);
        lineEditDiasPagados->setObjectName("lineEditDiasPagados");

        verticalLayout_17->addWidget(lineEditDiasPagados);


        horizontalLayout_21->addLayout(verticalLayout_17);


        verticalLayout_15->addLayout(horizontalLayout_21);

        verticalSpacer_3 = new QSpacerItem(20, 21, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_15->addItem(verticalSpacer_3);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName("horizontalLayout_19");
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_10);

        pushButtonRegPago = new QPushButton(tab_6);
        pushButtonRegPago->setObjectName("pushButtonRegPago");

        horizontalLayout_19->addWidget(pushButtonRegPago);


        verticalLayout_15->addLayout(horizontalLayout_19);

        tabWidgetRegPago->addTab(tab_6, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        verticalLayout = new QVBoxLayout(tab_3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        line_4 = new QFrame(tab_3);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::Shape::HLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_4);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        groupBox_2 = new QGroupBox(tab_3);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        verticalLayout_8 = new QVBoxLayout(groupBox_2);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName("verticalLayout_8");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");

        horizontalLayout_6->addWidget(label_5);

        lineEditPlacaMensual = new QLineEdit(groupBox_2);
        lineEditPlacaMensual->setObjectName("lineEditPlacaMensual");

        horizontalLayout_6->addWidget(lineEditPlacaMensual);


        verticalLayout_8->addLayout(horizontalLayout_6);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label = new QLabel(groupBox_2);
        label->setObjectName("label");

        horizontalLayout_11->addWidget(label);

        leCasilleroMensual = new QLineEdit(groupBox_2);
        leCasilleroMensual->setObjectName("leCasilleroMensual");

        horizontalLayout_11->addWidget(leCasilleroMensual);


        verticalLayout_8->addLayout(horizontalLayout_11);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");

        horizontalLayout_15->addWidget(label_6);

        lineEditPagoMensual = new QLineEdit(groupBox_2);
        lineEditPagoMensual->setObjectName("lineEditPagoMensual");

        horizontalLayout_15->addWidget(lineEditPagoMensual);


        verticalLayout_8->addLayout(horizontalLayout_15);


        horizontalLayout_16->addWidget(groupBox_2);

        line_2 = new QFrame(tab_3);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_16->addWidget(line_2);

        groupBox = new QGroupBox(tab_3);
        groupBox->setObjectName("groupBox");
        groupBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout_5->addWidget(label_2);

        lineEditNombreMensual = new QLineEdit(groupBox);
        lineEditNombreMensual->setObjectName("lineEditNombreMensual");

        horizontalLayout_5->addWidget(lineEditNombreMensual);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        lineEditDireccionMensual = new QLineEdit(groupBox);
        lineEditDireccionMensual->setObjectName("lineEditDireccionMensual");

        horizontalLayout_4->addWidget(lineEditDireccionMensual);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        horizontalLayout_2->addWidget(label_4);

        lineEditTelefonoMensual = new QLineEdit(groupBox);
        lineEditTelefonoMensual->setObjectName("lineEditTelefonoMensual");

        horizontalLayout_2->addWidget(lineEditTelefonoMensual);


        verticalLayout_5->addLayout(horizontalLayout_2);


        horizontalLayout_16->addWidget(groupBox);


        verticalLayout->addLayout(horizontalLayout_16);

        line_3 = new QFrame(tab_3);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_3);

        labelFechaInicio = new QLabel(tab_3);
        labelFechaInicio->setObjectName("labelFechaInicio");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Liberation Serif")});
        font3.setPointSize(14);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setStyleStrategy(QFont::PreferAntialias);
        font3.setHintingPreference(QFont::PreferVerticalHinting);
        labelFechaInicio->setFont(font3);
        labelFechaInicio->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        labelFechaInicio->setAutoFillBackground(false);
        labelFechaInicio->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(labelFechaInicio);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_6);

        dateEdit = new QDateEdit(tab_3);
        dateEdit->setObjectName("dateEdit");
        sizePolicy.setHeightForWidth(dateEdit->sizePolicy().hasHeightForWidth());
        dateEdit->setSizePolicy(sizePolicy);
        dateEdit->setDateTime(QDateTime(QDate(2014, 1, 1), QTime(0, 0, 0)));
        dateEdit->setMaximumDateTime(QDateTime(QDate(8000, 1, 9), QTime(23, 59, 59)));
        dateEdit->setDisplayFormat(QString::fromUtf8("yyyy-MM-dd"));
        dateEdit->setCalendarPopup(true);
        dateEdit->setDate(QDate(2014, 1, 1));

        horizontalLayout_10->addWidget(dateEdit);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_10);

        verticalSpacer = new QSpacerItem(20, 181, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalSpacer_2 = new QSpacerItem(578, 28, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);

        pushButtonRegistrar = new QPushButton(tab_3);
        pushButtonRegistrar->setObjectName("pushButtonRegistrar");

        horizontalLayout_8->addWidget(pushButtonRegistrar);


        verticalLayout->addLayout(horizontalLayout_8);

        tabWidgetRegPago->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        verticalLayout_21 = new QVBoxLayout(tab_4);
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setContentsMargins(11, 11, 11, 11);
        verticalLayout_21->setObjectName("verticalLayout_21");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_7 = new QLabel(tab_4);
        label_7->setObjectName("label_7");

        verticalLayout_7->addWidget(label_7);

        comboBoxVerMensualidad = new QComboBox(tab_4);
        comboBoxVerMensualidad->addItem(QString());
        comboBoxVerMensualidad->addItem(QString());
        comboBoxVerMensualidad->addItem(QString());
        comboBoxVerMensualidad->setObjectName("comboBoxVerMensualidad");

        verticalLayout_7->addWidget(comboBoxVerMensualidad);


        horizontalLayout_7->addLayout(verticalLayout_7);

        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setObjectName("verticalLayout_20");
        lbBuscarMensualidad = new QLabel(tab_4);
        lbBuscarMensualidad->setObjectName("lbBuscarMensualidad");

        verticalLayout_20->addWidget(lbBuscarMensualidad);

        lineEditFiltarmensualidad = new QLineEdit(tab_4);
        lineEditFiltarmensualidad->setObjectName("lineEditFiltarmensualidad");

        verticalLayout_20->addWidget(lineEditFiltarmensualidad);


        horizontalLayout_7->addLayout(verticalLayout_20);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);


        verticalLayout_21->addLayout(horizontalLayout_7);

        tableView = new QTableView(tab_4);
        tableView->setObjectName("tableView");
        tableView->setAutoFillBackground(true);
        tableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
        tableView->setTextElideMode(Qt::TextElideMode::ElideMiddle);
        tableView->horizontalHeader()->setCascadingSectionResizes(false);
        tableView->horizontalHeader()->setDefaultSectionSize(130);
        tableView->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableView->horizontalHeader()->setStretchLastSection(false);
        tableView->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableView->verticalHeader()->setStretchLastSection(false);

        verticalLayout_21->addWidget(tableView);

        tabWidgetRegPago->addTab(tab_4, QString());

        horizontalLayout_3->addWidget(tabWidgetRegPago);

        tabWidget->addTab(tab_2, QString());
        OtrosPagos = new QWidget();
        OtrosPagos->setObjectName("OtrosPagos");
        verticalLayout_18 = new QVBoxLayout(OtrosPagos);
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setContentsMargins(11, 11, 11, 11);
        verticalLayout_18->setObjectName("verticalLayout_18");
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setObjectName("verticalLayout_16");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        lb_Producto = new QLabel(OtrosPagos);
        lb_Producto->setObjectName("lb_Producto");

        horizontalLayout->addWidget(lb_Producto);

        cB_Productos = new QComboBox(OtrosPagos);
        cB_Productos->setObjectName("cB_Productos");

        horizontalLayout->addWidget(cB_Productos);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        lb_ValorProducto = new QLabel(OtrosPagos);
        lb_ValorProducto->setObjectName("lb_ValorProducto");

        horizontalLayout->addWidget(lb_ValorProducto);


        verticalLayout_16->addLayout(horizontalLayout);


        horizontalLayout_12->addLayout(verticalLayout_16);

        pB_VentaOtroProducto = new QPushButton(OtrosPagos);
        pB_VentaOtroProducto->setObjectName("pB_VentaOtroProducto");

        horizontalLayout_12->addWidget(pB_VentaOtroProducto);


        verticalLayout_18->addLayout(horizontalLayout_12);

        tW_Producto_Sel = new QTableView(OtrosPagos);
        tW_Producto_Sel->setObjectName("tW_Producto_Sel");
        sizePolicy2.setHeightForWidth(tW_Producto_Sel->sizePolicy().hasHeightForWidth());
        tW_Producto_Sel->setSizePolicy(sizePolicy2);

        verticalLayout_18->addWidget(tW_Producto_Sel);

        tabWidget->addTab(OtrosPagos, QString());

        verticalLayout_19->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 786, 27));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName("menuMenu");
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionLogin);
        menuMenu->addAction(actionEntrega);

        retranslateUi(MainWindow);
        QObject::connect(cbRegEntrada, &QCheckBox::clicked, tableInOutCar, &QTableView::setVisible);
        QObject::connect(cbRegSalida, &QCheckBox::clicked, tableViewRegVeh, &QTableView::setVisible);

        tabWidget->setCurrentIndex(0);
        tabWidgetRegPago->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Parqueadero el Guadual de Armenia", nullptr));
        actionGuardar->setText(QCoreApplication::translate("MainWindow", "Abrir", nullptr));
        actionGuardar_2->setText(QCoreApplication::translate("MainWindow", "Guardar", nullptr));
        actionGuardar_3->setText(QCoreApplication::translate("MainWindow", "Guardar", nullptr));
        actionSalir->setText(QCoreApplication::translate("MainWindow", "Cerrar", nullptr));
        actionAgregar_Operario->setText(QCoreApplication::translate("MainWindow", "Agregar Operario", nullptr));
        actionLogin->setText(QCoreApplication::translate("MainWindow", "&Login", nullptr));
        actionEntrega->setText(QCoreApplication::translate("MainWindow", "&Entrega", nullptr));
        actionIngresar_Productos->setText(QCoreApplication::translate("MainWindow", "Ingresar Productos", nullptr));
        labelPlaca->setText(QCoreApplication::translate("MainWindow", "Placa:", nullptr));
        pushButtonRegInOut->setText(QCoreApplication::translate("MainWindow", "Registrar Placa", nullptr));
        rB_Normal->setText(QCoreApplication::translate("MainWindow", "Normal", nullptr));
        rB_Lavada1->setText(QCoreApplication::translate("MainWindow", "Lavada 1", nullptr));
        rB_Lavada2->setText(QCoreApplication::translate("MainWindow", "Lavada 2", nullptr));
        cbRegEntrada->setText(QCoreApplication::translate("MainWindow", "Tabla de Registros Entrada:", nullptr));
        cbRegSalida->setText(QCoreApplication::translate("MainWindow", "Tabla de Registros de Salida:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Ingreso), QCoreApplication::translate("MainWindow", "Ingreso Vehiculos", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Buscar", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Valor a registrar", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Dias Pagados", nullptr));
        pushButtonRegPago->setText(QCoreApplication::translate("MainWindow", "Registrar Pago", nullptr));
        tabWidgetRegPago->setTabText(tabWidgetRegPago->indexOf(tab_6), QCoreApplication::translate("MainWindow", "Registrar Pago", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Datos Veh\303\255culo", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Placa                      ", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Casillero                ", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Valor Mensualidad", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Datos Propietario", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Nombre   ", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Direcci\303\263n", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Tel\303\251fono  ", nullptr));
        labelFechaInicio->setText(QCoreApplication::translate("MainWindow", "Inicio Mensualidad", nullptr));
        pushButtonRegistrar->setText(QCoreApplication::translate("MainWindow", "Registrar Usuario", nullptr));
        tabWidgetRegPago->setTabText(tabWidgetRegPago->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Registrar Usuario", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Ver", nullptr));
        comboBoxVerMensualidad->setItemText(0, QCoreApplication::translate("MainWindow", "Todos", nullptr));
        comboBoxVerMensualidad->setItemText(1, QCoreApplication::translate("MainWindow", "Proximos a Pagar", nullptr));
        comboBoxVerMensualidad->setItemText(2, QCoreApplication::translate("MainWindow", "Vencidas", nullptr));

        lbBuscarMensualidad->setText(QCoreApplication::translate("MainWindow", "Filtar", nullptr));
        tabWidgetRegPago->setTabText(tabWidgetRegPago->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Fechas de Corte", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Mensualidades", nullptr));
        lb_Producto->setText(QCoreApplication::translate("MainWindow", "Producto", nullptr));
        lb_ValorProducto->setText(QCoreApplication::translate("MainWindow", "Valor", nullptr));
        pB_VentaOtroProducto->setText(QCoreApplication::translate("MainWindow", "Registrar venta", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(OtrosPagos), QCoreApplication::translate("MainWindow", "Otros Pagos", nullptr));
        menuMenu->setTitle(QCoreApplication::translate("MainWindow", "&Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
