#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <time.h> //Para o timer
#include <string.h>
#include <math.h> //Para o usar o abs() na função tiro()

#define TITULO_JANELA "Castelo de Wolfenstein"
//---------------------------------------------------------------------
//Geral
#define TELA_ALTURA 300
#define TELA_LARGURA 800
#define CORDEFUNDO BLACK
#define CORDOTEXTOPRINCIPAL WHITE
#define CORDOTEXTOSECUNDARIO WHITE
#define CORDACAIXADEMENSAGENS GOLD
#define VELOCIDADEDOJOGADOR 1
#define VELOCIDADEDOINIMIGO 0.5
#define INTERVALODETEMPO 1 //Intervalo de tempo para o movimento inimigo
#define DISTANCIAHORIZONTALDASVIDAS 35

//Jogador
#define JOGADOR_POSICAO_X 380
#define JOGADOR_POSICAO_Y 130

//Inimigos
#define MAX_INIMIGOS 5 //Máximo de inimigos
#define INIMIGO_1_X 700
#define INIMIGO_1_Y 150
#define INIMIGO_2_X 100
#define INIMIGO_2_Y 150
#define INIMIGO_3_X 200
#define INIMIGO_3_Y 225
#define INIMIGO_4_X 600
#define INIMIGO_4_Y 225
#define INIMIGO_5_X 700
#define INIMIGO_5_Y 225

//Baú
#define BAU_QUANTIDADE 2            //Quantidade de baús
#define BAU_PONTUACAO_1 50          //Pontuação de aparecimento do 1o baú
#define BAU_PONTUACAO_2 120         //Pontuação de aparecimento do 2o baú
#define BAU_POSICAO_X_1 150         //Posição horizontal do 1o baú
#define BAU_POSICAO_Y_1 200         //Posição vertical do 1o baú
#define BAU_POSICAO_X_2 500         //Posição horizontal do 2o baú
#define BAU_POSICAO_Y_2 200         //Posição vertical do 2o baú
#define BAU_VIDAS_1 1               //Vidas no 1o baú
#define BAU_VIDAS_2 1               //Vidas no 2o baú
#define BAU_MUNICAO_1 2             //Munição no 1o baú
#define BAU_MUNICAO_2 2             //Munição no 2o baú
#define BAU_ALTURA 40               //Altura do baú
#define BAU_LARGURA 40              //Largura do baú

//Texto principal
#define TEXTO_PRINCIPAL_TAMANHO 22
#define TEXTO_PRINCIPAL_POSICAO_X 20
#define TEXTO_PRINCIPAL_POSICAO_Y 10
#define TEXTO_PRINCIPAL_COR GOLD

//Texto secundário
#define TEXTO_SECUNDARIO_TAMANHO 18
#define TEXTO_SECUNDARIO_POSICAO_X 680
#define TEXTO_SECUNDARIO_POSICAO_Y 250
#define TEXTO_SECUNDARIO_COR GOLD

//Teclas
#define TECLA_PAUSAR KEY_P
#define TECLA_CESSAR_PAUSAR KEY_O
#define TECLA_TIRO KEY_SPACE
#define TECLA_FACADA KEY_X
#define TECLA_SALVAR KEY_S

//Texturas
#define ARQUIVO_INIMIGO_0 "./assets/inimigo1.png"
#define ARQUIVO_JOGADOR_0 "./assets/testeJogador.png"
#define ARQUIVO_JOGADOR_0_0 "./assets/testeJogador0.png"
#define ARQUIVO_JOGADOR_0_1 "./assets/testeJogador1.png"
#define ARQUIVO_JOGADOR_0_2 "./assets/testeJogador2.png"
#define ARQUIVO_JOGADOR_1 "./assets/testeFacada.png"
#define ARQUIVO_JOGADOR_2_0 "./assets/tiroEsquerda.png"
#define ARQUIVO_JOGADOR_2_1 "./assets/tiroDireita.png"

#define ARQUIVO_VIDA_0 "./assets/testeVida.png"
#define ARQUIVO_VIDA_1 "./assets/testePerdeVida.png"

#define ARQUIVO_BAU_0 "./assets/bauFechado.png"
#define ARQUIVO_BAU_1 "./assets/bauAberto.png"
#define ARQUIVO_TIRO "./assets/testeProjetil.png"

#define ARQUIVO_PORTA_0 "./assets/testePortaFechada.png"
#define ARQUIVO_PORTA_1 "./assets/testePortaAberta.png"

#define ARQUIVO_FACA "./assets/Faca.png"

//Faca
#define VELOCIDADE_FACA 5
#define ALTURA_FACA 10
#define COMPRIMENTO_FACA 20

//Tiro
#define INTERVALO_TIROS 0.5 //Intervalo mínimo entre cada tiro
#define MAXIMO_CARREGADOR 6 //Tamanho do carregador
#define ALTURA_ARMA 10 //= Altura do jogador - altura do armamento em relação a seus pés

//Facada
#define TEMPO_ESPERA_FACA 3 //Tempo de espera para o arremesso de faca
/*
    Nível 1 - 1 inimigo; 2 - 2 inimigos; 3 - 3 inimigos
*/

//Tela do jogo
#define BOTAO_ESQUERDO 0

#define INTRO_TELA 0
#define MENU_TELA 1
#define NOVO_JOGO_TELA 2
#define CARREGAR_JOGO_TELA 3
#define RANKING_TELA 4
#define TUTORIAL_TELA 5
#define JOGO_TELA 6
#define INPUT_NOME_TELA 7
#define FIM_DE_JOGO_TELA 8
#define VOCE_VENCEU_TELA 9

//---------------------------------------------
 //Dimensões da tela
        const int telaAltura = TELA_ALTURA;
        const int telaLargura = TELA_LARGURA;
    //Elementos
        struct estruturaElemento{
            Vector2 posicao;
            Vector2 posicaoInicial;
            int direcao;
            float tamanho_X;
            float tamanho_Y;
            Texture2D texturaAtual;
            Texture2D textura0;
            Texture2D textura1; //Facada
            Texture2D textura2; //Atirando
            Texture2D textura3; //Morrendo
            Texture2D textura0_0; //Esquerda
            Texture2D textura0_1; //Direita
            Texture2D textura0_2; //Cima
            Texture2D textura2_0; //Atirando - esquerda
            Texture2D textura2_1; //Atirando - direita
            Rectangle retangulo;
            Rectangle retanguloFacada;
            int situacao;
        };
    //Textos
        struct estruturaTexto{
            char conteudo[50];
            int posicao_X;
            int posicao_Y;
            int tamanhoFonte;
            Color cor;
        };
    //Vida
        struct estruturaVida{
            Vector2 posicao0;
            Vector2 posicao1;
            Vector2 posicao2;
            int quantidade;
            Texture textura0;
            Texture textura1;
        };
    //Projétil - Faca ou tiro
        struct estruturaProjetil{
            bool ativo;
            bool mov;
            int direcao;
            int velocidade;
            Texture2D textura;
            Vector2 posicao;
            Rectangle retangulo;
        };
    //Objetos
        struct estruturaObjeto{
            int situacao;
            int existencia;
            Vector2 posicao;
            Texture2D texturaAtual;
            Texture2D textura0;
            Texture2D textura1;
            Rectangle retangulo;
        };

    //Variáveis, arranjos e estruturas
        //Estruturas
        struct estruturaElemento jogador; //Jogador
        struct estruturaElemento inimigo[5]; //Inimigos
        struct estruturaTexto textoPrincipal; //Texto principal
        struct estruturaTexto textoSecundario; //Texto secundário
        struct estruturaTexto caixaMensagens; //Caixa de mensagens
        struct estruturaVida vida; //Vida
        struct estruturaObjeto baus[BAU_QUANTIDADE]; //Baús
        struct estruturaProjetil tiros[MAXIMO_CARREGADOR]; //Tiros
        struct estruturaObjeto porta; //Porta
        struct estruturaProjetil faca; //Faca
        //Variaveis
        int tempoAtual = 0;
        int tempoExecucao[MAX_INIMIGOS];
        int tempoTiro = 0;
        int tempoFacada = 0;
        int tempoExecucaoFaca = 0;
        int tempoSalvar = 0;
        int pontuacao;
        //Outros
        Image imagem;
        bool colisao = false;
        bool colisaoFacada = false;
        bool pausado = false;
        int tempoUltimaAtualizacao = 0;
        int quantidadeTiros = 0;
        int nivel;
        int numeroInimigos;
        float timer2 = 0;
        int frame = 0;
        bool salvo = false;
        bool jogadorInicial = true;




//Definições gerais
    //Dimensões da tela
    const int screenWidth = 800;
    const int screenHeight = 300;

    int estadoTela = INTRO_TELA;

    //---------------------------------------------------------------------------------------
    //Variaveis Intro------------------------------------------------------------------------
    int logoPosicaoX = screenWidth/2 - 200;
    int logoPosicaoY = screenHeight/2 - 120;

    int framesIntroCont = 0;
    int letrasCont = 0;

    int bordaSuperiorComprimento = 16;
    int bordaEsquerdaAltura = 16;
    int bordaInferiorComprimento = 16;
    int bordaDireitaAltura = 16;

    int estadoIntro = 0;
    float alpha = 1.0f;
    float alpha2 = 1.0f;

    //Variaveis Menu-------------------------------------------------------------------------
    Rectangle btnNewGame = {325, 103, 150, 45};
    Rectangle btnLoadGame ={530, 103, 150, 45};
    Rectangle btnRanking = {125, 103, 150, 45};
    Rectangle btnTutotial = {530, 185, 150, 45};
    Rectangle btnQuit = {125, 185, 150, 45};
    //Variavel tutorial
    Rectangle btnVoltar = {670,247,120,40};
    //Variavel fim de jogo
    Rectangle btnMenu = {670,247,120,40};
    //---------------------------------------------------------------------------------------
    //Variaveis Mouse------------------------------------------------------------------------
    bool btnAcao = false;   // Button action should be activated
    Vector2 mousePosicao = { 0.0f, 0.0f };
    //----------------------------------------------------------------------------------------
    //FILE *arqbin

    //char nomearquivo[15]= "highscores.bin";








//Funçoes void--------------------------------------------------------------------------------

void pontuar(int numeroInimigo,Sound fxInimigoMorto){ //Função pontuar - quando mata um inimigo
    inimigo[numeroInimigo].situacao = 0;
    numeroInimigos -= 1;
    pontuacao += 10;
    //====================================================================
    //--->>> SOM !!! <<<--->>> INIMIGO MORTO <<<--->>> SOM !!! <<<--->>> I
    PlaySound(fxInimigoMorto);
    //====================================================================
    strcpy(textoPrincipal.conteudo,TextFormat("Nivel %d\nPontuacao: %d",nivel,pontuacao));
}

void carregarTextura(Texture2D *textura, char local[50],int altura,int largura){ //Carregar textura - para agilizar
    Image imagem = LoadImage(local);
    ImageResize(&imagem,largura,altura);
    *textura = LoadTextureFromImage(imagem);
}

void inicializar(){
    //Janela
    InitWindow(telaLargura,telaAltura,TITULO_JANELA);

    //Geral
    vida.quantidade = 3;
    pontuacao = 0;
    nivel = 1;
    for(int i=0; i<MAX_INIMIGOS; i++){
        tempoExecucao[i] = 0;
    }

    //Jogador
    jogador.posicaoInicial.x = JOGADOR_POSICAO_X;
    jogador.posicaoInicial.y = JOGADOR_POSICAO_Y;
    jogador.posicao = jogador.posicaoInicial; //Carrega a posição inicial do jogador
    jogador.direcao = 1; //Estabelece a direção inicial para a direita (tanto faz)
        //Ícone do jogador
            //Textura 0 - NORMAL À BAIXO
            carregarTextura(&jogador.textura0,ARQUIVO_JOGADOR_0,44,44);
            //Textura 0_0 - NORMAL À ESQUERDA
            carregarTextura(&jogador.textura0_0,ARQUIVO_JOGADOR_0_0,44,44);
            //Textura 0_1 - NORMAL À DIREITA
            carregarTextura(&jogador.textura0_1,ARQUIVO_JOGADOR_0_1,44,44);
            //Textura 0_2 - NORMAL À CIMA
            carregarTextura(&jogador.textura0_2,ARQUIVO_JOGADOR_0_2,44,44);
            //Textura 2_0 - TIRO À ESQUERDA
            carregarTextura(&jogador.textura2_0,ARQUIVO_JOGADOR_2_0,44,44);
            //Textura 2_1 - TIRO À DIREITA
            carregarTextura(&jogador.textura2_1,ARQUIVO_JOGADOR_2_1,44,44);
        //Retângulo do jogador
            jogador.retangulo.height = 40;
            jogador.retangulo.width = 40;
        //Retangulo da facada
            jogador.retanguloFacada.height = 80;
            jogador.retanguloFacada.width = 80;

    //Inimigo                        ===>>> Posições iniciais dos inimigos
    inimigo[0].posicaoInicial.x = INIMIGO_1_X;
    inimigo[0].posicaoInicial.y = INIMIGO_1_Y;
    inimigo[1].posicaoInicial.x = INIMIGO_2_X;
    inimigo[1].posicaoInicial.y = INIMIGO_2_Y;
    inimigo[2].posicaoInicial.x = INIMIGO_3_X;
    inimigo[2].posicaoInicial.y = INIMIGO_3_Y;
    inimigo[3].posicaoInicial.x = INIMIGO_4_X;
    inimigo[3].posicaoInicial.y = INIMIGO_4_Y;
    inimigo[4].posicaoInicial.x = INIMIGO_5_X;
    inimigo[4].posicaoInicial.y = INIMIGO_5_Y;

    for(int i=0; i<MAX_INIMIGOS; i++){ //Carrega a textura e as dimensões comuns a todos os inimigos
        carregarTextura(&inimigo[i].textura0,ARQUIVO_INIMIGO_0,40,40);
        inimigo[i].retangulo.height = 40;
        inimigo[i].retangulo.width = 40;
        inimigo[i].posicao = inimigo[i].posicaoInicial; //Carrega a posição inicial, mesmo que o inimigo não esteja ativo ainda
    }
    for(int i=0; i<nivel; i++){ //Ativação dos inimigos, conforme o nível
        inimigo[i].situacao = 1;
    }
    for(int i=nivel; i<MAX_INIMIGOS; i++){ //Os outros inimigos ficam inativos
        inimigo[i].situacao = 0;
    }

    //Texto principal
    if(nivel==1){
    strcpy(textoPrincipal.conteudo,TextFormat("Nivel %d\nPontuacao: %d",nivel,pontuacao));
    textoPrincipal.posicao_X = TEXTO_PRINCIPAL_POSICAO_X;
    textoPrincipal.posicao_Y = TEXTO_PRINCIPAL_POSICAO_Y;
    textoPrincipal.tamanhoFonte = TEXTO_PRINCIPAL_TAMANHO;
    textoPrincipal.cor = TEXTO_PRINCIPAL_COR;

    }
    //Texto secundário
    strcpy(textoSecundario.conteudo,TextFormat("Municao: %d/%d",MAXIMO_CARREGADOR-quantidadeTiros,MAXIMO_CARREGADOR));
    textoSecundario.posicao_X = TEXTO_SECUNDARIO_POSICAO_X;
    textoSecundario.posicao_Y = TEXTO_SECUNDARIO_POSICAO_Y;
    textoSecundario.tamanhoFonte = TEXTO_SECUNDARIO_TAMANHO;
    textoSecundario.cor = TEXTO_SECUNDARIO_COR;

    //Caixa de mensagens

    strcpy(caixaMensagens.conteudo,"");
    caixaMensagens.posicao_X = 30;
    caixaMensagens.posicao_Y = telaAltura - 30;
    caixaMensagens.tamanhoFonte = 20;
    caixaMensagens.cor = CORDACAIXADEMENSAGENS;


    //Vidas
    carregarTextura(&vida.textura0,ARQUIVO_VIDA_0,30,30);
    carregarTextura(&vida.textura1,ARQUIVO_VIDA_1,30,30);
    vida.posicao0.x = 750;
    vida.posicao0.y = 25;
    vida.posicao1.x = vida.posicao0.x - DISTANCIAHORIZONTALDASVIDAS;
    vida.posicao1.y = vida.posicao0.y;
    vida.posicao2.x = vida.posicao0.x - 2*DISTANCIAHORIZONTALDASVIDAS;
    vida.posicao2.y = vida.posicao0.y;

    //Projéteis
        //Faca
        faca.ativo = false;
        carregarTextura(&faca.textura,ARQUIVO_FACA,ALTURA_FACA,COMPRIMENTO_FACA);
        faca.velocidade = VELOCIDADE_FACA;
        faca.retangulo.height = ALTURA_FACA;
        faca.retangulo.width = COMPRIMENTO_FACA;

    //Objetos
        //Porta
        porta.situacao = 0;
        porta.texturaAtual = porta.textura0;
        carregarTextura(&porta.textura0,ARQUIVO_PORTA_0,58,46);
        carregarTextura(&porta.textura1,ARQUIVO_PORTA_1,58,46);
        porta.posicao.x = 100;
        porta.posicao.y = 100;
        porta.retangulo.x = porta.posicao.x;
        porta.retangulo.y = porta.posicao.y;
        porta.retangulo.height = 58;
        porta.retangulo.width = 46;
        //Baús
        baus[0].posicao.x = BAU_POSICAO_X_1;
        baus[0].posicao.y = BAU_POSICAO_Y_1;
        baus[1].posicao.x = BAU_POSICAO_X_2;
        baus[1].posicao.y = BAU_POSICAO_Y_2;
        for(int i=0; i<BAU_QUANTIDADE; i++){
            carregarTextura(&baus[i].textura0,ARQUIVO_BAU_0,BAU_ALTURA,BAU_LARGURA);
            carregarTextura(&baus[i].textura1,ARQUIVO_BAU_1,BAU_ALTURA,BAU_LARGURA);
            baus[i].situacao = 0;
            baus[i].existencia = 0;
            baus[i].retangulo.x = baus[i].posicao.x;
            baus[i].retangulo.y = baus[i].posicao.y;
            baus[i].retangulo.height = 40;
            baus[i].retangulo.width = 40;
        }
        printf("BAU: %f - %d",baus[0].retangulo.x,baus[0].retangulo.x);

    //Nível
    numeroInimigos = nivel; //Estabelece o número de inimigos, de acordo com o nível
}

void movimentoJogador(){ //Função do movimento do jogador - e mudança de textura conforme a direção
    if(jogadorInicial)jogador.texturaAtual = jogador.textura0;

    if((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && jogador.posicao.y >= 0){
            jogador.posicao.y -= VELOCIDADEDOJOGADOR;
            jogador.texturaAtual = jogador.textura0_2;
            jogadorInicial = false;
    }

    if((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && jogador.posicao.x >= 0){
            jogador.posicao.x -= VELOCIDADEDOJOGADOR;
            jogador.direcao = 0;
            jogador.texturaAtual = jogador.textura0_0;
            jogadorInicial = false;
    }

    if((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) && jogador.posicao.y <= (TELA_ALTURA - 64)){
            jogador.posicao.y += VELOCIDADEDOJOGADOR;
            jogador.texturaAtual = jogador.textura0;
            jogadorInicial = false;
    }

    if((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && jogador.posicao.x <= (TELA_LARGURA - 44)){
            jogador.posicao.x += VELOCIDADEDOJOGADOR;
            jogador.direcao = 1;
            jogador.texturaAtual = jogador.textura0_1;
            jogadorInicial = false;
    }

    jogador.retangulo.x = jogador.posicao.x;
    jogador.retangulo.y = jogador.posicao.y;
    jogador.retanguloFacada.x = jogador.posicao.x - 20;
    jogador.retanguloFacada.y = jogador.posicao.y - 20;
}

void movimentoInimigo(struct estruturaElemento* elemento, float velocidade, int i){ //Função do movimento do inimigo - e mudança de textura no movimento
    //Definição para facilitar a escrita
    float posicao_X = elemento->posicao.x, posicao_Y = elemento->posicao.y;

    //Movimento de perseguição
            if(posicao_X < jogador.posicao.x){
                posicao_X += velocidade;
            }
            if(posicao_Y < jogador.posicao.y){
                posicao_Y += velocidade;
            }
            if(posicao_X > jogador.posicao.x){
                posicao_X -= velocidade;
            }
            if(posicao_Y > jogador.posicao.y){
                posicao_Y -= velocidade;
            }

    //Atribuição do novo valor
    elemento->posicao.x = posicao_X;
    elemento->posicao.y = posicao_Y;
}

void colisoes(Sound fxJogadorMorto){ //Função colisões inimigo-jogador ===>>> Inclui também o código a ser executado no caso de morte do jogador
    for(int i=0;i<nivel;i++){
        if(inimigo[i].situacao == 1){
            colisao = CheckCollisionRecs(jogador.retangulo,inimigo[i].retangulo);
        }
    }
    if(colisao){
        vida.quantidade -= 1;
        PlaySound(fxJogadorMorto); //SOM JOGADOR MORTO
        if(vida.quantidade <= 0){
            /*strcpy(caixaMensagens.conteudo,TextFormat("Pontuacao final: %d", pontuacao));
            caixaMensagens.tamanhoFonte = TEXTO_PRINCIPAL_TAMANHO;
            caixaMensagens.cor = TEXTO_PRINCIPAL_COR;*/

            tempoUltimaAtualizacao = tempoAtual;
            estadoTela = FIM_DE_JOGO_TELA;
        }else{
            jogador.posicao = jogador.posicaoInicial;
            for(int i=0; i<nivel; i++){
                    inimigo[i].posicao = inimigo[i].posicaoInicial;
            }
        }
    }
}

void timer(){ //Função timer - padrão segundos
    tempoAtual = time(NULL);
}

void tiro(Sound fxTiro,Sound fxInimigoMorto){ //Função tiro - O tiro seguinte só é liberado após determinado intervalo de tempo
        if((tempoAtual >= tempoTiro + INTERVALO_TIROS) && (quantidadeTiros < MAXIMO_CARREGADOR)){ //Se passou o tempo de recarga e há munição, executa o tiro...
            for(int i=0; i<nivel; i++){
                if((inimigo[i].retangulo.y > (jogador.posicao.y - ALTURA_ARMA)) && ((inimigo[i].retangulo.y - inimigo[i].retangulo.height) < (jogador.posicao.y - ALTURA_ARMA))){
                    if(inimigo[i].posicao.x < jogador.posicao.x && jogador.direcao == 0 && inimigo[i].situacao == 1){
                        pontuar(i,fxInimigoMorto);
                    }
                    if(inimigo[i].posicao.x > jogador.posicao.x && jogador.direcao == 1 && inimigo[i].situacao == 1){
                        pontuar(i,fxInimigoMorto);
                    }
                }
            }
            quantidadeTiros += 1;
            tempoTiro = tempoAtual;

        if(jogador.direcao == 1){jogador.texturaAtual = jogador.textura2_1;}
        if(jogador.direcao == 0){jogador.texturaAtual = jogador.textura2_0;}

        PlaySound(fxTiro);//SOM TIRO

        }
}

void facada(Sound fxFaca){ //Função arremesso de faca
        if(tempoAtual >= tempoFacada + TEMPO_ESPERA_FACA && faca.ativo == false){ //Se tiver passado o tempo de espera para poder arremessar a faca, executa o código...
            faca.ativo = true; //Faca ativa
            faca.mov = true; //Faca em movimento
            faca.posicao.x = jogador.posicao.x; //Faca na mesma posição do jogador
            faca.posicao.y = jogador.posicao.y + 10; //Compensa a altura da faca em relação ao jogador
            faca.direcao = jogador.direcao; //Será atirada na mesma direção do jogador
            faca.retangulo.y = faca.posicao.y; //A posição do retângulo no eixo Y será constante, pois a faca é lançada horizontalmente
            tempoFacada = tempoAtual; //Timer

            //====================================================================
            //--->>> SOM !!! <<<--->>> FACA <<<--->>> SOM !!! <<<--->>> FACA <<<--
            PlaySound(fxFaca);
            //====================================================================
        }
}

void mudaNivel(){ //Mudança de nível

    //Texto principal
    strcpy(textoPrincipal.conteudo,TextFormat("Nivel %d\nPontuacao: %d",nivel,pontuacao));
    textoPrincipal.posicao_X = TEXTO_PRINCIPAL_POSICAO_X;
    textoPrincipal.posicao_Y = TEXTO_PRINCIPAL_POSICAO_Y;
    textoPrincipal.tamanhoFonte = TEXTO_PRINCIPAL_TAMANHO;
    textoPrincipal.cor = TEXTO_PRINCIPAL_COR;

    //Jogador
    jogador.posicao = jogador.posicaoInicial; //Carrega a posição inicial do jogador
    jogador.direcao = 1; //Estabelece a direção inicial para a direita (tanto faz)

    //====================================================================
    //--->>> SOM !!! <<<--->>> MUDANÇA DE NIVEL <<<--->>> SOM !!! <<<--->>
    //====================================================================

    //Inimigos
    for(int i=0; i<MAX_INIMIGOS; i++){ //Carrega a textura e as dimensões comuns a todos os inimigos
        inimigo[i].posicao = inimigo[i].posicaoInicial; //Carrega a posição inicial, mesmo que o inimigo não esteja ativo ainda
    }
    for(int i=0; i<nivel; i++){ //Ativação dos inimigos, conforme o nível
        inimigo[i].situacao = 1;
    }
    for(int i=nivel; i<MAX_INIMIGOS; i++){ //Os outros inimigos ficam inativos
        inimigo[i].situacao = 0;
    }
    numeroInimigos = nivel;

    //Porta
    porta.situacao = 0;
    porta.texturaAtual = porta.textura0;

    //Baús
    for(int i=0; i<BAU_QUANTIDADE; i++){
        if(baus[i].existencia == 1){
            baus[i].existencia = 0;
            baus[i].situacao = 1;
        }
    }
}

void salvar(){ //Salvar jogo
    printf("Salvando!");
    strcpy(caixaMensagens.conteudo,"Salvando");

    FILE *save;
    save = fopen("save.txt","w");

    fputs(TextFormat("%d\n%d\n%f\n%f\n%d\n%d\n%d\n%f\n%f\n%d\n%f\n%f\n%f\n%f\n%f\n%f\n%f\n%f\n%f\n%f\n",
                     nivel,
                     pontuacao,
                     jogador.posicao.x,
                     jogador.posicao.y,
                     jogador.direcao,
                     jogador.situacao,
                     porta.existencia,
                     porta.posicao.x,
                     porta.posicao.y,
                     porta.situacao,
                     inimigo[0].posicao.x,
                     inimigo[0].posicao.y,
                     inimigo[1].posicao.x,
                     inimigo[1].posicao.y,
                     inimigo[2].posicao.x,
                     inimigo[2].posicao.y,
                     inimigo[3].posicao.x,
                     inimigo[3].posicao.y,
                     inimigo[4].posicao.x,
                     inimigo[4].posicao.y
                     ),save);
    fclose(save);
}

void fecharJogo();

void configuracaoIntro(Sound fxIntro){
    if (estadoIntro == 0)                 // State 0: Small box blinking
    {
        framesIntroCont++;

        if (framesIntroCont == 120)
        {
            estadoIntro = 1;
            framesIntroCont = 0;      // Reset counter... will be used later...
        }
    }
    else if (estadoIntro == 1)            // State 1: Top and left bars growing
    {
        bordaSuperiorComprimento += 6;
        bordaEsquerdaAltura += 3;

        if (bordaSuperiorComprimento == 400) estadoIntro = 2;
    }
    else if (estadoIntro == 2)            // State 2: Bottom and right bars growing
    {
        PlaySound(fxIntro);
        bordaInferiorComprimento += 6;
        bordaDireitaAltura += 3;

        if (bordaInferiorComprimento == 400) estadoIntro = 3;
    }
    else if (estadoIntro == 3)            // State 3: Letters appearing (one by one)
    {
        framesIntroCont++;

        if (framesIntroCont/6)       // Every 12 frames, one more letter!
        {
            letrasCont++;
            framesIntroCont = 0;
        }

        if (letrasCont >= 72)     // When all letters have appeared, just fade out everything
        {
            alpha -= 0.02f;

            if (alpha <= 0.0f)
            {
                alpha = 0.0f;
                estadoIntro = 4;
            }
        }
    }
    else if (estadoIntro == 4)
    {
        do{
            alpha2 -= 0.01f;
        }while(alpha2 <= 0.0f);

        if (alpha2<0.01f)estadoIntro=5;

    }
}

void configuracaoMouse(){
    mousePosicao = GetMousePosition();
    btnAcao = false;
    if (IsMouseButtonReleased(BOTAO_ESQUERDO))btnAcao = true;
}

void configuracaoMenu(Sound fxButton){
    if (btnAcao && CheckCollisionPointRec(mousePosicao, btnNewGame))
    {
        PlaySound(fxButton);
        estadoTela = NOVO_JOGO_TELA;
        //inicia novo jogo

    }
    if (btnAcao && CheckCollisionPointRec(mousePosicao, btnLoadGame))
    {
        PlaySound(fxButton);

        //carrega jogo,

    }
    if (btnAcao && CheckCollisionPointRec(mousePosicao, btnRanking))
    {
        PlaySound(fxButton);
        estadoTela = RANKING_TELA;//------------------copiar

    }
    if (btnAcao && CheckCollisionPointRec(mousePosicao, btnTutotial))
    {
        PlaySound(fxButton);
        estadoTela = TUTORIAL_TELA;

        //tutorial
    }
    if (btnAcao && CheckCollisionPointRec(mousePosicao, btnQuit))
    {
        fecharJogo(); //quita
    }
}

void configuracaoTutorial(Sound fxButton){
    if(btnAcao && CheckCollisionPointRec(mousePosicao, btnVoltar))
    {
        PlaySound(fxButton);
        estadoTela=MENU_TELA;
    }
}


void configuracaoFimdeJogo(Sound fxButton){
    if(btnAcao && CheckCollisionPointRec(mousePosicao, btnMenu))
    {
        PlaySound(fxButton);
        estadoTela=MENU_TELA;
    }
}

void configuracaoVoceVenceu(Sound fxButton){
    if(btnAcao && CheckCollisionPointRec(mousePosicao, btnMenu))
    {
        PlaySound(fxButton);
        estadoTela=MENU_TELA;
    }
}


int main(void)
{
    // Inicialização
    //--------------------------------------------------------------------------------------

    int modoJogador = 0;
    inicializar();
    InitAudioDevice();

    //---------------------------------------------------------------------------------------
    //Carregar conteudo----------------------------------------------------------------------
    Sound fxButton = LoadSound("audio/somMenu.mp3");  // Load button sound
    Sound fxIntro = LoadSound("audio/teclado.mp3");
    Sound fxTiro = LoadSound("audio/tiro1.mp3");
    Sound fxInimigoMorto = LoadSound("audio/inimigomorte1.mp3");
    Sound fxJogadorMorto = LoadSound("audio/jogadormorte.mp3");
    Sound fxPause = LoadSound("audio/pause.mp3");
    Sound fxFaca = LoadSound("audio/faca.mp3");



    Texture2D fundoJogo1 = LoadTexture("./assets/fundojogonivel1.png");
    Texture2D fundoJogo2 = LoadTexture("./assets/fundojogonivel2.png");
    Texture2D fundoJogo3 = LoadTexture("./assets/fundojogonivel3.png");
    Texture2D fundoJogo4 = LoadTexture("./assets/fundojogonivel4.png");
    Texture2D fundoJogo5 = LoadTexture("./assets/fundojogonivel5.png");

    Texture2D fundoMenu = LoadTexture("./assets/menupronto.png");
    Texture2D fundoTutorial = LoadTexture("./assets/tutorial.png");
    Texture2D fundoFimdeJogo = LoadTexture("./assets/fundofimdejogo.png");
    Texture2D fundoVoceVenceu = LoadTexture("./assets/vocevenceu.png");
    Texture2D fundoRanking = LoadTexture("./assets/ranking.png");


    //Configurar FPS
    SetTargetFPS(60);
    //----------------------------------------------------------------------------------------

    void animacaoIntro(){
        if (estadoIntro == 0)
        {
            if ((framesIntroCont/15)%2) DrawRectangle(logoPosicaoX, logoPosicaoY, 16, 16, RAYWHITE);
        }
        else if (estadoIntro == 1)
        {
            DrawRectangle(logoPosicaoX, logoPosicaoY, bordaSuperiorComprimento, 16, RAYWHITE);
            DrawRectangle(logoPosicaoX, logoPosicaoY, 16, bordaEsquerdaAltura, RAYWHITE);
        }
        else if (estadoIntro == 2)
        {
            DrawRectangle(logoPosicaoX, logoPosicaoY, bordaSuperiorComprimento, 16, RAYWHITE);
            DrawRectangle(logoPosicaoX, logoPosicaoY, 16, bordaEsquerdaAltura, RAYWHITE);

            DrawRectangle(logoPosicaoX + 384, logoPosicaoY, 16, bordaDireitaAltura, RAYWHITE);
            DrawRectangle(logoPosicaoX, logoPosicaoY +200, bordaInferiorComprimento, 16, RAYWHITE);
        }
        else if (estadoIntro == 3)
        {
            DrawRectangle(logoPosicaoX, logoPosicaoY, bordaSuperiorComprimento, 16, Fade(RAYWHITE, alpha));
            DrawRectangle(logoPosicaoX, logoPosicaoY + 16, 16, bordaEsquerdaAltura-24 , Fade(RAYWHITE, alpha));

            DrawRectangle(logoPosicaoX + 384, logoPosicaoY + 16, 16, bordaDireitaAltura -24, Fade(RAYWHITE, alpha));
            DrawRectangle(logoPosicaoX, logoPosicaoY + 200, bordaInferiorComprimento, 16, Fade(RAYWHITE, alpha));

            DrawRectangle(logoPosicaoX+16,  logoPosicaoY+16 , 368, 168, Fade(BLACK, alpha));

            DrawText(TextSubtext("  Castle of\nWolfenstein", 0, letrasCont), screenWidth/2 - 150, screenHeight/2 - 80, 50, Fade(RAYWHITE, alpha));
            if(letrasCont>26)
            DrawText(TextSubtext("Feito por Lucas More e Henrique Martins",0,letrasCont-26), screenWidth/2 + 80, screenHeight -15, 15, Fade(RAYWHITE, alpha));
        }
        else if (estadoIntro == 4)
        {
            DrawRectangle(0,  0 , 800, 300, BLACK);
            DrawTexture(fundoMenu, 0, 0 , RAYWHITE);
            DrawRectangle(0,  0 , 800, 300, Fade(BLACK, alpha2));
        }
        else if (estadoIntro == 5)
        {
            DrawTexture(fundoMenu, 0, 0 , RAYWHITE);
            estadoTela=MENU_TELA;

        }
    }
    //----------------------------------------------------------------------------------------

    //Loop do jogo
    while (!WindowShouldClose())
    {
        // Atualizações
        //----------------------------------------------------------------------------------
        if (estadoTela == INTRO_TELA)configuracaoIntro(fxIntro);

        configuracaoMouse();

        if(estadoTela == MENU_TELA)configuracaoMenu(fxButton);

        if(estadoTela == TUTORIAL_TELA)configuracaoTutorial(fxButton);

        if(estadoTela == RANKING_TELA)configuracaoTutorial(fxButton);//---------------copiar

        if(nivel>5)estadoTela = VOCE_VENCEU_TELA;

        if(estadoTela == FIM_DE_JOGO_TELA){
            configuracaoFimdeJogo(fxButton);
            nivel=1;
            strcpy(caixaMensagens.conteudo,"");
        }

        if(estadoTela== VOCE_VENCEU_TELA){
            configuracaoVoceVenceu(fxButton);
            nivel=1;
        }


        if(estadoTela == NOVO_JOGO_TELA){
            for(int i=0; i<nivel; i++){
                inimigo[i].texturaAtual = inimigo[i].textura0;
        }

        //Timer
        timer(); //Timer padrão segundos
        timer2 += GetFrameTime(); //Timer padrão milissegundos:
        if(timer2 >= 0.2f){
            timer2 = 0;
            frame += 1;
        }
        frame = frame % 5;
        //printf("\n==> %f <==> %d <==",timer2,frame);


        //Atualizações
        if(!pausado && tempoAtual >= tempoUltimaAtualizacao + 3 && vida.quantidade > 0){
            movimentoJogador();
            for(int i=0; i<nivel; i++){
                if(inimigo[i].situacao == 1){
                    movimentoInimigo(&inimigo[i],VELOCIDADEDOINIMIGO,i);
                }
            }
            for(int i=0; i<nivel; i++){
                inimigo[i].retangulo.x = inimigo[i].posicao.x;
                inimigo[i].retangulo.y = inimigo[i].posicao.y;
            }

            //Facada e tiro
                if(IsKeyDown(TECLA_FACADA)){
                    facada(fxFaca);
                }else{
                    if(IsKeyDown(TECLA_TIRO)){
                        tiro(fxTiro,fxInimigoMorto);
                    }
                }
                if(faca.ativo == true && faca.mov == true){ //Se a faca estiver ativa e em movimento, executa o código
                    switch(faca.direcao){
                        case 0:
                                faca.posicao.x -= faca.velocidade; //Movimento da faca
                                faca.retangulo.x = faca.posicao.x; //Posiciona o retângulo junto da faca (o eixo Y já foi definido pois é constante)
                            break;
                        case 1:
                                faca.posicao.x += faca.velocidade;
                                faca.retangulo.x = faca.posicao.x;
                            break;
                    }
                    if(faca.posicao.x >= TELA_LARGURA - COMPRIMENTO_FACA || faca.posicao.x <= 0 || faca.posicao.y >= TELA_ALTURA - ALTURA_FACA || faca.posicao.y <= 0){
                        faca.mov = false;
                    }
                }else{
                    if(faca.ativo == true && faca.mov == false){ //Se a faca estiver ativa, mas parada, ...
                        if(CheckCollisionRecs(jogador.retangulo,faca.retangulo)){ //E se o jogador encostar nela, ...
                            faca.ativo = false; //Ela volta à posse do jogador (fica inativa)
                        }
                    }
                }

                //Detecção de colisões
                    //Jogador-inimigo
                    colisoes(fxJogadorMorto);
                    //Inimigo-faca
                    for(int i=0;i<nivel;i++){
                        if(inimigo[i].situacao == 1 && faca.mov == true){
                            if(CheckCollisionRecs(faca.retangulo,inimigo[i].retangulo)){
                                pontuar(i,fxInimigoMorto);
                                faca.mov = false;
                            }
                        }
                    }
                    //Jogador-baú
                    if(baus[0].existencia == 1 && baus[0].situacao == 0){
                        if(CheckCollisionRecs(jogador.retangulo,baus[0].retangulo)){
                            quantidadeTiros -= BAU_MUNICAO_1;
                            if(vida.quantidade < 4 - BAU_VIDAS_1){
                                vida.quantidade += BAU_VIDAS_1;
                            }
                            baus[0].situacao = 1;
                        }
                    }
                    if(baus[1].existencia == 1 && baus[1].situacao == 0){
                        if(CheckCollisionRecs(jogador.retangulo,baus[1].retangulo)){
                            quantidadeTiros -= BAU_MUNICAO_2;
                            if(vida.quantidade < 4 - BAU_VIDAS_2){
                                vida.quantidade += BAU_VIDAS_2;
                            }
                            baus[1].situacao = 1;
                        }
                    }

        }else{
            if(IsKeyDown(TECLA_CESSAR_PAUSAR)){
                pausado = false;
                PlaySound(fxPause);
                strcpy(caixaMensagens.conteudo,"");
            }
        }

        //Baús
        if(pontuacao >= BAU_PONTUACAO_1 && pontuacao < BAU_PONTUACAO_2 && baus[0].situacao == 0){
            baus[0].existencia = 1;
        }else{
            if(pontuacao >= BAU_PONTUACAO_2 && baus[1].situacao == 0){
                baus[1].existencia = 1;
            }
        }

        //Detecção do número de inimigos
        if(numeroInimigos == 0){
            porta.situacao = 1;
            porta.texturaAtual = porta.textura1;
            if(CheckCollisionRecs(jogador.retangulo,porta.retangulo)){
                nivel += 1;
                mudaNivel();
            }
        }else{
            porta.situacao = 0;
            porta.texturaAtual = porta.textura0;
        }

        //Se morreu, ...
        if(vida.quantidade <= 0 && tempoAtual >= tempoUltimaAtualizacao + 3){
            CloseWindow();
        }

        //Salvar
        if(IsKeyDown(TECLA_SALVAR) && tempoAtual > tempoSalvar + 3){
            salvar();
            tempoSalvar = tempoAtual;
            salvo = true;
        }else{
            if(salvo == true && tempoAtual > tempoSalvar + 2){
                salvo = false;
                strcpy(caixaMensagens.conteudo,"");
            }
        }

        //Pausar
        if(IsKeyDown(TECLA_PAUSAR)){
            pausado = true;
            PlaySound(fxPause);
            strcpy(caixaMensagens.conteudo,"Jogo pausado. Aperte O para continuar.");
        }

        }
        //----------------------------------------------------------------------------------


        // Desenhar
        //----------------------------------------------------------------------------------
        BeginDrawing();

            if(estadoTela==INTRO_TELA)
            {
                ClearBackground(BLACK);
                animacaoIntro();
            }


            if(estadoTela == MENU_TELA)
            {
            /*Visualizar botoes------------------------------
            DrawRectangle(325, 103, 150, 45 , BLACK); newgame
            DrawRectangle(530, 103, 150, 45 , BLACK); loadgame
            DrawRectangle(121, 103, 150, 45 , BLACK); ranking
            DrawRectangle(530, 185, 150, 45 , BLACK); tutorial
            DrawRectangle(121, 185, 150, 45 , BLACK); quit
            ------------------------------------------------*/
            DrawTexture(fundoMenu, 0, 0 , RAYWHITE);
            }


            if (estadoTela == NOVO_JOGO_TELA)
            {
                if(nivel==1){
                    DrawTexture(fundoJogo1, 0, 0 , RAYWHITE);
                }
                if(nivel==2){
                    DrawTexture(fundoJogo2, 0, 0 , RAYWHITE);
                }
                if(nivel==3){
                    DrawTexture(fundoJogo3, 0, 0 , RAYWHITE);
                }
                if(nivel==4){
                    DrawTexture(fundoJogo4, 0, 0 , RAYWHITE);
                }
                if(nivel==5){
                    DrawTexture(fundoJogo5, 0, 0 , RAYWHITE);
                }
                if(nivel==6){
                    /*if(pontuacao>pontuaca5) se for maior que a ultima das 5 pontuacoes, pede o nome
                    //estadoTela == INPUT_NOME_TELA
                    //se pontuacao maior que pontuacao x, pontuacaotemporaria=pontuacaox,pontuacaox=pontuacao, pontuacaox=pontuacao(x-1),
                    // pontuacaotemp=pontuacao(x-1), pontuacao (x-2)=pontuacao(x-1)..
                    else */estadoTela= FIM_DE_JOGO_TELA;
                }


            DrawText( //---------------------------<< TEXTO PRINCIPAL
                     textoPrincipal.conteudo,
                     textoPrincipal.posicao_X,
                     textoPrincipal.posicao_Y,
                     textoPrincipal.tamanhoFonte,
                     textoPrincipal.cor
                     );
            DrawText( //---------------------------<< TEXTO SECUNDÁRIO
                     TextFormat("Municao: %d/%d",MAXIMO_CARREGADOR-quantidadeTiros,MAXIMO_CARREGADOR),
                     textoSecundario.posicao_X,
                     textoSecundario.posicao_Y,
                     textoSecundario.tamanhoFonte,
                     textoSecundario.cor
                     );
            DrawText( //----------------------------<< CAIXA DE MENSAGENS
                     caixaMensagens.conteudo,
                     caixaMensagens.posicao_X,
                     caixaMensagens.posicao_Y,
                     caixaMensagens.tamanhoFonte,
                     caixaMensagens.cor
                     );

            DrawTextureV( //------------------------<< JOGADOR
                             jogador.texturaAtual,
                             jogador.posicao,
                             RAYWHITE
                             );
            for(int i=0; i<nivel; i++){
                if(inimigo[i].situacao == 1){
                    DrawTextureV( //------------------------<< INIMIGO
                                 inimigo[i].texturaAtual,
                                 inimigo[i].posicao,
                                 RAYWHITE
                                 );
                }
            }

            if(porta.situacao == 0){
                DrawTextureV(
                             porta.textura0,
                             porta.posicao,
                             RAYWHITE
                             );
            }else{
                if(porta.situacao == 1){
                    DrawTextureV(
                                 porta.texturaAtual,
                                 porta.posicao,
                                 RAYWHITE
                                 );
                    }
                }
            if(faca.ativo == true){
                DrawTextureV(
                             faca.textura,
                             faca.posicao,
                             RAYWHITE
                             );
            }

            //Vida
                if(vida.quantidade > 0){
                    DrawTextureV(vida.textura0,vida.posicao0,WHITE);
                }
                if(vida.quantidade > 1){
                    DrawTextureV(vida.textura0,vida.posicao1,WHITE);
                }
                if(vida.quantidade > 2){
                    DrawTextureV(vida.textura0,vida.posicao2,WHITE);
                }
            //Baús
            for(int i=0; i<BAU_QUANTIDADE; i++){
                if(baus[i].situacao == 1 && baus[i].existencia == 1){
                    DrawTextureV(baus[i].textura1,baus[i].posicao,WHITE);
                }else{
                    if(baus[i].situacao == 0 && baus[i].existencia == 1){
                        DrawTextureV(baus[i].textura0,baus[i].posicao,WHITE);
                    }
                }
            }
            }

            if (estadoTela == TUTORIAL_TELA)
            {
            //DrawRectangle(670,247,120,40,BLACK);
            DrawTexture(fundoTutorial, 0, 0 , RAYWHITE);

            }
            if(estadoTela == RANKING_TELA)
            {
            DrawTexture(fundoRanking, 0, 0 , RAYWHITE);
            }
            if (estadoTela == FIM_DE_JOGO_TELA)
            {
            //DrawRectangle(670,247,120,40,BLACK);
            DrawTexture(fundoFimdeJogo, 0, 0 , RAYWHITE);

            }
            if(estadoTela== VOCE_VENCEU_TELA){
            DrawTexture(fundoVoceVenceu, 0, 0 , RAYWHITE);

            }

            EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // Desinicialização
    //--------------------------------------------------------------------------------------

    fecharJogo();

    //--------------------------------------------------------------------------------------

    return 0;
}

void fecharJogo(Sound fxIntro, Sound fxButton)
{
        UnloadSound(fxIntro);
        UnloadSound(fxButton);

        CloseAudioDevice();
        CloseWindow();
}

