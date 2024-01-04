#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QPushButton>

double storedValue = 0.0;
bool additionClicked = false;
bool divisionClicked = false;
bool operationPerformed = false;
bool subtractionClicked = false;
bool modClicked = false;
bool multiplyClicked = false;

void connectSignToggle(QPushButton* toggleButton, QLineEdit* lineEdit) {
    QObject::connect(toggleButton, &QPushButton::clicked, lineEdit, [=]() {
        if (!lineEdit->text().isEmpty()) {
            QString text = lineEdit->text();
            double value = text.toDouble();
            value *= -1; // Change sign
            lineEdit->setText(QString::number(value));
        }
    });
}

void connectModButton(QPushButton* modButton, QLineEdit* lineEdit) {
    QObject::connect(modButton, &QPushButton::clicked, lineEdit, [=]() {
        if (!lineEdit->text().isEmpty()) {
            double currentValue = lineEdit->text().toDouble();
            if (!modClicked) {
                storedValue = currentValue;
                modClicked = true;
            } else {
                if (currentValue != 0) {
                    storedValue = fmod(storedValue, currentValue);
                } else {
                    lineEdit->setText("Error");
                    return;
                }
            }
            operationPerformed = true;
            additionClicked = false;
            subtractionClicked = false;
            multiplyClicked = false;
            divisionClicked = false;
        }
    });
}

void connectSubtractionButton(QPushButton* subButton, QLineEdit* lineEdit) {
    QObject::connect(subButton, &QPushButton::clicked, lineEdit, [=]() {
        if (!lineEdit->text().isEmpty()) {
            double currentValue = lineEdit->text().toDouble();
            if (!subtractionClicked) {
                storedValue = currentValue;
                subtractionClicked = true;
            } else {
                storedValue -= currentValue;
            }
            operationPerformed = true;
            divisionClicked = false;
            additionClicked = false;
            modClicked = false;
            multiplyClicked = false;
        }
    });
}

void connectMultiplyButton(QPushButton* multiplyButton, QLineEdit* lineEdit) {
    QObject::connect(multiplyButton, &QPushButton::clicked, lineEdit, [=]() {
        if (!lineEdit->text().isEmpty()) {
            double currentValue = lineEdit->text().toDouble();
            if (!multiplyClicked) {
                storedValue = currentValue;
                multiplyClicked = true;
            } else {
                storedValue *= currentValue;
            }
            operationPerformed = true;
            divisionClicked = false;
            subtractionClicked = false;
            additionClicked = false;
            modClicked = false;
        }
    });
}

void connectAdditionButton(QPushButton* addButton, QLineEdit* lineEdit) {
    QObject::connect(addButton, &QPushButton::clicked, lineEdit, [=]() {
        if (!lineEdit->text().isEmpty()) {
            double currentValue = lineEdit->text().toDouble();
            if (!additionClicked) {
                storedValue = currentValue;
                additionClicked = true;
            } else {
                storedValue += currentValue;
            }
            operationPerformed = true;
            divisionClicked = false;
            subtractionClicked = false;
            modClicked = false;
            multiplyClicked = false;
        }
    });
}


void connectDivisionButton(QPushButton* divideButton, QLineEdit* lineEdit) {
    QObject::connect(divideButton, &QPushButton::clicked, lineEdit, [=]() {
        if (!lineEdit->text().isEmpty()) {
            double currentValue = lineEdit->text().toDouble();
            if (!divisionClicked) {
                storedValue = currentValue;
                divisionClicked = true;
            } else {
                if (currentValue != 0) {
                    storedValue /= currentValue;
                } else {
                    lineEdit->setText("Error");
                    return;
                }
            }
            operationPerformed = true;
            additionClicked = false;
            subtractionClicked = false;
            modClicked = false;
            multiplyClicked = false;
        }
    });
}



void connectButtonToDisplay(QPushButton* button, const QString& value, QLineEdit* lineEdit) {
    QObject::connect(button, &QPushButton::clicked, lineEdit, [=]() {
        if (operationPerformed) {
            lineEdit->clear();
            operationPerformed = false;
        }
        lineEdit->insert(value);
    });
}


void connectClearButton(QPushButton* clearButton, QLineEdit* lineEdit) {
    QObject::connect(clearButton, &QPushButton::clicked, lineEdit, [=]() {
        lineEdit->clear();
        storedValue = 0.0;
        additionClicked = false;
        divisionClicked = false;
        operationPerformed = false;
    });
}

void connectEqualsButton(QPushButton* equalsButton, QLineEdit* lineEdit) {
    QObject::connect(equalsButton, &QPushButton::clicked, lineEdit, [=]() {
        if (!lineEdit->text().isEmpty()) {
            double currentValue = lineEdit->text().toDouble();
            if (additionClicked) {
                storedValue += currentValue;
                lineEdit->setText(QString::number(storedValue));
                additionClicked = false;
            } else if (divisionClicked) {
                if (currentValue != 0) {
                    storedValue /= currentValue;
                    lineEdit->setText(QString::number(storedValue));
                    divisionClicked = false;
                } else {
                    lineEdit->setText("Error");
                }
            } else if (subtractionClicked) {
                storedValue -= currentValue;
                lineEdit->setText(QString::number(storedValue));
                subtractionClicked = false;
            } else if (modClicked) {
                if (currentValue != 0) {
                    storedValue = fmod(storedValue, currentValue);
                    lineEdit->setText(QString::number(storedValue));
                    modClicked = false;
                } else {
                    lineEdit->setText("Error");
                }
            } else if (multiplyClicked) {
                storedValue *= currentValue;
                lineEdit->setText(QString::number(storedValue));
                multiplyClicked = false;
            }
            operationPerformed = true;
        }
    });
}



int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Create MainWindow instance
    MainWindow w;

    // Access QLineEdit within MainWindow
    QLineEdit* display = w.findChild<QLineEdit*>("display");

    display->setPlaceholderText("0");

    QDoubleValidator* doubleValidator = new QDoubleValidator(display);
    doubleValidator->setDecimals(6);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);

    // Calculate the maximum input size including decimal places
    doubleValidator->setRange(-9999999999.999, 9999999999.999);

    display->setValidator(doubleValidator);

    display->show();

    QPushButton* button0 = w.findChild<QPushButton*>("button0");
    QPushButton* button1 = w.findChild<QPushButton*>("button1");
    QPushButton* button2 = w.findChild<QPushButton*>("button2");
    QPushButton* button3 = w.findChild<QPushButton*>("button3");
    QPushButton* button4 = w.findChild<QPushButton*>("button4");
    QPushButton* button5 = w.findChild<QPushButton*>("button5");
    QPushButton* button6 = w.findChild<QPushButton*>("button6");
    QPushButton* button7 = w.findChild<QPushButton*>("button7");
    QPushButton* button8 = w.findChild<QPushButton*>("button8");
    QPushButton* button9 = w.findChild<QPushButton*>("button9");
    QPushButton* buttonDecimal = w.findChild<QPushButton*>("buttonDecimal");
    QPushButton* buttonClear = w.findChild<QPushButton*>("buttonClear");
    QPushButton* buttonAdd = w.findChild<QPushButton*>("buttonAdd");
    QPushButton* buttonEquals = w.findChild<QPushButton*>("buttonEquals");
    QPushButton* buttonDivide = w.findChild<QPushButton*>("buttonDivide");
    QPushButton* buttonToggleSign = w.findChild<QPushButton*>("buttonToggleSign");
    QPushButton* buttonSubtract = w.findChild<QPushButton*>("buttonSubtract");
    QPushButton* buttonMod = w.findChild<QPushButton*>("buttonMod");
    QPushButton* buttonMultiply = w.findChild<QPushButton*>("buttonMultiply");

    connectButtonToDisplay(button0, "0", display);
    connectButtonToDisplay(button1, "1", display);
    connectButtonToDisplay(button2, "2", display);
    connectButtonToDisplay(button3, "3", display);
    connectButtonToDisplay(button4, "4", display);
    connectButtonToDisplay(button5, "5", display);
    connectButtonToDisplay(button6, "6", display);
    connectButtonToDisplay(button7, "7", display);
    connectButtonToDisplay(button8, "8", display);
    connectButtonToDisplay(button9, "9", display);
    connectButtonToDisplay(buttonDecimal, ".", display);
    connectClearButton(buttonClear, display);
    connectAdditionButton(buttonAdd, display);
    connectEqualsButton(buttonEquals, display);
    connectDivisionButton(buttonDivide, display);
    connectSignToggle(buttonToggleSign, display);
    connectSubtractionButton(buttonSubtract, display);
    connectModButton(buttonMod, display);
    connectMultiplyButton(buttonMultiply, display);

    // Show MainWindow
    w.show();

    return a.exec();
}
