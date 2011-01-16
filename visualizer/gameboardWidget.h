#ifndef GAMEBOARDWIDGET_H
#define GAMEBOARDWIDGET_H

#include <QtGui>
#include <QtOpenGL>
#include <QTime>
#include <QTimer>
#include <list>
#include "texture.h"
#include "parser.h"
#include "visualizerWindow.h"
#include "visettings.h"
#include "drawGLFont.h"

using namespace std;

class VisualizerWindow;

enum eTextures
{
	T_REDBOT_ACTION = 0,
	T_REDBOT_BUILDER,
	T_REDBOT_CANNON,
	T_REDBOT_DAMAGE,
	T_REDBOT_ENGINE,
	T_REDBOT_FORCE,
	T_REDBOT_FRAME,
	T_REDBOT_JOINT,

	T_REDPART_ATTACK,
	T_REDPART_BUILD,

	T_BLUBOT_ACTION,
	T_BLUBOT_BUILDER,
	T_BLUBOT_CANNON,
	T_BLUBOT_DAMAGE,
	T_BLUBOT_ENGINE,
	T_BLUBOT_FORCE,
	T_BLUBOT_FRAME,
	T_BLUBOT_JOINT,

	T_BLUPART_ATTACK,
	T_BLUPART_BUILD,

	T_BG,
	T_DEFAULTBG,
	T_GRID,
	T_FONT,

	T_WALL100,
	T_WALL75,
	T_WALL50,
	T_WALL25,

	T_EXPLODE, 

	numTextures

};

Unit *findExistance( GameState &state, int unit );

class Gameboard : public QGLWidget
{
	Q_OBJECT
		friend class VisualizerWindow;

	public:
		Gameboard( QWidget *parent );
		~Gameboard();

		void toggleMapGrid();

		bool loadBackground( QString filename );
		void clearBackground();

	private slots:

	protected:
		void initializeGL();
		void resizeGL( int width, int height );
		void paintGL();
		void timerEvent( QTimerEvent * );
		void drawBackground( );
		void drawScoreboard( Game *game );
		void drawMouse();
		void drawProgressbar( Game * game);
		void drawWinnerScreen( Game *game, int elapsed );
		void drawIntroScreen( Game *game, int elapsed );

		void drawSingleUnit(Game * game, Unit * unit, int frame, int unitSize, float falloff, bool dead = false);

		void drawBots( Game* game, float falloff );
		void drawSingleBot( Game *game, Bot * bot, int frame, int unitSize, float falloff, bool dead = false );

		void drawWalls( Game *game, float falloff);
		void drawSingleWall( Game *game, Wall * wall, int frame, int unitSize );

		void drawFrames( Game *game, float falloff);
		void drawSingleFrame( Game *game, Frame * botFrame, int frame, int unitSize );

		void drawAnimations( Game * game, float falloff);
		void drawAttack( Game * game, Attack * attack, float falloff );
		void drawBuild( Game * game, Build * build, float falloff );
		void drawHeal( Game * game, Heal * heal, float falloff );
		void drawCollide(Game * game, Collide * collide, float falloff);


		void talkRobotsGodDamnitTalk(Game *game);
		void printStats(Game *game);

		bool loadAllTextures( QString & message );
		bool loadTexture(QString filename, eTextures texID, QString & errString);

		void drawControl();

		void drawHealth( int x, int y, int h, int w, int maxHealth, int health, int owner );
		void drawSprite( int x, int y, int h, int w, int texture, bool selected, int owner );

		float getPercentage(int owner = -1, int size = -1);
		map<int,string> selectedIDs;

		texture textures[numTextures];

		VisualizerWindow *parent;

		QTime time;
		QTime buttonTimes;

		bool hasMapGrid;
		bool hasDefaultBG;					 //default background

		void mousePressEvent( QMouseEvent *event );
		void mouseReleaseEvent( QMouseEvent *event );
		void mouseMoveEvent( QMouseEvent *event );

		DrawGLFont *drawFont;

		bool leftButtonDown;
		bool leftDoubleClick;
		bool leftButtonDrag;

		bool rightButtonDown;
		bool midButtonDown;

		int curX;
		int curY;

		int clickX;
		int clickY;

		int dragX;
		int dragY;

		int leftButtonTime;
		int rightButtonTime;
		int midButtonTime;

		int timerId;

};
#endif
