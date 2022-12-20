#ifndef SPLITTER_H
#define SPLITTER_H

#include <QtGui>
#include <QWidget>
#include <QSplitter>

class Splitter : public QSplitter
{
    Q_OBJECT
public:
    explicit Splitter(Qt::Orientation orientation, QWidget *parent = nullptr);
    explicit Splitter(QWidget *parent = nullptr);

    enum Direction
    {
        CW,
        CCW,
    };

    void swap();
    void rotate(Direction direct = CW);
    void setRatio(const int firstPercents = 50);

protected:
    void contextMenuEvent(QContextMenuEvent *);
};

#endif // SPLITTER_H
