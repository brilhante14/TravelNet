#ifndef DEFINED_Data
#define DEFINED_Data 1

typedef struct Data Data;

struct Data{
  char* Data;
  int DataInt;
};

Data *criarData(char*);

int validaData(char*);

Data *somarData(Data *, int);

void liberarData(Data **);

#endif