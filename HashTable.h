//A nossa hashtable será utilizada para armazenar todos os usuários cadastrados no nosso sistema. As chaves da hashtable serão os ids dos usuários, e os valores da hashtable serão os próprios usuários.
#ifndef DEFINED_HashTable
#define DEFINED_HashTable 1

typedef struct Node Node;
typedef struct hashtable HashTable;

void redimensionar(HashTable*, int);

Node *newNodeStr(char*, void *);

HashTable *newHashTable();

int hashInt(int, HashTable *);

int hashStr(char*, HashTable *);

void putStr(HashTable *, char*, void *);

void *getStr(HashTable *, char*);

void *remStr(HashTable *, char*);

void redimensionar(HashTable *, int);

#endif