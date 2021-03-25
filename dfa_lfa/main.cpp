#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

ifstream in("lfa_in");
ofstream out("lfa_out");

struct noduri{
    int nr = 0;
    int adiacente[1000];
    char muchii[1000];
};

noduri v[100000];
int drum[100000];
int fin[100000];

int nr_stari_finale;
bool cautare_init(int el){
    for(int i=0;i<nr_stari_finale;i++)
        if(fin[i] == el) return true;
    return false;
}

void verifica(int init, int poz, char s[], bool &ok){
    if(s[poz] == '\0'){
        if(cautare_init(init) == true){
            drum[poz] = init;
            ok = true;
        }
        else ok = false;
    }
    else{
        char w = s[poz];
        int p = 0;
        for(int i=0;i<v[init].nr;i++)
            if(v[init].muchii[i] == w){
                int urm = v[init].adiacente[i];
                verifica(urm, poz+1, s, ok);
                if(ok == true) drum[poz] = init;
                p++;
            }
            if(!p){
                ok = false;
                return;
            }
    }
}

void mesaj(int nr_test,int p, int l){
    out<<"Cuvantul "<<nr_test+1<<'\n';
    if(p == true)
        {   out<<"DA"<<'\n';
            out<<"TRASEU: ";
            for(int i=0;i<=l;i++)
                out<<drum[i]<<" ";
            out<<'\n';
    }else{
        out<<"NU"<<'\n';
    }
}

int main(){
   int nr_noduri, nr_muchii;
   in>>nr_noduri>>nr_muchii;
   int n1,n2;
   char c;
   for(int i=0;i<nr_muchii;i++){
        in>>n1>>n2;
        in.get();
        in>>c;
        v[n1].adiacente[v[n1].nr] = n2;
        v[n1].muchii[v[n1].nr] = c;
        v[n1].nr++;
   }
    int stare_init;
    in>>stare_init;
    in>>nr_stari_finale;
    for(int i=0;i<nr_stari_finale;i++) in>>fin[i];
    int nr_cuvinte;
    in>>nr_cuvinte;
    in.get();
    for(int i=0;i<nr_cuvinte;i++){
        char cuvant[100];
        in.getline(cuvant,100);
        bool ok = false;
        verifica(stare_init,0,cuvant,ok);
        mesaj(i,ok,strlen(cuvant));
    }
    return 0;
}
