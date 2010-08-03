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
extern QImage svgCompassRing;
extern QImage svgSpeedNeedle;

#ifdef Q_OS_SYMBIAN
#define TEXTDIVIDER 38
#else
#define UIDIR "/Users/hurenkam/workspace/qtracker/images/"
#define TEXTDIVIDER 14
#endif

#ifdef USE_QT_RESOURCES
#define DASHRCDIR   ":/dash/"
#define MAPRCDIR    ":/map/"
#define CSSRCDIR    ":/css/"
#define SPLASHRCDIR ":/splash/"
#define DIALOGRCDIR ":/dialog/"
#else
#define DASHRCDIR    GetDrive() + "/private/EA82CEF3/ui/"
#define MAPRCDIR     GetDrive() + "/private/EA82CEF3/ui/"
#define CSSRCDIR     GetDrive() + "/private/EA82CEF3/ui/"
#define SPLASHRCDIR  GetDrive() + "/private/EA82CEF3/ui/"
#define DIALOGRCDIR  GetDrive() + "/private/EA82CEF3/ui/"
#endif

void LoadImages();
QString GetDrive();
QString GetDriveAndPath();
#endif /* UI_H_ */
