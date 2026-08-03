#include "hud.h"
#include "entity.h"

//void InventoryInit(Inventory* inv){}
void HudDraw(int x, int y) {
	int hp_perc = (int)gPlayer->health / 10;// g_player->data->maxHealth;
	ImageDrawText(x, y, TEX_GUI, "hp=");
	for (int i = 0; i < hp_perc; i++){
		ImageDrawText(x+(i*8)+24, y, TEX_GUI, "|");
	}
}

