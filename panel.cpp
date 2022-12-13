#include "panel.h"
#include <QtWidgets/QScrollBar>
#include <QMenu>
#include <QSplitter>

Panel::Panel(QSplitter *parent, const QString text): QPlainTextEdit(parent)
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
        parent->addWidget(this);
    }
}

void Panel::create(Qt::Orientation orientation, bool reverse)
{
    QSplitter *prnt = static_cast<QSplitter *>(parent());
    prnt->setOrientation(orientation);

    QSplitter *splitCrnt = new QSplitter(prnt);
    splitCrnt->setChildrenCollapsible(false);
    splitCrnt->setHandleWidth(2);
    QSplitter *splitNew = new QSplitter(prnt);

    setParent(splitCrnt);
    splitCrnt->addWidget(this);

    new Panel(splitNew, /* Debug only begin */ this->toPlainText() + "X" /* Debug only end */);

    if (!reverse)
    {
        prnt->insertWidget(0, splitCrnt);
        prnt->insertWidget(1, splitNew);
    }
    else
    {
        prnt->insertWidget(1, splitCrnt);
        prnt->insertWidget(0, splitNew);
    }
}

void Panel::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu contMenu(this);

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

    contMenu.exec(event->globalPos());
}
