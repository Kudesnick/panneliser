#include <QMenu>
#include <QList>
#include "splitter.h"

Splitter::Splitter(Qt::Orientation orientation, QWidget *parent):
    QSplitter(orientation, parent)
{
    setChildrenCollapsible(false);
    setHandleWidth(2);
}

Splitter::Splitter(QWidget *parent):
    Splitter(Qt::Vertical, parent)
{}

void Splitter::swap()
{
    insertWidget(0, widget(1));
}

void Splitter::rotate(Direction direct)
{
    if (orientation() == Qt::Horizontal)
    {
        setOrientation(Qt::Vertical);
        if (direct == CCW)
        {
            swap();
        }
    }
    else
    {
        setOrientation(Qt::Horizontal);
        if (direct == CW)
        {
            swap();
        }
    }
}

void Splitter::setRatio(const int firstPercents)
{
    setSizes({firstPercents * 10000, (100 - firstPercents) * 10000});
}

void Splitter::contextMenuEvent(QContextMenuEvent *event)
{
    class Action : public QAction
    {
    private:
        const int val_;
    public:
        Action(const int _val):
            QAction(), val_(_val)
        {}

        const int &val = val_;
    };

    QMenu contMenu(this);

    QAction Swap("Swap", &contMenu);
    contMenu.addAction(&Swap);
    connect(&Swap, &QAction::triggered, this, &Splitter::swap);

    QAction RotCW("Rotate CW", &contMenu);
    contMenu.addAction(&RotCW);
    connect(&RotCW, &QAction::triggered, this, [=](){this->rotate(CW);});

    QAction RotCCW("Rotate CCW", &contMenu);
    contMenu.addAction(&RotCCW);
    connect(&RotCCW, &QAction::triggered, this, [=](){this->rotate(CCW);});

    Action Ratio[] = {{20}, {30}, {40}, {50} ,{60} ,{70} ,{80}};

    for (auto &item : Ratio)
    {
        item.setText(QStringLiteral("%1/%2").arg(item.val).arg(100 -  item.val));
        item.setParent(&contMenu);
        contMenu.addAction(&item);
        connect(&item, &QAction::triggered, this, [&](){this->setRatio(item.val);});
    }

    contMenu.exec(event->globalPos());
}
