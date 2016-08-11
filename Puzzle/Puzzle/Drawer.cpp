#include "Drawer.h"
#include "DxLib.h"
#include "Framework.h"
#include "Map.h"
#include "Chip.h"
#include "UI.h"

DrawerPtr Drawer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Drawer >( fw->getTask( Drawer::getTag( ) ) );
}

Drawer::Drawer( ) {
	_num_img = LoadGraph( "Resources/Number.png" );
	_chip_img = LoadGraph( "Resources/Chip.png" );
	_chip = Chip::getTask( );
	_map = Map::getTask( );
}

Drawer::~Drawer( ) {
}

void Drawer::update( ) {
	drawMap( );
	drawUI( );
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
	DrawRectExtendGraph( x - size, y - size, x + _map->getChipSize( ) + size, y + _map->getChipSize( ) + size, getChipResource( type ), 0, 60, 60, _chip_img, TRUE );
}

int Drawer::getChipResource( TYPE type ) {//後、STL::mapで変える。
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
	drawNum( 0, 0, ui->canChangeNum( ) );
}

void Drawer::drawNum( int x, int y, int num ) { //後、10以上でも対応するように。<math.h>
	const int NUMBER_SIZE = 40;
	DrawRectGraph( x, y, num * NUMBER_SIZE, 0, NUMBER_SIZE, NUMBER_SIZE, _num_img, TRUE, FALSE );
}
