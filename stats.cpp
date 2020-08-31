#include "stats.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QTextStream"
#include "QDebug"
#include "xlsxdocument.h"

Stats::Stats() {

}

Stats::Stats(QFile& fileObj) {

    if ((fileObj.exists()) && (fileObj.open(QIODevice::ReadOnly))) {

        // Считывание файла, полученного с сайта, для анализа
        QTextStream fileText(&fileObj);
        QString strFile = (QString)fileText.readAll();
        fileObj.close();

        QByteArray fileBytes = strFile.toLocal8Bit();
        auto jsonDoc = QJsonDocument::fromJson(fileBytes);

        if(jsonDoc.isNull()) {
            qDebug()<<"Failed to create JSON doc.";
            exit(1);
        }

        QJsonArray mainArr = jsonDoc.array();

        if(!jsonDoc.isArray()) {
            qDebug()<<"JSON is not an array.";
            exit(2);
        }

        foreach (const QJsonValue &mainValue, mainArr) {

            Matches match;

            QJsonObject mainObj = mainValue.toObject();
            match.current = parseData(mainObj);

            QJsonObject obj = mainObj["matches"].toObject();

            QJsonArray arr = obj["homeHome"].toArray();
            foreach (const QJsonValue &value, arr) {
                QJsonObject tempObj = value.toObject();
                match.homeHome.push_back(parseData(tempObj));
            }

            arr = obj["homeAway"].toArray();
            foreach (const QJsonValue &value, arr) {
                QJsonObject tempObj = value.toObject();
                match.homeAway.push_back(parseData(tempObj));
            }

            arr = obj["awayHome"].toArray();
            foreach (const QJsonValue &value, arr) {
                QJsonObject tempObj = value.toObject();
                match.awayHome.push_back(parseData(tempObj));
            }

            arr = obj["awayAway"].toArray();
            foreach (const QJsonValue &value, arr) {
                QJsonObject tempObj = value.toObject();
                match.awayAway.push_back(parseData(tempObj));
            }

            arr = obj["homeMutual"].toArray();
            foreach (const QJsonValue &value, arr) {
                QJsonObject tempObj = value.toObject();
                match.homeMutual.push_back(parseData(tempObj));
            }

            arr = obj["awayMutual"].toArray();
            foreach (const QJsonValue &value, arr) {
                QJsonObject tempObj = value.toObject();
                match.awayMutual.push_back(parseData(tempObj));
            }

            data.push_back(match);

        }
    }
    else {
        qDebug() << "Failed to open file";
        exit(1);
    }

}

Stats &Stats::operator=(const Stats & right) {

    this->data = right.data;
    this->bets = right.bets;

    return *this;

}

Info Stats::parseData(QJsonObject &obj) {

    Info info;

    info.homeName.append(obj["homeName"].toString());
    info.awayName.append(obj["awayName"].toString());

    QJsonArray arr = obj["homeResults"].toArray();
    foreach (const QJsonValue &value, arr)
        info.homeResults.push_back(value.toString().toInt());

    arr = obj["awayResults"].toArray();
    foreach (const QJsonValue &value, arr)
        info.awayResults.push_back(value.toString().toInt());

    info.calcGameScoreWithoutOT();
    info.isWhoWin();

    return info;

}

void Stats::createVectorOfBets(QVector<double> param) {

    foreach (Matches value, data) {

        bets+=value.percentOfWins(param);
        //bets+=value.avgTotal();

    }

}

void Stats::writeBetsOnExcel() {

    QXlsx::Document doc("bets.xlsx");

    bool isEmpty = false;
    int rowForWrite;
    for (int i = 1; !isEmpty; ++i) {

        QString str = doc.read(i, 1).toString();
        isEmpty = str.isEmpty();
        if (isEmpty)
            rowForWrite = i;

    }

    foreach (ExcelInfo value, bets) {

        doc.write(rowForWrite, 1, value.date);
        doc.write(rowForWrite, 2, value.teams);
        doc.write(rowForWrite, 3, value.strategyName);
        doc.write(rowForWrite, 4, value.bet);
        doc.write(rowForWrite, 6, value.comment);

        doc.saveAs("bets.xlsx");

        rowForWrite++;

    }

}

