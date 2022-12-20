#ifndef PANEL_H
#define PANEL_H


#include <QtGui>
#include <QPlainTextEdit>
#include "splitter.h"

class Panel : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit Panel(Splitter *parent, const QString text = "");
    static void Remove(Panel *);

protected:
    void contextMenuEvent(QContextMenuEvent *);

private:
    void create(Qt::Orientation orientation, bool reverse);
    void swap();
    Splitter *parentSplittter();
};

#endif // PANEL_H
