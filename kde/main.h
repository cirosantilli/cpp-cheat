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
        void setText();
        void saveConf();
        void readConf();
        void saveConfXT();
        void readConfXT();

    private:
        KTextEdit* textArea;
        void setupActions();
};

#endif
