//Serve para organizar as viagens.
#include "Data.h"
#include <stdio.h>
#include <stdlib.h>

//Criar um struct de data com a data passada pelo usuário.
//string no formato de data DD/MM/AAAA
Data *criarData(char* data){
  Data *d = (Data*) malloc(sizeof(Data));
  d->Data = data;
  //Aqui temos a data propriamente dita, como formato de inteiro e não mais de string, mas ambos serão armazenados.
  //A data entrada será no formato DD/MM/AAAA, e será tranformada em AAAAMMDD(um único inteiro)
  int i = d->Data[1] - '0';
  i += 10 * (d->Data[0] - '0');

  i += 100 * (d->Data[4] - '0');
  i += 1000 * (d->Data[3] - '0');

  i += 10000 * (d->Data[9] - '0');
  i += 100000 * (d->Data[8] - '0');
  i += 1000000 * (d->Data[7] - '0');
  i += 10000000 * (d->Data[6] - '0');

  d->DataInt = i;
  return d;
}

//Funçao que dirá se a data inserida é válida.
int validaData(char* data){
  int n = 0;
  while(data[n])n++; 
  if(n != 10) return 0;
  // DD/MM/AAAA

  // Valida as '/' do formato de data
  if(data[2] != data[5] || data[2] != '/' ) return 0;

  // Valida os possíveis dias do mês (01 - 30)
  if(data[0] < '0' || data[0] > '3') return 0;
  if(data[0] == '0' && data[1] == '0') return 0;
  if(data[0] == '3' && data[1] != '0') return 0;  
  if(data[1] < '0' || data[0] > '9') return 0;

  // Valida os possíveis meses do ano (01 - 12)
  if(data[3] == '0'){ // 01 - 09
      if(data[4] < '1' || data[0] > '9') return 0;
  }else if(data[3] == '1'){ // 10 - 12
      if(data[4] < '0' || data[4] > '2') return 0;
  }else return 0;

  // Valida o ano (2010 - 2029)
  if(data[6] != '2') return 0;
  if(data[7] != '0') return 0;
  if(data[8] != '1' && data[8] != '2') return 0;
  if(data[9] < '0' || data[9] > '9') return 0;

  return 1;
}

// Não altera a data 'data' passada, ao invés cria e retorna uma nova Data resultante da soma
//Tempo que a viagem irá durar, retornando a data de retorno do usuário.
Data *somarData(Data *data, int dias){
  Data *d = criarData(data->Data);
  
  int Dias, Meses, Anos; // soma dos dias, meses, e anos das duas datas

  Dias = data->DataInt%100 + dias;
  Meses = data->DataInt/100%100 + (Dias-1)/30;
  Anos = data->DataInt/10000 + (Meses-1)/12;


  Dias = Dias%30; // Restringe entre 0-29
  Meses = Meses%12; // Restringe entre 0-11
  if(Dias == 0) Dias = 30;
  if(Meses == 0) Meses = 12;

  d->DataInt = Dias + 100*Meses + 10000*Anos;
  
  d->Data = (char*) malloc(sizeof(char) * 11);
  d->Data[0] = '0' + Dias/10;
  d->Data[1] = '0' + Dias%10;
  d->Data[2] = '/';
  d->Data[3] = '0' + Meses/10;
  d->Data[4] = '0' + Meses%10;
  d->Data[5] = '/';
  d->Data[6] = '0' + Anos/1000;
  d->Data[7] = '0' + Anos/100%10;
  d->Data[8] = '0' + Anos/10%10;
  d->Data[9] = '0' + Anos%10;
  d->Data[10] = 0;

  return d;
}

void liberarData(Data **data){
  free((*data)->Data);
  free(*data);
}