#include <iostream>
#include <sstream>
#include "visualizerWindow.h"

using namespace std;

Options::Options()
{
	addOptions();
}


void Options::togglePersistant( bool on)
{
	setAttr( lastFrame, -1 );
	setAttr( persistantTalking, on );
}


void Options::toggleTeam1( bool on )
{
	setAttr( lastFrame, -1 );
	setAttr( team1Talk, on );
}


void Options::toggleTeam2( bool on )
{
	setAttr( lastFrame, -1 );
	setAttr( team2Talk, on );
}


void Options::sliderChanged( int value )
{
	setAttr(unitSize, value );
}


void Options::addOptions()
{
	QVBoxLayout *vbox = new QVBoxLayout;

	QCheckBox *team1 = new QCheckBox( tr( "Show Player 1 Talk" ), this );
	team1->setCheckState( Qt::Checked );
	QCheckBox *team2 = new QCheckBox( tr( "Show Player 2 Talk" ), this );
	team2->setCheckState( Qt::Checked );
	QCheckBox *persistant = new QCheckBox( tr( "Persistant Talking?" ), this );

	QSlider *unitSizeSlider = new QSlider(Qt::Horizontal);
	unitSizeSlider->setTickInterval( 16 );
	unitSizeSlider->setMinimum(0);
	unitSizeSlider->setMaximum(128);
	unitSizeSlider->setSliderPosition( getAttr( unitSize ) );

	connect(
		unitSizeSlider,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(sliderChanged(int))
		);

	vbox->addWidget( team1 );
	vbox->addWidget( team2 );
	vbox->addWidget( persistant );
	vbox->addWidget( new QLabel( "Unit Size: ", this ) );
	vbox->addWidget( unitSizeSlider );

	connect( team1, SIGNAL( toggled(bool) ), this, SLOT( toggleTeam1(bool) ) );
	connect( team2, SIGNAL( toggled(bool) ), this, SLOT( toggleTeam2(bool) ) );
	connect( persistant, SIGNAL( toggled(bool) ), this, SLOT( togglePersistant(bool) ) );

	setLayout( vbox );

}


VisualizerWindow::VisualizerWindow()
{
	setGeometry( 0, 0, 1280, 1024 );

	string configErr;

	if (!visettings::instance()->loadFromFile(configErr))
	{
		QMessageBox::critical(this,"Config File Load Error",configErr.c_str());
	}


	createActions();
	createMenus();
	createLayout();

	setWindowTitle( "Modular Visualizer" );
	fullScreen = getAttr(arenaMode) ? false : true;
	toggleFullScreen();
	gamelog = 0;
}


void VisualizerWindow::closeEvent( QCloseEvent *event )
{
	if( event ) {}
}


void VisualizerWindow::viewGameDocs()
{
	//experement:
	QProcess webPage;
	//todo: Need to make this cross platform
	webPage.start(tr("firefox.exe"),QStringList(tr("mail.google.com")));

	cout << "Going to game docs website" << endl;
}


GameState *VisualizerWindow::getFrame( int frame )
{
	if( frame == -1 )
		frame = getAttr(frameNumber);
	return &gamelog->states[frame];
}


bool VisualizerWindow::loadGamelog( char *filename )
{

	if ( filename == NULL )
	{
		QMessageBox::critical(this,"Error","No Gamelog Specified!");
		return false;
	}

	if ( string (filename) == string("")  )
	{
		return false;
	}

	Game * temp = new Game;

	if ( !parseFile( *temp, filename ) )
	{

		QMessageBox::critical(this,"Error","Invalid Game Log or Unknown Argument");
		delete temp;
		return false;
	}

	if( gamelog )
		delete gamelog;

	gamelog = temp;

	//cout << gamelog->states.size() << endl;
	if( gamelog->states.size() < 2 )
	{
		QMessageBox::critical(this,"Error","Suicided on Turn 1.  Suicide is unethical" );
		delete gamelog;
		gamelog = 0;
		return false;
	}


	string basename = "";

	string file = filename;

	int i = file.size()-1;
	for( ; i > 0; i-- )
	{
		if( file[i] == '\\' || file[i] == '/' )
		{
			i++;
			break;
		}
	}
	//cout << i << endl;

	setAttr( gamelogName, file.substr( i,file.size()-i) ); 


	controlSlider->setMaximum( gamelog->states.size()-1 );
	return true;
}


void VisualizerWindow::openGamelog()
{

	//Get the gamelog's Filename:

	//todo: argument 3 should be the default directory of the game logs
	//todo: argument 4 should have the actual extention of a game log

	// Kill the GL Paint interrupt timer so open dialogue can load.
	gameboard->killTimer( gameboard->timerId );


	QFileDialog dlg;

	string directory = "";
	ifstream in( "lastDir" );
	if( in.is_open() )
	{
		
		getline( in, directory ); 
	}

	in.close();

	QString fileName =
		dlg.getOpenFileName(
		this,
		tr("Open Game Log"),
		directory.c_str(),
		tr("Log Files(*.gamelog)")
		);


	for( int i = fileName.size()-1; i >= 0; i-- )
	{
		if( fileName.toLocal8Bit().constData()[i] == '\\' ||
				fileName.toLocal8Bit().constData()[i] == '/' )
		{
			string file = fileName.toLocal8Bit().constData();
			directory = file.substr( 0, i );
			break;
		}
	}

	ofstream out( "lastDir" );
	out << directory.c_str() << endl;
	out.close();


	loadGamelog( (char *)fileName.toLocal8Bit().constData() );

	// Reset to frame zero
	setAttr( frameNumber, 0 );
	setAttr( playSpeed, getAttr( defaultSpeed ) );
	setAttr( currentMode, getAttr( defaultMode ) );

	// Start her up again
	gameboard->timerId = gameboard->startTimer( 20 );


}


void VisualizerWindow::toggleFullScreen()
{

	if( !fullScreen )
		showFullScreen();
	else
		showNormal();
	fullScreen = !fullScreen;
	show();
}


void VisualizerWindow::closeFullScreen()
{
	if( fullScreen )
	{
		showNormal();
		fullScreen = !fullScreen;
		show();
	}
}


void VisualizerWindow::toggleMapGrid()
{
	gameboard->toggleMapGrid();
}


void VisualizerWindow::clearBackground()
{
	gameboard->clearBackground();
}


void VisualizerWindow::loadBackground()
{
	QString filename =
		QFileDialog::getOpenFileName(
		this,
		"Open Background",
		"~/",
		"Images(*.png *.jpg)"
		);

	if ( filename == tr("") )
		return;

	if ( !gameboard->loadBackground( filename ) )
	{
		QMessageBox::critical(
			this,
			"Error",
			"The file you selected for a background wouldn't load"
			);
	}

}


void VisualizerWindow::closeGamelog()
{
	//todo: clear out the game log and recover all allocated memory
	//delete gamelog;
	//gamelog = NULL;
}


void VisualizerWindow::exitProgram()
{
	//clear out the game log, recover all allocated memory
	closeGamelog();

	//exit the program
	QApplication::quit();
}


void VisualizerWindow::createMenus()
{

	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openGameAct);
	fileMenu->addAction(closeGameAct);
	fileMenu->addAction(exitAct);

	viewMenu = menuBar()->addMenu(tr("&View"));
	viewMenu->addAction(toggleFullScreenAct);
	viewMenu->addAction(toggleMapGridAct);
	viewMenu->addAction(loadBackgroundAct);
	viewMenu->addAction(clearBackgroundAct);

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(viewGameDocsAct);
}


void VisualizerWindow::controlSliderDrag()
{
	setAttr( dragging, true );
}


void VisualizerWindow::controlSliderReleased()
{
	setAttr( dragging, false );
}


void VisualizerWindow::controlSliderChanged(int frame)
{
	setAttr( frameNumber, frame );
	if ( getAttr( currentMode ) == play && frame == 1 )
	{
		stopClicked();
	}
}


void VisualizerWindow::stopClicked()
{
	setAttr( frameNumber, 0 );
	setAttr( currentMode, paused );
	controlSlider->setSliderPosition( 0 );
	playButton->setText("Play");
}


void VisualizerWindow::playClicked()
{
	if( getAttr( currentMode ) == paused)
	{
		setAttr( currentMode, play );
		playButton->setText("Pause");
		setAttr( playSpeed, getAttr(defaultSpeed));
	}
	else
	{
		setAttr( currentMode, paused );
		playButton->setText("Play");
	}
}


void VisualizerWindow::fastForwardClicked()
{
	if(getAttr(currentMode) == paused)
	{
		setAttr( currentMode, play );
		playButton->setText("Pause");
	}

	else if(getAttr(currentMode) == play)
	{
		setAttr( currentMode, fastForward );
		setAttr( playSpeed, getAttr(playSpeed)/2);
	}
	else if(getAttr(currentMode) == fastForward && getAttr(playSpeed)>getAttr(minSpeed))
	{
		setAttr( playSpeed, getAttr(playSpeed)/2);
	}
	else if(getAttr(currentMode) == rewinding)
	{
		if(getAttr(playSpeed) == getAttr(defaultSpeed)/2)
		{
			setAttr( playSpeed, getAttr(defaultSpeed));
			setAttr( currentMode, play );
		}
		else
		{
			setAttr( playSpeed, getAttr(playSpeed)*2);
		}
	}
}


void VisualizerWindow::rewindClicked()
{
	if(getAttr(currentMode) == paused)
	{
		setAttr( currentMode, play );
		playButton->setText("Pause");
	}

	else if(getAttr(currentMode) == play)
	{
		setAttr( currentMode, rewinding );
		setAttr( playSpeed, getAttr(playSpeed)/2);
	}
	else if(getAttr(currentMode) == rewinding && getAttr(playSpeed) > getAttr(minSpeed))
	{
		setAttr( playSpeed, getAttr(playSpeed)/2);
	}
	else if(getAttr(currentMode) == fastForward)
	{
		if(getAttr(playSpeed) == getAttr(defaultSpeed)/2)
		{
			setAttr( playSpeed, getAttr(defaultSpeed));
			setAttr( currentMode, play );
		}
		else
		{
			setAttr( playSpeed, getAttr(playSpeed)*2);
		}
	}
}


void VisualizerWindow::createLayout()
{
	// Remove awkward spacing around the edges
	setContentsMargins( 0, 0, 0, 0 );
	layout()->setContentsMargins( 0, 0, 0, 0 );
	QGLFormat f = QGLFormat::defaultFormat();
	f.setSampleBuffers(true);
	QGLFormat::setDefaultFormat(f);
	if (!QGLFormat::hasOpenGL())
	{
		QMessageBox::information(
			0,
			"Opengl",
			"SYSTEM DOES NOT SUPPORT OPENGL",
			QMessageBox::Ok);
		return;
	}

	controlSlider = new QSlider(Qt::Horizontal);
	controlSlider->setStyleSheet( "\
			QSlider::groove:horizontal {\
			height: 8px;\
			border: 1px solid #999999;\
			background: qlineargradient( x1: 0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\
			}\
			QSlider::handle:horizontal {\
			width: 50px;\
			height: 15px;\
			border: 1px solid #999999;\
			margin: -2px 0px; \
			border-radius: 3px;\
			background: qlineargradient(x1:0, y1:0, x2:1, y2:1,stop:0 #b4b4b4, stop:1 #909090);\
			}\
		  QSlider::sub-page:horizontal {\
			background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1, stop: 0 #F66E00, stop: 1 #CF5C00);\
			height: 10px;\
			border-radius: 4px;\
		  }	");

	turnLabel = new QLabel(this);
	gameboard = new Gameboard(this);

	QDockWidget *bottomDock = new QDockWidget(this );
	bottomDock->setAllowedAreas( Qt::BottomDockWidgetArea );
	//bottomDock->setFeatures( QDockWidget::NoDockWidgetFeatures );
	bottomDock->setMinimumHeight( 0 );

	QHBoxLayout *debugLayout = new QHBoxLayout;
	console = new QTextEdit;
	console->setReadOnly(true);
	toolBox = new QTabWidget;
	bottomBar = new QFrame;
	controlBar = new QFrame;
	scoreboard = new Scoreboard;
	unitSelection = new QFrame;

  QHBoxLayout *unitSelectionLayout = new QHBoxLayout;                   
  unitSelectionL = new UnitSelection;
  unitSelectionR = new UnitSelection;                                   
  unitSelectionLayout->addWidget(unitSelectionL);                       
  unitSelectionLayout->addWidget(unitSelectionR);                       
  unitSelection->setLayout(unitSelectionLayout);

	options = new Options;
	playButton = new QPushButton("Pause");
	rewindButton = new QPushButton("<<");
	fastForwardButton = new QPushButton(">>");
	stopButton = new QPushButton("Stop");

	// Creates the layout for the controlBar
	QHBoxLayout *controlLayout = new QHBoxLayout;
	controlLayout->addWidget(controlSlider);
	controlLayout->addWidget(turnLabel);
	controlLayout->addWidget(playButton);
	controlLayout->addWidget(rewindButton);
	controlLayout->addWidget(fastForwardButton);
	controlLayout->addWidget(stopButton);
	controlBar->setLayout(controlLayout);

	//toolBox->addTab( scoreboard, tr( "Scoreboard" ) );
	toolBox->addTab( unitSelection, tr( "Unit Stats" ) );
	toolBox->addTab( options, tr("Options") );
	//unitSelection->setFixedHeight( 50 );

	debugLayout->addWidget( console );
	debugLayout->addWidget( toolBox );

	bottomBar->setLayout( debugLayout );

	//bottomBar->setMaximumHeight( 250 );

	QFrame *bottomFrame = new QFrame;
	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->setContentsMargins( 0, 0, 0, 0 );
	debugLayout->setContentsMargins( 0, 0, 0, 0 );

	playButton->setFixedWidth(50);
	rewindButton->setFixedWidth(30);
	fastForwardButton->setFixedWidth(30);
	stopButton->setFixedWidth(45);
	controlBar->setFixedHeight( 40 );
	controlSlider->setTickInterval( 50 );
	//controlSlider->setTickPosition( QSlider::TicksBothSides );
	controlSlider->setMaximum( 0 );
	controlSlider->setMinimum( 0 );
	controlSlider->setTracking( true );

	bottomFrame->setLayout( vbox );
	bottomFrame->setMinimumHeight( 12 );
	bottomDock->setWidget( bottomFrame );

	if( !getAttr(arenaMode ) )
	{
		addDockWidget( Qt::BottomDockWidgetArea, bottomDock );
	}
	else
	{
		bottomDock->hide();
	}

	connect(
		controlSlider,
		SIGNAL(sliderPressed()),
		this,
		SLOT(controlSliderDrag())
		);
	connect(
		controlSlider,
		SIGNAL(sliderReleased()),
		this,
		SLOT(controlSliderReleased())
		);
	connect(
		controlSlider,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(controlSliderChanged(int))
		);
	connect(
		stopButton,
		SIGNAL(clicked()),
		this,
		SLOT(stopClicked())
		);
	connect(
		playButton,
		SIGNAL(clicked()),
		this,
		SLOT(playClicked())
		);
	connect(
		fastForwardButton,
		SIGNAL(clicked()),
		this,
		SLOT(fastForwardClicked())
		);
	connect(
		rewindButton,
		SIGNAL(clicked()),
		this,
		SLOT(rewindClicked())
		);

	vbox->addWidget(bottomBar, 2);
	vbox->addWidget(controlBar, 1);

	setCentralWidget( gameboard );
}


// TODO: Combine these two functions
void VisualizerWindow::advanceFrame()
{
	setAttr( currentMode, paused );

	int frame = getAttr( frameNumber );
	if( (unsigned)frame < gamelog->states.size()-1 )
		setAttr( frameNumber, frame+1 );
	controlSlider->setSliderPosition( frame+1 );
}


void VisualizerWindow::previousFrame()
{
	setAttr( currentMode, paused );
	int frame = getAttr( frameNumber );
	if( frame  > 0 )
		setAttr( frameNumber, frame-1 );
	controlSlider->setSliderPosition( frame-1 );
}


void VisualizerWindow::playPause()
{
	static int lastMode = play;
	if( getAttr( currentMode ) == paused )
	{
		setAttr( currentMode, play );
	}
	else
	{
		lastMode = getAttr( currentMode );
		setAttr( currentMode, paused );

	}
}


void VisualizerWindow::createActions()
{
	openGameAct = new QAction(tr("&Open Game Log"), this);
	openGameAct->setShortcut(tr("Ctrl+O"));
	openGameAct->setStatusTip(tr("Open a Game Log"));
	connect( openGameAct, SIGNAL(triggered()), this, SLOT(openGamelog()));

	closeGameAct = new QAction(tr("&Close Gamelog"),this);
	openGameAct->setStatusTip(tr("Close the current Game Log"));
	connect( closeGameAct, SIGNAL(triggered()), this, SLOT(closeGamelog()));

	exitAct = new QAction(tr("&Exit"),this);
	exitAct->setShortcut(tr("Ctrl+Q"));
	exitAct->setStatusTip(tr("Exit the program"));
	connect( exitAct, SIGNAL(triggered()), this, SLOT(exitProgram()));

	viewGameDocsAct = new QAction( tr("View &Game Documents"), this);
	viewGameDocsAct->setShortcut(tr("F1"));
	viewGameDocsAct->setStatusTip(tr("Documents Related to the Competition"));
	connect( viewGameDocsAct, SIGNAL(triggered()), this, SLOT(viewGameDocs()));

	toggleFullScreenAct = new QAction( tr("&Full Screen"), this );
	toggleFullScreenAct->setShortcut( tr("F11" ) );
	toggleFullScreenAct->setStatusTip( tr("Toggle Fullscreen Mode") );
	connect( toggleFullScreenAct, SIGNAL(triggered()), this, SLOT(toggleFullScreen()) );

	//todo: give this a shortcut key
	toggleMapGridAct = new QAction( tr("Toggle Grid"), this );
	toggleMapGridAct->setCheckable( true );
	toggleMapGridAct->setShortcut( tr( "Ctrl+G" ) );
	toggleMapGridAct->setStatusTip( tr("Toggle the grid on the map") );
	toggleMapGridAct->setChecked( getAttr( MapGrid ) );
	connect( toggleMapGridAct, SIGNAL(triggered()), this, SLOT(toggleMapGrid()) );

	loadBackgroundAct = new QAction( tr("Load Background"), this );
	loadBackgroundAct->setStatusTip( tr("Load a new picture as the background") );
	connect( loadBackgroundAct, SIGNAL(triggered()), this, SLOT(loadBackground()) );

	clearBackgroundAct = new QAction( tr("Clear Background"), this );
	clearBackgroundAct->setStatusTip( tr("Go back to the default background") );
	connect( clearBackgroundAct, SIGNAL(triggered()), this, SLOT(clearBackground()) );

	(void) new QShortcut( QKeySequence( tr( "Right" ) ), this, SLOT( advanceFrame() ) );
	(void) new QShortcut( QKeySequence( tr( "Left" ) ), this, SLOT( previousFrame() ) );
	(void) new QShortcut( QKeySequence( tr( "Space" ) ), this, SLOT( playPause() ) );
	(void) new QShortcut( QKeySequence( tr( "Escape" ) ), this, SLOT( closeFullScreen() ) );

	//	QAction *advance = new QAction( this );
	//	advance->setShortcut( tr("Ctrl+P") );
	//	connect( advance, SIGNAL(triggered()), this, SLOT(openGamelog()) );

}
