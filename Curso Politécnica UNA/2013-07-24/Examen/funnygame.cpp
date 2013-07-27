#include <iostream>

using namespace std;

class Blown{ public:  int a[1000]; };

int graph[1000][1000];

int n,k;

int firstflight;

void treealizar(int nodo){
	for(int i=0;i<n;i++){
		if(graph[nodo][i]){
			graph[i][nodo]=0;
			treealizar(i);
		}
	}

}

int min(int act, Blown &b, int alfa, int beta);

int max(int act, Blown &b, int alfa, int beta){
	int res, max=-5, maxf;
	static int firsttime=1;
	for(int i=0;i<n;i++){
		if(graph[act][i] && !b.a[i]){
			Blown newb=b;
			newb.a[act]=1;
			res=min(i,newb,alfa,beta);
			
			if(res>beta)
				return res;
			if(res>alfa)
				alfa=res;
			if(max<res){
				max=res;
				maxf=i;
			}
		}
	}
	if(firsttime){
		firsttime=0;
		firstflight=maxf;
	}
	if(max==-5)
		return -1;
	return max;
}

int min(int act, Blown &b, int alfa, int beta){
	int res, min=5;
	for(int i=0;i<n;i++){
		if(graph[act][i] && !b.a[i]){
			Blown newb=b;
			newb.a[act]=1;
			res=max(i,newb,alfa,beta);
			
			if(res<alfa)
				return res;
			if(res<beta)
				beta=res;
			if(min>res)
				min=res;
		}
	}
	if(min==5)
		return 1;
	return min;
}



int main(int argc, char **argv){
	for(int i=0;i<1000;i++){
		for(int j=0;j<1000;j++){
			graph[i][j];
		}
	}
	cin >> n;
	cin >> k;
	
	for(int i=0;i<n-1;i++){
		int a,b;
		cin>>a;cin>>b;
		graph[a][b]=1;
		graph[b][a]=1;
	}
	
	Blown b;
	for(int i=0;i<1000;i++)
		b.a[i]=0;
	
	int res=max(k,b,-5,5);
	
	cout << res << firstflight;
	
	return 0;
}