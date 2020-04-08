#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXDISC 10
#define MAXAL 50

typedef struct s1{
int cod;
char nome[50],cpf[11];
struct s1 *prox;
char disc[MAXDISC][50];
int qtde;
}aluno;	

typedef struct s2{
	int cod,creditos;
	char nome[50], prof[50];
	struct s2 *prox;
	int qtde;
	char al[MAXAL][50];

}disciplina;

typedef struct s3{
	char periodo[6];
	aluno *headal;
	disciplina *headdisc;

}periodo;

void insereal(periodo *p)
{
	char alunim[50],cpf[11];
	int codigo;
	printf("digite o nome do al: ");scanf("%s",alunim);
	printf("digite o cpf do al: ");scanf("%s",cpf);
	printf("digite o cod do al: ");scanf("%d",&codigo);
	aluno *al; al=p->headal;
	if(al==NULL)
	{
		aluno *aux;
		aux=(aluno*)malloc(sizeof(aluno));
		strcpy(aux->nome,alunim);		
		strcpy(aux->cpf,cpf);
		aux->cod=codigo;
		aux->prox=NULL;
		aux->qtde=0;
		p->headal=aux;
		return;
	}
	else
	{
		p->headal=al;
		while(al->prox!=NULL)
		{
			al=al->prox;
		}
		
		aluno *aux;
		aux=(aluno*)malloc(sizeof(aluno));
		strcpy(aux->nome,alunim);		
		strcpy(aux->cpf,cpf);
		aux->cod=codigo;
		aux->prox=NULL;
		aux->qtde=0;
		al->prox=aux;
		return;
	}
}

void listaluno(aluno *al)//ta listando so os codigos dos alunos, e mais facil q os nomes
{
	if(al==NULL){printf("Nao ha alunos cadastrados nesse periodo\n");}
	else{	
			while(al->prox!=NULL)
			{
				printf("%d\n",al->cod);
				al=al->prox;
			}
				printf("%d\n",al->cod);
		}
}

void excluialuno(periodo *p,int alu)//excluir atraves do codigo do aluno
{		
	int b=0;
	aluno *al; al=p->headal;
	if(alu==al->cod){p->headal=al->prox;free(al);}//se o aluno q quer excluir e o primeiro da lista
	else{
			p->headal=al;
			aluno *ant;
			while(alu!=al->cod){
				ant = al;
				al=al->prox;
				if(al==NULL){printf("o aluno nao foi encontrado\n");b=1;break;}//nao achou o aluno
								}
			if(b==0){
				ant->prox=al->prox;free(al);printf("aluno excluido com sucesso\n");
				}
		}
	return;
}

void initperiod(periodo *p)//inicializar tds os ponteiros das listas encadeadas apontando pra NULL
{
	for(int i=0;i<10;i++)
	{
	p[i].headal=NULL;
	p[i].headdisc=NULL;
	}
	return;
}

void inseredisc(periodo *p)
{
	char nome[50],prof[50];
	int codigo,creditos;
	printf("digite o nome da disc: ");scanf("%s",nome);
	printf("digite o nome do prof : ");scanf("%s",prof);
	printf("digite o cod da disc: ");scanf("%d",&codigo);
	printf("digite a qtde de creditos: ");scanf("%d",&creditos);

	disciplina *disc; disc=p->headdisc;
	if(disc==NULL)
	{
		disciplina *aux;
		aux=(disciplina*)malloc(sizeof(disciplina));
		strcpy(aux->nome,nome);		
		strcpy(aux->prof,prof);
		aux->cod=codigo;
		aux->creditos=creditos;
		aux->prox=NULL;
		aux->qtde=0;
		p->headdisc=aux;
		return;
	}
	else
	{
		p->headdisc=disc;
		while(disc->prox!=NULL)
		{
			disc=disc->prox;
		}
		
		disciplina *aux;
		aux=(disciplina*)malloc(sizeof(disciplina));
		strcpy(aux->nome,nome);		
		strcpy(aux->prof,prof);
		aux->cod=codigo;
		aux->creditos=creditos;
		aux->prox=NULL;
		aux->qtde=0;
		disc->prox=aux;
		return;
	}
}

void listdisciplina(disciplina *disc)
{
	if(disc==NULL){printf("Nao ha disciplinas cadastradas nesse periodo\n");}
	else{	
			while(disc->prox!=NULL)
			{
				printf("%d\n",disc->cod);
				disc=disc->prox;
			}
				printf("%d\n",disc->cod);
		}
}

void excluidisc(periodo *p,int dis)//excluir atraves do codigo da disc
{		
	int b=0;
	disciplina *disc; disc=p->headdisc;
	if(dis==disc->cod){p->headdisc=disc->prox;free(disc);}//se a disc q quer excluir e o primeiro da lista
	else{
			p->headdisc=disc;
			disciplina *ant;
			while(dis!=disc->cod){
				ant = disc;
				disc=disc->prox;
				if(disc==NULL){printf("a disc nao foi encontrads\n");b=1;break;}//nao achou a disc
								}
			if(b==0){
				ant->prox=disc->prox;free(disc);printf("disciplina excluido com sucesso\n");
				}
		}
	return;
}

void poediscaluno(aluno *al, disciplina *disc)
{	
	int codal,coddisc;
	printf("digite o codigo do aluno que quer: ");scanf("%d",&codal);
	printf("digite o codigo da disciplina que quer: ");scanf("%d",&coddisc);

	while(al->cod!=codal){al=al->prox;	if(al==NULL){printf("aluno nao encontrado");return;}}					//ja tenho o aluno
	while(disc->cod!=coddisc){disc=disc->prox;	if(disc==NULL){printf("disciplina nao encontrada");return;}}	//ja tenho a disc

	if(al->qtde == MAXDISC){printf("aluno cheio de materia\n");return;}
	if(disc->qtde == MAXAL){printf("disciplina lotada\n");return;}

	strcpy(al->disc[al->qtde], disc->nome);al->qtde++;//adiciona a materia no vetor de string de disciplina do aluno
	strcpy(disc->al[disc->qtde], al->nome);disc->qtde++;//adiciona o aluno no vetor de string de alunos da disciplina

	return;
}
/*
void tiradiscaluno(aluno *al, disciplina *disc)
{	
	int codal,coddisc;
	printf("digite o codigo do aluno que quer: ");scanf("%d",&codal);
	printf("digite o codigo da disciplina que quer retirar: ");scanf("%d",&coddisc);

	while(al->cod!=codal){al=al->prox;	if(al==NULL){printf("aluno nao encontrado");return;}}					//ja tenho o aluno
	while(disc->cod!=coddisc){disc=disc->prox;	if(disc==NULL){printf("disciplina nao encontrada");return;}}	//ja tenho a disc

	if(al->qtde==0){printf("o aluno nao tem disciplinas\n");return;}
	al->disc[al->qtde]=*disc;al->qtde++;
	if(disc->qtde==0){printf("nao ha disciplinas pra tirar\n");return;}
	disco->al[disc->qtde]=*al;disc->qtde++;
	return;
}
*/

void printaluno(aluno *al, int cod)
{
	while(al->cod!=cod){al=al->prox; if(al==NULL){printf("nao encontrou o aluno\n");return;} }
	printf("nome: %s\n",al->nome);
	printf("cpf: %s\n",al->cpf);
	printf("codigo: %d\n",al->cod);
	printf("disciplinas cadastradas: \n");
	
	for(int k=0;k<=al->qtde;k++){printf("%s\n",al->disc + k);}

	return;
}

int main()
{
	int d=1,per=0,auxx;
	char aux[50];
	periodo period[10];initperiod(period);
	while(d!=0)
	{
		printf("\ndigite a opcao pretendida: ");
		printf("\n1)mudar periodo(formato xxxx.x)\n2)inserir aluno\n3)remover aluno\n4)inserir disciplina para um aluno\n5)remover disciplina para um aluno\n6)cadastrar disciplina\n7)excluir disciplina\n8)listar alunos\n9)listardisciplinas\n10)listarcaracaluno\n0)finalizar programa   :");
		scanf("%d",&d);
		switch(d){
			case 1:
			  	printf("qual o periodo voce quer entrar, entre 2016.1 - 2020.2?");scanf("%d",&per); break;
			
			case 2: 
			//insereal(period[per].headal,period[per]);	
			insereal(&period[per]);
			       	break;	
			
			case 3:if(period[per].headal==NULL){printf("nao ha aluno para ser removido\n");} 
					else{printf("digite o codigo do aluno que quer ser removido");scanf("%d",&auxx);
						excluialuno(&period[per],auxx);}   break;
			
			case 4:  if(period[per].headal==NULL){printf("nao ha alunos\n");break;} 
					if(period[per].headdisc==NULL){printf("nao ha disciplinas\n");break;} 
					poediscaluno(period[per].headal,period[per].headdisc); break;
			
			case 5:  break;
			
			case 6: inseredisc(&period[per]); break;
			
			case 7:if(period[per].headdisc==NULL){printf("nao ha disciplina para ser removida\n");} 
				     else{printf("digite o codigo da disciplina que quer ser removida");scanf("%d",&auxx);
					 excluidisc(&period[per],auxx);} break;
			
			case 8: listaluno(period[per].headal);break;

			case 9: listdisciplina(period[per].headdisc); break;
			
			case 10: 
				if(period[per].headal==NULL){printf("nao ha aluno cadastrado\n");break;} 
				printf("digite o codigo do aluno q quer: ");scanf("%d",&auxx);
				printaluno(period[per].headal,auxx); break;

	       		}
	}	
}