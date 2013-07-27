#include <iostream>
#include <cstdio>
#include <set>


using namespace std;


#define MXSIZE 1000000
#define PSIZE 100000

bool numeros[MXSIZE];
long long primos[PSIZE];
set <long long> setprimos;
set<long long>::iterator it;

int main(int argc, char **argv){

	long long n,c,i,primo;
	
	for(i=2;i<MXSIZE;i++){
		numeros[i]=true;
	}
	int ban=1;
	
	primo=2;
	long long x;
	x=0;
	while(ban){
		
		for(i=2;i*primo<MXSIZE;i++){
			numeros[i*primo]=false;
			
		}
		//
		for(i=primo+1;i<=n;i++){
			if(numeros[i]==true){
				//cout << i <<" ";
				++x;
				primo=i;
				break;
			}
		}
		if(i>n) ban=0;
	}
	cout << x <<" ";
	
	
	long long count=1;
	primos[0]=1;
	for(i=2;i<=n;i++){
		if(numeros[i]==true){
			primos[count]=i;
			setprimos.insert(i);
			count++;
		}
	}
	
	cout << "count:"<<count<<endl;
	cin >> n;
	long long val;
	
	while(n){
		ban=0;
		cout<<n<<":"<<endl;
		for(i=2;i<count;i++){
			cout << " no: "<< primos[i] << "+" << val ;
			val=n-primos[i];
			if(val<primos[i])
				break;
			it=setprimos.find(val);
			if(it != setprimos.end()){
				cout << primos[i] << "+" << val << endl;
				ban=1;
				break;
			}
		}
		if(ban==0){
			cout <<"NO WAY!"<< endl;
		}
		cin >> n;
	}
	return 0;
}