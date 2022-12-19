#include "panel.h"
#include <QtWidgets/QScrollBar>
#include <QMenu>

Panel::Panel(Splitter *parent, const QString text): QPlainTextEdit(parent)
{
    /* Debug only begin */
    QTextCharFormat colorOutCurr;
    colorOutCurr.setForeground(Qt::white);
    colorOutCurr.setBackground(Qt::black);
    QTextCursor tmpCcursor = QTextCursor(document());
    tmpCcursor.movePosition(QTextCursor::End);
    tmpCcursor.insertText(text, colorOutCurr);

    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    setPalette(p);

    setReadOnly(true);
    /* Debug only end */

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    if (parent)
    {
        parent->setChildrenCollapsible(false);
        parent->setHandleWidth(2);
    }
}

Panel::~Panel()
{
    Splitter *prnt = parentSplittter();
    setParent(nullptr);

    if (true
        && prnt
        && prnt->count() >= 2
       )
    {
        const int DelId = prnt->indexOf(this);
        const int saveId = (DelId == 0) ? 1 : 0;

        Splitter *newPrnt = dynamic_cast<Splitter *>(prnt->parent());
        if (newPrnt)
        {
            prnt->widget(saveId)->setParent(newPrnt);
            newPrnt->replaceWidget(newPrnt->indexOf(prnt), prnt->widget(saveId));
        }

        delete prnt;
    }
}


void Panel::create(Qt::Orientation orientation, bool reverse)
{
    Splitter *prnt = parentSplittter();
    if (prnt)
    {
        int index = prnt->indexOf(this);

        Splitter *splitNew = new Splitter(orientation, prnt);

        Panel *panelNew = new Panel(splitNew, /* Debug only begin */ this->toPlainText() + "X" /* Debug only end */);
        setParent(splitNew);

        prnt->insertWidget(index, splitNew);

        if (!reverse)
        {
            splitNew->insertWidget(0, this);
            splitNew->insertWidget(1, panelNew);
        }
        else
        {
            splitNew->insertWidget(0, panelNew);
            splitNew->insertWidget(1, this);
        }
    }
}

void Panel::swap()
{
    Splitter *prnt = parentSplittter();
    if (prnt)
    {
        prnt->swap();
    }
}


Splitter *Panel::parentSplittter()
{
    return dynamic_cast<Splitter *>(parent());
}


void Panel::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu contMenu(this);

    QAction Swap("Swap", &contMenu);
    contMenu.addAction(&Swap);
    connect(&Swap, &QAction::triggered, this, &Panel::swap);

    QAction Up("Up", &contMenu);
    contMenu.addAction(&Up);
    connect(&Up, &QAction::triggered, this, [=](){this->create(Qt::Vertical, true);});

    QAction Down("Down", &contMenu);
    contMenu.addAction(&Down);
    connect(&Down, &QAction::triggered, this, [=](){this->create(Qt::Vertical, false);});

    QAction Left("Left", &contMenu);
    contMenu.addAction(&Left);
    connect(&Left, &QAction::triggered, this, [=](){this->create(Qt::Horizontal, false);});

    QAction Right("Right", &contMenu);
    contMenu.addAction(&Right);
    connect(&Right, &QAction::triggered, this, [=](){this->create(Qt::Horizontal, true);});

    QAction Del("Delete", &contMenu);
    contMenu.addAction(&Del);
    connect(&Del, &QAction::triggered, this, [&](){QTimer::singleShot(0, this, [&]{delete this;});});

    contMenu.exec(event->globalPos());
}
