#include <iostream>

using namespace std;

int main(int argc, char** argv){
	int n,d;
	int alarr[100];
	cin >> n; cin>>d;
	while(d!=0){
		for(int alu=0;alu<n;alu++){
			alarr[alu] = 1;
		}
		for(int dinner=0;dinner<d;dinner++){
			for(int alu=0;alu<n;alu++){
				int aux;
				cin >> aux;
				alarr[alu] = alarr[alu] & aux;
			}
		}
		int ban=0;
		for(int alu=0;alu<n;alu++){
			if(alarr[alu]==1){
				cout << "yes" << endl;
				ban=1;
				break;
			}
		}
		if(!ban)
			cout << "no" << endl;
		cin >> n; cin>>d;
	}
	return 0;
}