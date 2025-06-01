#pragma once

#include <QDialog>
#include <QTableView>
#include <QVBoxLayout>
#include "../domain/Dog.h"
#include "AdoptedDogsTableModel.h"

class ShowAllAdoptedDialog : public QDialog {
    Q_OBJECT

private:
    QTableView* tableView;
    AdoptedDogsTableModel* model;

public:
    explicit ShowAllAdoptedDialog(const std::vector<Dog>& adoptedDogs, QWidget* parent = nullptr);
};
