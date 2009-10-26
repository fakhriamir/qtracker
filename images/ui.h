/*
 * ui.h
 *
 *  Created on: 4-okt-2009
 *      Author: Mark
 */

#ifndef UI_H_
#define UI_H_

#include <QtGui>
extern QImage svgClock;
extern QImage svgAltitude;
extern QImage svgHeading;
extern QImage svgSatView;
extern QImage svgSpeed10;
extern QImage svgSpeed200;

extern QImage svgLong;
extern QImage svgShort;
extern QImage svgSecond;
extern QImage svgCompassNeedle;
extern QImage svgSpeedNeedle;

#ifdef Q_OS_SYMBIAN
#define UIDIR "/private/EA82CEF3/ui/"
#define TEXTDIVIDER 36
#else
#define UIDIR "/Users/hurenkam/workspace/qtracker/images/"
#define TEXTDIVIDER 12
#endif

void LoadImages();
QString GetDrive();
#endif /* UI_H_ */
