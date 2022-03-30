#include <allegro.h>

int sair = 0;
void sair_allegro();

int main()
{
	allegro_init();
	install_keyboard();
	set_color_depth(32);
	set_close_button_callback(sair_allegro);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
	set_window_title("Jogo de Plataforma");
	
	while(!sair){
		
		
	}
	return 0;
}
END_OF_MAIN()

void sair_allegro()
{
	sair = 1;
}
END_OF_FUNCTION(sair_allegro);
