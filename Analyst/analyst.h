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

private:
    Ui::Analyst *ui;
};

#endif // ANALYST_H
