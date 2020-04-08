#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct s1{
int cod;
char nome[50],cpf[11];
struct s2 *disc;
struct s1 *prox;
}aluno;	

typedef struct s2{
	int cod,creditos;
	char nome[50], prof[50];
	aluno *al;
	struct s2 *prox;
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
						excluialuno(&period[per],auxx);}    break;
			
			case 4:  break;
			
			case 5:  break;
			
			case 6: inseredisc(&period[per]); break;
			
			case 7:if(period[per].headdisc==NULL){printf("nao ha disciplina para ser removida\n");} 
					else{printf("digite o codigo da disciplina que quer ser removida");scanf("%d",&auxx);
					 excluidisc(&period[per],auxx);} break;
			
			case 8: listaluno(period[per].headal);break;

			case 9: listdisciplina(period[per].headdisc); break;
			
	       		}
	}	
}