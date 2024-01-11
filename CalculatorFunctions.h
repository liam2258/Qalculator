#ifndef CALCULATOR_FUNCTIONS_H
#define CALCULATOR_FUNCTIONS_H

#include <QLineEdit>
#include <QPushButton>

extern double storedValue;
extern bool additionClicked;
extern bool divisionClicked;
extern bool operationPerformed;
extern bool subtractionClicked;
extern bool modClicked;
extern bool multiplyClicked;

void connectSignToggle(QPushButton* toggleButton, QLineEdit* lineEdit);
void connectModButton(QPushButton* modButton, QLineEdit* lineEdit);
void connectSubtractionButton(QPushButton* subButton, QLineEdit* lineEdit);
void connectMultiplyButton(QPushButton* multiplyButton, QLineEdit* lineEdit);
void connectAdditionButton(QPushButton* addButton, QLineEdit* lineEdit);
void connectDivisionButton(QPushButton* divideButton, QLineEdit* lineEdit);
void connectButtonToDisplay(QPushButton* button, const QString& value, QLineEdit* lineEdit);
void connectClearButton(QPushButton* clearButton, QLineEdit* lineEdit);
void connectEqualsButton(QPushButton* equalsButton, QLineEdit* lineEdit);

#endif // CALCULATOR_FUNCTIONS_H
