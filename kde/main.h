#ifndef MAIN_H
#define MAIN_H

#include <KXmlGuiWindow>
#include <KTextEdit>

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent=0);

    public Q_SLOTS:
        void saveConfig();
        void viewConfig();
        void showSettingsDialog();
        void saveSettingsXt();
        void loadSettingsXt();

    private:
        KTextEdit* textArea;
        void setupActions();
        int port;
        QString serverName;
};

#endif
