#include <cstdlib>
#include <iostream>

#include <KApplication>
#include <KAboutData>
#include <KAction>
#include <KActionCollection>
#include <KCmdLineArgs>
#include <KConfigGroup>
#include <KLocale>
#include <KMessageBox>
#include <KMenuBar>
#include <KSharedConfigPtr>

#include <kdecheat_settings.h>
#include "main.h"

MainWindow::MainWindow(QWidget *parent)
    : KXmlGuiWindow(parent)
{
    textArea = new KTextEdit;
    setCentralWidget(textArea);
    setupActions();

    /*
    #setGUI

        Creates GUI elements from `ui.rc` files.
    */

        this->setupGUI(Default, "kdecheatui.rc");
}

void MainWindow::setText()
{
    textArea->setText("abc");
}

/*
#SharedConfig

    Shares multiple KConf instances nicely amongst concurrent access.

    Better than using KConf directly.

    New alternative to this method; KConfig XT

    Configuration files are ini files kept under `~/.kde/share/config` in Linux.

#ConfigGroup

    Inside a given config file or ini section, which ini section we are looking for.

#writeEntry

    Writting to config file is immediate.
*/
void MainWindow::saveConf()
{
    // Name of the config file is determined from the application name if not given.
    // Ex: kdecheatrc.
    KSharedConfigPtr config = KSharedConfig::openConfig();

    KConfigGroup generalGroup(config, "general");
    generalGroup.writeEntry("string", textArea->toPlainText());

    // lessGeneral is a subgroup of general and appears as `[general][lessGeneral]`
    // in the `ini` file.
    KConfigGroup lessGeneralGroup(&generalGroup, "lessGeneral");

    // Any type is ok:
    lessGeneralGroup.writeEntry("int", 1);
}

/*
#readEntry

    The second parameter is the default value.
*/
void MainWindow::readConf()
{
    KSharedConfigPtr config = KSharedConfig::openConfig();
    // Name of the ini header is `[general]`.
    KConfigGroup generalGroup(config, "general");
    textArea->setText(generalGroup.readEntry("string", "abc"));
}

/*
#Config XT

    Newer configuration method.

    Configuration is specified in an XML format.
*/
void MainWindow::saveConfXT() {
    ExampleSettings::setServerName( "www.kde.com" );
    ExampleSettings::setPort( 80 );
    ExampleSettings::self()->writeConfig();
}

void MainWindow::readConfXT() {
    QString m_server = ExampleSettings::serverName();
    int m_port       = ExampleSettings::port();
}

void MainWindow::setupActions()
{
    {
        KAction* clearAction = new KAction(this);
        clearAction->setText(i18n("&Clear"));
        clearAction->setIcon(KIcon("document-new"));
        clearAction->setShortcut(Qt::CTRL + Qt::Key_W);
        // The first string determines the action name
        actionCollection()->addAction("clear", clearAction);
        connect(clearAction, SIGNAL(triggered(bool)),
                textArea, SLOT(clear()));
    }

    /*
    #StandardAction

        Offers standard actions.

        Those actions have standard names, icons and shortcuts.

        They are automatically put inside standard menus. For exampe, quit goes under "File".
    */
    {
        KStandardAction::quit(kapp, SLOT(quit()), actionCollection());
    }

    // setText action
    {
        KAction* action = new KAction(this);
        action->setText(i18n("&Set Text"));
        action->setShortcut(Qt::CTRL + Qt::Key_S);
        actionCollection()->addAction("setText", action);
        connect(action, SIGNAL(triggered(bool)),
                this, SLOT(setText()));
    }

    // saveConf action
    {
        KAction* action = new KAction(this);
        action->setShortcut(Qt::CTRL + Qt::Key_D);
        action->setText(i18n("Save Conf"));
        actionCollection()->addAction("saveConf", action);
        connect(action, SIGNAL(triggered(bool)),
                this, SLOT(saveConf()));
    }

    // readConf action
    {
        KAction* action = new KAction(this);
        action->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_C);
        action->setText(i18n("Read Conf"));
        actionCollection()->addAction("readConf", action);
        connect(action, SIGNAL(triggered(bool)),
                this, SLOT(saveConf()));
    }

    // saveConfXT action
    {
        KAction* action = new KAction(this);
        action->setText(i18n("save Conf XT"));
        actionCollection()->addAction("saveConfXT", action);
        connect(action, SIGNAL(triggered(bool)),
                this, SLOT(saveConfXT()));
    }

    // readConfXT action
    {
        KAction* action = new KAction(this);
        action->setText(i18n("Read Conf XT"));
        actionCollection()->addAction("readConfXT", action);
        connect(action, SIGNAL(triggered(bool)),
                this, SLOT(readConfXT()));
    }
}

int main (int argc, char *argv[])
{
    // Most of the descriptive parameters show on the `Help > About` menu item.
    KAboutData aboutData(
        // The program name used internally.
        "kdecheat",
        // The message catalog name
        // If null, program name is used instead.
        0,
        // A displayable program name string.
        ki18n("KDE Cheat"),
        // The program version string.
        "1.0",
        // Short description of what the app does.
        ki18n("Short description."),
        // The license this code is released under
        KAboutData::License_GPL,
        // Copyright Statement
        ki18n("(c) 2007"),
        // Optional text shown in the About box.
        // Can contain any information desired.
        ki18n("Shown in the about box."),
        // The program homepage string.
        "http://example.com/",
        // The bug report email address
        "submit@bugs.kde.org");

    KCmdLineArgs::init( argc, argv, &aboutData );
    KApplication app;

    /*
    #XMLGUI

        GUI components that can be configured via *ui.rc XML files.

        Examples:

        - KXmlGuiWindow

    #XmlGuiWindow

        Suitable for a main window.

        Is usually used as a base class.

        Provides:

        - main menu with:

            - Help
            - Settings with "Configure Shortcuts" and "Configure Toolbars"
            - Show statusbar

        - status bar

        As the name suggests, this class is part of the XMLGUI KDE technology.

    #MainWindow

        Good possibility for main window class.

        Inherits KXmlGuiWindow, so supports XMLGUI.
    */

    MainWindow* window = new MainWindow();
    window->show();

    //#MessageBox

        /*
        KGuiItem yesButton( i18n( "Hello" ),
                            QString(),
                            i18n( "This is a tooltip" ),
                            i18n( "This is a WhatsThis help text." ) );

        KMessageBox::questionYesNo(0, i18n( "Hello World" ), i18n( "Hello" ), yesButton )
            == KMessageBox::Yes ? EXIT_SUCCESS : EXIT_FAILURE;
        */

    return app.exec();
}
