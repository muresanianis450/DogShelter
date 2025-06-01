#pragma once
#ifndef ADOPTEDDOGSTABLEMODEL_H
#define ADOPTEDDOGSTABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include "../domain/Dog.h" // Assuming Dog.h defines the Dog class

class AdoptedDogsTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit AdoptedDogsTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void setDogs(const std::vector<Dog>& dogs);
    void addDog(const Dog& dog); // If you want to add one by one
    void removeDog(int row); // If you want to remove one by one

private:
    std::vector<Dog> dogs;
};

#endif // ADOPTEDDOGSTABLEMODEL_H