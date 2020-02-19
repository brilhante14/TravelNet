#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Viagem.h"

//Detectar viagens com choque de datas. 1 == Choque.
int consulta(Agendamento* novo, Viagem* raiz){
  int data, duracao;
  duracao = novo->duracao;
  data = novo->data->DataInt;
  // printf("\n%d Dur\n", duracao);
  // Data* data_aux = raiz->detalhes->data;
  Data* data_aux;
  Data* x = novo->data;
  Data* data_f = somarData(novo->data, duracao);
  while(raiz != 0){
    data_aux = raiz->detalhes->data;
    Data* data_aux_f = somarData(data_aux, raiz->detalhes->duracao);
    if( (x->DataInt >= data_aux->DataInt && x->DataInt <= data_aux_f->DataInt) ||
    (data_f->DataInt >= data_aux->DataInt && data_f->DataInt <= data_aux_f->DataInt) ||
    (data_aux->DataInt >= x->DataInt && data_aux->DataInt <= data_f->DataInt) ||
    (data_aux_f->DataInt >= x->DataInt && data_aux_f->DataInt <= data_f->DataInt) ) return 1;
    liberarData(&data_aux_f);
    // for(int i=0; i<raiz->detalhes->duracao; ++i){
    //   printf("%d \n %d \n %d \n_____\n", data_aux->DataInt, data, data_f->DataInt);
    //   if(data>=data_aux->DataInt && data_aux->DataInt<=data_f->DataInt) return 1;
    //   x = somarData(x, 1);
    //   data = x->DataInt;
    // }
    if(avaliador(novo, raiz->detalhes)) raiz = raiz->prox;
    else raiz = raiz->ant;
  }
  liberarData(&data_f);
  return 0;
}

//Preenche os campos de agendamento
Agendamento* criarAgendamento(int id, Data *data, int duracao, char* pais, char* cidade){
  char* Data = (char*) malloc(sizeof(char) * 11);
  Agendamento* a = (Agendamento*)malloc(sizeof(Agendamento));
  a->Id = id;
  a->data = data;
  a->duracao = duracao;
  a->pais = pais;
  a->cidade = cidade;
  return a;
}

//Cria um nó, com seus respectivos campos de agendamento, e o retorna
Viagem* criar_viagem(int id, Data *data, int duracao, char* pais, char* cidade){
  Agendamento* a = criarAgendamento(id, data, duracao, pais, cidade);
  Viagem *v = (Viagem *) malloc(sizeof(Viagem));
  if(v == 0){
    return 0;
  }
  v->detalhes = a;
  v->ant = 0;
  v->prox = 0;
  return v; 
}

//Remoção recursiva
void limparViagens(Viagem* raiz){
  if(raiz != 0){
    // percorrerArvore(raiz, liberarViagem, 1);
    if(raiz->ant!=0){
    //   // removerViagem(raiz->ant);
      limparViagens(raiz->ant);
    }
    if(raiz->prox!=0){
    //   // removerViagem(raiz->prox);
      limparViagens(raiz->prox);
    }  
    // // free(raiz->detalhes);
    liberarViagem(raiz);
  }
  // // raiz = 0;
}



// void removerViagem(Viagem* v){
//   if(v->prox==0 && v->ant==0) free(v);
// }

//Decidir por ordem cronológica o caminho na árvore
//1 == direita | 0 == esquerda;
int avaliador(Agendamento* a, Agendamento* b){
  return (a->data->DataInt < b->data->DataInt);
}

//1 == falha;
int adicionarDireita(Viagem* original, Viagem* novo){
  if(original !=0){ 
    if(original->detalhes->data->DataInt > novo->detalhes->data->DataInt){
      return adicionarEsquerda(original,novo);
    }
    if(consulta(novo->detalhes, original)){ 
      return 1;
    }
    else if(original->prox == 0){
        original->prox = novo;
        return 0;
    }
    else{
      int decisao = avaliador(original->prox->detalhes,novo->detalhes);
      if(decisao == 1){
        adicionarDireita(original->prox,novo);
      }
      else{
        adicionarEsquerda(original->prox,novo);
      }
      return 0;
    }
  }
  return 1;
}

//1 == falha;
int adicionarEsquerda(Viagem* original, Viagem* novo){
  if(original !=0){
    if(original->detalhes->data->DataInt < novo->detalhes->data->DataInt){
      return adicionarDireita(original,novo);
    }
    if(consulta(novo->detalhes, original)) return 1;
    else if(original->ant == 0){
        original->ant = novo;
        return 0;
      }
    else{
      int decisao = avaliador(original->ant->detalhes, novo->detalhes);
      if(decisao ==1){
        adicionarEsquerda(original->ant,novo);
      }
      else{
        adicionarDireita(original->ant,novo);
      }
      return 0;
    }
  } else original = novo;
  return 1;
}

int procurarViagem(Viagem* fonte,Viagem* c){
  while(fonte!=0){ 
    if(c->detalhes->Id == fonte->detalhes->Id){
      return 0;
    }
    // if(c->detalhes == fonte->detalhes->ano){
    //   int decisao = avaliador(fonte->detalhes,c->detalhes);
    //   if(decisao ==0){
    //     fonte = fonte->prox;
    //   }
    //   else{
    //     fonte=fonte->ant;
    //   }
    // }
    else if(c->detalhes->data->DataInt > fonte->detalhes->data->DataInt){
      fonte = fonte->prox;
    }
  }
  return 0;
}

// Procura a Viagem pela chave 'chave' na subárvore enraizada em 'raiz'. Se achá-la, retira ela da árvore. retorn 1 caso conseguiu, 0 caso não.
// A chave é o DataInt da data da viagem que vai ser removida
int removerViagem(Viagem **raiz, int chave){
  Viagem *aux = *raiz, *pai = 0;
  while(aux != 0 && aux->detalhes->data->DataInt != chave){
    pai = aux;
    if(chave < aux->detalhes->data->DataInt){
      aux = aux->ant;
    }else{
      aux = aux->prox;
    }
  }
  if(aux == 0) return 0;
  if(aux->ant == 0){
    if(pai == 0) *raiz = aux->prox;
    else if(aux == pai->ant) pai->ant = aux->prox;
    else pai->prox = aux->prox;
    liberarViagem(aux);
  }else if(aux->prox == 0){
    if(pai == 0) *raiz = aux->ant;
    else if(aux == pai->ant) pai->ant = aux->ant;
    else pai->prox = aux->ant;
    liberarViagem(aux);
  }else{
    Viagem *aux2 = aux;
    aux = aux2->prox;
    pai = aux2;
    while(aux->ant != 0){
      pai = aux;
      aux = aux->ant;
    }
    free(aux2->detalhes->data);
    free(aux2->detalhes);
    aux2->detalhes = aux->detalhes;
    if(pai == aux2) pai->prox = aux->prox;
    else pai->ant = aux->prox;
    free(aux);
  }
  return 1;
}

void liberarViagem(Viagem *v){
  free(v->detalhes->data);
  free(v->detalhes);
  free(v);
}


// Printa os detalhes de uma viagem
void printarViagem(Viagem *v){
  Data* data_f = somarData(v->detalhes->data, v->detalhes->duracao);
  printf("%d\t%s\t%s\t%s\t\t\t%s\n", v->detalhes->Id, v->detalhes->data->Data,data_f->Data, v->detalhes->cidade, v->detalhes->pais);
}

// visita a subárvore enraizada em 'v', e chama a função visitar para v, sendo essa função sendo recebida como parâmetro 
// ordem == -1 => vistar em Pré-Ordem
// ordem ==  0 => visitar em Ordem
// ordem ==  1 => visitar em Pós-Ordem
// 0 == arvore inteira
// 1 == filtragem
void percorrerArvore(Viagem *v, void visitar(Viagem *), int ordem, Data *data, char cidade[30], char pais[30]){
  if(v != 0){
    int Bool = 1;
    if(ordem == 1){ 
      if(data != 0 && v->detalhes->data->DataInt < data->DataInt){
        Bool = 0;
      } else if(cidade != 0 && strcmp(cidade, v->detalhes->cidade) == 0){
        Bool = 0;
      } else if(pais != 0 && strcmp(pais, v->detalhes->pais) == 0){
        Bool = 0;
      }
    }
    //else if(ordem == 2) {
    //  
    //} 
    else{
      if(v->ant != 0) percorrerArvore(v->ant, visitar, ordem, data, cidade, pais);
       visitar(v);
      if(v->prox != 0) percorrerArvore(v->prox, visitar, ordem, data, cidade, pais);
      return;
    }
    if(v->ant != 0) percorrerArvore(v->ant, visitar, ordem, data, cidade, pais);
    if(!Bool) visitar(v);
    if(v->prox != 0) percorrerArvore(v->prox, visitar, ordem, data, cidade, pais);
  }
    //  if(ordem == -1 && Bool) visitar(v);
    //   if(data != 0 && v->detalhes->data->DataInt >= data->DataInt){
    //     Bool = 0;
    //   }
    //   if(cidade != 0 && strcmp(cidade, v->detalhes->cidade) != 0){
    //     Bool = 0;
    //   }
    //   if(pais != 0 && strcmp(pais, v->detalhes->pais) != 0){
    //     Bool = 0;
    //   }
    //   if(Bool) visitar(v);
    // }
}

// Vai printar todas as viagens da árvore enraizada em 'raiz'
void printarArvore(Viagem *raiz, int ordem, Data *data, char cidade[30], char pais[30]){
  printf("ID\tData\t\tRetorno\t\tCidade\t\tPaís\n");
  percorrerArvore(raiz, printarViagem, ordem, data, cidade, pais);
}

int avaliador_data(Data* a, Data* b){
  return (a->DataInt < b->DataInt);
}

void filtrar(Viagem *v, Data *D, char p[30], char c[30]){
  if(D!=0){
    if(v!=0 && v->detalhes->data->DataInt == D->DataInt){
      printf("%d\t%s\t%s\t\t%s\n", v->detalhes->Id, v->detalhes->data->Data, v->detalhes->cidade,v->detalhes->pais);
    } else {
      int decisao = 3;
      if(v->ant==0 && v->prox == 0){
        return;
      }
      if(v->prox == 0){
        decisao =avaliador_data(v->detalhes->data, D);
      }
      else if(v->ant ==0){
        decisao = avaliador_data(v->detalhes->data,D);
      }else{ 
        decisao = avaliador_data(v->detalhes->data, D);}
      if(decisao ==0){
        if(v->ant ==0){
          return;
        }else{
          filtrar(v->ant,D,0,0);
        }
      }
      else if(decisao == 1){
        if(v->prox ==0){
          return;
        }
        else{
          filtrar(v->prox,D,0,0);
        }
      }
      return;
    }
  } else if(p!=0) printarArvore(v,1,0,0,p);      
  else if(c!=0) printarArvore(v,1,0,c,0);
}

// void printarPais(Viagem *v){
  //if(v)
  //printf("%d\t%s\t%s\t%s\n", v->detalhes->Id, v->detalhes->data->Data,data_f->Data, v->detalhes->cidade);
// }



Viagem *buscarViagemPorData(Viagem *raiz, int dataInt){
  while(raiz != 0){
    if(raiz->detalhes->data->DataInt == dataInt){
      return raiz;
    }else if(raiz->detalhes->data->DataInt < dataInt){
      raiz = raiz->ant;
    }else{
      raiz = raiz->prox;
    }
  }
  return 0;
}


// 1 = achou
// 0 = não achou
int buscarViagemPorID(Viagem *raiz, int ID){
  if(raiz != 0){
    if(raiz->detalhes->Id == ID){
      return 1;
    }
    if(buscarViagemPorID(raiz->ant, ID)) return 1;
    return buscarViagemPorID(raiz->prox, ID);
  }
  return 0;
}
