#include "gameboardWidget.h"
#include <sstream>

void Gameboard::drawWinnerScreen( Game *game, int elapsed )
{

	glDisable(GL_TEXTURE_2D);
	glBegin( GL_QUADS );
	glVertex3f( 0, 0, 0 );
	glVertex3f( 1280, 0, 0 );
	glVertex3f( 1280, 1024, 0 );
	glVertex3f( 0, 1024, 0 );
	glEnd();

	glEnable( GL_TEXTURE_2D );

	if( game->winner )
		glColor4f( 0, 0, 1, 1 );
	else
		glColor4f( 1, 0, 0, 1 );

	stringstream ss;
	ss << game->players[game->winner] << " WINS";

	glTranslatef( 640, 250, 0 );
	glScalef( 1.5, 1.5, 1.5 );
	drawFont->setAlignment( align_center );
	drawFont->drawString( ss.str().c_str() );
	ss.str("");
	ss <<	"By ";
	ss << game->winReason << endl;
	glTranslatef( 0, 32, 0 );
	string output = ss.str();
	output = output.substr( 0, output.size()-1);
	drawFont->drawString( output.c_str() );
	drawFont->setAlignment( align_left );

}

void Gameboard::drawIntroScreen( Game *game, int elapsed )
{
	glDisable( GL_TEXTURE_2D );

	glPushMatrix();
	glLoadIdentity();
	glScalef( getAttr(boardWidthPx), getAttr(boardHeightPx), 1 );
	glColor4f( 1, 1, 1, 1 );
	glBegin( GL_QUADS );
	glVertex3f( 0, 0, 0 );
	glVertex3f( 0, 1, 0 );
	glVertex3f( 1, 1, 0 );
	glVertex3f( 1, 0, 0 );
	glEnd();

	glLoadIdentity();

	stringstream ss;

	glTranslatef( getAttr(unitSize)*game->states[0].boardX/3, 300, 0 );
	drawFont->resetColors();
	drawFont->addColor( 1, 0, 0 );
	drawFont->addColor( 0, 0, 0 );
	drawFont->addColor( 0, 0, 1 );

	ss << "$" <<  game->players[0] << "$ vs.$ " << game->players[1];

	glColor4f( 0, 0, 0, 1 );
	drawFont->setAlignment( align_left );
	drawFont->drawString( ss.str().c_str() );
	drawFont->setAlignment( align_left );
	drawFont->resetColors();

	glPopMatrix();

	glEnable( GL_TEXTURE_2D );



}

void Gameboard::drawScoreboard( Game *game)
{

	glEnable(GL_BLEND);

	stringstream ss;

	glPushMatrix();

	if (drawFont != NULL)
	{	
		
		ss << getAttr( team1Score );

		glColor3f( 1, .4, .4 );
		drawFont->drawString( game->players[0].c_str() );
		glTranslatef( 0, 32, 0 );
		drawFont->drawString( ss.str().c_str() );
		ss.str("");

		ss << getAttr( team2Score );
		glColor3f( .6, .6, 1 );
		drawFont->setAlignment( align_right );
		glTranslatef( getAttr( unitSize )*game->states[0].boardX, -32, 0 );
		drawFont->drawString( game->players[1].c_str() );
		glTranslatef( 0, 32, 0 );

		drawFont->drawString( ss.str().c_str() );

		drawFont->setAlignment( align_left );
		glPopMatrix();
		glColor4f( 1,1,1,1 );
		glPushMatrix();
		glTranslatef( 640, 0, 0 );
		drawFont->setAlignment( align_center );
		drawFont->drawString( "Mega Miner 6: Modular" );
		glTranslatef( 0, 32, 0 );
		if( getAttr( gamelogName ).size() )
			drawFont->drawString( getAttr( gamelogName ).c_str() );
		drawFont->setAlignment( align_left );
		drawFont->resetColors();

	}
	glColor3f( 1, 1, 1 );

	glPopMatrix();

}


void Gameboard::drawProgressbar( Game *game )
{

	glEnable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );

	glPushMatrix();

	int w = getAttr(unitSize)*game->states[0].boardX*getAttr(frameNumber)/(game->states.size()-1);
	int h = 12;

	// Find correct y position
	glTranslatef( 0,getAttr(unitSize)*game->states[0].boardY, 0 );

	glColor4f( 1, 1, 1, 1 );
	glBegin( GL_QUADS );

	glVertex3f( 0, 0, 0 );
	glVertex3f( w, 0, 0 );
	glVertex3f( w, h, 0 );
	glVertex3f( 0, h, 0 );

	glEnd();

	glPopMatrix();

	glEnable( GL_TEXTURE_2D );

}


void Gameboard::drawMouse()
{
	if( leftButtonDrag )
	{

		glPushMatrix();

		glDisable( GL_TEXTURE_2D );

		glColor4f( 0, .7, 0, .4 );
		glBegin( GL_QUADS );
		glVertex3f( curX, curY, 0 );
		glVertex3f( dragX, curY, 0 );
		glVertex3f( dragX, dragY, 0 );
		glVertex3f( curX, dragY, 0 );
		glEnd();

		glColor4f( 0, .5, 0, .7 );

		glLineWidth( 2 );
		glBegin( GL_LINE_LOOP );
		glVertex3f( curX, curY, 0 );
		glVertex3f( dragX, curY, 0 );
		glVertex3f( dragX, dragY, 0 );
		glVertex3f( curX, dragY, 0 );
		glEnd();

		glColor4f( 1, 1, 1, 1 );

		glPopMatrix();
	}
}


void Gameboard::drawBackground()
{

	glPushMatrix();
	float baseHeight = getAttr( boardHeightPx );
	float baseWidth  = getAttr( boardWidthPx );

	glScalef( (float)getAttr(unitSize)/32, (float)getAttr(unitSize)/32,1 );
	if ( hasDefaultBG )
	{
		glDisable( GL_TEXTURE_2D );

		glColor4f( 1, 1, 1, 1 );

		glBegin( GL_QUADS );
		glTexCoord2f( 0, 0 );
		glVertex3f( 0, 0, 0 );
		glTexCoord2f( 20, 0 );
		glVertex3f( baseWidth, 0, 0 );
		glTexCoord2f( 20, 10 );
		glVertex3f( baseWidth, baseHeight, 0 );
		glTexCoord2f( 0, 10 );
		glVertex3f( 0, baseHeight, 0 );
		glEnd();



		glEnable( GL_TEXTURE_2D );

		glBindTexture( GL_TEXTURE_2D, textures[T_DEFAULTBG].getTexture() );

		glColor4f( 1, 1, 1, .95 );
		glBegin( GL_QUADS );

		glTexCoord2f( 0, 0 );
		glVertex3f( 0, 0, 0 );
		glTexCoord2f( 20, 0 );
		glVertex3f( baseWidth, 0, 0 );
		glTexCoord2f( 20, 10 );
		glVertex3f( baseWidth, baseHeight, 0 );
		glTexCoord2f( 0, 10 );
		glVertex3f( 0, baseHeight, 0 );
		glEnd();


		if ( hasMapGrid )
		{
			glBindTexture( GL_TEXTURE_2D, textures[T_GRID].getTexture() );

			glBegin( GL_QUADS );

			glTexCoord2f( 0, 0 );
			glVertex3f( 0, 0, 0 );
			glTexCoord2f( 20, 0 );
			glVertex3f( baseWidth, 0, 0 );
			glTexCoord2f( 20, 10 );
			glVertex3f( baseWidth, baseHeight, 0 );
			glTexCoord2f( 0, 10 );
			glVertex3f( 0, baseHeight, 0 );

			glEnd();
		}
	}

	if ( !hasDefaultBG )
	{

		//todo: maximums should be defined by config file
		glBindTexture( GL_TEXTURE_2D, textures[T_BG].getTexture() );

		float width = (float)textures[T_BG].getWidth();
		float height =(float)textures[T_BG].getHeight();

		float aspect = width / height;

		if ( width > baseWidth )		 // width too big
		{
			width = baseWidth;
			height =  aspect / baseWidth;
		}

		if ( height > baseHeight )	 // height too big
		{
			height = baseHeight;
			width = aspect * baseHeight;
		}
		glBegin( GL_QUADS );

		glTexCoord2f( 0, 1 );
		glVertex3f( 0, 0, 0 );

		glTexCoord2f( 1, 1 );
		glVertex3f( width, 0, 0 );

		glTexCoord2f( 1, 0 );
		glVertex3f( width, height, 0 );

		glTexCoord2f( 0, 0 );
		glVertex3f( 0, height, 0 );

		glEnd();

	}
	glPopMatrix();
}


//Draws Territory Control Bar
void Gameboard::drawControl(  )
{
	float baseWidth  = getAttr(unitSize)*parent->gamelog->states[0].boardX;

	float barWidth = .9*baseWidth;
	float spacer = .05*baseWidth;
																 //Player 1's control percentage
	float onePercent = getPercentage(0);
																 //Player 2's control percentage
	float twoPercent = getPercentage(1);


	glColor4f(1, 1, 1, 1);

	glPushMatrix();
	glDisable( GL_TEXTURE_2D );

	glTranslatef( spacer, 10, 0);

	//draws all the basic lines that form the bar
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glVertex3f(0, 8, 0);
	glVertex3f(0, -8, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(barWidth, 0, 0);

	glVertex3f(barWidth, 8, 0);
	glVertex3f(barWidth, -8, 0);

	glVertex3f(barWidth/2, 8, 0);
	glVertex3f(barWidth/2, -8, 0);
	glEnd();

	//draws player 1's control percentage
	glColor4f(1, 0, 0, .8);
	glBegin(GL_QUADS);
	glVertex3f(0, 7.5, 0);
	glVertex3f(onePercent*barWidth, 7.5, 0);
	glVertex3f(onePercent*barWidth, -7.5, 0);
	glVertex3f(0, -7.5, 0);
	glEnd();

	//draws player 2's control percentage
	glColor4f(0, 0, 1, .8);
	glBegin(GL_QUADS);
	glVertex3f(barWidth, 7.5, 0);
	glVertex3f(barWidth-(twoPercent*barWidth), 7.5, 0);
	glVertex3f(barWidth-(twoPercent*barWidth), -7.5, 0);
	glVertex3f(barWidth, -7.5, 0);
	glEnd();

	glPopMatrix();
	glEnable( GL_TEXTURE_2D );
}


void Gameboard::drawHealth( int x, int y, int w, int h __attribute__ ((unused)), int maxHealth, int health, int owner = 2)
{
	float barLength = (health/static_cast<float>(maxHealth));

	glDisable(GL_TEXTURE_2D);
	switch(owner)
	{
		case 0:											 //player 1
			glColor4f(1, 1, 0, .6);
			break;
		case 1:											 //player 2
			glColor4f(0, 1, 1, .8);
			break;
		default:										 //shouldn't happen
			glColor4f(.5, .5, .5, .6);
			break;
	}
	glPushMatrix();
	glTranslatef( (x + w*.05), y+2, 0 );
	glScalef( (w*.9), 1, 1 );

	glBegin(GL_QUADS);

	glVertex3f(0.0f, 4.0f, 0.0f);
	glVertex3f(barLength, 4.0f, 0.0f);
	glVertex3f(barLength, 0.0f, 0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glEnd();
	if(owner == 1)
	{

	}
	else
	{
	}
	glColor4f( 0, 0, 0, .7 );

	glLineWidth (1.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f( 0.0, 4.0f, 0 );
	glVertex3f( 1, 4.0f, 0 );
	glVertex3f( 1, 0.0, 0 );
	glVertex3f( 0.0f, 0.0, 0 );

	glEnd();
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);

}
