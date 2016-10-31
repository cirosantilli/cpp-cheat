#include <iostream>
#include <sstream>

#include <QApplication>
#include <QDesktopWidget>
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QIcon>
#include <QPushButton>
#include <QTabWidget>
#include <QWidget>
// tr
#include <QObject>
#include <QShortcut>
// enum Qt::AlignmentFlag {AlignTop, ...}
#include <Qt>

#include "SlotTest.h"
#include "ui_qt_designer.h"

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
    The main GUI objects used to set the position of GUI objects are Widget and Layout.

    #Widget

        Can have fixed sizes.

        Can set one single internal layout with `setLayout`.

        Widgets in general don't have setAlignment, but some such as QLabel do,
        so there is no need to embed them inside another layout for alignment.

    #Layout

        Cannot have fixed size.
        Occupies its entire parent.

        Can contain several inner:

        - layouts via `addLayout`
        - widgets via `addWidget`.

        Possible determine the aligment of items (center, left, etc) inside it via `setAlignment`.

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
    QVBoxLayout *setCursorTabLayout = new QVBoxLayout();
    {
        QLabel *label = new QLabel("Hover the mouse over the frames:");
        label->setAlignment(Qt::AlignCenter);
        label->setFixedHeight(buttonHeight);

        QHBoxLayout *framesLayout = new QHBoxLayout();
        {
            {
                QFrame *frame = new QFrame(&window);
                frame->setFrameStyle(QFrame::Box);
                frame->setCursor(Qt::SizeAllCursor);
                QHBoxLayout *frameLayout = new QHBoxLayout();
                QLabel *label = new QLabel("SizeAllCursor", frame);
                frameLayout->addWidget(label);
                frameLayout->setAlignment(Qt::AlignCenter);
                frame->setLayout(frameLayout);
                framesLayout->addWidget(frame);
            }

            {
                QFrame *frame = new QFrame(&window);
                frame->setFrameStyle(QFrame::Box);
                frame->setCursor(Qt::WaitCursor);
                QHBoxLayout *frameLayout = new QHBoxLayout();
                QLabel *label = new QLabel("WaitCursor", frame);
                frameLayout->addWidget(label);
                frameLayout->setAlignment(Qt::AlignCenter);
                frame->setLayout(frameLayout);
                framesLayout->addWidget(frame);
            }

            {
                QFrame *frame = new QFrame(&window);
                frame->setFrameStyle(QFrame::Box);
                frame->setCursor(Qt::PointingHandCursor);
                QHBoxLayout *frameLayout = new QHBoxLayout();
                QLabel *label = new QLabel("PointingHandCursor", frame);
                frameLayout->addWidget(label);
                frameLayout->setAlignment(Qt::AlignCenter);
                frame->setLayout(frameLayout);
                framesLayout->addWidget(frame);
            }
        }

        setCursorTabLayout->addWidget(label);
        setCursorTabLayout->addLayout(framesLayout);
    }
    QWidget *setCursorWidget = new QWidget();
    setCursorWidget->setLayout(setCursorTabLayout);

    //#setToolTip
    QVBoxLayout *setToolTipLayout = new QVBoxLayout();
    {
        QLabel *label = new QLabel("Hover the mouse over the frames and don't move it for a while:");
        label->setAlignment(Qt::AlignCenter);
        label->setFixedHeight(buttonHeight);

        QHBoxLayout *framesLayout = new QHBoxLayout();
        {
            {
                QFrame *frame = new QFrame(&window);
                frame->setFrameStyle(QFrame::Box);
                frame->setToolTip(QObject::tr("setToolTip left"));

                QHBoxLayout *frameLayout = new QHBoxLayout();
                QLabel *label = new QLabel("left", frame);
                frameLayout->addWidget(label);
                frameLayout->setAlignment(Qt::AlignCenter);
                frame->setLayout(frameLayout);
                framesLayout->addWidget(frame);
            }

            {
                QFrame *frame = new QFrame(&window);
                frame->setFrameStyle(QFrame::Box);
                frame->setToolTip(QObject::tr("setToolTip right"));

                QHBoxLayout *frameLayout = new QHBoxLayout();
                QLabel *label = new QLabel("right", frame);
                frameLayout->addWidget(label);
                frameLayout->setAlignment(Qt::AlignCenter);
                frame->setLayout(frameLayout);
                framesLayout->addWidget(frame);
            }
        }

        setToolTipLayout->addWidget(label);
        setToolTipLayout->addLayout(framesLayout);
    }
    QWidget *setToolTipWidget = new QWidget();
    setToolTipWidget->setLayout(setToolTipLayout);

    //#Shortcut
    QWidget *shortcutWidget = new QWidget();
    {
        QShortcut *mainWindowShortcut = new QShortcut(QKeySequence("Ctrl+Q"), &window);
        QObject::connect(mainWindowShortcut, SIGNAL(activated()), qApp, SLOT(quit()));

        /*
        Shortcuts are only activated if the parent widget is active.

        If there are two possible actions for a shortcut, TODO nothing happens, or undefined?
        */

        QShortcut *tabShortcut = new QShortcut(QKeySequence("Ctrl+W"), shortcutWidget);
        QObject::connect(tabShortcut, SIGNAL(activated()), &slotTest, SLOT(cout()));
        QShortcut *tabShortcut2 = new QShortcut(QKeySequence("Ctrl+Q"), shortcutWidget);
        QObject::connect(tabShortcut2, SIGNAL(activated()), &slotTest, SLOT(cout()));

        QHBoxLayout *layout = new QHBoxLayout();
        QLabel *label = new QLabel(
                "<p>Shortcuts:</p>"
                "<ul>"
                 "<li>Ctrl+Q : quit (global</li>"
                 "<li>Ctrl+Q : cout (local to this tab)</li>"
                 "<li>Ctrl+W : cout (local to this tab)</li>"
                "<ul>\n"
                ,
                shortcutWidget);
        layout->addWidget(label);
        layout->setAlignment(Qt::AlignCenter);
        shortcutWidget->setLayout(layout);
    }

    //#MenuBar
    {
        QPixmap ico("ico.png");

        QAction *cout = new QAction(ico, QObject::tr("&cout"), &window);
        QAction *title = new QAction(QObject::tr("&title"), &window);
        QAction *inc  = new QAction(QObject::tr("&inc"),  &window);
        QAction *quit = new QAction(QObject::tr("&quit"), &window);
        quit->setShortcut(Qt::CTRL + Qt::SHIFT +Qt::Key_Q);

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

    /*
    #Qt Designer

        See `ui` files.

    #ui files

        The `.ui` files are XML files that describe layout.

        This XML format contains information that generates C++ layout code.

        They are typically generated by the Qt Designer tool
        (executable name `designer` under Ubuntu 13.10).

        In order to process ui files, add to `qt.pro`:

            FORMS += my.ui

        This will generate a header file `ui_my.h` which you can include in your application.

        The class name is that given in the Qt Editor to the top level object under the namespace `Ui::`.
    */
    {
        QWidget *widget = new QWidget;
        Ui::QtDesignerWidget ui;
        ui.setupUi(widget);
        tabs->addTab(widget, QObject::tr("Qt Designer"));
    }

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
