#include "Drawer.h"
#include "DxLib.h"
#include "Framework.h"
#include "Map.h"
#include "Chip.h"
#include "UI.h"
#include "Result.h"

const int BG_IMG_WIDTH = 484;
const int BG_IMG_HEIGHT = 785;
const int SEEWEED_WIDTH = 30;
const int SEEWEED_HEIGHT = 120;
const int CHIP_IMG_SIZE = 60;
const int NUMBER_SIZE = 40;

const int ANI_FPS = 30;

DrawerPtr Drawer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Drawer >( fw->getTask( Drawer::getTag( ) ) );
}

Drawer::Drawer( ) {
	_num_img = LoadGraph( "Resources/Number.png" );
	_chip_img = LoadGraph( "Resources/Chip.png" );
	_background_img = LoadGraph( "Resources/Background.png" );
	_seeweed_img = LoadGraph( "Resources/seeweed.png" );

	_chip = Chip::getTask( );
	_map = Map::getTask( );
	_result = Result::getTask( );

	_ani_timer = 0;
}

Drawer::~Drawer( ) {
}

void Drawer::update( ) {
	drawBackground( );
	drawMap( );
	drawUI( );
	drawResult( );
}

void Drawer::drawMap( ) {
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		drawChip( i, -3 );
	}
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		if ( _chip->getChip( i ).status != STATUS::STATUS_NONE ) {
			drawChip( i, 3 );
		}
	}
}

void Drawer::drawChip( int idx, int size ) {
	TYPE type = _chip->getChip( idx ).type;
	int x = ( idx % Map::MAP_X_NUM ) * _map->getChipSize( );
	int y = ( idx / Map::MAP_X_NUM ) * _map->getChipSize( ) + _map->getChipSize( ) * 2;//後マジックnumber消す。
	int r = size;
	DrawRectExtendGraph( x - size,                        y - size, 
						 x + _map->getChipSize( ) + size, y + _map->getChipSize( ) + size, 
						 getChipIMG( type ),              0, 
						 CHIP_IMG_SIZE,                   CHIP_IMG_SIZE, 
						 _chip_img,                       TRUE );
}

int Drawer::getChipIMG( TYPE type ) {//後、STL::mapで変える。
	FrameworkPtr fw = Framework::getInstance( );
	switch ( type ) {
	case TYPE::TYPE_A:
		return 1 * fw->getWindowWidth( ) / TYPE::TYPE_MAX;
		break;
	case TYPE::TYPE_B:
		return 2 * fw->getWindowWidth( ) / TYPE::TYPE_MAX;
		break;
	case TYPE::TYPE_C:
		return 3 * fw->getWindowWidth( ) / TYPE::TYPE_MAX;
		break;
	case TYPE::TYPE_D:
		return 4 * fw->getWindowWidth( ) / TYPE::TYPE_MAX;
		break;
	case TYPE::TYPE_E:
		return 5 * fw->getWindowWidth( ) / TYPE::TYPE_MAX;
		break;
	default:
		return 0xffffff;
		break;
	}
}

void Drawer::drawUI( ) {
	UIPtr ui = UI::getTask( );
	drawNum( 18, 25, ui->canChangeNum( ) );
}

void Drawer::drawNum( int x, int y, int num ) { //後、10以上でも対応するように。<math.h>
	DrawRectGraph( x, y, num * NUMBER_SIZE, 0, NUMBER_SIZE, NUMBER_SIZE, _num_img, TRUE, FALSE );
}

void Drawer::drawBackground( ) {
	_ani_timer++;
	int ani = ( _ani_timer / ANI_FPS ) % 5;
	FrameworkPtr fw = Framework::getInstance( );
	DrawRectExtendGraph( 0,                     0, 
						 fw->getWindowWidth( ), fw->getWindowHeight( ), 
						 0,						0, 
						 BG_IMG_WIDTH,			BG_IMG_HEIGHT, 
						 _background_img,		TRUE );

	//plz magic number delete
	DrawRectExtendGraph( 10,                  fw->getWindowHeight( ) - SEEWEED_HEIGHT, 
						 SEEWEED_WIDTH + 10,  fw->getWindowHeight( ), 
						 ani * SEEWEED_WIDTH, 0, 
						 SEEWEED_WIDTH,       SEEWEED_HEIGHT, 
						 _seeweed_img,        TRUE );
	DrawRectExtendGraph( 50,                  fw->getWindowHeight( ) - SEEWEED_HEIGHT, 
						 SEEWEED_WIDTH + 50,  fw->getWindowHeight( ), 
						 ani * SEEWEED_WIDTH, SEEWEED_HEIGHT,
						 SEEWEED_WIDTH,       SEEWEED_HEIGHT, 
						 _seeweed_img,        TRUE );
	DrawRectExtendGraph( 90,                  fw->getWindowHeight( ) - SEEWEED_HEIGHT, 
						 SEEWEED_WIDTH + 90,  fw->getWindowHeight( ), 
						 ani * SEEWEED_WIDTH, SEEWEED_HEIGHT * 2, 
						 SEEWEED_WIDTH,       SEEWEED_HEIGHT, 
						 _seeweed_img,        TRUE );
}

void Drawer::drawResult( ) {
	if ( _result->isFail( ) ) {
		DrawString( 0, 0, "FAIL", 0xff0000 );
	}
}