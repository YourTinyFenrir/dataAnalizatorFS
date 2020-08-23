#ifndef MATCHES_H
#define MATCHES_H

#include "QVector"
#include "QVector2D"

struct ExcelInfo {
    QString date;
    QString teams;
    QString strategyName;
    QString bet;
    double koef;
    QString comment;

    ExcelInfo& operator= (const ExcelInfo& right) {
        this->date = right.date;
        this->teams = right.teams;
        this->strategyName = right.strategyName;
        this->bet = right.bet;
        this->koef = right.koef;
        this->comment = right.comment;

        return *this;
    }
};

struct Info {
    QString homeName;
    QString awayName;
    QVector<int> homeResults;
    QVector<int> awayResults;

    Info();
    QVector<int> winners; // 0 - ничья, 1 - победа хозяев, 2 - победа гостей
    void calcGameScoreWithoutOT();
    void isWhoWin();
};

struct Matches {
    Info current;
    QVector<Info> homeHome;
    QVector<Info> homeAway;
    QVector<Info> awayHome;
    QVector<Info> awayAway;
    QVector<Info> homeMutual;
    QVector<Info> awayMutual;

    QVector<ExcelInfo> percentOfWins(QVector<double>);
    void calcAverage();
    QVector<double> poissonDistribution(double);
    QVector<ExcelInfo> avgTotal();
};

#endif // MATCHES_H
