#include "Viagem.h"
#include "Usuario.h"
#include "HashTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Função que recebe string ID do usuário e o nome real do usuário.
Usuario *criarUsuario(char* id, char* nome){
  //Aloca um espaço para o usuário e armazena no ponteiro u.
  Usuario *u = (Usuario *) malloc(sizeof(Usuario));
  //Atribuição de campos.
  u->Id = id;
  u->Nome = nome;
  //lista encadeada dos amigos do usuário.
  u->primeiro = u->ultimo = 0 ;
  u->Viagens = 0;
  return u;
}

//Recebe o usuário u e o amigo que será adicionado no u.
int adicionarAmigo(Usuario *u, Usuario *amigo){
  // Usuario* amigo = (Usuario*)getStr(ht,id);
  //tentando adicionar um amigo inválido.
  if(amigo == 0){
    return 0;
  }
  //nó da lista de amigos do usuário u. 
  Amigo* amiguinho = (Amigo *) malloc(sizeof(Amigo));
  amiguinho->u = amigo;
  //atribuindo ponteiro pra nulo, em formato de fila, adicionamos os amigos.
  amiguinho->prox = 0; 
  //primeiro amigo a ser adicionado
  if(u->primeiro ==0){
    u->primeiro = u->ultimo = amiguinho;
  }
  else{
    u->ultimo->prox = amiguinho;
    u->ultimo = amiguinho;
  }
  return 1;
}

//essa função irá remover um amigo.
int removerAmigo(Usuario* u,char* id){
  //procura a partir do inicio da lista o amigo a ser removido. Ponteiro para o anterior e para o usuário.
  Amigo* anterior = 0;
  Amigo* aux = u->primeiro;
  //procura o amigo que vai ser removido e mantém o ponteiro auxiliar apontando para o amigo a ser removido.
  while(aux != 0 && strcmp(id, aux->u->Id)){
    anterior = aux;
    aux = aux->prox;
  }
  //chegou no final da lista e não achou o amigo que seria removido.
  if(aux == 0) return 0;
  //achou o amigo que será removido, serve para dizer se o amigo que será removido é o primeiro da lista. 
  else if(anterior == 0) {
    u->primeiro = aux->prox;
    //atualiza o ponteiro para o novo primeiro amigo.
    if(u->primeiro == 0) u->ultimo = 0;
    //caso do amigo a ser removido ser o último.
  }else if(aux == u->ultimo) u->ultimo = anterior;
  //amigo a ser removido não está no começo nem no final, atualizando os ponteiros.
  else{
    anterior->prox = aux->prox;
    aux->prox = 0;
  }
  //liberando o nó removido.
  free(aux);
  return 1;
}

//Função printa o usuário!
void printarUsuario(Usuario *u){
  printf("%s\t%s\n", u->Id, u->Nome);
}

//Função para printar os amigos do usuário na lista simplesmente encadeada.
void printarAmigos(Usuario *u){
  printf("Id\tNome\n");
  Amigo *aux = u->primeiro;
  while(aux != 0){
    printarUsuario(aux->u);
    aux = aux->prox;
  }
}

//não utilizaremos provavelmente! =D
char* gerarId(int *i){
  char* id = (char*) malloc(sizeof(char) * 7);
  for(int i=0; i<6; i++){
    if(rand()%2 == 0) id[i] = rand()%26 + 'A';
    else id[i] = rand()%10 + '0';
  }
  id[6] = 0;
  return id;
}