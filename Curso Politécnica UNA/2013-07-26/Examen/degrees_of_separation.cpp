#include <iostream>
#include <string>

#include <map>

using namespace std;

int graph[50][50];

int dupligraph[50][50];


map<string,int> namesmap;

int p,r;

int nameToInt(string &nombre){
	if(namesmap.find(nombre) == namesmap.end() ){
		namesmap[nombre]=namesmap.size();
	}
	return namesmap[nombre];
}

void breakConns(int nodo){
	for(int i=0;i<50;i++){
		if(dupligraph[nodo][i]){
			dupligraph[nodo][i]=0;
			dupligraph[i][nodo]=0;
		}
		breakConns(i);
	}
}

int conectado(){
	for(int i=0;i<50;i++){
		for(int j=0;j<50;j++){
			dupligraph[i][j]=graph[i][j];
		}
	}
	
	for(int i=0;i<50;i++){
		for(int j=0;j<50;j++){
			if( dupligraph[i][j] )
				return 0;
		}
	}
	return 1;
}

int main(int argc, char **argv){
	cin >> p; cin >> r;
	int network=0;
	while(p!=0){
		network++;
		//cout << p << " " << r;

		namesmap.clear();
		for(int i=0;i<50;i++){
			for(int j=0;j<50;j++){
				graph[i][j]=0;
			}
		}
		

		for(int i=0;i<r;i++){
			string nombre1,nombre2;
			int id1,id2;
			cin >> nombre1; cin >> nombre2;
			cout << nombre1 << " " << nombre2 << endl;
			id1=nameToInt(nombre1);
			id2=nameToInt(nombre2);
			graph[id1][id2]=1;
			graph[id2][id1]=1;
		}
		
	
		if(!conectado()){
			cout << "Network " << network << " DISCONNECTED" << endl;
			continue;
		}
		
		cout << "Network " << network<< " CONECTED" << endl;
		
		
		cin >> p; cin >> r;
	}
}