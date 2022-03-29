#include <allegro.h>
#define pulom 120

int main()
{
	//Iicialização
	allegro_init();
	install_timer();
	install_keyboard();
	set_color_depth(32);
	//instal_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	set_window_title("Janela");
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
	
	//Variáveis
	int x = 100, y = 100, hpulo;
	BITMAP* buffer = create_bitmap(800, 600);
	BITMAP* imagem = load_bitmap("scott.bmp", NULL);
	BITMAP* chao = load_bitmap("chao.bmp", NULL);
	
	while(!key[KEY_ESC])
	{
		draw_sprite(buffer, chao, 0, 500);
		hpulo = (500 - 70) - y;
		if(key[KEY_RIGHT] && x < (800 - 50))
			x += 1;
		if(key[KEY_LEFT] && x > 0)
			x -= 1;
		if(key[KEY_UP] && y > 0)
			y -= 1;
		if(key[KEY_DOWN] && y < (500 - 70))
			y += 1;
		if(y < (500 - 70) && (!key[KEY_UP] || (hpulo > pulom)))	
		{
			y += 1;
		}
		draw_sprite(buffer, imagem, x, y);
		draw_sprite(screen, buffer, 0, 0);
		//rest(1);
		clear(buffer);
	}
	destroy_bitmap(buffer);
	destroy_bitmap(imagem);
	return 0;
}
END_OF_MAIN();
