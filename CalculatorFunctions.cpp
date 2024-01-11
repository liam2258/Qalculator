#include "CalculatorFunctions.h"
#include <cmath> // Include for fmod function

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
