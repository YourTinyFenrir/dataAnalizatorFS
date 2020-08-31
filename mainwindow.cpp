#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QFile"
#include "QTextStream"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Открытие файла с данными с FlashScore и его обработка
    QFile forRead("json.txt");
    Stats temp(forRead);
    stats = temp;

    // Считывание из файла параметров для обработки данных
    QFile cfg("cfg.txt");

    if (!cfg.exists()) {

        QVector<double> defaultCfg;
        defaultCfg.push_back(0.8); defaultCfg.push_back(0.75);
        defaultCfg.push_back(0.2); defaultCfg.push_back(0.6);
        defaultCfg.push_back(0.25); defaultCfg.push_back(0.65);
        defaultCfg.push_back(0.9); defaultCfg.push_back(0.75);

        cfg.open(QIODevice::WriteOnly);

        QTextStream stream(&cfg);
        for (int i = 0; i < 8; ++i)
            stream << QString::number(defaultCfg[i], 'f', 2) << endl;

        cfg.close();

    }

    if (cfg.open(QIODevice::ReadOnly)) {
        QTextStream fileText(&cfg);

        QVector<double> param;
        for (int i = 0; i < 8; ++i)
            param.push_back(fileText.readLine(0).toDouble());

        cfg.close();

        ui->par11->setValue(param[0]);
        ui->par12->setValue(param[1]);
        ui->par13L->setValue(param[2]);
        ui->par13H->setValue(param[3]);
        ui->par14L->setValue(param[4]);
        ui->par14H->setValue(param[5]);
        ui->par31->setValue(param[6]);
        ui->par32->setValue(param[7]);
    }
    else {
        qDebug() << "Failed to open file";
        exit(1);
    }

    // Настройка TableWidget для вывода результата
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setShowGrid(true);
    QStringList strList(QStringList() << ("")
                                      << ("Дата")
                                      << ("Матч")
                                      << ("Стратегия")
                                      << ("Ставка")
                                      << ("Примечание"));
    ui->tableWidget->setHorizontalHeaderLabels(strList);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->textAboutEndOfWrite->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_createVectorOfBetsButton_clicked() {

    ui->textAboutEndOfWrite->hide();

    // Сохранение параметров для обработки данных с целью повторного использования
    QVector<double> param;

    param.push_back(ui->par11->value());
    param.push_back(ui->par12->value());
    param.push_back(ui->par13L->value());
    param.push_back(ui->par13H->value());
    param.push_back(ui->par14L->value());
    param.push_back(ui->par14H->value());
    param.push_back(ui->par31->value());
    param.push_back(ui->par32->value());

    QFile cfg("cfg.txt");
    if ((cfg.exists()) && (cfg.open(QIODevice::WriteOnly))) {

        QTextStream stream(&cfg);
        for (int i = 0; i < 8; ++i)
            stream << QString::number(param[i], 'f', 2) << endl;

    }

    cfg.close();

    // Поиск предполагаемых ставок, вывод их на TableWidget
    stats.createVectorOfBets(param);

    QVector<ExcelInfo> bets = stats.getBets();
    for (int i = 0; i < bets.length(); ++i) {

       ui->tableWidget->insertRow(i);
       QTableWidgetItem *item = new QTableWidgetItem();
       item->data(Qt::CheckStateRole);
       item->setCheckState(Qt::Unchecked);
       ui->tableWidget->setItem(i, 0, item);
       ui->tableWidget->setItem(i, 1, new QTableWidgetItem(bets[i].date));
       ui->tableWidget->setItem(i, 2, new QTableWidgetItem(bets[i].teams));
       ui->tableWidget->setItem(i, 3, new QTableWidgetItem(bets[i].strategyName));
       ui->tableWidget->setItem(i, 4, new QTableWidgetItem(bets[i].bet));
       ui->tableWidget->setItem(i, 5, new QTableWidgetItem(bets[i].comment));

    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

}

void MainWindow::on_WriteBetsOnExcelButton_clicked() {

    ui->textAboutEndOfWrite->hide();

    // Сохранение выбранных пользователем ставок
    QVector<ExcelInfo> bets = stats.getBets();
    QVector<ExcelInfo> selectedBets;
    for (int i = 0; i < bets.length(); ++i) {

        if (ui->tableWidget->item(i, 0)->checkState() == Qt::Checked)
            selectedBets.push_back(bets[i]);

    }

    stats.setBets(selectedBets);
    stats.writeBetsOnExcel();

    ui->textAboutEndOfWrite->setHidden(false);

}
