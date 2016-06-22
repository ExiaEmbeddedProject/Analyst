#ifndef ANALYST_H
#define ANALYST_H

#include <QMainWindow>

namespace Ui {
    class Analyst;
}

class Analyst : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Analyst(QWidget *parent = 0);
        ~Analyst();

    public slots:
        void callTracker();

    private:
        Ui::Analyst *ui;
        void test();

};

#endif // ANALYST_H
