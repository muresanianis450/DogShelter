

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include "service/service.h"
#include "QVBoxLayout"
#include <QFormLayout>
#include <QMessageBox>

class UpdateDogDialog : public QDialog {
    Q_OBJECT

public:
    explicit UpdateDogDialog(Service& service, QWidget *parent = nullptr);

private slots:
    void handleUpdate();

private:
    Service& service;

    QLineEdit *oldNameInput;
    QLineEdit *oldBreedInput;
    QLineEdit *oldAgeInput;
    QLineEdit *oldLinkInput;

    QLineEdit *newNameInput;
    QLineEdit *newBreedInput;
    QLineEdit *newAgeInput;
    QLineEdit *newLinkInput;

};

