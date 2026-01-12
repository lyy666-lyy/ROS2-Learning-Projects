#include <QApplication>
#include <QLabel>
#include <QString>

int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);// Initialize the Qt application
    QLabel* label = new QLabel();
    QString message = QString::fromStdString("Hello, Qt with C++17!");
    label->setText(message);
    label->show();
    app.exec();

    return 0;
}