#ifndef STATS_H
#define STATS_H

#include "QVector"
#include "QVector4D"
#include "QFile"
#include "QJsonObject"
#include "matches.h"

class Stats {
private:
    QVector<Matches> data;
    QVector<ExcelInfo> bets;
public:
    Stats();
    Stats(QFile&);
    Stats& operator= (const Stats&);
    QVector<ExcelInfo> getBets() { return bets; }
    void setBets(QVector<ExcelInfo> bets) { this->bets = bets; }
    Info parseData(QJsonObject&);
    void createVectorOfBets(QVector<double>);
    void writeBetsOnExcel();
};

#endif // STATS_H
