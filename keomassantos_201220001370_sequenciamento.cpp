#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

//variaveis globais
int *tabe;
int subcadeia=3;

//Definição da clase doenca

class Doenca{
  
public:
  struct gene{
      float quant;
    string g;
    int flag;
    
  };

 string codigo;
  int quantidade_genes;
 gene *genes;

 
void clean_genes(){
  
   delete [] genes;
  
}
 
 void set_codigo(string n){
  codigo=n;
}
string get_codigo(){
  
  return codigo;
  
}

float retorna_quant (int x ){
  
  return genes[x].quant;
 
}
  
string retorna_gene(int x ){
  
  return genes[x].g;
  
  
}
void inicia_genes(int x){
  
  genes = new gene [x];
  quantidade_genes=x;
  
  
}

void define_flag(int tam){
  
 float p;
  for(int i =0 ;i < tam; i++){
    p=porcent(i);
    if(p >= ((float)0.9)){
      
   genes[i].flag=1;
    }else{
      
      genes[i].flag=0;
    }
    
  }

  
  
}

void define_genes(int indice,string ge, float q){
  
  genes[indice].g=ge;
  
  genes[indice].quant =q;
  
  
}


void count_quant(int indice, int quantidade){
  
  genes[indice].quant=genes[indice].quant+quantidade;
  
}

float porcent(int indice){
  
  return   genes[indice].quant/(float) genes[indice].g.length();
  
  
}

float resultado(int tam){
 int count=0;

for(int i=0; i < tam; i++){
  
  count=count + genes[i].flag;
  
} 
  
 return   roundf ( (((float)count / (float)tam )*100)); 
  
}



};


///codigo do kmp para lista

void inicializar(int *tab, int m){
  for(int i =0; i<m ; i++){
    tab[i]=-1;
    
  }
  
}



void calcular_tabela(int *tab, string P) {
  unsigned int i, m = P.length();
  int j = -1;
  inicializar(tab, m);
  for(i = 1; i < m; i++) {
    while(j >= 0 && P[j + 1] != P[i]) j = tab[j];
    if(P[j + 1] == P[i]) j++;
   tab[i] = j;
}
}









void busca_kmp2(int *tab, string T, string P,int ind,Doenca &b) {
unsigned int i, n = T.length();
unsigned int m = P.length();
int j = -1;
calcular_tabela(tab, P);
for(i = 0; i < n; i++) {
  
if((P[j+1] != T[i])&& (j>=subcadeia -1) ){
    
      b.count_quant(ind,j+1);
      //cortando strings
      P=P.substr(j+1,P.length());
      //cout<<P<<endl;
      T=T.substr(i+1,T.length());
      
      //zerando e iniciando  tabela
      delete [] tab;
      tab = new int [P.length()];
    
      busca_kmp2(tab,T,P,ind,b);
    
      break;
       
  }  
  
  while(j >= 0 && P[j + 1] != T[i]) j = tab[j];
     if(P[j + 1] == T[i]) j++;     
     

  
     if( (i == n-1) && (j>=subcadeia -1)){
   
      b.count_quant(ind,j+1);
   
}
     
     
}
 
 
 

  
}   


//Ordenação

struct saida{
  string c;
  int p;
  
};

saida *s;

void insertSort(saida a[], int length)
{
    int i, j, value;
  saida value2;
    for(i = 1; i < length; i++)
    {
        value = a[i].p;
	value2 =a[i];
        for (j = i - 1; j >= 0 && a[j].p < value; j--)
        {
            a[j + 1] = a[j];
        }
        a[j + 1] = value2;
    }
}


  
//


int main(int argc, char **argv) {
  
  ofstream output (argv[2]);
  //setando o arquivo  
  ifstream input(argv[1]);
  
  
  
  
  //lendo tamanho de subcadeia e DNA
  
  string DNA;
  input >> subcadeia >>DNA;
  
  //lendo # Doenças e Instaciando objeto Doenca
  int aux_ngenes=0;
  Doenca obj;
  int numero_doencas=0;
  input >> numero_doencas;
  
  //instaciando auxiliar para saida
  s =new saida [numero_doencas];
  
  //Laço principal pegando codigos e executando
  
  for(int i=0; i< numero_doencas;i++){
    
    input >> obj.codigo;
    input>> aux_ngenes;
    //cout<<aux_ngenes<<endl;
    obj.inicia_genes(aux_ngenes);
    
    //lendo genes
    for(int h=0; h <aux_ngenes;h++){
      string aux_gene;
      input >> aux_gene;
      //cout << aux_gene<<endl;
      obj.define_genes(h,aux_gene,0);
    tabe = new int [obj.genes[h].g.length()];
  
      busca_kmp2(tabe,DNA,obj.retorna_gene(h),h,obj);
    }  
    obj.define_flag(aux_ngenes);
    
    s[i].c=obj.codigo,s[i].p= obj.resultado(aux_ngenes);
    
    obj.clean_genes();
    
  }
  
  
   
  input.close();
  
  
  insertSort(s,numero_doencas);
  
  for(int i=0; i < numero_doencas; i++){
   output<< s[i].c<<": "<<s[i].p<<"%"<<endl;
    
  }
  output.close();
  
  
  
    return 0;
}
