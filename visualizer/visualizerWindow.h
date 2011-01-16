#ifndef VISUALIZERWINDOW_H
#define VISUALIZERWINDOW_H

#include <QtGui>
#include <QSlider>
#include <QMainWindow>
#include <QDockWidget>
#include <QShortcut>
#include <QLabel>

#include "gameboardWidget.h"
#include "parser.h"
#include "statsDialog.h"


class Gameboard;

// defines playback modes
enum
{
	play = 0,
	paused,
	stop,
	fastForward,
	rewinding
};

class UnitSelection: public QLabel
{
	Q_OBJECT
		public:

};

class Scoreboard: public QWidget
{
	Q_OBJECT
		public:

};

class Options: public QWidget
{
	Q_OBJECT
		public:
		Options();
		void addOptions();
	private slots:
		void togglePersistant(bool );
		void toggleTeam1(bool );
		void toggleTeam2(bool );
		void sliderChanged(int);
};

class VisualizerWindow: public QMainWindow
{
	Q_OBJECT
		friend class Gameboard;
	public:
		VisualizerWindow();
		GameState *getFrame( int frame = -1 );
		bool loadGamelog( char *filename );

		Game *gamelog;

		// Play controls
	protected:
		QSlider *controlSlider;
		QLabel *turnLabel;
		QPushButton *playButton;
		QPushButton *rewindButton;
		QPushButton *fastForwardButton;
		QPushButton *stopButton;
		void closeEvent( QCloseEvent *event );

		bool fullScreen;

	private slots:
		void openGamelog();
		void closeGamelog();
		void exitProgram();
		void toggleFullScreen();
		void closeFullScreen();
		void toggleMapGrid();
		void loadBackground();
		void clearBackground();
		void advanceFrame();
		void previousFrame();
		void playPause();

		// Help File
		void viewGameDocs();

		// Play control fuctions
		void controlSliderDrag();
		void controlSliderReleased();
		void controlSliderChanged(int frame);
		void stopClicked();
		void playClicked();
		void fastForwardClicked();
		void rewindClicked();

	private:
		void createMenus();
		void createLayout();
		void createActions();

		QMenu *fileMenu;
		QMenu *viewMenu;
		QMenu *helpMenu;



		QFrame *bottomBar;
		QFrame *controlBar;
		QTextEdit *console;
		QTabWidget *toolBox;

		Scoreboard *scoreboard;
		Options *options;

                QFrame *unitSelection;
                UnitSelection *unitSelectionL;
                UnitSelection *unitSelectionR;

		QAction *viewGameDocsAct;
		QAction *openGameAct;
		QAction *closeGameAct;
		QAction *toggleFullScreenAct;
		QAction *toggleMapGridAct;
		QAction *loadBackgroundAct;
		QAction *clearBackgroundAct;

		QAction *exitAct;

		Gameboard *gameboard;

};
#endif
