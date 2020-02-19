#ifndef DEFINED_Usuario
#define DEFINED_Usuario 1

#include "HashTable.h"
#include "Viagem.h"

typedef struct Amigo Amigo;

typedef struct Usuario Usuario;

//Struct contendo usuário, id do usuário, nome do usuário e uma lista encadeada onde serão guardados os amigos do usuário, viagem é a raiz da ABB.
struct Usuario{
  char* Id;
  char* Nome;
  Amigo* primeiro, *ultimo;
  Viagem* Viagens;
};
//Nó da lista encadeada de amigos do usuario.
struct Amigo{
  Usuario* u;
  Amigo* prox;
};
//Função que cria o usuário.
Usuario *criarUsuario(char *, char *);

// int adicionarAmigo(Usuario *, char* , HashTable *);
int adicionarAmigo(Usuario *, Usuario *);

int removerAmigo(Usuario* u,char* id);

void printarUsuario(Usuario *);

void printarAmigos(Usuario *);

char* gerarId();

#endif