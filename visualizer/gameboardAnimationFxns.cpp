#include "gameboardWidget.h"
#include <stdlib.h>
#include <time.h>



void Gameboard::drawAnimations( Game * game, float falloff)
{

	int frame = getAttr( frameNumber );
	for (std::vector<Animation*>::iterator it = game->states[frame].animations.begin();
		it != game->states[frame].animations.end();
		it++)
	{
		switch ( (*it)->type)
		{
			case ADD:
				break;
			case ATTACK:
				drawAttack(game,(Attack*)(*it),falloff);
				break;
			case BUILD:
				drawBuild(game,(Build*)(*it),falloff);
				break;
			case COLLIDE:
				drawCollide(game,(Collide*)(*it),falloff);
				break;
			case COMBINE:
				break;
			case HEAL:
				drawHeal(game,(Heal*)(*it),falloff);
				break;
			case MOVE:
				break;
			case REMOVE:
				break;
			case SPLIT:
				break;
		}
	}
}


Unit *findExistance( GameState &state, int unit )
{
	if( state.bots.find( unit ) != state.bots.end() )
		return (Unit *)&state.bots[unit];
	if( state.frames.find( unit ) != state.frames.end() )
		return (Unit *)&state.frames[unit];
	if( state.walls.find( unit ) != state.walls.end() )
		return (Unit *)&state.walls[unit];
	if( state.units.find( unit ) != state.units.end() )
		return (Unit *)&state.units[unit];

	return 0;

}


void Gameboard::drawCollide(Game * game, Collide * collide, float falloff)
{
	int x0, y0, xf, yf;
	int frame = getAttr( frameNumber );
	int unitSize = getAttr( unitSize );
	// Make the random seed the pointer so jitter is consistant

	if ((unsigned)frame + 1 < game->states.size()-1)
	{
		GameState stateCurrent = game->states[frame];
		GameState stateBackward = game->states[frame-1];
		GameState stateForward = game->states[frame+1];

		Unit *attacker = findExistance( stateCurrent,  collide->attacker );
		Unit *victim   = findExistance( stateBackward, collide->victim );
		Unit *deadUnit = findExistance( stateForward,  collide->victim );

		if ( !victim )
		{
			victim = findExistance( stateCurrent,  collide->victim );
		}

		if ( !attacker )
		{
			attacker = findExistance( stateBackward,  collide->attacker );
		}

		if ( !deadUnit && victim )	 //draw the dead unit
		{
			drawSingleUnit(game,victim,frame-1,unitSize,falloff,true);
			//todo: add to dead units
		}

		if (victim && attacker)			 //temporary
		{

			x0 = attacker->x*unitSize;
			y0 = attacker->y*unitSize;

			xf = victim->x*unitSize;
			yf = victim->y*unitSize;

			float x, y;
			if (falloff < .5)
			{
				x = (xf-x0)*falloff + x0;
				y = (yf-y0)*falloff + y0;
			}
			else
			{
				x = -(xf-x0)*falloff + x0;
				y = -(yf-y0)*falloff + y0;
			}

			Bot attackCopy = *((Bot*)(attacker));

			attackCopy.x = x;
			attackCopy.y = y;

			drawSingleBot(game,&attackCopy,frame,unitSize,falloff);
		}
	}
}


void Gameboard::drawAttack( Game * game, Attack * attack, float falloff )
{
	int x0, y0, xf, yf;
	int frame = getAttr( frameNumber );
	int unitSize = getAttr( unitSize );
	// Make the random seed the pointer so jitter is consistant
	srand( (long unsigned int)attack );
	static int lag = 0;

	if ((unsigned)frame + 1 < game->states.size()-1)
	{
		lag++;
		GameState stateCurrent = game->states[frame];
		GameState stateBackward = game->states[frame-1];
		GameState stateForward = game->states[frame+1];

		int bulletSize = unitSize*3/5;

		Unit *attacker = findExistance( stateCurrent,  attack->attacker );
		Unit *victim   = findExistance( stateBackward, attack->victim );
		Unit *deadUnit = findExistance( stateForward,  attack->victim );

		if( !attacker || !victim )
			return;

		if ( !deadUnit )						 //draw the dead unit
		{
			drawSingleUnit(game,victim,frame,unitSize,falloff,true);
			//todo: add to dead units
		}

		int xJitter = 0;						 //rand() % attacker->size*unitSize*2/3- attacker->size*unitSize/3;
		int yJitter = 0;						 //rand() % attacker->size*unitSize*2/3 - attacker->size*unitSize/3;

		x0 = attacker->x*unitSize+(attacker->size-1)*unitSize/2+(unitSize-bulletSize)/2 + xJitter;
		y0 = attacker->y*unitSize+(attacker->size-1)*unitSize/2+(unitSize-bulletSize)/2 + yJitter;

		xf = victim->x*unitSize+(victim->size-1)*unitSize/2+(unitSize-bulletSize)/2;
		yf = victim->y*unitSize+(victim->size-1)*unitSize/2+(unitSize-bulletSize)/2;

		float init = (float)(rand()%100)/100;
		float coolFalloff = (falloff-init)/(.45);
		if( coolFalloff > 1 )
			coolFalloff = 1;
		if( coolFalloff < 0 )
			coolFalloff = 0;

		float x, y;
		x = (xf-x0)*coolFalloff + x0;
		y = (yf-y0)*coolFalloff + y0;

		glPushMatrix();
		glTranslatef(x,y,0);
		glScalef( bulletSize , bulletSize, 1 );

		glEnable( GL_TEXTURE_2D );
		switch (stateCurrent.bots[attack->attacker].owner)
		{
			case 0:

				glColor4f( 0, 1, 0, 1 );
				glBindTexture( GL_TEXTURE_2D, textures[T_REDPART_ATTACK].getTexture() );
				break;
			default:
				glColor4f( 0, .7, 1, 1 );
				glBindTexture( GL_TEXTURE_2D, textures[T_BLUPART_ATTACK].getTexture() );

		}

		glBegin(GL_QUADS);

		glTexCoord2f( 0, 0 ); glVertex3f(0, 1.0f, 0);
		glTexCoord2f( 1, 0 ); glVertex3f( 1.0f, 1.0f, 0);
		glTexCoord2f( 1, 1 ); glVertex3f( 1.0f,0, 0);
		glTexCoord2f( 0, 1 ); glVertex3f(0,0,0);

		glEnd();

		glPopMatrix();
	}
}


void Gameboard::drawBuild( Game * game , Build * build , float falloff  )
{
	int x0, y0, xf, yf;
	int frame = getAttr( frameNumber );
	int unitSize = getAttr( unitSize );
	// Make the random seed the pointer so jitter is consistant

	if ((unsigned)frame + 1 < game->states.size()-1)
	{
		GameState stateCurrent = game->states[frame];
		GameState stateBackward = game->states[frame-1];
		GameState stateForward = game->states[frame+1];

		Unit *builder = findExistance( stateCurrent,  build->builder );
		Unit *victim   = findExistance( stateBackward, build->frame );

		if ( !victim )
		{
			victim   = findExistance( stateCurrent, build->frame );
		}

		if ( victim )
		{

			x0 = builder->x*unitSize+(builder->size-1)*unitSize/2;
			y0 = builder->y*unitSize+(builder->size-1)*unitSize/2;

			xf = victim->x*unitSize+(victim->size-1)*unitSize/2;
			yf = victim->y*unitSize+(victim->size-1)*unitSize/2;

			float x, y;
			x = (xf-x0)*falloff + x0;
			y = (yf-y0)*falloff + y0;

			glPushMatrix();

			/*
			if ( (xf-x0 == 0) && (yf-y0 > 0) )
				glRotated(90, 0,0,1);

			if ( (xf-x0 < 0) && (yf-y0 == 0) )
				glRotated(90, 0,0,2);

			if ( (xf-x0 == 0) && (yf-y0 < 0) )
				glRotated(90, 0,0,-1);
			*/
			glTranslatef(x,y,0);
			glScalef( unitSize , unitSize, 1 );

			glEnable( GL_TEXTURE_2D );
			switch (stateCurrent.bots[build->builder].owner)
			{
				case 0:

					glColor4f( 1, .7, .7, 1 );
					glBindTexture( GL_TEXTURE_2D, textures[T_REDPART_BUILD].getTexture() );
					break;
				default:
					glColor4f( .7, .7, 1, 1 );
					glBindTexture( GL_TEXTURE_2D, textures[T_BLUPART_BUILD].getTexture() );

			}

			glBegin(GL_QUADS);

			glTexCoord2f( 0, 0 ); glVertex3f(0, 1.0f, 0);
			glTexCoord2f( 1, 0 ); glVertex3f( 1.0f, 1.0f, 0);
			glTexCoord2f( 1, 1 ); glVertex3f( 1.0f,0, 0);
			glTexCoord2f( 0, 1 ); glVertex3f(0,0,0);

			glEnd();

			glPopMatrix();
		}
	}
}


void Gameboard::drawHeal( Game * game , Heal * heal , float falloff  )
{
	int x0, y0, xf, yf;
	int frame = getAttr( frameNumber );
	int unitSize = getAttr( unitSize );
	// Make the random seed the pointer so jitter is consistant

	if ((unsigned)frame + 1 < game->states.size()-1)
	{
		GameState stateCurrent = game->states[frame];
		GameState stateBackward = game->states[frame-1];
		GameState stateForward = game->states[frame+1];

		Unit *healer = findExistance( stateCurrent,  heal->healer );
		Unit *victim   = findExistance( stateBackward, heal->victim );

		if ( !victim )
		{
			victim   = findExistance( stateCurrent, heal->victim );
		}

		if ( victim && healer )
		{

			x0 = healer->x*unitSize+(healer->size-1)*unitSize/2;
			y0 = healer->y*unitSize+(healer->size-1)*unitSize/2;

			xf = victim->x*unitSize+(victim->size-1)*unitSize/2;
			yf = victim->y*unitSize+(victim->size-1)*unitSize/2;

			float x, y;
			x = (xf-x0)*falloff + x0;
			y = (yf-y0)*falloff + y0;

			glPushMatrix();

			glTranslatef(x,y,0);

			glScalef( unitSize , unitSize, 1 );

			glEnable( GL_TEXTURE_2D );
			switch (stateCurrent.bots[heal->healer].owner)
			{
				case 0:

					glColor4f( 1, .7, .7, 1 );
					glBindTexture( GL_TEXTURE_2D, textures[T_REDPART_BUILD].getTexture() );
					break;
				default:
					glColor4f( .7, .7, 1, 1 );
					glBindTexture( GL_TEXTURE_2D, textures[T_BLUPART_BUILD].getTexture() );

			}

			glBegin(GL_QUADS);

			glTexCoord2f( 0, 0 ); glVertex3f(0, 1.0f, 0);
			glTexCoord2f( 1, 0 ); glVertex3f( 1.0f, 1.0f, 0);
			glTexCoord2f( 1, 1 ); glVertex3f( 1.0f,0, 0);
			glTexCoord2f( 0, 1 ); glVertex3f(0,0,0);

			glEnd();

			glPopMatrix();
		}
	}
}
