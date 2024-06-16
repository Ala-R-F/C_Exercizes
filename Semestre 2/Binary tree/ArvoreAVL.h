
typedef struct NO* ArvAVL;

ArvAVL* cria_ArvAVL();
void libera_ArvAVL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, int x, int y, int z, int coord);
int estaVazia_ArvAVL(ArvAVL *raiz);
int altura_ArvAVL(ArvAVL *raiz);
int totalNO_ArvAVL(ArvAVL *raiz);
int consulta_ArvAVL(ArvAVL *raiz, int valor, int coord);//
void emOrdem_ArvAVL(ArvAVL *raiz);
void printRoot(ArvAVL *raiz);
struct NO* procuraMenor(struct NO** atual, int coord);
void sucY(ArvAVL *raiz);
