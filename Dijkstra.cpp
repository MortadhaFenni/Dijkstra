//Created at 19/11/2018
#include <iostream>
                                   
using namespace std;

int nbv, arv; //variable globale

bool verifierLeChemin(int V[][100], int *tI, int *tJ, int mem, int i, int j, bool VH){
	
	if(V[i][j] == 1 && (j == arv || i == arv))//condition d'arret
			return 1;
	
	if(i == j){
		return verifierLeChemin(V, tI, tJ, mem, i+1, j, 1);
	}
	else{
		if(VH==1){
			for(int v = 0; v < nbv; v++){
				if(i == tI[v])
					return verifierLeChemin(V, tI, tJ, mem, i+1, j, 1);
			}
		}
		else{
			for(int v = 0; v < nbv; v++){
				if(j == tJ[v])
					return verifierLeChemin(V, tI, tJ, mem, i, j+1, 0);
			}
		}
		if(i >= nbv){//condition d'arret
			return 0;
		}
		if(V[i][j] == 0){
			if(VH==1){
				return verifierLeChemin(V, tI, tJ, mem, i+1, j, 1);
			}
			else{
				return verifierLeChemin(V, tI, tJ, mem, i, j+1, 0);
			}
		}
		else{
			if(VH==1){
				tI[mem] = i;
				if(verifierLeChemin(V, tI, tJ, mem+1, i, 0, 0)){
					return 1;
				}
				else{
					for(int x = mem; x < nbv; x++){
						tI[x] = -1;
					}
					return verifierLeChemin(V, tI, tJ, mem, i+1, j, 1);
					
				}
			}
			else{
				tJ[mem] = j;
				if(verifierLeChemin(V, tI, tJ, mem+1, j, 0, 0))
					return 1;
				else{
					for(int x = mem; x < nbv; x++){
						tJ[x] = -1;
					}
					return verifierLeChemin(V, tI, tJ, mem, i, j+1, 0);
				}
			}
		}
	}
}

int main(){
	
	int V[100][100];
	int dep;
	
	do{//interdire a l'utilisateur d'entrer moins de deux villes et des nbr negatif 
		cout<<"\nDonnez le nombre de villes : ";
		cin>>nbv;
		if(nbv <= 1 || nbv<0)
			cout<<"\n<!> Donnez un nombre superieure a 1 <!>\n";
	}while(nbv <= 1 || nbv<0);
	
	int *tabI = new int[nbv], *tabJ = new int[nbv];

	//remplissage de matrice
	for(int i = 0; i < nbv; i++){
		for(int j = 0; j <= i; j++){
			if(i == j){
				V[i][j] = 0;
			}
			else{
				cout<<"\nUn lien entre la ville "<<j+1;
				cout<<" et la ville "<<i+1;
				cout<<" ? (1->oui / 0->non) : ";
				cin>>V[i][j];
			}
		}
	}
	//l'affichage de matrice
	for(int i=0;i<nbv;i++){
		for(int j=0;j<=i;j++){
			cout<<V[i][j]<<"\t";
		}
		cout<<"\n";
	}
	
	do{//interdire a l'utilisateur d'entrer des valeur negatif ou seperieur a nbv
	cout<<"\nLa ville de depart : ";
	cin>>dep;
	dep--;
	if(dep >= nbv || dep<0)
		cout<<"\n<!> La ville n'est pas lister ressayer <!>\n";
	}while(dep >= nbv || dep<0);
	
	do{//interdire a l'utilisateur d'entrer des valeur negatif ou seperieur a nbv
	cout<<"\nLa ville d'arrive : ";
	cin>>arv;
	arv--;
	if(arv >= nbv || dep<0)
		cout<<"\n<!> La ville n'est pas lister ressayer <!>\n";
	}while(arv >= nbv || dep<0);
	
	//c'est pour faciliter de stocke les villes et affiche
	for(int i = 0; i < nbv; i++){
		tabI[i] = -1;
		tabJ[i] = -1;
	}
	
	
	if(verifierLeChemin(V, tabI, tabJ, 0, dep, 0, 0)==1){
		cout<<"\nIl existe un chemin ";
		if(V[dep][arv] || V[arv][dep]){
			cout<<"#direct entre la ville "<<dep+1<<" et la ville "<<arv+1<<endl;
		}
		else{
			cout<<"#entre la ville "<<dep+1<<" et la ville "<<arv+1<<" en passent par :\n";
			for(int x = 0; x < nbv; x++){
				if(tabI[x]==dep){
					tabI[x]=-1;
				}
				if(tabJ[x]==dep){
					tabJ[x]=-1;
				}
				if(tabI[x]==dep+1){
					 if(V[arv][dep+1]!=1){
					 	tabI[x]=-1;
					 }
				}
				if(tabJ[x]==dep+1){
					if(V[arv][dep+1]!=1){
					 	tabJ[x]=-1;
					 }
				}
				if(tabI[x] != (-1)){
					if(tabI[x]==tabJ[x+2]){
						tabI[x+1]=-1;
						tabJ[x+2]=-1;
					}
				}
				else if(tabJ[x] != (-1)){
					if(tabJ[x]==tabI[x+2]){
						tabJ[x+1]=-1;
						tabI[x+2]=-1;
					}
				}
			}
			for(int x=0;x<nbv;x++){
				if(tabI[x] != (-1))
					cout<<"-La ville "<<tabI[x]+1<<endl;
				if(tabJ[x] != (-1))
					cout<<"-La ville "<<tabJ[x]+1<<endl;
			}
		}
		cout<<"Bonne route ! (^^)"<<endl;
	}
	else{
		cout<<"\nIl n'existe pas de chemin entre la ville ";
		cout<<dep+1<<" et la ville "<<arv+1<<endl;
		cout<<"A la prochaine ! (^^)"<<endl;
	}

	delete []tabI;
	delete []tabJ;
	return 0;
}
