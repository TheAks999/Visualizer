#include "gameboardWidget.h"

/** @todo: change to resource manager
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



	//Other Textures
	if ( !loadTexture( getAttr( defBGFileName ).c_str(), T_DEFAULTBG, errString ) )
		flag = true;
	if ( !loadTexture( getAttr( gridFileName ).c_str(), T_GRID, errString ) )
		flag = true;
	if( !loadTexture( getAttr( explodeFileName ).c_str(), T_EXPLODE, errString ) )
		flag = true;

	if( !loadTexture( getAttr( whitePawnFile ).c_str(), T_WHITE_PAWN, errString ) )
		flag = true;
	if( !loadTexture( getAttr( whiteRookFile ).c_str(), T_WHITE_ROOK, errString ) )
		flag = true;
	if( !loadTexture( getAttr( whiteBishopFile ).c_str(), T_WHITE_BISHOP, errString ) )
		flag = true;
	if( !loadTexture( getAttr( whiteKnightFile ).c_str(), T_WHITE_KNIGHT, errString ) )
		flag = true;
	if( !loadTexture( getAttr( whiteQueenFile ).c_str(), T_WHITE_QUEEN, errString ) )
		flag = true;
	if( !loadTexture( getAttr( whiteKingFile ).c_str(), T_WHITE_KING, errString ) )
		flag = true;

	if( !loadTexture( getAttr( blackPawnFile ).c_str(), T_BLACK_PAWN, errString ) )
		flag = true;
	if( !loadTexture( getAttr( blackRookFile ).c_str(), T_BLACK_ROOK, errString ) )
		flag = true;
	if( !loadTexture( getAttr( blackBishopFile ).c_str(), T_BLACK_BISHOP, errString ) )
		flag = true;
	if( !loadTexture( getAttr( blackKnightFile ).c_str(), T_BLACK_KNIGHT, errString ) )
		flag = true;
	if( !loadTexture( getAttr( blackQueenFile ).c_str(), T_BLACK_QUEEN, errString ) )
		flag = true;
	if( !loadTexture( getAttr( blackKingFile ).c_str(), T_BLACK_KING, errString ) )
		flag = true;


	message = errString;

	return !flag;

}
*/
