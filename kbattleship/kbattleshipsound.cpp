/***************************************************************************
                             kbattleshipsound.cpp
                             -------------------
    Developers: (c) 2000 Nikolas Zimmermann <wildfox@kde.org>
                (c) 2000 Daniel Molkentin <molkentin@kde.org>

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "kbattleshipsound.moc"

SimpleSoundServer *soundserver = 0;
static bool soundRunning;

KBattleshipSound::KBattleshipSound() : QObject()
{
    initSoundServer();
}

KBattleshipSound::~KBattleshipSound()
{
}

void KBattleshipSound::initSoundServer()
{
    soundserver = new SimpleSoundServer;
    *soundserver = Arts::Reference( "global:Arts_SimpleSoundServer" );
    if( soundserver->isNull() )
    {
	KMessageBox::error( 0L, i18n( "Couldn't connect to Arts Soundserver. Sound deactivated" ) );
	soundRunning = false;
    }
    else
    {
	soundRunning = true;
    }
	
}

void KBattleshipSound::playSound( int file )
{
    kdDebug() << "PLAY!" << endl;
    if( isRunning() )
    {
	KStandardDirs *stdDirs = KGlobal::dirs();
	QString picDir;
	QStringList picDirl = stdDirs->findDirs( "data", "kbattleship" );
	for( QStringList::Iterator it=picDirl.begin(); it!=picDirl.end(); ++it )
	{
	    picDir=*it;
	    break;
	}

	picDir = picDir + "sounds/";
    
	switch( file )
	{
	    case SHIP_EXPLODE:
		soundserver->play( QString( picDir + QString( "ship-explode.mp3" ) ).latin1() );
		break;
		
	    case PLAYER1_SHOOT_HIT:
		soundserver->play( QString( picDir + QString( "ship-player1-shoot.mp3" ) ).latin1() );
		break;
		
	    case PLAYER2_SHOOT_HIT:
		soundserver->play( QString( picDir + QString( "ship-player2-shoot.mp3" ) ).latin1() );
		break;

	    case PLAYER_SHOOT_WATER:
		kdDebug() << "I'll play this NOW" << endl;
		kdDebug() << "File: " <<  QString( picDir + QString( "ship-player-shoot-water.mp3" ) ) << endl;
		soundserver->play( QString( picDir + QString( "ship-player-shoot-water.mp3" ) ).latin1() );
		break;
    
	    case SHIP_SINK:
		soundserver->play( QString( picDir + QString( "ship-sink.mp3" ) ).latin1() );
		break;
	}
    }
}

bool KBattleshipSound::isRunning()
{
    kdDebug() << "RUNCHECK!" << endl;
    kdDebug() << "isRunning: " << soundRunning << endl;
    return soundRunning;
}
