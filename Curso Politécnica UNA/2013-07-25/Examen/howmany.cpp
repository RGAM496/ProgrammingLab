#include <iostream>
#include <cstdio>

using namespace std;

class Path{
public:
	int p[41];
	int c;
};

int n,r,k;
int cantformas;

void f(Path &p){
	if(p.c>=2*n+1){
		if(p.p[p.c-1] != 0){
			return;
		}
		int cantpicos=0;
		for(int i=1;i<2*n;i++){
			if( p.p[i-1]==k-1 && p.p[i+1]==k-1 && p.p[i]==k){
				cantpicos++;
			}
		}
		if(cantpicos==r){
			cantformas++;
			/*
			for(int i=0;i<p.c;i++){
				cout << p.p[i] << " ";
			}
			cout << endl;
			*/
		}
	}else{
		if( ( (double)(2*n-p.c) / (double)(p.p[p.c-1]) ) >= (double)1){
			Path pup=p;
			pup.p[pup.c] = pup.p[pup.c-1] + 1;
			pup.c++;
			f(pup);
		}
		if( p.p[p.c-1] > 0 ){
			Path pdwn=p;
			pdwn.p[pdwn.c]=pdwn.p[pdwn.c-1] -1;
			pdwn.c++;
			f(pdwn);
		}
	}
}

int main(int argc, char **argv){
	while(scanf("%d %d %d", &n, &r, &k) == 3){
		Path p;
		cantformas=0;
		for(int i=0;i<41;i++){
			p.p[i]=0;
		}
		p.c=1;
		f(p);
		cout << cantformas << endl;
	}
}