#include <string.h>
#include <stdlib.h>
#include "HashTable.h"


struct Node{
    char* KeyChar;
    void *Value;
};

struct hashtable{
    Node* *vetor, *null;
    int n, m, min;
    float coef1, coef2;
};

// Inicializa um Node com a chave 'key' e valor 'value'
Node *newNodeStr(char* key, void *value){
    Node *no = (Node*) malloc(sizeof(Node));
    no->KeyChar = key;
    no->Value = value;
    return no;
}




// Inicializa uma Tabela de dispersão de tamanho mínimo 10
HashTable *newHashTable(){
    HashTable *ht = (HashTable*) malloc(sizeof(HashTable));
    ht->min = 10;
    ht->m = ht->min;
    ht->n = 0;
    ht->vetor = (Node**) malloc(sizeof(Node) * ht->m);
    ht->coef1 = 1.25;
    ht->coef2 = 5;
    for(int i=0; i < ht->m; i++) ht->vetor[i] = 0;
    return ht;
}

// Pega uma posião no vetor da tabela 'ht' dada uma chave de inteiro 'key'
int hashInt(int key, HashTable *ht){
    if(key < 0) key = -key;
    return key % ht->m;
}
// Pega uma posição no vetor da tabela 'ht' dada uma chave de string 'key'
int hashStr(char* key, HashTable *ht){
    int i=0, hash=0;
    while(key[i]){
        hash = hash*8193 + key[i]*8193;
        i++;
    }
    return hashInt(hash, ht);
}

// Insere na tabelta 'ht' um valor qualquer 'value' relacionado à chave de string 'key'
void putStr(HashTable *ht, char* key, void *value){
    if(key != 0){ //Detecta se a chave 'key' não é ponteiro nulo
        if((float)ht->n / (float)ht->m > 0.9) redimensionar(ht, ht->m*ht->coef1 + ht->coef2);
        int j = hashStr(key, ht);
        while(ht->vetor[j] != 0 && strcmp(ht->vetor[j]->KeyChar, key) != 0){
            j++;
            if(j==ht->m) j=0;
        }
        if(ht->vetor[j] != 0) {
            ht->vetor[j]->Value = value;
        }else{
            ht->vetor[j] = newNodeStr(key, value);
            ht->n++;
        }
    }
}

// Checa se a chave 'key' está na tabela 'ht', e retorna o valor correspondente caso sim, ou ponteiro nulo caso não
void *getStr(HashTable *ht, char* key){
    int j = hashStr(key, ht);
    while(ht->vetor[j] != 0 && (ht->vetor[j]->KeyChar == 0 || strcmp(key, ht->vetor[j]->KeyChar) != 0)){
        j++;
        if(j == ht->m) j=0;
    }
    if(ht->vetor[j] == 0) return 0;
    return ht->vetor[j]->Value;
}

// Se a chave estiver na tabela, remove de lá e retorna o valor correspondente
void *remStr(HashTable *ht, char* key){
    if(((float)ht->m / (float)ht->n) < 0.7) redimensionar(ht, (ht->m -ht->coef2) / ht->coef1);
    int j = hashStr(key, ht);
    while(ht->vetor[j] != 0 && (ht->vetor[j] == ht->null || strcmp(key, ht->vetor[j]->KeyChar) != 0)){
        j++;
        if(j == ht->m) j=0;
    }
    if(ht->vetor[j] == 0) return 0;
    ht->n--;
    void *p = ht->vetor[j]->Value;
    ht->vetor[j] = ht->null;
    return p;
}

// redimensiona o vetor da tabela, tornando-a dinâmica
void redimensionar(HashTable *ht, int newSize){
    if(newSize < 10) newSize = 10;
    HashTable *Ht = newHashTable();
    Ht->m = newSize;
    free(Ht->vetor);
    Ht->vetor = (Node**) malloc(sizeof(Node) * Ht->m);
    for(int i=0; i<ht->m; i++){
        if(ht->vetor[i] != 0){
          putStr(Ht, ht->vetor[i]->KeyChar, ht->vetor[i]->Value);
        }
        free(ht->vetor[i]);
    }
    free(ht->vetor);
    ht->vetor = Ht->vetor;
    ht->m = newSize;
    free(Ht->null);
    free(Ht);
}