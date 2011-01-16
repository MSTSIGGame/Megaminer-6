#include "visettings.h"

visettings *visettings::inst = NULL;


visettings::visettings()
{
	// Every 150 ms
	defaultSpeed = 150;
	playSpeed = defaultSpeed;
	minSpeed = 10;
	frameNumber = 0;

	dragging = false;

	unitSize = 32;
	currentMode=defaultMode=0;

	team1Talk = true;
	team2Talk = true;
	persistantTalking = false;

	doubleClickTime = 275;

	gamelogName = "";

	boardOffsetY = 75;
}


visettings::~visettings()
{
	if( inst )
		delete inst;
	inst = 0;
}


bool visettings::loadFromFile(string & errString)
{
	Config configFile( "VISCONFIG" );

	errString = "";
	string outString;
	bool errFlag;
	bool returnFlag = false;

	setAttr( defaultSpeed, configFile.pInt( "DefaultSpeed", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( playSpeed, configFile.pInt( "DefaultSpeed", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( unitSize, configFile.pInt( "UnitSize", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;

	// File Name Attributes

	setAttr( defBGFileName, configFile.pString( "defBGFileName", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( wall100FileName, configFile.pString( "wall100FileName", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( wall75FileName, configFile.pString( "wall75FileName", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( wall50FileName, configFile.pString( "wall50FileName", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( wall25FileName, configFile.pString( "wall25FileName", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;

	setAttr( gridFileName, configFile.pString( "gridFileName", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;

	// Bot Files
	// Red Bots
	setAttr( redActionFile, configFile.pString("RedActionFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( redBuilderFile, configFile.pString("RedBuilderFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( redCannonFile, configFile.pString("RedCannonFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( redDamageFile, configFile.pString("RedDamageFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( redEngineFile, configFile.pString("RedEngineFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( redForceFile, configFile.pString("RedForceFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( redFrameFile, configFile.pString("RedFrameFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( redAttackFile, configFile.pString("RedAttackFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( redBuildAnimFile, configFile.pString("RedBuildAnimFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( redJointFile, configFile.pString("RedJointFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;

	// Blue Bots
	setAttr( bluActionFile, configFile.pString("BluActionFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( bluBuilderFile, configFile.pString("BluBuilderFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( bluCannonFile, configFile.pString("BluCannonFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( bluDamageFile, configFile.pString("BluDamageFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( bluEngineFile, configFile.pString("BluEngineFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( bluForceFile, configFile.pString("BluForceFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( bluFrameFile, configFile.pString("BluFrameFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( bluAttackFile, configFile.pString("BluAttackFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( bluBuildAnimFile, configFile.pString("BluBuildAnimFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( bluJointFile, configFile.pString("BluJointFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;

	setAttr( explodeFileName, configFile.pString( "ExplodeFile", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;

	//For Board Drawing, these are the maximums
	setAttr( boardHeightPx, configFile.pInt( "BoardHeightPx", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( boardWidthPx, configFile.pInt( "BoardWidthPx", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;

	setAttr( defaultMode, configFile.pInt( "PauseOnLoad", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	currentMode=defaultMode;

	setAttr( arenaMode, configFile.pInt( "ArenaMode", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( winnerScreenTime, configFile.pInt( "WinnerScreenTime", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;

	setAttr( defaultFont, configFile.pString( "defaultFont", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( defaultFontWidths, configFile.pString( "defaultFontWidths", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;

	setAttr( doubleClickTime, configFile.pInt( "doubleClickTime", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;

	setAttr( MapGrid, configFile.pBool( "MapGrid", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;

	setAttr( initTime, configFile.pInt( "InitializationTime", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;
	setAttr( showInitScreen, configFile.pBool( "ShowInitScreen", errFlag, outString ) );
	errString += outString; returnFlag |= errFlag;

	return !returnFlag;

	//setAttr( filename, configFile.pString( "filenameString", errFlag, errString ) );
	// Eh.... to retrieve a particular type of input it's:
	// configFile.pString,pBool,pDouble,or pInt
	//
	// if the attribute you are looking for isnt there
	// errFlag is set to true and errString is an error message
	// no more messy exits when the attribute doesnt exist
}
