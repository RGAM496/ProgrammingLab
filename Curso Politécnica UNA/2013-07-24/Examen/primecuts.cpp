#include <iostream>
#include <cstdio>


using namespace std;

bool numeros[1000];
int primos[300];

int main(int argc, char **argv){

	int n,c,i;
	int sfr;
	//cin >> n >> c;
	
	while(2==scanf("%d %d", &n, &c)){
		if(n==1){
			cout << n << " " << c << ": 1" << endl << endl;
			//return 1;
		}else{
			for(i=2;i<=n;i++){
				numeros[i]=true;
			}
			int primo=2,ban=1;
			
			while(ban){
				for(i=2;i*primo<=n;i++){
					numeros[i*primo]=false;
				}
				for(i=primo+1;i<=n;i++){
					if(numeros[i]==true){
						primo=i;
						break;
					}
				}
				if(i>n) ban=0;
			}
			
			int count=1;
			primos[0]=1;
			for(i=2;i<=n;i++){
				if(numeros[i]==true){
					primos[count]=i;
					count++;
				}
			}
			int ini,fin;
			
			if(count%2 == 0){
				ini= count/2-c;  ////puede ser -1
				if(ini < 0) ini =0;
				fin=count/2+c;
				if(fin>count) fin=count;
			}else{
				ini= count/2-c+1;  ////puede ser -1
				if(ini < 0) ini =0;
				fin=count/2+c;
				if(fin>count) fin=count;
			}
			cout << n << " " << c << ":";
			for(int i=ini;i<fin;i++){
				cout << " " << primos[i];
			}
			cout << endl << endl;
		}
	}
	return 0;
}