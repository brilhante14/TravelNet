/*
João Victor - 473977
Gabriel Passos - 470692
Gabriel Brilhante - 472078
Laura Petrola - 471913
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "Data.h"
#include "HashTable.h"
#include "Viagem.h"
#include "Usuario.h"


Viagem *pedirViagem();
void adicionarAmigoMutuo(HashTable *, char*, char*);
int menuPrincipal(Usuario *);
int menuDeAmigos(HashTable *ht, Usuario *);
int menuDeViagens(Usuario *);
int cadastro(HashTable *ht);

int main() {
  srand(time(0));
  
	HashTable *ht = newHashTable();
  char id_adc[5];

  //CRIANDO USUARIOS PARA O BANCO DE DADOS
  putStr(ht, "1", criarUsuario("1", "Pablo"));
  putStr(ht, "2", criarUsuario("2", "Bosco"));
  putStr(ht, "3", criarUsuario("3", "Rudini"));
  putStr(ht, "4", criarUsuario("4", "Cláudia"));
  putStr(ht, "5", criarUsuario("5", "Pordeus"));
  putStr(ht, "6", criarUsuario("6", "Emmanuel"));
  putStr(ht, "7", criarUsuario("7", "Lincoln"));
  putStr(ht, "8", criarUsuario("8", "Neuman"));
  putStr(ht, "9", criarUsuario("9", "Othin"));
  putStr(ht, "A", criarUsuario("A", "Victor Fields"));
  putStr(ht, "B", criarUsuario("B", "Coronel"));
  putStr(ht, "C", criarUsuario("C", "Julio"));
  
   //ADICIONANDO VIAGENS PARA OS USUARIOS
  ((Usuario*)getStr(ht,"1"))->Viagens = criar_viagem(1 ,criarData("25/10/2020"),15,"Brasil","Fortaleza");
  adicionarDireita(((Usuario*)getStr(ht,"1"))->Viagens, criar_viagem(2 ,criarData("24/11/2020"),30,"Brasil","Rio de janeiro"));
  adicionarDireita(((Usuario*)getStr(ht,"1"))->Viagens, criar_viagem(3 ,criarData("25/12/2026"),21,"Brasil","Cascavel"));
  ((Usuario*)getStr(ht,"3"))->Viagens = criar_viagem(4 ,criarData("04/02/2019"),7,"Acre","Belém");
  adicionarDireita(((Usuario*)getStr(ht,"3"))->Viagens , criar_viagem(5 ,criarData("25/10/2020"),6,"Brasil","Salvador"));
  adicionarDireita(((Usuario*)getStr(ht,"3"))->Viagens, criar_viagem(6 ,criarData("01/10/2022"),25,"Brasil","Cascavel"));
  adicionarDireita(((Usuario*)getStr(ht,"1"))->Viagens , criar_viagem(7 ,criarData("7/01/2019"),9,"Brasil","Viçosa"));
  ((Usuario*)getStr(ht,"7"))->Viagens = criar_viagem(8 ,criarData("16/05/2022"),42,"Brasil","Maraponga");
  adicionarDireita(((Usuario*)getStr(ht,"1"))->Viagens , criar_viagem(9 ,criarData("21/06/2020"),1,"Brasil","Maraponga"));
  ((Usuario*)getStr(ht,"B"))->Viagens = criar_viagem(10 ,criarData("30/12/2025"),3,"Acre","Rio Branco");


  //Usuario *user = (Usuario *) getStr(ht, "B");
  // printarAmigos(user);
  //printf("\n");
  printf("======= Bem vindo a nossa rede social: TravelNet =======\n");
  printf("Digite o nome de usuário que você deseja: (max:20) ");
  char usuario[20];
  scanf("%s",usuario);
  printf("Digite o seu ID: (max:5) ");
  char id[5];
  scanf("%s",id);
  Usuario *user = (Usuario *) getStr(ht, id);
  while(user != 0){
    printf("Esse ID já está está sendo usado!\n");
    printf("Digite o ID do novo usuário: ");
    scanf("%s", id);
    user = (Usuario*) getStr(ht, id);
  }
  
  putStr(ht,id,criarUsuario(id, usuario));
  user = getStr(ht, id);

  adicionarAmigoMutuo(ht, id, "5");
  adicionarAmigoMutuo(ht, id, "C");
  adicionarAmigoMutuo(ht, id, "A");
  adicionarAmigoMutuo(ht, "B", "7");
  // Menus:
  // 0 = Sair
  // 1 = Principal
  // 2 = Amigos
  // 3 = Viagens
  // 4 = Cadastrar novo usuário
  // 5 = Adicionar amigo
  int menu = 1;
  while(menu){
    printf("\n");
        char *new_ID = (char *)malloc(sizeof(char) *6); 
        char *new_name = (char *) malloc(sizeof(char) *21);
    switch(menu){
      case 1:
        menu = menuPrincipal(user);
      break;
      case 2:
        menu = menuDeAmigos(ht, user);
      break;
      case 3:
        menu = menuDeViagens(user);
      break;
      case 4:
        printf("Digite o nome do novo usuário: ");
        scanf("%s", new_name);
        printf("Digite o ID do novo usuário: ");
        scanf("%s", new_ID);
        Usuario *User = (Usuario*) getStr(ht, new_ID);
        while(User != 0){
          printf("Esse ID já está está sendo usado!\n");
          printf("Digite o ID do novo usuário: ");
          scanf("%s", new_ID);
          User = (Usuario*) getStr(ht, new_ID);
        }
        putStr(ht, new_ID, criarUsuario(new_ID, new_name));
        printf("Usuário cadastrado com sucesso!\n");
        menu = 2;
      break;
      case 5:
        printf("Digite o ID do usuário que você quer adicionar: ");
        scanf("%s", id_adc);
        Usuario *amigo = (Usuario *) getStr(ht, id_adc);
        if(amigo == 0){
          printf("Não encontrei esse usuário no sistema!\n");
          menu = menuDeAmigos(ht, user);
        }else{
          Amigo *aux = user->primeiro;
          while(aux != 0 && strcmp(aux->u->Id, id_adc) != 0){
            aux = aux->prox;
          }
          if(aux == 0){
            adicionarAmigoMutuo(ht, user->Id, id_adc);
            printf("Você e %s agora são amigos!\n", amigo->Nome);
          }else printf("Você e %s já são amigos\n", aux->u->Nome);
          menu = menuDeAmigos(ht, user);
        }
      break;
      default:
      break;
    }
  }
	return 0;
}

 //Menu Principal da rede
int menuPrincipal(Usuario *user){
  printf("Bem vindo ao TravelNet, %s!\n", user->Nome);
  printf("Digite:\nAmigos - para ver seus amigos\nViagens - para ver suas viagens\nSair - para encerrar sua conexão\n");
  char *new_name = (char *) malloc(sizeof(char) *21);
  char escolha[8];
  scanf("%s", escolha);
  if(strcmp(escolha, "Amigos") == 0){
    return 2;
  }else if(strcmp(escolha, "Viagens") == 0){
    return 3;
  }else if(strcmp(escolha, "Sair") == 0){char *new_ID = (char *)malloc(sizeof(char) *6); 
    return 0;
  }else{
    printf("Escolha inválida!\n");
    return 1;
  }
}

// Menu de amigos do usuário
int menuDeAmigos (HashTable* ht, Usuario *user){
  char *new_name = (char *) malloc(sizeof(char) *21);
  printf("Digite:\n");
  printf("\"Adicionar\" para adicionar um amigo,\n\"Remover\" para voltar para o início,\n\"Cadastrar\" para cadastrar um novo amigo,\n\"Listar\" para verificar seus amigos, \n\"Voltar\" para remover um amigo,\n");
  printf("Ou digite o ID de um amigo para ver o suas viagens;\n ");
 
  char id_rmv[5];
  char escolha[8];
  scanf("%s", escolha);

  // adicionar um novo amigo
  if(strcmp(escolha, "Adicionar") == 0){
    return 5;
  } else if(strcmp(escolha,"Listar")==0){
    printf("Esses são seus amigos: \n");
    printarAmigos(user);
    printf("Digite o ID de um amigo para vê as viagens dele, ou \"Voltar\": ");
    scanf("%s", escolha);
  } else if(strcmp(escolha, "Voltar") == 0){
    return 1;
  } else if(strcmp(escolha, "Cadastrar") == 0){
    return 4;
  }
  // remove um amigo do usuário
  else if(strcmp(escolha, "Remover") == 0){
    printf("Digite o ID do amigo que você quer remover: ");
    scanf("%s", id_rmv);
    if(removerAmigo(user, id_rmv)) {
      printf("Você e %s não são mais amigos!", ((Usuario *)getStr(ht, id_rmv))->Nome);
    }else{
      printf("Não encontrei esse usuário no sistema!\n");
    }
    return 2;
  }
  // procurar um amigo com o id digitado (escolha)
    else{
      // Usuario *amigo = (Usuario *) getStr(ht, escolha);
      Amigo *Amigo = user->primeiro;
      while(Amigo != 0 && strcmp(Amigo->u->Id, escolha) != 0){
        Amigo = Amigo->prox;
      }
      if(Amigo == 0) printf("Não encontrei esse usuário na sua lista de amigos!\n");
      else{
        Usuario *amigo = Amigo->u;
        printf("Digite \n\"Filtrar\" para filtrar as viagens;\n\"Listar\" para listar as viagens do seu amigo;\n");
        scanf("%s", escolha);
        if(strcmp(escolha,"Listar") == 0){
          printf("Essas são todas as viagens que o %s agendou:\n", amigo->Nome);
          printarArvore(amigo->Viagens,0,0,0,0);
        }
        else if(strcmp(escolha, "Filtrar") == 0){
          
          // Filtrar as viagens do amigo
          if(amigo->Viagens ==0){
            printf("\n\n%s não possui viagens agendadas!\n", amigo->Nome);
            return 3;
          }

          // Consultar viagens filtradas
          printf("\n\nDigite: \n\"Data\" para filtrar por data;\n");
          printf("\"Local\" para filtrar por local;\n");
          // char escolha_f[7];
          scanf("%s",escolha);
          if(strcmp(escolha,"Data")==0){
            printf("Digite a data desejada: ");
            char* data = (char*) malloc(sizeof(char)*11);
            scanf("%s",data);
            while(!validaData(data)){
              printf("Digite uma data válida! Ex: 25/11/2019\n");
              printf("Digite a DATA da sua viagem: ");
              scanf("%s",data);
            }
            Data *D = criarData(data);  
            printf("Viagens agendadas para essa data:\n");
            printf("ID\tData\t\tCidade\t\tPaís\n");
            filtrar(amigo->Viagens,D,0,0);
          } else if(strcmp(escolha,"Local")==0){
            printf("\n\nDigite: \n\"País\" para filtrar por país;\n\"Cidade\" para filtrar por cidade;\n");
            char escolha_s[10];
            scanf("%s", escolha_s);
            printf("Digite o local desejado: ");
            char local[30];
            scanf("%s",local);
            if(strcmp(escolha_s,"País")==0){
              filtrar(amigo->Viagens,0,local,0);
            } else if(strcmp(escolha_s,"Cidade")==0){
              filtrar(amigo->Viagens,0,0,local);
            }
          }
            printf("\n ____________________________________ \n");
        }
      }
      return 2;
    }
    return 2;
}

// Menu de viagens do usuário
int menuDeViagens(Usuario *user){
  printf("Aqui estão todas as suas viagens agendadas:\n");
  printarArvore(user->Viagens,0,0,0,0);
  printf("\n\nDigite: \n\"Novo\" para agendar uma nova viagem;\n\"Filtrar\" para filtrar suas viagens;\n\"Voltar\" para retornar ao menu principal;\n\"Remover\" para remover uma viagem agendada;\n");
  printf(" A DATA de uma das viagens agendadas para alterar detalhes;\n");
  char* escolha = (char*) malloc(sizeof(char)*11);
  scanf("%s", escolha);
  if(strcmp(escolha, "Novo") == 0){
    Viagem *nova = pedirViagem(user);
    
    if(user->Viagens == 0){
      user->Viagens = nova;
    }else if(adicionarDireita(user->Viagens, nova)){
      printf("\n\nParece que o período dessa viagem entrou em conflito com outra que você já marcou anteriormente, tente novamente.\n\n");
      liberarViagem(nova);
      return 3;
    }
    printf("\n\nViagem agendada com sucesso!\n");
  } else if(strcmp(escolha,"Filtrar") == 0){
    if(user->Viagens ==0){
      printf("\n\nVocê ainda não possui viagens agendadas!\n");
      return 3;
    }

    // Consultar viagens filtradas
    printf("\n\nDigite: \n\"Data\" para filtrar por data;\n");
    printf("\"Local\" para filtrar por local;\n");
    char escolha_f[7];
    scanf("%s",escolha_f);
    if(strcmp(escolha_f,"Data")==0){
      printf("Digite a data desejada: ");
      char* data = (char*) malloc(sizeof(char)*11);
      scanf("%s",data);
      while(!validaData(data)){
        printf("Digite uma data válida! Ex: 25/11/2019\n");
        printf("Digite a DATA da sua viagem: ");
        scanf("%s",data);
      }
      Data *D  =criarData(data);  
      printf("Viagens agendadas para essa data:\n");
      printf("ID\tData\t\tCidade\t\tPaís\n");
      filtrar(user->Viagens,D,0,0);
    } else if(strcmp(escolha,"Local")==0){
      printf("\n\nDigite: \n\"País\" para filtrar por país;\n\"Cidade\" para filtrar por cidade;\n");
      char escolha_s[30];
      scanf("%s", escolha_s);
      printf("Digite o local desejado: ");
      char local[10];
      scanf("%s",local);
      if(strcmp(escolha_s,"País")==0){
        filtrar(user->Viagens,0,local,0);
      } else if(strcmp(escolha_s,"Cidade")==0){
        filtrar(user->Viagens,0,0,local);
      }
    }
      printf("\n ____________________________________ \n");
  } else if(strcmp(escolha,"Remover") == 0){
  if(user->Viagens == 0){
    printf("Você não possui nenhuma viagem!\n");
      printf("\n ____________________________________ \n");
    return 3;
  }
	printf("Digite a data da viagem que deseja remover: ");
	char *data_rmv = (char*)malloc(sizeof(char)*11);
	scanf("%s", data_rmv);
	while(!validaData(data_rmv)){
	printf("Digite uma data válida! Ex: 25/11/2019\n");
	printf("Digite a DATA da sua viagem: ");
	scanf("%s",data_rmv);
	}
	Data *Data_Rem = criarData(data_rmv);
	if(removerViagem(&user->Viagens, Data_Rem->DataInt)) printf("Remoção concluída!\n");
  	printf("\n ____________________________________ \n");	
	return 3;
  } else if(strcmp(escolha,"Voltar") == 0){
    return 1;
  } else {
      Data *D_search = criarData(escolha);
      Viagem *v = buscarViagemPorData(user->Viagens, D_search->DataInt);
      if(v == 0) printf("Não encontrei essa viagem no sistema!\n");
      else{
        Viagem *nova = pedirViagem(user);
        liberarData(&v->detalhes->data);
        free(v->detalhes);
        v->detalhes = nova->detalhes;
      }
  }
  return 3;
}

Viagem *pedirViagem(Usuario* user){
  int id, duracao;
  char* data = (char*) malloc(sizeof(char) * 11);
  char* pais = (char*) malloc(sizeof(char) * 30);
  char* cidade = (char*) malloc(sizeof(char) * 30);
  printf("Digite o ID da sua viagem: ");
  scanf("%d",&id);
  while(buscarViagemPorID(user->Viagens,id) == 1 ){
    printf("Esse ID já está está sendo usado!\n");
    printf("Digite o ID da nova viagem: ");
    scanf("%d", &id);
  }
  printf("Digite a DATA da sua viagem: ");
  scanf("%s",data);
  while(!validaData(data)){
    printf("Digite uma data válida! Ex: 25/11/2019\n");
    printf("Digite a DATA da sua viagem: ");
    scanf("%s",data);
  }
  printf("Digite a DURAÇÃO da sua viagem (em dias): ");
  scanf("%d",&duracao);
  printf("Digite o PAÍS da sua viagem: ");
  scanf("\n%[^\n]s", pais);
  printf("Digite a CIDADE da sua viagem: ");
  scanf("\n%[^\n]s", cidade);
  return criar_viagem(id, criarData(data), duracao, pais, cidade);
}

void adicionarAmigoMutuo(HashTable *ht, char* A, char* B){
  adicionarAmigo((Usuario *) getStr(ht, A), (Usuario *) getStr(ht, B));
  adicionarAmigo((Usuario *) getStr(ht, B), (Usuario *) getStr(ht, A));
}