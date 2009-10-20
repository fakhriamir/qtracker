#include <QtGui>
#include "qgaugewidget.h"

#include <iostream>
using namespace std;
//#define LOG( a ) cout << a
#define LOG( a )


const char* states[] = {
    "stIdle",
    "stInitialTouch",
    "stSingleTapPending",
    "stLongTouch",
    "stSecondTouch",
    "stMoving",
//    "stLongMove",
    0
};

QGaugeWidget::QGaugeWidget(QWidget *parent)
    : QWidget(parent)
    , state(StIdle)
    , minx(25)
    , miny(25)
{
    singletaptimer.setSingleShot(true);
    singletaptimer.setInterval(200);
    connect(&singletaptimer,SIGNAL(timeout()),this,SLOT(singleTapTimeout()));
    longtaptimer.setSingleShot(true);
    longtaptimer.setInterval(1000);
    connect(&longtaptimer,SIGNAL(timeout()),this,SLOT(longTapTimeout()));
}

QGaugeWidget::~QGaugeWidget()
{
    singletaptimer.stop();
    longtaptimer.stop();
}

void QGaugeWidget::mousePressEvent(QMouseEvent *event)
{
    LOG( states[state] << "\n <-- mousePressEvent\n"; )
    previous = event->pos();
    switch(state)
    {
    case StIdle:
        startLongTapTimer();
        state = StInitialTouch;
        LOG ( " --> startLongTapTimer\n" << states[state] << "\n\n"; )
        break;
    case StSingleTapPending:
        cancelSingleTapTimer();
        startLongTapTimer();
        state = StSecondTouch;
        LOG ( " --> cancelSingleTapTimer\n --> startLongTapTimer\n" << states[state] << "\n\n"; )
        break;
    default:
        LOG( "^^^ unexpected event!\n\n"; )
        // error!
        break;
    }
}

void QGaugeWidget::longTapTimeout()
{
    LOG( states[state] << "\n <-- longTapTimeout\n"; )
    switch(state)
    {
    case StInitialTouch:
    case StSecondTouch:
        state = StLongTouch;
        LOG ( states[state] << "\n\n"; )
        break;
    default:
        LOG( "^^^ unexpected event!\n\n"; )
        // error!
        break;
    }
}

void QGaugeWidget::singleTapTimeout()
{
    LOG( states[state] << "\n <-- singleTapTimeout\n"; )
    switch(state)
    {
    case StSingleTapPending:
        state = StIdle;
        emit singleTap();
        LOG ( " --> emit singleTap\n" << states[state] << "\n\n"; )
        break;
    default:
        LOG( "^^^ unexpected event!\n\n"; )
        // error!
        break;
    }
}
/*
void QGaugeWidget::longMoveTimeout()
{
    LOG( states[state] << "\n <-- longTapTimeout\n"; )
    switch(state)
    {
    case StMoving:
        state = StLongMove;
        LOG ( states[state] << "\n\n"; )
        break;
    default:
        LOG( "^^^ unexpected event!\n\n"; )
        // error!
        break;
    }
}

void QGaugeWidget::startLongMoveTimer()
{
    longmovetimer.start();
}

void QGaugeWidget::cancelLongMoveTimer()
{
    longmovetimer.stop();
}

*/
void QGaugeWidget::startLongTapTimer()
{
    longtaptimer.start();
}

void QGaugeWidget::startSingleTapTimer()
{
    singletaptimer.start();
}

void QGaugeWidget::cancelLongTapTimer()
{
    longtaptimer.stop();
}

void QGaugeWidget::cancelSingleTapTimer()
{
    singletaptimer.stop();
}

void QGaugeWidget::mouseMoveEvent(QMouseEvent* event)
{
    int dx = event->pos().x() - previous.x();
    int dy = event->pos().y() - previous.y();

    LOG( states[state] << "\n <-- mouseMove\n"; )
        switch(state)
        {
        case QGaugeWidget::StInitialTouch:
        case QGaugeWidget::StSecondTouch:
            if ((abs(dx) > minx) || (abs(dy) > miny))
            {
                        state = StMoving;
                        //startLongMoveTimer();
                        previous = event->pos();
                        emit drag(dx,dy);
            }
            break;
        case QGaugeWidget::StLongTouch:
                state = StMoving;
        case QGaugeWidget::StMoving:
                previous = event->pos();
                emit drag(dx,dy);
                break;
        //case QGaugeWidget::StLongMove:
        //	previous = event->pos();
        //	emit drag(dx,dy);
        //	break;
        default:
                LOG( "^^^ unexpected event!\n\n"; )
                // error!
                break;
        }
        LOG ( " --> cancelLongTapTimer\n --> cancelSingleTapTimer\n --> emit drag()" << states[state] << "\n\n"; )
}

void QGaugeWidget::mouseReleaseEvent(QMouseEvent * /*event*/)
{
    LOG( states[state] << "\n <-- mouseRelease\n"; )
    switch(state)
    {
    case QGaugeWidget::StInitialTouch:
        cancelLongTapTimer();
        state = StSingleTapPending;
        startSingleTapTimer();
        LOG ( " --> cancelLongTapTimer\n --> startSingleTapTimer\n" << states[state] << "\n\n"; )
        break;
    case QGaugeWidget::StSecondTouch:
        cancelLongTapTimer();
        state = StIdle;
        emit doubleTap();
        LOG ( " --> cancelLongTapTimer\n --> emit doubleTap\n" << states[state] << "\n\n"; )
        break;
    case QGaugeWidget::StLongTouch:
        state = StIdle;
        emit longTap();
        LOG ( " --> emit longTap\n" << states[state] << "\n\n"; )
        break;
    case QGaugeWidget::StMoving:
        // emit drag event
        //cancelLongMoveTimer();
        state = StIdle;
        LOG ( states[state] << "\n\n"; )
        break;
    //case QGaugeWidget::StLongMove:
    //    // emit drag event
    //    state = StIdle;
    //    LOG ( states[state] << "\n\n"; )
    //    break;
    default:
        LOG( "^^^ unexpected event!\n\n"; )
        // error!
        break;
    }
}
