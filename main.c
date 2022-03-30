#include <allegro.h>

// Definição de constantes
#define width 800
#define height 600

// Definição de Estruturas
typedef struct {
	int x, y; 	// Coordenada na janela
	int wx, wy;	// Coordenada na imagem
	int w, h;	// Tamanho do sprite
} SPRITE;

// Variáveis globais
int sair = 0;
SPRITE player = { 0, 0, 0, 0, 68, 90};
int nTile = 0, direcao = 0;

// Declaração de Funções
void sair_allegro();
void control();

// Inicio do Programa
int main()
{
	// Inicializa
	allegro_init();
	install_keyboard();
	set_color_depth(32);
	set_close_button_callback(sair_allegro);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0);
	set_window_title("Jogo de Plataforma");
	
	// Cria elementos visuais do jogo
	BITMAP* buffer = create_bitmap(width, height);
	BITMAP* boneco = load_bitmap("source/steve.bmp", NULL);

	// Variávei locais
	int x = 0, y = 0;
	
	// Mantem programa aberto
	while(!sair)
	{
		control();
		masked_blit(boneco, buffer, player.wx + nTile * player.w, player.wy + direcao * player.h , player.x, player.y, player.w, player.h);
		draw_sprite(screen, buffer, 0, 0);
		rest(50);
		clear(buffer);
	}

	// Encerra arquivos carregados no programa
	destroy_bitmap(buffer);
	destroy_bitmap(boneco);
	return 0;
}
END_OF_MAIN()

// Função dos controles do jogo
void control()
{
	if(key[KEY_LEFT])
	{
		player.x -= 20;
		direcao = 1;
		nTile--;
	}

	if(key[KEY_RIGHT])
	{
		player.x += 20;
		direcao = 0;
		nTile++;
	}

	if(key[KEY_UP])
	{
		player.y -= 20;
	}

	if(key[KEY_DOWN])
	{
		player.y += 20;	
	}

	if((!key[KEY_LEFT] && !key[KEY_RIGHT]))
	{
		nTile = 3;
	}
	
	if(nTile > 2 && nTile != 3)
		nTile = 0;
	if(nTile < 0)
		nTile = 3;
}

// Função chamada quando o X da janela é clicado
void sair_allegro()
{
	sair = 1;
}
END_OF_FUNCTION(sair_allegro);
