#ifndef PANEL_H
#define PANEL_H


#include <QtGui>
#include <QPlainTextEdit>
#include <QSplitter>

class Panel : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit Panel(QSplitter *parent, const QString text = "");

protected:
    void contextMenuEvent(QContextMenuEvent *);

private:
    void create(Qt::Orientation orientation, bool reverse);
};

#endif // PANEL_H
