#ifndef SLOTS_H
#define SLOTS_H

#include <QObject>

class SlotTest : public QObject
{
    Q_OBJECT

    public:

        SlotTest(QWidget *window) : i(0), window(window) {}

        int i;

    public slots:
    //public Q_SLOTS: // Generally the same.

        void cout();
        void inc();
        void title();

    private:

        QWidget *window;
};

#endif
