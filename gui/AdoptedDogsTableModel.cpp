#include "AdoptedDogsTableModel.h"

AdoptedDogsTableModel::AdoptedDogsTableModel(QObject *parent)
    : QAbstractTableModel(parent) {}

int AdoptedDogsTableModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return static_cast<int>(dogs.size());
}

int AdoptedDogsTableModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return 4; // Breed, Name, Age, Photo Link
}

QVariant AdoptedDogsTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        const Dog& dog = dogs[index.row()];
        switch (index.column()) {
            case 0: return QString::fromStdString(dog.getBreed());
            case 1: return QString::fromStdString(dog.getName());
            case 2: return dog.getAge();
            case 3: return QString::fromStdString(dog.getPhotography());
            default: break;
        }
    }
    return QVariant();
}

QVariant AdoptedDogsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return QString("Breed");
            case 1: return QString("Name");
            case 2: return QString("Age");
            case 3: return QString("Photo Link");
            default: break;
        }
    }
    return QVariant();
}

void AdoptedDogsTableModel::setDogs(const std::vector<Dog>& dogList) {
    beginResetModel();
    dogs = dogList;
    endResetModel();
}

void AdoptedDogsTableModel::addDog(const Dog& dog) {
    beginInsertRows(QModelIndex(), static_cast<int>(dogs.size()), static_cast<int>(dogs.size()));
    dogs.push_back(dog);
    endInsertRows();
}

void AdoptedDogsTableModel::removeDog(int row) {
    if (row >= 0 && row < dogs.size()) {
        beginRemoveRows(QModelIndex(), row, row);
        dogs.erase(dogs.begin() + row);
        endRemoveRows();
    }
}