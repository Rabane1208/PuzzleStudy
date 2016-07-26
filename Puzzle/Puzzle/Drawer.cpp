#include "Drawer.h"
#include "DxLib.h"
#include "Framework.h"
#include "Map.h"
#include "Chip.h"

DrawerPtr Drawer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Drawer >( fw->getTask( Drawer::getTag( ) ) );
}

Drawer::Drawer( ) {
	_num_img = LoadGraph( "Resources/Number.png" );
	_chip = Chip::getTask( );
	_map = Map::getTask( );
}

Drawer::~Drawer( ) {
}

void Drawer::update( ) {
	drawMap( );
	drawNum( 0, 0, 1 );
}

void Drawer::drawMap( ) {
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		drawChip( i, _map->getChipSize( ) / 2 );
	}
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		if ( _chip->getChip( i ).status != STATUS::STATUS_NONE ) {
			drawChip( i, _map->getChipSize( ) * 6 / 10 );
		}
	}
}

void Drawer::drawChip( int idx, int size ) {
	TYPE type = _chip->getChip( idx ).type;
	int x = ( idx % Map::MAP_X_NUM ) * _map->getChipSize( ) + _map->getChipSize( ) / 2 + 1;
	int y = ( idx / Map::MAP_X_NUM ) * _map->getChipSize( ) + _map->getChipSize( ) * 5 / 2;
	int r = size;
	DrawCircle( x, y, r, getChipResource( type ), TRUE );
}

int Drawer::getChipResource( TYPE type ) {//å„ÅASTL::mapÇ≈ïœÇ¶ÇÈÅB
	switch ( type ) {
	case TYPE::TYPE_A:
		return 0xff0000;
		break;
	case TYPE::TYPE_B:
		return 0x00ff00;
		break;
	case TYPE::TYPE_C:
		return 0x0000ff;
		break;
	case TYPE::TYPE_D:
		return 0xffff00;
		break;
	case TYPE::TYPE_E:
		return 0x00ffff;
		break;
	case TYPE::TYPE_F:
		return 0xff00ff;
		break;
	default:
		return 0xffffff;
		break;
	}
}

void Drawer::drawUI( ) {

}
void Drawer::drawNum( int x, int y, int num ) {
	const int NUMBER_SIZE = 40;
	DrawRectGraph( x, y, num * NUMBER_SIZE, 0, NUMBER_SIZE, NUMBER_SIZE, _num_img, TRUE, FALSE );
}
