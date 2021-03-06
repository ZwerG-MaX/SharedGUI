#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    int iter;

public slots:
    void addObj();
    void patchObj(int id);
    void removeObj(int id);
};

#endif // WIDGET_H
