#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QPushButton>
#include "CalculatorFunctions.h"

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
