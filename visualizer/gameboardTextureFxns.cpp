#include "gameboardWidget.h"

bool Gameboard::loadTexture(QString filename, eTextures texID, QString & errString)
{
	if ( !textures[texID].loadImage( filename ) )
	{
		if (QString("") != errString)
		{
			errString += ", ";
		}

		errString += filename;
		return false;
	}
	return true;
}



bool Gameboard::loadAllTextures( QString & message )
{

	bool flag = false;
	QString errString;

	if ( !textures[T_FONT].loadImage( getAttr( defaultFont ).c_str() ) )
	{
		errString += getAttr( defaultFont ).c_str();
		flag = true;
	}
	else
	{
		drawFont = new DrawGLFont( textures[T_FONT].getTexture(), getAttr( defaultFontWidths ) );
	}

	//red bots:

	if ( !loadTexture( getAttr( redActionFile ).c_str(), T_REDBOT_ACTION, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( redBuilderFile ).c_str(), T_REDBOT_BUILDER, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( redCannonFile ).c_str(), T_REDBOT_CANNON, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( redDamageFile ).c_str(), T_REDBOT_DAMAGE, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( redEngineFile ).c_str(), T_REDBOT_ENGINE, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( redForceFile ).c_str(), T_REDBOT_FORCE, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( redFrameFile ).c_str(), T_REDBOT_FRAME, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( redAttackFile ).c_str(), T_REDPART_ATTACK, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( redBuildAnimFile ).c_str(), T_REDPART_BUILD, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( redJointFile ).c_str(), T_REDBOT_JOINT, errString ) )
		flag = true;

	//blue bots:
	if ( !loadTexture( getAttr( bluActionFile ).c_str(), T_BLUBOT_ACTION, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( bluBuilderFile ).c_str(), T_BLUBOT_BUILDER, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( bluCannonFile ).c_str(), T_BLUBOT_CANNON, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( bluDamageFile ).c_str(), T_BLUBOT_DAMAGE, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( bluEngineFile ).c_str(), T_BLUBOT_ENGINE, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( bluForceFile ).c_str(), T_BLUBOT_FORCE, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( bluFrameFile ).c_str(), T_BLUBOT_FRAME, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( bluAttackFile ).c_str(), T_BLUPART_ATTACK, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( bluBuildAnimFile ).c_str(), T_BLUPART_BUILD, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( bluJointFile ).c_str(), T_BLUBOT_JOINT, errString ) )
		flag = true;

	//Other Textures

	if ( !loadTexture( getAttr( defBGFileName ).c_str(), T_DEFAULTBG, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( gridFileName ).c_str(), T_GRID, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( wall100FileName ).c_str(), T_WALL100, errString ) )
		flag = true;
	if ( !loadTexture( getAttr( wall75FileName ).c_str(), T_WALL75, errString ) )
		flag = true;
	if ( !loadTexture( getAttr( wall50FileName ).c_str(), T_WALL50, errString ) )
		flag = true;
	if ( !loadTexture( getAttr( wall25FileName ).c_str(), T_WALL25, errString ) )
		flag = true;
	if( !loadTexture( getAttr( explodeFileName ).c_str(), T_EXPLODE, errString ) )
		flag = true;

	message = errString;

	return !flag;

}
