#include "drawGLFont.h"

#include <iostream>
#include <sstream>
using namespace std;

DrawGLFont::DrawGLFont()
{

	// Do Nothing.... Oh What fun...
	alignment = align_left;
}


Color DrawGLFont::retrieveColor( int id )
{
	if( id >= colors.size() )
		return Color( 0, 0, 0 );
	return colors[id];
}

void DrawGLFont::resetColors()
{
	colors.clear();
}

void DrawGLFont::setAlignment( int align )
{
	alignment=align;
}

void DrawGLFont::addColor( float r, float g, float b )
{
	colors.push_back( Color( r, g, b ) );
}

bool DrawGLFont::loadNewFont(
int fontTextureId,
string fontWidthsFile
)
{
	textureId = fontTextureId;

	ifstream file( fontWidthsFile.c_str() );
	if( !file.is_open() )
		return false;

	for( int i = 0; i < 256; i++ )
	{
		char temp;
		file.read( &temp, sizeof(char) );
		widths[i] = temp;
		file.read( &temp, sizeof(char) );
	}

	kerning = 1;
	bold = false;

	return true;
}

void DrawGLFont::setColor( int &i, string message )
{
	i++;
	i++;
	stringstream ss;
	while( message[i] != ')' )
	{
		ss << message[i];
		i++;
	}
	
	int k = atoi( ss.str().c_str() );
	Color color = retrieveColor( k );
	glColor3f( color.r, color.g, color.b );

}

void DrawGLFont::drawAlignedLeft( string message, int offset = 0 )
{
	int index = 0;
	for( int i = 0; (unsigned)i < message.size(); i++ )
	{

		unsigned char c = message[i];

		if( colors.size() && colors[index].index+offset == i )
		{
			glColor3f( colors[index].r, colors[index].g, colors[index].b );
			index++;
		}

		c = c-32 + (bold ? 128 : 0);

		// Draw Current Character
		drawCharacter( c );
		// Move Cursor over by character width plus some
		glTranslatef( widths[c]+kerning, 0, 0 );
	}

}

void DrawGLFont::drawAlignedCenter( string message )
{
	int mid = message.size()/2;
	glPushMatrix();

	string left = message.substr( 0, mid );
	drawAlignedRight( left, -mid );
	glPopMatrix();
	string right = message.substr( mid, mid+1 );
	drawAlignedLeft( right, mid );
	

}

void DrawGLFont::drawAlignedRight( string message, int offset = 0 )
{
	int cIndex = colors.size()-1;
	for( int i = message.size()-1; i >= 0; i-- )
		{

			unsigned char c = message[i];

			if( (cIndex+1) && colors[cIndex].index+offset > i )
			{
				
				glColor3f( colors[cIndex].r, colors[cIndex].g, colors[cIndex].b );
				cIndex--;
			}

			c = c-32 + (bold ? 128 : 0);

			glTranslatef( -widths[c]-kerning, 0, 0 );
			// Draw Current Character
			drawCharacter( c );
			// Move Cursor over by character width plus some
		}
}

void DrawGLFont::drawString( string message )
{
	// We don't want to mess with the original matrix
	glPushMatrix();


	string massage = "";
	int index = 0;
	int colorindex = 0;

	for( int i = 0; i < message.size(); i++ )
	{
		if( message[i] == '$' )
		{
			i++;
			colors[colorindex++].index = index;
		}
		massage += message[i];
		index++;
	}
	


	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, textureId );
	Color color(0,0,0);
	if( colors.size() > 0 )
	{
		color = retrieveColor( 0 );
		glColor3f( color.r, color.g, color.b );
	}

	switch( alignment )
	{
		case align_right:
			drawAlignedRight( massage );
			break;
		case align_center:
			drawAlignedCenter( massage );
			break;
		default:
			drawAlignedLeft( massage );
	}
	



	glPopMatrix();

}


void DrawGLFont::drawCharacter( unsigned char c )
{
	float off = (float)-1/16;

	int tmp = (int)c;
	float x = (float)((int)tmp%16)/16;
	float y = 1-(float)((int)tmp/16)/16;

	glBegin( GL_QUADS );

	glTexCoord2f(x, y+off);
	glVertex3f( 0, 32, 0 );
	glTexCoord2f(x-off,y+off);
	glVertex3f( 32, 32, 0 );
	glTexCoord2f( x-off,y);
	glVertex3f( 32, 0, 0 );
	glTexCoord2f( x, y );
	glVertex3f( 0, 0, 0 );

	glEnd();

}
