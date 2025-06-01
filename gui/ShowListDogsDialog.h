//
// Created by mures on 5/11/2025.
//

#ifndef SHOWLISTDOGSDIALOG_H
#define SHOWLISTDOGSDIALOG_H
#include "MainWindow.h"

#include <QDialog>
#include <QTableWidget>


class ShowListDogsDialog : public QDialog{
Q_OBJECT

public:
    ShowListDogsDialog(Service& service, QWidget *parent = nullptr);

private slots:
    void populateTable();

private:
    Service& service;
    QTableWidget *tableWidget;
};



#endif //SHOWLISTDOGSDIALOG_H
