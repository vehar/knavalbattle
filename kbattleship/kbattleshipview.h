/***************************************************************************
                              kbattleshipview.h
                             -------------------
    Developers: (c) 2000-2001 Nikolas Zimmermann <wildfox@kde.org>
                (c) 2000-2001 Daniel Molkentin <molkentin@kde.org>

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef KBATTLESHIPVIEW_H
#define KBATTLESHIPVIEW_H

#include <kmainwindow.h>
#include <qpainter.h>
#include <qwidget.h>
#include <qstring.h>
#include <qlist.h>
#include "kship.h"
#include "kbattlefield.h"

class KBattleshipView : public QWidget
{
    Q_OBJECT
    public:
        KBattleshipView(QWidget *parent = 0, const char *name = 0, bool draw = false);
        ~KBattleshipView();

	KBattleField *field() { return battlefield; }
	
        void startDrawing();
        void clearField();
        void changeOwnFieldData(int fieldx, int fieldy, int type);
        void changeEnemyFieldData(int fieldx, int fieldy, int type);

	void previewShip(int fieldx, int fieldy, int type, bool rotate);

	int getOwnFieldState(int fieldx, int fieldy);
	int getEnemyFieldState(int &fieldx, int &fieldy);

    signals:
        void sigEnemyFieldClicked(int, int);
        void sigOwnFieldClicked(int, int, int);
	void sigMouseOverField(int, int, bool);

    private:
	bool eventFilter(QObject *object, QEvent *event);
	
        KBattleField *battlefield;
	bool m_drawGrid;
	bool m_decide;
	int m_lastX;
	int m_lastY;
};

#endif
