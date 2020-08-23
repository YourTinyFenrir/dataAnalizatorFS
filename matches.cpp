#include "matches.h"
#include "QDate"

Info::Info() {
    winners.resize(5);
}

void Info::calcGameScoreWithoutOT() {

    if (homeResults.length() > 0 && awayResults.length() > 0) {

        int sumHome = 0;
        int sumAway = 0;

        for (int i = 1; i < 5; ++i) {

            sumHome += homeResults[i];
            sumAway += awayResults[i];

        }

        homeResults[0] = sumHome;
        awayResults[0] = sumAway;

    }

}

void Info::isWhoWin() {

    if (homeResults.length() > 0 && awayResults.length() > 0) {

        for (int i = 0; i < 5; ++i) {

            if (homeResults[i] == awayResults[i])
                winners[i] = 0;
            else if (homeResults[i] > awayResults[i])
                winners[i] = 1;
            else
                winners[i] = 2;

        }

    }

}

QVector<ExcelInfo> Matches::percentOfWins(QVector<double> param) {

    // Поиск ставок по проценту побед

    // 0 - par11, 1 - par12, 2 - par13L, 3 - par13H
    // 4 - par14L, 5 - par 14H, 6 - par31, 7 - par32

    QVector<ExcelInfo> res;

    QVector<double> homeHomeWins(5);
    QVector<double> homeAwayWins(5);
    QVector<double> awayHomeWins(5);
    QVector<double> awayAwayWins(5);
    QVector<double> homeMutualWins(5);
    QVector<double> awayMutualWins(5);

    if (homeHome.length() >= 10) { // Чтобы избежать ситуаций, когда недостаточно данных для анализа
        foreach (Info value, homeHome) {

            for (int i = 0; i < 5; ++i) {

                if (value.winners[i] == 1)
                    homeHomeWins[i]++;

            }
        }
        for (int i = 0; i < 5; ++i) {

           double percent = homeHomeWins[i] / homeHome.length();
           if (percent >= param[0]) {
               ExcelInfo temp;
               temp.date = QDate::currentDate().toString("d.MM.yyyy");
               temp.teams = current.homeName + " - " + current.awayName;
               if (i == 0)
                    temp.strategyName = "1.1М Процент побед в матче (с учетом локации)";
               else
                    temp.strategyName = "1.1Ч Процент побед в четверти (с учетом локации)";
               if (i == 0)
                    temp.bet = "П1 в основное время";
               else
                    temp.bet = "П1 в " + QString::number(i) + " четверти";
               temp.koef = 0;
               temp.comment = "Процент побед = " + QString::number(percent);

               res.push_back(temp);
           }

        }
    }

    if (homeAway.length() >= 10) {
        foreach (Info value, homeAway) {

            for (int i = 0; i < 5; ++i) {

                if (value.winners[i] == 2)
                    homeAwayWins[i]++;

            }
        }
        for (int i = 0; i < 5; ++i) {

           double percent = (homeHomeWins[i] + homeAwayWins[i]) / (homeHome.length() + homeAway.length());
           if (percent >= param[1]) {
               ExcelInfo temp;
               temp.date = QDate::currentDate().toString("d.MM.yyyy");
               temp.teams = current.homeName + " - " + current.awayName;
               if (i == 0)
                    temp.strategyName = "1.2М Процент побед в матче (без учета локации)";
               else
                    temp.strategyName = "1.2Ч Процент побед в четверти (без учета локации)";
               if (i == 0)
                    temp.bet = "П1 в основное время";
               else
                    temp.bet = "П1 в " + QString::number(i) + " четверти";
               temp.koef = 0;
               temp.comment = "Процент побед = " + QString::number(percent);

               res.push_back(temp);
           }

        }
    }


    if (awayAway.length() >= 10) {
        foreach (Info value, awayAway) {

            for (int i = 0; i < 5; ++i) {

                if (value.winners[i] == 2)
                    awayAwayWins[i]++;

            }
        }
        for (int i = 0; i < 5; ++i) {

           double percent = awayAwayWins[i] / awayAway.length();
           if (percent >= param[0]) {
               ExcelInfo temp;
               temp.date = QDate::currentDate().toString("d.MM.yyyy");
               temp.teams = current.homeName + " - " + current.awayName;
               if (i == 0)
                    temp.strategyName = "1.1М Процент побед в матче (c учетом локации)";
               else
                    temp.strategyName = "1.1Ч Процент побед в четверти (с учетом локации)";
               if (i == 0)
                    temp.bet = "П2 в основное время";
               else
                    temp.bet = "П2 в " + QString::number(i) + " четверти";
               temp.koef = 0;
               temp.comment = "Процент побед = " + QString::number(percent);

               res.push_back(temp);
           }

        }
    }


    if (awayHome.length() >= 10) {
        foreach (Info value, awayHome) {

            for (int i = 0; i < 5; ++i) {

                if (value.winners[i] == 1)
                    awayHomeWins[i]++;

            }
        }
        for (int i = 0; i < 5; ++i) {

           double percent = (awayHomeWins[i] + awayAwayWins[i]) / (awayHome.length() + awayAway.length());
           if (percent >= param[1]) {
               ExcelInfo temp;
               temp.date = QDate::currentDate().toString("d.MM.yyyy");
               temp.teams = current.homeName + " - " + current.awayName;
               if (i == 0)
                    temp.strategyName = "1.2М Процент побед в матче (без учета локации)";
               else
                    temp.strategyName = "1.2Ч Процент побед в четверти (без учета локации)";
               if (i == 0)
                    temp.bet = "П2 в основное время";
               else
                    temp.bet = "П2 в " + QString::number(i) + " четверти";
               temp.koef = 0;
               temp.comment = "Процент побед = " + QString::number(percent);

               res.push_back(temp);
           }

        }
    }



    for (int i = 0; i < 5; ++i) {

       double percent1;
       double percent2;

       if (homeHome.length() >= 10 && awayAway.length() >= 10) {
               percent1 = homeHomeWins[i] / homeHome.length();
               percent2 = awayAwayWins[i] / awayAway.length();
               if (percent1 >= param[3] && percent2 <= param[2]) {
                   ExcelInfo temp;
                   temp.date = QDate::currentDate().toString("d.MM.yyyy");
                   temp.teams = current.homeName + " - " + current.awayName;
                   if (i == 0)
                        temp.strategyName = "1.3М Процент побед в матче (с учетом локации)";
                   else
                        temp.strategyName = "1.3Ч Процент побед в четверти (с учетом локации)";
                   if (i == 0)
                        temp.bet = "П1 в основное время";
                   else
                        temp.bet = "П1 в " + QString::number(i) + " четверти";
                   temp.koef = 0;
                   temp.comment = "Процент побед хозяев = " + QString::number(percent1) + "; Процент побед гостей = " + QString::number(percent2);

                   res.push_back(temp);
               }

               if (percent1 <= param[2] && percent2 >= param[3]) {
                   ExcelInfo temp;
                   temp.date = QDate::currentDate().toString("d.MM.yyyy");
                   temp.teams = current.homeName + " - " + current.awayName;
                   if (i == 0)
                        temp.strategyName = "1.3М Процент побед в матче (с учетом локации)";
                   else
                        temp.strategyName = "1.3Ч Процент побед в четверти (с учетом локации)";
                   if (i == 0)
                        temp.bet = "П2 в основное время";
                   else
                        temp.bet = "П2 в " + QString::number(i) + " четверти";
                   temp.koef = 0;
                   temp.comment = "Процент побед хозяев = " + QString::number(percent1) + "; Процент побед гостей = " + QString::number(percent2);

                   res.push_back(temp);
               }

           if (homeAway.length() >= 10 && awayHome.length() >= 10) {
               percent1 = (homeHomeWins[i] + homeAwayWins[i]) / (homeHome.length() + homeAway.length());
               percent2 = (awayHomeWins[i] + awayAwayWins[i]) / (awayHome.length() + awayAway.length());
               if (percent1 >= param[5] && percent2 <= param[4]) {
                   ExcelInfo temp;
                   temp.date = QDate::currentDate().toString("d.MM.yyyy");
                   temp.teams = current.homeName + " - " + current.awayName;
                   if (i == 0)
                        temp.strategyName = "1.4М Процент побед в матче (без учета локации)";
                   else
                        temp.strategyName = "1.4Ч Процент побед в четверти (без учета локации)";
                   if (i == 0)
                        temp.bet = "П1 в основное время";
                   else
                        temp.bet = "П1 в " + QString::number(i) + " четверти";
                   temp.koef = 0;
                   temp.comment = "Процент побед хозяев = " + QString::number(percent1) + "; Процент побед гостей = " + QString::number(percent2);

                   res.push_back(temp);
               }

               if (percent1 <= param[4] && percent2 >= param[5]) {
                   ExcelInfo temp;
                   temp.date = QDate::currentDate().toString("d.MM.yyyy");
                   temp.teams = current.homeName + " - " + current.awayName;
                   if (i == 0)
                        temp.strategyName = "1.4М Процент побед в матче (без учета локации)";
                   else
                        temp.strategyName = "1.4Ч Процент побед в четверти (без учета локации)";
                   if (i == 0)
                        temp.bet = "П2 в основное время";
                   else
                        temp.bet = "П2 в " + QString::number(i) + " четверти";
                   temp.koef = 0;
                   temp.comment = "Процент побед хозяев = " + QString::number(percent1) + "; Процент побед гостей = " + QString::number(percent2);

                   res.push_back(temp);
               }
           }
       }

    }


    if (homeMutual.length() >= 10) {
        foreach (Info value, homeMutual) {

            for (int i = 0; i < 5; ++i) {

                if (value.winners[i] == 1)
                    homeMutualWins[i]++;

            }
        }
        for (int i = 0; i < 5; ++i) {

           double percent = homeMutualWins[i] / homeMutual.length();
           if (percent >= param[6]) {
               ExcelInfo temp;
               temp.date = QDate::currentDate().toString("d.MM.yyyy");
               temp.teams = current.homeName + " - " + current.awayName;
               if (i == 0)
                    temp.strategyName = "3.1М Процент побед в личных встречах в матче (с учетом локации)";
               else
                    temp.strategyName = "3.1Ч Процент побед в личных встречах в четверти (с учетом локации)";
               if (i == 0)
                    temp.bet = "П1 в основное время";
               else
                    temp.bet = "П1 в " + QString::number(i) + " четверти";
               temp.koef = 0;
               temp.comment = "Процент побед = " + QString::number(percent);

               res.push_back(temp);
           }

           if (percent <= (1 - param[6])) {
               ExcelInfo temp;
               temp.date = QDate::currentDate().toString("d.MM.yyyy");
               temp.teams = current.homeName + " - " + current.awayName;
               if (i == 0)
                    temp.strategyName = "3.1М Процент побед в личных встречах в матче (с учетом локации)";
               else
                    temp.strategyName = "3.1Ч Процент побед в личных встречах в четверти (с учетом локации)";
               if (i == 0)
                    temp.bet = "П2 в основное время";
               else
                    temp.bet = "П2 в " + QString::number(i) + " четверти";
               temp.koef = 0;
               temp.comment = "Процент побед = " + QString::number(1 - percent);

               res.push_back(temp);
           }

        }
    }


    if (awayMutual.length() >= 10) {
        foreach (Info value, awayMutual) {

            for (int i = 0; i < 5; ++i) {

                if (value.winners[i] == 2)
                    awayMutualWins[i]++;

            }
        }
        for (int i = 0; i < 5; ++i) {

           double percent = (homeMutualWins[i] + awayMutualWins[i]) / (homeMutual.length() + awayMutual.length());
           if (percent >= param[7]) {
               ExcelInfo temp;
               temp.date = QDate::currentDate().toString("d.MM.yyyy");
               temp.teams = current.homeName + " - " + current.awayName;
               if (i == 0)
                    temp.strategyName = "3.2М Процент побед в личных встречах в матче (без учета локации)";
               else
                    temp.strategyName = "3.2Ч Процент побед в личных встречах в четверти (без учета локации)";
               if (i == 0)
                    temp.bet = "П1 в основное время";
               else
                    temp.bet = "П1 в " + QString::number(i) + " четверти";
               temp.koef = 0;
               temp.comment = "Процент побед = " + QString::number(percent);

               res.push_back(temp);
           }

           if (percent <= (1 - param[7])) {
               ExcelInfo temp;
               temp.date = QDate::currentDate().toString("d.MM.yyyy");
               temp.teams = current.homeName + " - " + current.awayName;
               if (i == 0)
                    temp.strategyName = "3.2М Процент побед в личных встречах в матче (с учетом локации)";
               else
                    temp.strategyName = "3.2Ч Процент побед в личных встречах в четверти (с учетом локации)";
               if (i == 0)
                    temp.bet = "П2 в основное время";
               else
                    temp.bet = "П2 в " + QString::number(i) + " четверти";
               temp.koef = 0;
               temp.comment = "Процент побед = " + QString::number(1 - percent);

               res.push_back(temp);
           }

        }
    }

    return res;

}

QVector<double> Matches::poissonDistribution(double avg) {



}

QVector<ExcelInfo> Matches::avgTotal() {

    QVector<ExcelInfo> res;

    QVector<QVector2D> homeHomeAvg(5);
    QVector<QVector2D> homeAwayAvg(5);
    QVector<QVector2D> awayHomeAvg(5);
    QVector<QVector2D> awayAwayAvg(5);
    QVector<QVector2D> homeMutualAvg(5);
    QVector<QVector2D> awayMutualAvg(5);

    // Расчет средних значений
    foreach (Info value, homeHome) {

        for (int i = 0; i < 5; ++i) {

            homeHomeAvg[i].setX(homeHomeAvg[i].x() + value.homeResults[i]);
            homeHomeAvg[i].setY(homeHomeAvg[i].y() + value.awayResults[i]);

        }
    }
    for (int i = 0; i < 5; ++i) {

        homeHomeAvg[i].setX(homeHomeAvg[i].x() / homeHome.length());
        homeHomeAvg[i].setY(homeHomeAvg[i].y() / homeHome.length());

    }



    foreach (Info value, homeAway) {

        for (int i = 0; i < 5; ++i) {

            homeAwayAvg[i].setX(homeAwayAvg[i].x() + value.homeResults[i]);
            homeAwayAvg[i].setY(homeAwayAvg[i].y() + value.awayResults[i]);

        }
    }
    for (int i = 0; i < 5; ++i) {

        homeAwayAvg[i].setX(homeAwayAvg[i].x() / homeAway.length());
        homeAwayAvg[i].setY(homeAwayAvg[i].y() / homeAway.length());

    }



    foreach (Info value, awayHome) {

        for (int i = 0; i < 5; ++i) {

            awayHomeAvg[i].setX(awayHomeAvg[i].x() + value.homeResults[i]);
            awayHomeAvg[i].setY(awayHomeAvg[i].y() + value.awayResults[i]);

        }
    }
    for (int i = 0; i < 5; ++i) {

        awayHomeAvg[i].setX(awayHomeAvg[i].x() / awayHome.length());
        awayHomeAvg[i].setY(awayHomeAvg[i].y() / awayHome.length());

    }



    foreach (Info value, awayAway) {

        for (int i = 0; i < 5; ++i) {

            awayAwayAvg[i].setX(awayAwayAvg[i].x() + value.homeResults[i]);
            awayAwayAvg[i].setY(awayAwayAvg[i].y() + value.awayResults[i]);

        }
    }
    for (int i = 0; i < 5; ++i) {

        awayAwayAvg[i].setX(awayAwayAvg[i].x() / awayAway.length());
        awayAwayAvg[i].setY(awayAwayAvg[i].y() / awayAway.length());

    }

    /*double avg;
    QVector<double> koefs;
    for (int i = 0; i < 5; ++i) {

        avg = (homeHomeAvg[i].x() + awayAwayAvg[i].x()) / 2;
        koefs = poissonDistribution(avg);

    }*/


    foreach (Info value, homeMutual) {

        for (int i = 0; i < 5; ++i) {

            homeMutualAvg[i].setX(homeMutualAvg[i].x() + value.homeResults[i]);
            homeMutualAvg[i].setY(homeMutualAvg[i].y() + value.awayResults[i]);

        }
    }
    for (int i = 0; i < 5; ++i) {

        homeMutualAvg[i].setX(homeMutualAvg[i].x() / homeMutual.length());
        homeMutualAvg[i].setY(homeMutualAvg[i].y() / homeMutual.length());

    }



    foreach (Info value, awayMutual) {

        for (int i = 0; i < 5; ++i) {

            awayMutualAvg[i].setX(awayMutualAvg[i].x() + value.homeResults[i]);
            awayMutualAvg[i].setY(awayMutualAvg[i].y() + value.awayResults[i]);

        }
    }
    for (int i = 0; i < 5; ++i) {

        awayMutualAvg[i].setX(awayMutualAvg[i].x() / awayMutual.length());
        awayMutualAvg[i].setY(awayMutualAvg[i].y() / awayMutual.length());

    }

    return res;

}
