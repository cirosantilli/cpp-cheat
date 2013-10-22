#include <iostream>
#include <sstream>

#include <QApplication>
#include <QDesktopWidget>
#include <QFrame>
#include <QGridLayout>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QIcon>
#include <QPushButton>
#include <QTabWidget>
#include <QWidget>
#include <QObject>      //tr
#include <QShortcut>
#include <Qt>           //enum Qt::AlignmentFlag {AlignTop, ...}

#include "SlotTest.h"

int buttonHeight = 25;

void SlotTest::cout() {
    std::cout << "i = " << i << std::endl;
}

void SlotTest::inc() {
    i++;
}

void SlotTest::title() {
    std::stringstream newTitle;
    newTitle << "i = " << i;
    window->setWindowTitle(newTitle.str().c_str());
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // For most purposes, this could also be a QWidget.
    QMainWindow window;
    SlotTest slotTest(&window);
    QTabWidget *tabs = new QTabWidget(&window);

    /*
    #Widget

        Can have fixed sizes.

        Can set an internal layout with `setLayout`.

    #Layout

        Cannot have fixed size.

        Occupies its entire parent.

    #MainWindow

        Cannot do `setLayout`.

        Has some extra functionality with respect to `Widget`.

    #QString

        Has no `std::string` constructor.
        Solution: `QString::fromStdString(s)` or `QString(s.c_str())`

        Convertion to `std::string`: <http://stackoverflow.com/questions/4214369/how-to-convert-qstring-to-stdstring>
        As of 5.0, toStdString is good.
    */

    /*
    #PushButton

    #connect

        Connect takes:

        - object 1
        - signal 1
        - object 2
        - signal 2

        When working with qmake, without modifying defaults,
        declaration of QObjects with slots *must be in separate headers!*.
        <http://stackoverflow.com/questions/13614593/linker-error-with-qt-signal-slot-example>
    */

        QVBoxLayout *pushButtonLayout = new QVBoxLayout();
        {
            QPushButton *quit = new QPushButton(QObject::tr("quit"));
            QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
            quit->setFixedHeight(buttonHeight);

            //TODO why clicking on the button does nothing?
            QPushButton *cout = new QPushButton(QObject::tr("cout"));
            QObject::connect(cout, SIGNAL(clicked()), &slotTest, SLOT(cout()));
            cout->setFixedHeight(buttonHeight);

            QPushButton *inc = new QPushButton(QObject::tr("inc"));
            QObject::connect(inc, SIGNAL(clicked()), &slotTest, SLOT(inc()));
            inc->setFixedHeight(buttonHeight);

            QPushButton *title = new QPushButton(QObject::tr("title"));
            QObject::connect(title, SIGNAL(clicked()), &slotTest, SLOT(title()));
            title->setFixedHeight(buttonHeight);

            pushButtonLayout->addWidget(quit);
            pushButtonLayout->addWidget(cout);
            pushButtonLayout->addWidget(title);
            pushButtonLayout->addWidget(inc);

            pushButtonLayout->setAlignment(Qt::AlignTop);
        }
        QWidget *pushButtonWidget = new QWidget();
        pushButtonWidget->setLayout(pushButtonLayout);

    //#setCursor
    QHBoxLayout *setCursorLayout = new QHBoxLayout();
    {
        QFrame *frame1 = new QFrame(&window);
        frame1->setFrameStyle(QFrame::Box);
        frame1->setCursor(Qt::SizeAllCursor);

        QFrame *frame2 = new QFrame(&window);
        frame2->setFrameStyle(QFrame::Box);
        frame2->setCursor(Qt::WaitCursor);

        QFrame *frame3 = new QFrame(&window);
        frame3->setFrameStyle(QFrame::Box);
        frame3->setCursor(Qt::PointingHandCursor);

        setCursorLayout->addWidget(frame1);
        setCursorLayout->addWidget(frame2);
        setCursorLayout->addWidget(frame3);
    }
    QWidget *setCursorWidget = new QWidget();
    setCursorWidget->setLayout(setCursorLayout);

    //#setToolTip
    QHBoxLayout *setToolTipLayout = new QHBoxLayout();
    {
        QFrame *frame1 = new QFrame(&window);
        frame1->setFrameStyle(QFrame::Box);
        frame1->setToolTip(QObject::tr("setToolTip left"));

        QFrame *frame2 = new QFrame(&window);
        frame2->setFrameStyle(QFrame::Box);
        frame2->setToolTip(QObject::tr("setToolTip right"));

        setToolTipLayout->addWidget(frame1);
        setToolTipLayout->addWidget(frame2);
    }
    QWidget *setToolTipWidget = new QWidget();
    setToolTipWidget->setLayout(setToolTipLayout);

    //#Shortcut

        QShortcut *mainWindowShortcut = new QShortcut(QKeySequence("Ctrl+Q"), &window);
        QObject::connect(mainWindowShortcut, SIGNAL(activated()), qApp, SLOT(quit()));

        /*
        Shortcuts are only activated if the parent widget is active.

        If there are two possible actions for a shortcut, TODO nothing happens, or undefined?
        */

        QWidget *shortcutWidget = new QWidget();
        QShortcut *tabShortcut = new QShortcut(QKeySequence("Ctrl+W"), shortcutWidget);
        QObject::connect(tabShortcut, SIGNAL(activated()), qApp, SLOT(quit()));
        QShortcut *tabShortcut2 = new QShortcut(QKeySequence("Ctrl+Q"), shortcutWidget);
        QObject::connect(tabShortcut2, SIGNAL(activated()), &slotTest, SLOT(cout()));

    //#MenuBar
    {
        QPixmap ico("ico.png");

        QAction *cout = new QAction(ico, QObject::tr("&cout"), &window);
        QAction *title = new QAction(QObject::tr("&title"), &window);
        QAction *inc  = new QAction(QObject::tr("&inc"),  &window);
        QAction *quit = new QAction(QObject::tr("&quit"), &window);
        quit->setShortcut("CTRL+SHIFT+Q");

        QMenu *m1;
        //menuBar method only exists for QMainWindow, not for QWidget.
        m1 = window.menuBar()->addMenu(QObject::tr("m&1"));
        m1->addAction(cout);
        m1->addAction(title);
        m1->addAction(inc);
        m1->addSeparator();
        m1->addAction(quit);

        QObject::connect(quit,  SIGNAL(triggered()), qApp,      SLOT(quit()));
        QObject::connect(title, SIGNAL(triggered()), &slotTest, SLOT(title()));
        QObject::connect(cout,  SIGNAL(triggered()), &slotTest, SLOT(cout()));
        QObject::connect(inc,   SIGNAL(triggered()), &slotTest, SLOT(inc()));
    }

    tabs->addTab(pushButtonWidget, QObject::tr("PushButton"));
    tabs->addTab(setCursorWidget,  QObject::tr("setCursor"));
    tabs->addTab(setToolTipWidget, QObject::tr("setToolTip"));
    tabs->addTab(shortcutWidget,   QObject::tr("Shortcut"));

    //#window

        window.setCentralWidget(tabs);
        window.move(100, 200);
        window.resize(600, 400);
        window.setWindowTitle(QObject::tr("setWindowTitle"));
        window.setWindowIcon(QIcon("ico.svg"));
        window.show();

    //#desktop

        QDesktopWidget *desktop = QApplication::desktop();
        std::cout << "desktop" << std::endl;
        std::cout << "width() = " << desktop->width() << std::endl;
        std::cout << "height() = " << desktop->height() << std::endl;

    return app.exec();
}
