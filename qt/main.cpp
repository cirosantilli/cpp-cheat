#include <iostream>

#include <QApplication>
#include <QDesktopWidget>
#include <QIcon>
#include <QWidget>
#include <QObject>      //tr

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //#desktop

        QDesktopWidget *desktop = QApplication::desktop();
        std::cout << "desktop" << std::endl;
        std::cout << "width() = " << desktop->width() << std::endl;
        std::cout << "height() = " << desktop->height() << std::endl;

    //#BoxLayout

    //#BoxLayout

        //QVBoxLayout layout;
        //layout.addWidget(&textEdit);

    //#window

        QWidget window;
        window.move(100, 200);
        window.resize(250, 150);
        window.setWindowTitle(QObject::tr("setWindowTitle"));
        window.setToolTip(QObject::tr("setToolTip"));
        window.setWindowIcon(QIcon("ico.svg"));
        window.show();

    return app.exec();
}

/*
#include <QtGui>

int main(int argv, char **args)
{
    QApplication app(argv, args);

    QTextEdit textEdit;
    QPushButton quitButton(tr("Quit"));

    QObject::connect(&quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout layout;
    layout.addWidget(&textEdit);
    layout.addWidget(&quitButton);

    QWidget window;
    window.setLayout(&layout);
    window.resize(250, 150);
    window.setWindowTitle("setWindowTitle");

    window.show();

    return app.exec();
}
*/
