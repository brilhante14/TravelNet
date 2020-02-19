#ifndef DEFINED_Viagem
#define DEFINED_Viagem 1

#include "Data.h"

typedef struct Agendamento Agendamento;
struct Agendamento{
  int Id,duracao;
  // char cidade[30],pais[30];
  char* cidade, * pais;
  Data* data; 
};

typedef struct Viagem Viagem;
struct Viagem{
  Viagem* prox, *ant;
  Agendamento* detalhes;
};


Agendamento* criarAgendamento(int, Data *, int, char*, char*);

Viagem* criar_viagem(int, Data *, int, char*, char*);

int consuta(Agendamento* novo, Agendamento* raiz);

void limparViagens(Viagem* raiz);

void liberarViagem(Viagem *);

int removerViagem(Viagem **, int);

int avaliador(Agendamento* a, Agendamento* b);

int adicionarDireita(Viagem* original, Viagem* novo);

int adicionarEsquerda(Viagem* original, Viagem* novo);

int subArvoreDireita(Viagem* fonte);

int subArvoreEsquerda(Viagem* fonte);

int procurarViagem(Viagem* fonte,Viagem* c);

void printarViagem(Viagem *v);

void percorrerArvore(Viagem *v, void visitar(Viagem *), int ordem, Data *data, char cidade[30], char pais[30]);

void printarArvore(Viagem *raiz, int ordem, Data *data, char cidade[30], char pais[30]);

void filtrar(Viagem *v, Data *D, char p[30], char c[30]);

int avaliador_data(Data* a, Data* b);

Viagem *buscarViagemPorData(Viagem *, int);
int buscarViagemPorID(Viagem *, int);

#endif