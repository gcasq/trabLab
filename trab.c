//este codigo le um arquivo de disciplinas com multiplas linhas no formato: "periodo(xxxx.x),nome,prof,codigo,creditos"
//este codigo le um arquivo de alunos no formato: "periodo,nome,prof,codigo,materia cadastrada"
//para cada materia, deve ser adicionada uma nova linha com o mesmo aluno e a matéria a ser adicionada
//se quer adicionar o aluno sem matéria nenhuma, coloque "NHF" no lugar da matéria, que então ele entrará sem nenhuma matéria vinculada a ele
//para todas as leituras, caso coloque um periodo invalido ou caso queira cadastrar um aluno ou disciplina novos com o código repetido, não acontecerá nada
//é limitada a quantidade de disciplinas que cada aluno pode ter, e vice-versa, porém é permitido que se altere de forma fácil o limite, redefinindo os "#define" logo abaixo
//este código aceita os períodos entre 2016.1 até 2020.2
//este código destroi o arquivo de alunos e o arquivo de disciplinas ao final dele, e os recria com mesmo nome e colocando as atualizações
//as buscas por aluno e disciplina ocorrem mediante os seus códigos
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXDISC 10
#define MAXAL 50
typedef struct s1{
int cod;
char nome[50],cpf[11];
struct s1 *prox; //aponta pro prox elemento da lista encadeada
char disc[MAXDISC][50]; //vetor que armazena os nomes das disciplinas que aluno cadastrou
int qtde;//indice que indica quantas disciplinas cada aluno tem no momento
}aluno;	

typedef struct s2{
	int cod,creditos;
	char nome[50], prof[50];
	struct s2 *prox;//aponta pro prox elemento da lista encadeada
	int qtde;//indice que indica quantos alunos cada disciplina tem no momento
	char al[MAXAL][50];//vetor que armazena os nomes dos alunos que tão cadastrados na disc

}disciplina;

typedef struct s3{
	char periodo[7];
	aluno *headal;//ponteiro que aponta para o primeiro elemento da lista encadeada dos alunos, em casa periodo
	disciplina *headdisc;//ponteiro que aponta para o primeiro elemento da lista encadeada da disciplina, em casa periodo

}periodo;

void insereal(periodo *p)//o parametro de entrada é o endereço na memória de toda a struct do período que eu estou dentro. A partir dela, tenho acesso aos ponteiros que apontam para o início das listas encadeadas dos alunos e disciplinas. A partir daqui, é só trabalhar normalmente com uma lista encadeada
{
	char alunim[50],cpf[11];
	int codigo;
	printf("digite o nome do al: ");scanf("%s",alunim);
	printf("digite o cpf do al: ");scanf("%s",cpf);
	printf("digite o cod do al: ");scanf("%d",&codigo);
	aluno *al; al=p->headal; //al - serve apenas para armazenar o ponteiro para o começo da lista encadeada dos alunos
	if(al==NULL) //caso em que não há alunos cadastrados
	{
		aluno *aux; //struct que armazenará as informações do aluno
		aux=(aluno*)malloc(sizeof(aluno));
		strcpy(aux->nome,alunim);		
		strcpy(aux->cpf,cpf);
		aux->cod=codigo;
		aux->prox=NULL;
		aux->qtde=0;
		p->headal=aux;//altera o valor do ponteiro que está dentro do período, para colocar o novo aluno como sendo a cabeça da lista
		return;
	}
	else
	{
		p->headal=al;//apenas pra me assegurar de que não vou alterar o valor da cabeça da lista encadeada, acho que é desnecessário isso
		if(al->cod==codigo){printf("ja existe outro aluno com esse codigo nesse periodo\n");return;}
		while(al->prox!=NULL)
		{
			al=al->prox;
			if(al->cod==codigo){printf("ja existe outro aluno com esse codigo nesse periodo\n");return;}
		}//esse while é pra chegar até o final da lista, pra add o aluno depois dela
		
		aluno *aux;
		aux=(aluno*)malloc(sizeof(aluno));
		strcpy(aux->nome,alunim);		
		strcpy(aux->cpf,cpf);
		aux->cod=codigo;
		aux->prox=NULL;//novo elemento aponta pra NULL
		aux->qtde=0;
		al->prox=aux;//faz o novo penultimo elemento apontar para o que acabei de criar
		return;
	}
}
//obs: o insereal precisa do periodo como parametro de entrada na função, e o listaluno apenas 
//precisa do ponteiro que aponta pra cabeça da lista, sem necessitar do periodo. Isso é porque 
//o listaluno não altera nada, apenas printa, enquanto que o insereal eu preciso alterar qual é
//o ponteiro para a cabeça da lista no caso em que inicialmente não havia aluno algum (linha 48)

void listaluno(aluno *al)//ta listando so os codigos dos alunos, e mais facil q os nomes. O parametro de entrada é o ponteiro para a cabeça da lista encadeada dos alunos
{
	if(al==NULL){printf("Nao ha alunos cadastrados nesse periodo\n");}
	else{	
			while(al->prox!=NULL)//percorrendo os proximos elementos da lista encadeada e printando
			{
				printf("%s\t",al->nome);
				printf("%d\n",al->cod);
				al=al->prox;
			}
				printf("%s\t",al->nome);
				printf("%d\n",al->cod);//printa o ultimo
		}
}

void tiraaldiscadp(disciplina *disc, char *nomeal)//usado qdo exclui um aluno, pra retirar ele de tds as disciplinas
{	
	int k,cont;
	
	while(disc!=NULL){
		cont=0;
	for(k=0;k<disc->qtde;k++)
	{	
		if(strcmp(disc->al[k],nomeal)==0){cont=1;break;}
	}
	if(cont==1){strcpy(disc->al[k], disc->al[disc->qtde-1]); disc->qtde--;} //tirando o aluno da disc (meio xereu)
	
	disc=disc->prox;
	}
	return;
}//essa função é chamada automaticamente qdo excluo o aluno

void excluialuno(periodo *p,int alu)//o parametro de entrada é o período e o código do aluno que quero retirar
{		
	int b=0;
	aluno *al; al=p->headal; //al so serve pra armazenar a cabeça da lista encadeada dos alunos
	if(alu==al->cod){p->headal=al->prox;
	tiraaldiscadp(p->headdisc,al->nome);//exclui o aluno de cada uma das disc do periodo
	free(al);}//se o aluno q quer excluir e o primeiro da lista
	else{
			p->headal=al;
			aluno *ant;//armazena o aluno anterior ao que esta sendo percorrido, serve pra quando eu excluir um, fazer o anterior apontar para o novo proximo
			while(alu!=al->cod){//esse while é pra buscar o aluno que tem o código que eu quero excluir
				ant = al;
				al=al->prox;
				if(al==NULL){printf("o aluno nao foi encontrado\n");b=1;break;}//nao achou o aluno
								}
			if(b==0){//aqui exclui o aluno com o comando free. o valor de b muda pra 1 caso n ache ninguem, aí não entra nesse if
				ant->prox=al->prox;
					tiraaldiscadp(p->headdisc,al->nome);//exclui o aluno de cada uma das disc do periodo
					free(al);printf("aluno excluido com sucesso\n");
				}
		}
	return;
}//botar pra tirar da disciplina

void initperiod(periodo *p)//inicializar tds os ponteiros das listas encadeadas apontando pra NULL
{
	for(int i=0;i<10;i++)
	{
	p[i].headal=NULL;
	p[i].headdisc=NULL;
	}
	strcpy(p[0].periodo,"2016.1");
	strcpy(p[1].periodo,"2016.2");
	strcpy(p[2].periodo,"2017.1");
	strcpy(p[3].periodo,"2017.2");
	strcpy(p[4].periodo,"2018.1");
	strcpy(p[5].periodo,"2018.2");
	strcpy(p[6].periodo,"2019.1");
	strcpy(p[7].periodo,"2019.2");
	strcpy(p[8].periodo,"2020.1");
	strcpy(p[9].periodo,"2020.2");
	return;
}//em cada periodo existente, faz os ponteiros das listas encadeadas apontarem para NULL. Isso e porque não há alunos nem disciplinas em nenhum periodo no momento em que é criado

void inseredisc(periodo *p)//funciona IGUAL o insereal, só diferencia nos dados
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
		if(disc->cod==codigo){printf("ja existe outra disc com esse codigo nesse periodo\n");return;}
		while(disc->prox!=NULL)
		{
			disc=disc->prox;
			if(disc->cod==codigo){printf("ja existe outra disc com esse codigo nesse periodo\n");return;}
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

void listdisciplina(disciplina *disc)//funciona IGUAL o listaluno
{
	if(disc==NULL){printf("Nao ha disciplinas cadastradas nesse periodo\n");}
	else{	
			while(disc->prox!=NULL)
			{
				printf("%s\t",disc->nome);
				printf("%d\n",disc->cod);
				disc=disc->prox;
			}	
				printf("%s\t",disc->nome);
				printf("%d\n",disc->cod);
		}
}

void tiradiscalunoadp(aluno *al, char *nomedisc)//usado qdo excluo disciplina do periodo, pra tirar ela de tds os alunos.
{	
	int k,cont;//cont e um auxiliar, pra caso de fato o aluno tenha a disciplina
	
	while(al!=NULL){
		cont=0;
	for(k=0;k<al->qtde;k++)
	{	
		if(strcmp(al->disc[k],nomedisc)==0){cont=1;break;}//pra entrar no if, o al tem a disciplina
	}
	if(cont==1){strcpy(al->disc[k], al->disc[al->qtde-1]); al->qtde--;} //excluo a disciplina do aluno
	
	al=al->prox;
	}
	return;
}//essa funcao é chamada automaticamente qdo excluo a disciplina

void excluidisc(periodo *p,int dis)//excluir atraves do codigo da disc. Funciona IGUAL o excluialuno
{		
	int b=0; char auxx[50];
	disciplina *disc; disc=p->headdisc;
	if(dis==disc->cod){p->headdisc=disc->prox;

	tiradiscalunoadp(p->headal,disc->nome);//exclui a disciplina de cada um dos alunos do periodo

	free(disc);}//se a disc q quer excluir e o primeiro da lista
	else{
			p->headdisc=disc;
			disciplina *ant;
			while(dis!=disc->cod){
				ant = disc;
				disc=disc->prox;
				if(disc==NULL){printf("a disc nao foi encontrads\n");b=1;break;}//nao achou a disc
								}
			if(b==0){
				ant->prox=disc->prox;
				tiradiscalunoadp(p->headal,disc->nome);//exclui a disciplina de cada um dos alunos do periodo
				free(disc);printf("disciplina excluido com sucesso\n");
				}
		}
	return;
}//botar pra excluir de cada aluno

void poediscaluno(aluno *al, disciplina *disc)//os parametros de entrada são os ponteiros que apontam para as cabeças das listas encadeadas do aluno e disciplina
{	
	int codal,coddisc;
	printf("digite o codigo do aluno que quer: ");scanf("%d",&codal);
	printf("digite o codigo da disciplina que quer: ");scanf("%d",&coddisc);

	while(al->cod!=codal){al=al->prox;	if(al==NULL){printf("aluno nao encontrado\n");return;}}					//percorre a lista dos alunos e fixa na que tem o código do aluno desejado
	while(disc->cod!=coddisc){disc=disc->prox;	if(disc==NULL){printf("disciplina nao encontrada\n");return;}}	//msma coisa, só q pra disciplina

	if(al->qtde == MAXDISC){printf("aluno cheio de materia\n");return;}//verifica se o aluno atingiu o limite dele
	if(disc->qtde == MAXAL){printf("disciplina lotada\n");return;}//msma coisa, pra disciplina

	for(int k=0;k<al->qtde;k++){if(strcmp(al->disc[k],disc->nome)==0){printf("aluno ja cadastrado nessa disciplina!\n");return;}  }//aluno já se cadastrou na disciplina

	strcpy(al->disc[al->qtde], disc->nome);al->qtde++;//adiciona a materia no vetor de string de disciplina do aluno, e aumenta a qtde de materias. essa qtde vai ser o índice para trabalharmos com esse vetor
	strcpy(disc->al[disc->qtde], al->nome);disc->qtde++;//adiciona o aluno no vetor de string de alunos da disciplina. msma coisa com a qtde

	return;
}

void tiradiscaluno(aluno *al, disciplina *disc)
{	
	int codal,coddisc,k;
	printf("digite o codigo do aluno que quer: ");scanf("%d",&codal);
	printf("digite o codigo da disciplina que quer retirar: ");scanf("%d",&coddisc);

	while(al->cod!=codal){al=al->prox;	if(al==NULL){printf("aluno nao encontrado");return;}}					//ja tenho o aluno
	while(disc->cod!=coddisc){disc=disc->prox;	if(disc==NULL){printf("disciplina nao encontrada");return;}}	//ja tenho a disc
	for(k=0;k<al->qtde;k++)
	{	
		//if(strcmp(al->disc + k,disc->nome)==0){break;}
		if(strcmp(al->disc[k],disc->nome)==0){break;}

	}
	strcpy(al->disc[k], al->disc[al->qtde-1]); al->qtde--; //tirando a disc do aluno (meio xereu)

	for(k=0;k<disc->qtde;k++)
	{		
		if(strcmp(disc->al[k],al->nome)==0){break;}
	}
	strcpy(disc->al[k], disc->al[disc->qtde-1]); disc->qtde--; //tirando aluno da disc

	return;
}

void printaluno(aluno *al, int cod)//lista todas as caracteristicas de um aluno atraves do codigo dele, incluindo as disciplinas cadastradas
{
	while(al->cod!=cod){al=al->prox; if(al==NULL){printf("nao encontrou o aluno\n");return;} }//percorre a lista procurando o aluno. se n achar, printa essa msg
	printf("nome: %s\n",al->nome);
	printf("cpf: %s\n",al->cpf);
	printf("codigo: %d\n",al->cod);
	printf("disciplinas cadastradas: \n");
	char aux[50];
	for(int k=0;k<al->qtde;k++){strcpy(aux,al->disc[k]);
		printf("%s\n",aux);}//printa as disciplinas em que o aluno ta cadastrado.

	return;
}

void printdisc(disciplina *disc, int cod)//funciona IGUAL o printaluno
{
	while(disc->cod!=cod){disc=disc->prox; if(disc==NULL){printf("nao encontrou a disciplina\n");return;} }
	printf("nome: %s\n",disc->nome);
	printf("prof: %s\n",disc->prof);
	printf("codigo: %d\n",disc->cod);
	printf("creditos: %d\n",disc->creditos);
	printf("alunos cadastrados: \n");
	char aux[50];
	for(int k=0;k<disc->qtde;k++){strcpy(aux,disc->al[k]);
		printf("%s\n",aux);}
	return;
}

int mudaperiodo(int x,char *string)
{
	if(strcmp(string,"2016.1")==0){printf("periodo alterado para %s\n",string);return 0;}
	if(strcmp(string,"2016.2")==0){printf("periodo alterado para %s\n",string);return 1;}
	if(strcmp(string,"2017.1")==0){printf("periodo alterado para %s\n",string);return 2;}
	if(strcmp(string,"2017.2")==0){printf("periodo alterado para %s\n",string);return 3;}
	if(strcmp(string,"2018.1")==0){printf("periodo alterado para %s\n",string);return 4;}
	if(strcmp(string,"2018.2")==0){printf("periodo alterado para %s\n",string);return 5;}
	if(strcmp(string,"2019.1")==0){printf("periodo alterado para %s\n",string);return 6;}
	if(strcmp(string,"2019.2")==0){printf("periodo alterado para %s\n",string);return 7;}
	if(strcmp(string,"2020.1")==0){printf("periodo alterado para %s\n",string);return 8;}
	if(strcmp(string,"2020.2")==0){printf("periodo alterado para %s\n",string);return 9;}
	else{printf("periodo invalido: \n");return x;}
}

int mudaperiodo2(char *string)
{
	if(strcmp(string,"2016.1")==0){return 0;}
	if(strcmp(string,"2016.2")==0){return 1;}
	if(strcmp(string,"2017.1")==0){return 2;}
	if(strcmp(string,"2017.2")==0){return 3;}
	if(strcmp(string,"2018.1")==0){return 4;}
	if(strcmp(string,"2018.2")==0){return 5;}
	if(strcmp(string,"2019.1")==0){return 6;}
	if(strcmp(string,"2019.2")==0){return 7;}
	if(strcmp(string,"2020.1")==0){return 8;}
	if(strcmp(string,"2020.2")==0){return 9;}
	else{return 20;}
}

void inseredisc2(periodo *p, char *nome, char *prof, int codigo, int creditos)//funciona IGUAL o inseredisc, mas pro arquivo, em q n tem printf nenhum
{
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
		if(disc->cod==codigo){return;}
		while(disc->prox!=NULL)
		{
			disc=disc->prox;
			if(disc->cod==codigo){return;}//se tiver outra disciplina com o mesmo codigo, nao faz nada
		}
		if(strcmp(disc->nome,nome)==0){return;}
		while(disc->prox!=NULL)
		{
			disc=disc->prox;
			if(strcmp(disc->nome,nome)==0){return;}//se tiver outra disciplina com o mesmo nome, nao faz nada
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

void insereal2(periodo *p,char *alunim,char *cpf, int codigo, char *materia)//o parametro de entrada é o endereço na memória de toda a struct do período que eu estou dentro. A partir dela, tenho acesso aos ponteiros que apontam para o início das listas encadeadas dos alunos e disciplinas. A partir daqui, é só trabalhar normalmente com uma lista encadeada
{
	aluno *al; al=p->headal;int l=0,m=0;
	aluno *mod;//para armazenar o ponteiro do aluno que vou trabalhar
	disciplina *disc; disc=p->headdisc;
	if(al==NULL) //caso em que não há alunos cadastrados
	{
		aluno *aux; //struct que armazenará as informações do aluno
		aux=(aluno*)malloc(sizeof(aluno));
		strcpy(aux->nome,alunim);		
		strcpy(aux->cpf,cpf);
		aux->cod=codigo;
		aux->prox=NULL;
		aux->qtde=0;
		p->headal=aux;//altera o valor do ponteiro que está dentro do período, para colocar o novo aluno como sendo a cabeça da lista
		mod=aux;
	}
	else
	{
		p->headal=al;//apenas pra me assegurar de que não vou alterar o valor da cabeça da lista encadeada, acho que é desnecessário isso
		if(al->cod==codigo){mod=al;l=1;}
		while(al->prox!=NULL)
		{
			al=al->prox;
			if(al->cod==codigo){mod=al;l=1;}
		}//esse while é pra chegar até o final da lista, pra add o aluno depois dela
		if(l==0){
		aluno *aux;
		aux=(aluno*)malloc(sizeof(aluno));
		strcpy(aux->nome,alunim);		
		strcpy(aux->cpf,cpf);
		aux->cod=codigo;
		aux->prox=NULL;//novo elemento aponta pra NULL
		aux->qtde=0;
		al->prox=aux;//faz o novo penultimo elemento apontar para o que acabei de criar
		mod=aux;		
				}
	}
		//a partir de agora tenho o aluno endereçado na struct mod, pra adicionar a matéria
 //	if(strcmp(materia,"NaoHaMateria")==0){return;}
	if(strcmp(materia,"NHM")==0){return;}	
	else{
			while(disc!=NULL){	//verificação se existe a matéria cadastrada anteriormente:
				if(strcmp(materia,disc->nome)==0){m=1;break;}	//se nao chegar nisso aqui, e pq a materia n existe no periodo e portanto nao aconteceu nada
				disc=disc->prox;}

	if(m==1){//ou seja, a materia existe mesmo
			if(mod->qtde == MAXDISC){return;}//verifica se o aluno atingiu o limite dele. se sim, n faz nada
			if(disc->qtde == MAXAL){return;}//msma coisa, pra disciplina. se sim, n faz nada

			for(int k=0;k<mod->qtde;k++){if(strcmp(mod->disc[k],disc->nome)==0){return;}}//aluno ja cadastrado nessa disciplina

			strcpy(mod->disc[mod->qtde], disc->nome);mod->qtde++;//adiciona a materia no vetor de string de disciplina do aluno, e aumenta a qtde de materias. essa qtde vai ser o índice para trabalharmos com esse vetor
			strcpy(disc->al[disc->qtde], mod->nome);disc->qtde++;//adiciona o aluno no vetor de string de alunos da disciplina. msma coisa com a qtde
			}
		}
	return;
}

int main()
{
	int d=1,per=0,auxx;//per - índice do período; d - opção escolhida no menu; auxx - valores inteiros que serão dados como entrada nas diversas opções do menu
	char mudaperiod[6];//aux - nome que sera dado como entrada nas diversas opções do menu
	periodo *period; FILE *al2,*disc2;
	period=(periodo*)malloc(10*sizeof(periodo));initperiod(period);
	char nome_prof[50], nome_alu[50], nome_dis[50],perio[7],materia[50],cpf[12];
    int cod_dis, n_cred, n_alu;

    disc2 = fopen("testedisc.txt","r");
    while(fscanf(disc2, "%6s %s %s %d %d", perio, nome_dis, nome_prof, &cod_dis, &n_cred) != EOF){
	per=mudaperiodo2(perio);
	if(per==20){}//se o periodo ta incorreto, o resto do while nao faz nada
	else{//se o periodo ta correto:
		inseredisc2(&period[per],nome_dis,nome_prof,cod_dis,n_cred);
		}
	}

	al2 = fopen("testealunos.txt","r");
    while(fscanf(al2, "%6s %s %d %s %s", perio, nome_alu,&n_alu, cpf, materia) != EOF){
	per=mudaperiodo2(perio);
	if(per==20){}//se o periodo ta incorreto, o resto do while nao faz nada
	else{//se o periodo ta correto:
		insereal2(&period[per],nome_alu,cpf,n_alu,materia);
		}
	}
	fclose(disc2);
	fclose(al2);

	while(d!=0)
	{
		printf("\ndigite a opcao pretendida: ");
		printf("\n1)mudar periodo(formato xxxx.x)\n2)inserir aluno\n3)remover aluno\n4)inserir disciplina para um aluno\n");
		printf("5)remover disciplina para um aluno\n6)cadastrar disciplina\n7)excluir disciplina\n");
		printf("8)listar alunos\n9)listardisciplinas\n10)listarcaracaluno\n11)listcaracdisc\n0)finalizar programa   : ");
		
		scanf("%d",&d);
		switch(d){
			case 1:
			  	printf("qual o periodo voce quer entrar, entre 2016.1 - 2020.2?: ");scanf("%s",mudaperiod);per=mudaperiodo(per,mudaperiod);break;
			
			case 2: 
			insereal(&period[per]);
			       	break;	
			
			case 3:if(period[per].headal==NULL){printf("nao ha aluno para ser removido\n");} 
					else{printf("digite o codigo do aluno que quer ser removido: ");scanf("%d",&auxx);
						excluialuno(&period[per],auxx);}   break;
			
			case 4:  if(period[per].headal==NULL){printf("nao ha alunos\n");break;} 
					if(period[per].headdisc==NULL){printf("nao ha disciplinas\n");break;} 
					poediscaluno(period[per].headal,period[per].headdisc); break;
			
			case 5:  if(period[per].headal==NULL){printf("nao ha alunos\n");break;} 
					if(period[per].headdisc==NULL){printf("nao ha disciplinas\n");break;} 
					tiradiscaluno(period[per].headal,period[per].headdisc); break;
			
			case 6: inseredisc(&period[per]); break;
			
			case 7:if(period[per].headdisc==NULL){printf("nao ha disciplina para ser removida\n");} 
				     else{printf("digite o codigo da disciplina que quer ser removida: ");scanf("%d",&auxx);
					 excluidisc(&period[per],auxx);} break;
			
			case 8: listaluno(period[per].headal);break;

			case 9: listdisciplina(period[per].headdisc); break;
			
			case 10: 
				if(period[per].headal==NULL){printf("nao ha aluno cadastrado\n");break;} 
				printf("digite o codigo do aluno q quer: ");scanf("%d",&auxx);
				printaluno(period[per].headal,auxx); break;

			case 11:	
					if(period[per].headdisc==NULL){printf("nao ha disciplina cadastrada\n");break;} 
					printf("digite o codigo da disciplina q quer: ");scanf("%d",&auxx);
					printdisc(period[per].headdisc,auxx);break;
	       		}
	}	
	disc2=fopen("testedisc.txt","w");//começo a gravação do txt das disciplinas
	disciplina *disc3;
	for(int y=0;y<10;y++)
	{
		disc3=period[y].headdisc;
		while(disc3!=NULL)
		{
			fprintf(disc2,"%s %s %s %d %d\n", period[y].periodo,disc3->nome, disc3->prof, disc3->cod,disc3->creditos);
			disc3=disc3->prox;
		}
	}//termino gravação do txt das disciplinas
	fclose(disc2);
	
	al2=fopen("testealunos.txt","w");//começo a gravação do txt dos alunos
	aluno *al3;char nomemat[50];
		for(int y=0;y<10;y++)
	{
		al3=period[y].headal;
		while(al3!=NULL)
		{
			if(al3->qtde==0){fprintf(al2,"%s %s %d %s NHM\n",period[y].periodo, al3->nome,al3->cod,al3->cpf);}
			else{
				for(int t=0;t<al3->qtde;t++)
				{
				strcpy(nomemat,al3->disc[t]);
				fprintf(al2,"%s %s %d %s %s\n",period[y].periodo, al3->nome,al3->cod,al3->cpf,nomemat);
				}
			}
			al3=al3->prox;
		}
	}//termino gravação do txt dos alunos
	fclose(al2);
return 0;}