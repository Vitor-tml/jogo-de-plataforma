#include <allegro.h>

// Definição de constantes
#define width 780
#define height 600
#define gravidade 4
#define vup 15							// Velocidade de subida
#define out -500
// Definição de Estruturas
typedef struct {
	int x, y; 	// Coordenada na janela
	int wx, wy;	// Coordenada na imagem
	int w, h;	// Tamanho do sprite
} SPRITE;

// Variáveis globais
SPRITE chao = {0, 0, 0, 0, 60, 60};		// Cenário
SPRITE player = {0, 0, 0, 0, 68, 90};	// Player
SPRITE bloco[10][14];					// Matriz do cenário
int sair = 0;							// Fechar programa
int nTile = 0, direcao = 0;				// Animação
int vly = 0, caindo = 1;				// Física do game
int pulando = 0;						// Flag do pulo
int pLimit = 0;							// Limite do pulo
char mp[13][10];
// Declara BITMAPs do programa
BITMAP *buffer, *boneco, *plataforma;

// Declaração de Funções
void sair_allegro();
void control();
void mapa();
int hitbox(SPRITE a, SPRITE b);
void blocos();

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
	
	// Carrega elementos visuais do jogo
	buffer = create_bitmap(width, height);
	boneco = load_bitmap("source/steve.bmp", NULL);
	plataforma = load_bitmap("source/chao.bmp", NULL);

	// Variávei locais
	int i, j;	// Iteração de loops
	
	// Alinhamento da matriz (cenário)
	for(i =  0; i < 10; i ++)
		for(j = 0; j < 13; j ++)
		{
			bloco[i][j].y = i * 60;
			bloco[i][j].x = j * 60;
			bloco[i][j].w = 60;
			bloco[i][j].h = 60;
			bloco[i][j].wy = 0;
			bloco[i][j].wx = 0;
		}
	mapa();
	// Mantem programa aberto
	while(!sair)
	{
		control();
		blocos();
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
	if(key[KEY_SPACE] && !pulando && vly)
	{
		pLimit = player.y;
		pulando = 1;
	}

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
	
	if(pulando && player.y > pLimit - 30)
	{
		player.y += vly;
		vly = -vup;
		 caindo = 1;
	}else
		if(caindo)
		{
			pulando = 0;
			vly += gravidade;
			player.y += vly;
		}else
		{
			pulando = 0;
			vly = 0;
		}
	caindo = 1;
}

// Função de Colisão
int hitbox(SPRITE a, SPRITE b)
{
	if((a.x + a.w > b.x) && (a.x < b.x + b.w) && (a.y + a.h > b.y) && (a.y < b.y + b.h))
		return 1;
	else 
		return 0;
}

// Funcão que cria o mapa
void mapa()
{
	int i, j;
	char mapa[13][10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 14 x 10
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
						  1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
						  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
	for(i =  0; i < 10; i ++)
		for(j = 0; j < 13; j ++)
		{
			if(mapa[i][j])
			{
				bloco[i][j].wx = (mapa[i][j] - 1) * bloco[i][j].w;
			}
			else
			bloco[i][j].x = out;
			mp[i][j] = mapa[i][j];
		}
}
// Funcão do cenário
void blocos()
{
	int i, j;
	for(i =  0; i < 10; i ++)
			for(j = 0; j < 13; j ++)
			{
				draw_sprite(buffer, plataforma, bloco[i][j].x, bloco[i][j].y);
				if(hitbox(player, bloco[i][j]))
				{
					player.y = bloco[i][j].y - player.h;
					caindo = 0;
					pulando = 0;
				}
			}
}

// Função chamada quando o X da janela é clicado
void sair_allegro()
{
	sair = 1;
}
END_OF_FUNCTION(sair_allegro);
