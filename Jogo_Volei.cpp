#include<iostream>
#include<string.h>
#include<math.h>
#include<time.h>

using namespace std;

class jogador{
protected:
    const string nome;
    const int ataque,passe,defesa;
    const int pesoa,pesop,pesod;
    double habilidadeindividual;
public:
    jogador(string nome,int ataque,int passe,int defesa,int pesoa, int pesop, int pesod):nome(nome),ataque(ataque),passe(passe),defesa(defesa),pesoa(pesoa),pesop(pesop),pesod(pesod){
        habilidadeindividual=(ataque*pesoa+passe*pesop+defesa*pesod)/(pesoa+pesod+pesop);
                                                        }
    int gethabil(){return habilidadeindividual;}
};

class levantador:public jogador{
private:
    int melhornocampeonato;
public:
    levantador(string nome,int ataque,int passe,int defesa, int melhornocampeonato):jogador(nome,ataque,passe,defesa,1,6,3){
        this->melhornocampeonato=melhornocampeonato;
        habilidadeindividual=habilidadeindividual+10*melhornocampeonato;
        }
};

class libero:public jogador{
private:
    int vezesmelhorpasse;
public:
    libero(string nome,int ataque,int passe,int defesa,int vezesmelhorpasse):jogador(nome,ataque,passe,defesa,0,5,5){
        this->vezesmelhorpasse=vezesmelhorpasse;
        int a;
        a=vezesmelhorpasse/10;
        habilidadeindividual=habilidadeindividual*pow(2,a);
        }
};

class meia:public jogador{
private:
    int jogosembloqueio;
public:
    meia(string nome,int ataque,int passe,int defesa,int jogosembloqueio):jogador(nome,ataque,passe,defesa,4,1,3){
        this->jogosembloqueio=jogosembloqueio;
        habilidadeindividual=habilidadeindividual-jogosembloqueio;
        }
};

class ponta:public jogador{
public:
    ponta(string nome,int ataque,int passe,int defesa):jogador(nome,ataque,passe,defesa,4,3,3){}
};

class oposto:public jogador{
private:
    int marcoumaispontos;
public:
    oposto(string nome,int ataque,int passe,int defesa,int marcoumaispontos):jogador(nome,ataque,passe,defesa,6,1,3){
        this->marcoumaispontos=marcoumaispontos;
        habilidadeindividual=habilidadeindividual+20*marcoumaispontos;
        }
};

class Time{
private:
    string nometime;
    jogador **jogadores;
    int somahabil,lev,lib,mei,pont,opost;
    int sets;

public:
    Time(string nometime){
        this->nometime=nometime;
        jogadores = new (nothrow) jogador*[7];
        lev=0,lib=0,mei=0,pont=0,opost=0;
        sets=0;
        //jogadores: vetor de 7 elementos: [levantador,libero,meia1,meia2,ponta1,ponta2,oposto]
        //só serão aceitos a inserção de jogadores já existentes neste vetor, por intermédio da Main
    }
    Time(string nometime,levantador &lev1,libero &lib1,meia &m1,meia &m2,ponta &p1,ponta &p2,oposto &o1){
        this->nometime=nometime;
        jogadores = new (nothrow) jogador*[7];
        lev=0,lib=0,mei=0,pont=0,opost=0;
        sets=0;
        inserelev(lev1);
        inserelib(lib1);
        inseremeias(m1,m2);
        inserepontas(p1,p2);
        insereoposto(o1);
    }
    void inserelev(levantador &lev1){jogadores[0]=&lev1;lev=1;}
    void inserelib(libero &lib1){jogadores[1]=&lib1;lib=1;}
    void inseremeias(meia &m1,meia &m2){jogadores[2]=&m1,jogadores[3]=&m2;mei=1;}
    void inserepontas(ponta &p1,ponta &p2){jogadores[4]=&p1,jogadores[5]=&p2;pont=1;}
    void insereoposto(oposto &o1){jogadores[6]=&o1;opost=1;}
    void resetset(){sets=0;}
    void ganhouset(){sets++;}
    int getset(){return sets;}
    int pegarHabilidadeTotal(){
        if(lev==0||lib==0||mei==0||pont==0||opost==0){return -1;}
        else{
        somahabil=0;
        for(int i=0;i<=6;i++)
        {
            somahabil+=jogadores[i]->gethabil();
        }
        return somahabil;
        }
    }
    string getnome(){return nometime;}
};

class set{
private:
    int p1,p2,habil1,habil2;
    double x;
    float time1recebe,time2recebe;
public:
    set(){p1=0;p2=0;cout<<"construtor"<<endl;}
    void defineprob(Time &t1, Time &t2){
        habil1=t1.pegarHabilidadeTotal();
        habil2=t2.pegarHabilidadeTotal();
        time1recebe = (habil1*1.25)/(habil1*1.25+habil2);//prob time 1 ganhar qdo recebe
        time1recebe = time1recebe*10000;
        time1recebe = (int)time1recebe;
        time2recebe = (habil1)/(habil2*1.25+habil1);     //prob time 1 ganhar qdo time 2 recebe
        time2recebe = time2recebe*10000;
        time2recebe = (int)time2recebe;
    }
    int getprob1recebe(){return time1recebe;}
    int getprob2recebe(){return time2recebe;}
    int getp1(){return p1;}
    int getp2(){return p2;}
    void aumentap1(){p1++;}
    void aumentap2(){p2++;}
    void set_x(double x){this->x=x;}
    double get_x(){return x;}

    virtual void go(Time &t1, Time &t2){
        defineprob(t1,t2);

        while(1){
            //time 1 começa recebendo, com o 25% bonus
            x=rand()%10000+1; //numero aleatorio entre 1 e 10000
            if(x<=time1recebe){aumentap1();}
            else{aumentap2();}
            cout<<"Placar =  "<<t1.getnome()<<": "<<getp1()<<" "<<t2.getnome()<<" "<<getp2()<<endl;
            if(condvictory()==true){break;}

            //time 2 recebe depois
            x=rand()%10000+1; //numero aleatorio entre 1 e 10000
            if(x<=time2recebe){aumentap1();}
            else{aumentap2();}
            cout<<"Placar =  "<<t1.getnome()<<": "<<getp1()<<" "<<t2.getnome()<<" "<<getp2()<<endl;
            if(condvictory()==true){break;}
        }
            ganhouset(t1,t2);
   }

    virtual void ganhouset(Time &t1, Time &t2){

        if(getp1()>=getp2()){t1.ganhouset();cout<<"Vencedor do set: "<<t1.getnome()<<endl;}
        else{t2.ganhouset();cout<<"Vencedor do set: "<<t2.getnome()<<endl;}
        cout<<"Placar de sets: "<<t1.getnome()<<": "<<t1.getset()<<" "<<t2.getnome()<<" "<<t2.getset()<<endl<<endl;
    }

    virtual bool condvictory(){
        if(getp1()>=25||getp2()>=25){
            if(abs(getp1()-getp2())>=2){return true;}
            else{return false;}
                                    }
        else{return false;}
    }
};

class tiebreak:public set{
private:

public:
    tiebreak():set(){}

    void ganhouset(Time &t1, Time &t2){

        if(getp1()>=getp2()){t1.ganhouset();cout<<"Vencedor do tiebreak: "<<t1.getnome()<<endl;}
        else{t2.ganhouset();cout<<"Vencedor do tiebreak: "<<t2.getnome()<<endl;}
        cout<<"Placar de sets: "<<t1.getnome()<<": "<<t1.getset()<<" "<<t2.getnome()<<" "<<t2.getset()<<endl<<endl;
    }

    bool condvictory(){
        if(getp1()>=15||getp2()>=15){
            if(abs(getp1()-getp2())>=2){return true;}
            else{return false;}
        }
        else{return false;}
    }
};

class Partida{
private:
    set s1,s2,s3,s4;
    tiebreak tb;
public:
    bool realizar(Time *t1, Time *t2){
        if(t1->pegarHabilidadeTotal()==-1||t2->pegarHabilidadeTotal()==-1||t1==t2){return false;}
        else{
            //cout<<vencedor(*t1,*t2)<<endl;
            vencedor(*t1,*t2);
            return true;
        }
    }
    //string vencedor(Time &t1, Time &t2){
    void vencedor(Time &t1, Time &t2){
        if(&t1==&t2){cout<<"isso nunca será printado";}
        t1.resetset();t2.resetset();

        s1.go(t1,t2);
        s2.go(t1,t2);
        s3.go(t1,t2);
        if(t1.getset()!=3 && t2.getset()!=3){
            s4.go(t1,t2);
            if(t1.getset()==2 && t2.getset()==2){
                                                tb.go(t1,t2);
                                                }
                                            }
        else{
            }
    }

    string getwinner(Time &t1, Time &t2){
        if(t1.getset()==3){return t1.getnome();}
        if(t2.getset()==3){return t2.getnome();}
    }
};

int main(){
    
    srand((unsigned)time(NULL));

    levantador lev1("paulo",1,2,3,6);
    libero lib1("pedro",1,2,3,3);
    meia m1("jose",1,2,3,4),m2("gustavo",1,2,3,6);
    oposto o1("raul",1,2,3,2);
    ponta p1("gabriel",1,2,3),p2("guilherme",1,2,3);

    levantador lev2("paulo",1,2,3,5);
    libero lib2("pedro",1,2,3,0);
    meia m3("jose",1,2,3,1),m4("gustavo",1,2,3,3);
    oposto o2("raul",1,2,3,2);
    ponta p3("gabriel",1,2,3),p4("guilherme",1,2,3);

    Time t1("flamengo"),t2("fluminense",lev2,lib2,m3,m4,p3,p4,o2);
    t1.inserelev(lev1);
    t1.inserelib(lib1);
    t1.inseremeias(m1,m2);
    cout<<t1.pegarHabilidadeTotal()<<endl;

    t1.insereoposto(o1);
    cout<<t1.pegarHabilidadeTotal()<<endl;

    t1.inserepontas(p1,p2);
    cout<<t1.pegarHabilidadeTotal()<<endl;
    cout<<t2.pegarHabilidadeTotal()<<endl;
 
    Partida part1;

    if (part1.realizar(&t1,&t2)){cout<<"Vencedor da partida: "<<part1.getwinner(t1,t2);}
    cout<<endl;


    return 0;
}