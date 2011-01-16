#include "gameboardWidget.h"

void Gameboard::drawSingleUnit(Game * game, Unit * unit, int frame, int unitSize, float falloff, bool dead)
{
	if( game->states[frame].bots.find( unit->id ) != game->states[frame].bots.end() )
		drawSingleBot(game,(Bot*)unit,frame,unitSize,falloff, dead);

	if( game->states[frame].frames.find( unit->id ) != game->states[frame].frames.end() )
		drawSingleFrame(game,(Frame*)unit,frame,unitSize);

	if( game->states[frame].walls.find( unit->id ) != game->states[frame].walls.end() )
		drawSingleWall(game,(Wall*)unit,frame,unitSize);


}


void Gameboard::drawSprite( int x, int y, int w, int h, int texture, bool selected = false, int owner = 2)
{

	glBindTexture( GL_TEXTURE_2D, textures[texture].getTexture() );
	glPushMatrix();
	glTranslatef( x, y, 0 );
	glScalef( w, h, 0 );
	glColor4f(1.0,1.0,1.0,1.0f);
	glBegin(GL_QUADS);

	glTexCoord2f( 0, 0 );
	glVertex3f(0, 1.0f, 0);
	glTexCoord2f( 1, 0 );
	glVertex3f( 1.0f, 1.0f, 0);
	glTexCoord2f( 1, 1 );
	glVertex3f( 1.0f,0, 0);
	glTexCoord2f( 0, 1 );
	glVertex3f(0,0,0);

	glEnd();

	glDisable( GL_TEXTURE_2D );

	if (selected)
	{
		switch (owner)
		{
			case 0:										 //player 1
				glColor4f(5.0f,0.0f,0.0f,1.0f);
				break;
			case 1:										 //player 2
				glColor4f(0.0f,0.0f,5.0f,1.0f);
				break;
			default:
				glColor4f(0.2f,0.2f,0.2f,1.0f);

		}

		glLineWidth(3.0f);

		glBegin (GL_LINE_LOOP);

		glVertex3f(0, 1.0f, 1);
		glVertex3f( 1.0f, 1.0f, 1);
		glVertex3f( 1.0f,0, 1);
		glVertex3f(0,0, 1);

		glEnd();
		glLineWidth(1.0f);
	}

	glPopMatrix();

	glEnable( GL_TEXTURE_2D );

}


void Gameboard::drawSingleBot(Game * game, Bot * bot, int frame, int unitSize, float falloff, bool dead)
{

	int x0, y0, x1, y1;
	x0 = x1 = bot->x*unitSize;
	y0 = y1 = bot->y*unitSize;
	if((unsigned)frame+1 < game->states.size() )
	{
		if( game->states[frame+1].bots.find(bot->id) != game->states[frame+1].bots.end() )
		{
			x1 = game->states[frame+1].bots[bot->id].x*unitSize;
			y1 = game->states[frame+1].bots[bot->id].y*unitSize;
		}
	}

	//is it selected?
	bool selected = false;
	if ( selectedIDs.find( bot->id ) != selectedIDs.end() )
	{
		selected = true;
	}

	// find owner
	int owner = bot->owner;

	//set bot to appropriate type
	int sprite;

	if( dead )
	{
		sprite = T_EXPLODE;

	} else

	if (owner == 0)
	{
		switch (bot->type)
		{
			case 1:										 //Action
				sprite = T_REDBOT_ACTION;
				break;

			case 2:										 //Builder
				sprite = T_REDBOT_BUILDER;
				break;

			case 3:										 //Cannon
				sprite = T_REDBOT_CANNON;
				break;

			case 4:										 //Damage
				sprite = T_REDBOT_DAMAGE;
				break;

			case 5:										 //Engine
				sprite = T_REDBOT_ENGINE;
				break;

			case 6:										 //Force
				sprite = T_REDBOT_FORCE;
				break;

			default:									 // temp fix
				sprite = T_REDBOT_JOINT;

		}
	}
	else
	{
		switch (bot->type)
		{
			case 1:										 //Action
				sprite = T_BLUBOT_ACTION;
				break;

			case 2:										 //Builder
				sprite = T_BLUBOT_BUILDER;
				break;

			case 3:										 //Cannon
				sprite = T_BLUBOT_CANNON;
				break;

			case 4:										 //Damage
				sprite = T_BLUBOT_DAMAGE;
				break;

			case 5:										 //Engine
				sprite = T_BLUBOT_ENGINE;
				break;

			case 6:										 //Force
				sprite = T_BLUBOT_FORCE;
				break;

			default:									 // temp fix
				sprite = T_BLUBOT_JOINT;
		}
	}

	drawSprite( (int)(x0+(x1-x0)*falloff),(int)(y0+(y1-y0)*falloff),unitSize*bot->size,unitSize*bot->size, sprite, selected, owner );

	if ( bot->partOf == 0)
		drawHealth( (int)(x0+(x1-x0)*falloff), (int)(y0+(y1-y0)*falloff), unitSize*bot->size, unitSize*bot->size, bot->maxHealth, bot->health, owner );

}





void Gameboard::drawBots( Game *game, float falloff )
{

	int frame = getAttr(frameNumber);
	int unitSize = getAttr( unitSize );

	for(
		std::map<int,Bot>::iterator it = game->states[frame].bots.begin();
		it != game->states[frame].bots.end();
		it++
		)
	{
		bool flag = false;


		//keeps count of each player's percentage
		getPercentage(it->second.owner, it->second.size);

		if (it->second.partOf != 0)
		{
			// if the bot it is part of is a non-typed bot, draw it
			if (game->states[frame].bots.find(it->second.partOf)->second.type == 0)
			{
				flag = true;
			}
		}

		if ((it->second.partOf == 0 ) || flag)
		{
			bool dead = false;
			if( frame < game->states.size()-1 )
			{

				if( !findExistance( game->states[frame+1], it->second.id ) )
					dead = true;
				
				if( dead )
					for( std::vector<Animation*>::iterator i = game->states[frame+1].animations.begin(); i != game->states[frame+1].animations.end(); i++ )
					{
						if( (*i)->type == SPLIT )
						{
							if( it->second.id == ((Split*)(*i))->robot )
								dead = false;
						}
					}

				drawSingleBot( game,&(it->second), frame, unitSize, falloff, dead );
			}
		}

	}
}


//todo: naming is bad, game frames and frame bots are too similar
void Gameboard::drawFrames( Game *game, float falloff __attribute__ ((unused)) )
{

	int frame = getAttr(frameNumber);
	int unitSize = getAttr( unitSize );

	for(
		std::map<int,Frame>::iterator it = game->states[frame].frames.begin();
		it != game->states[frame].frames.end();
		it++
		)
	{
		drawSingleFrame(game,&(it->second),frame,unitSize);

	}
}


void Gameboard::drawSingleFrame( Game *game, Frame * botFrame, int frame, int unitSize )
{
	int x0, y0;
	x0 = botFrame->x*unitSize;
	y0 = botFrame->y*unitSize;

	//is it selected?
	bool selected = false;
	if ( selectedIDs.find( botFrame->id ) != selectedIDs.end() )
	{

		selected = true;
	}

	int sprite = T_REDBOT_FRAME;

	if( botFrame->owner == 1 )
		sprite = T_BLUBOT_FRAME;

	drawSprite( x0,y0,unitSize*botFrame->size,unitSize*botFrame->size, sprite, selected, botFrame->owner );
	drawHealth( x0,y0, unitSize*botFrame->size, unitSize*botFrame->size, botFrame->maxHealth, botFrame->health, botFrame->owner );

}


//Warning this has been hacked from the drawbots function
void Gameboard::drawWalls( Game *game, float falloff __attribute__ ((unused)) )
{

	int frame = getAttr( frameNumber );
	int unitSize = getAttr( unitSize );

	for(
		std::map<int,Wall>::iterator it = game->states[frame].walls.begin();
		it != game->states[frame].walls.end();
		it++
		)
	{

		drawSingleWall( game,&(it->second),frame,unitSize);

	}

}


void Gameboard::drawSingleWall( Game *game, Wall * wall, int frame, int unitSize )
{
	int x0, y0;
	x0 = wall->x*unitSize;
	y0 = wall->y*unitSize;

	//is it selected?
	bool selected = false;
	if ( selectedIDs.find( wall->id ) != selectedIDs.end() )
	{

		selected = true;
	}

	int sprite = T_WALL100;

	if (wall->health <= 0.25 * wall->maxHealth )
	{
		sprite = T_WALL25;
	}
	else if (wall->health < 0.50 * wall->maxHealth)
	{
		sprite = T_WALL50;
	}
	else if (wall->health < 0.75 * wall->maxHealth)
	{
		sprite = T_WALL75;
	}

	drawSprite( x0,y0,unitSize*wall->size,unitSize*wall->size, sprite, selected, 2 );
}
