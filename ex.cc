#include <iostream>
#include <vector>
#include <utility>

using namespace std;

using matrix = vector<vector<int>>;

vector<pair<int, int>> millores;
matrix classes;
int penalti;

void escriu(vector<int> out){
	cout << "{";
	for(int& a : out){
		cout << a << ", ";
	}
	cout << "}" << endl;
}

void swap(vector<int>& out, int& a, int& b){
	int c = out[a];
	out[a]=out[b];
	out[b]=c;
}

int penalitzacio(vector<int>& out){
	
	int C = out.size();
	int M = millores.size();
	int pen = 0;

	for(int i=0; i<M; i++){
		
		int mida = millores[i].second;
		int ce = millores[i].first;

		for(int j=0; j<C+mida; j++){
			// El vector out té les classes dels cotxes com a elementes del vector
			
			int n=0;
			// count
			for(int k=j-mida+1; k<=j; k++){
				bool dont=false;
				if(k<0) k=0;
				else if(k>=C) bool dont=true;

				// Contem els nombres de cotxes dins en un entorn de j;
				if(classes[out[k]][i+2]==1 and not dont) n=n+1;
			}
			// Si hi ha penalització, la sumem.
			if(n>ce) pen = pen + (n - ce);
		}
	}
}

void gen(vector<int>& out, int a, const int& C){
	for(int i=a+1; i<C; i++){
		swap(out, a, i);
		gen(out, a+1, C);
	}
	if(a==C and penalitzacio(out)<penalti){
		escriu(out);
	}
}

int main(){
	//               LLEGIM L'INPUT
	int C, M, K;
	// C cars, M millores, K classes
	cin >> C >> M >> K;
	millores = vector<pair<int, int>>(M);
	// Posem les millores en un vector de pairs.
	for(int i=0; i<M; i++){
		int a;
		cin >> a;
		millores[i]={a, 0};
	}
	for(int i=0; i<M; i++){
		int a;
		cin >> a;
		millores[i]={millores[i].first, a};
	}

	// M+2 es correspon a la part de booleans final 
	// més els dos numeros, el que defineix la classe 
	// i el que ens diu quants otxes haurem de fer
	classes = matrix(K, vector<int>(M+2));
	for(int i=0; i<K; i++){
		int a;
		cin >> a;  // Num. de la classe
		classes[i][0] = a;
		cin >> a;  // Num. de cotxes dins la classe
		classes[i][1] = a;
		for(int j=2; j<M+2; j++){
			cin >> a;  // Llegim i guardem els booleans
			classes[i][j] = a;
		}
	}

	// Definim un vector on tindrem l'output, la sortida de 
	// l'ordre dels cotxes i que serà sobre el que operarem. 
	// Cada cotxe serà descrit amb el número de la classe que espera tenir.
	vector<int> out;
	// Omplim el vector amb les diferents classes.
	for(int i=0; i<K; i++){
		int b = classes[i][1];
		for(int j=0; j<b; j++){
			out.push_back(i);
		}
	}

	//            COMENCEM L'EXHAUSTIVE SEARCH
	//Creem una funció que ens conti les penalitzacions, i un 
	// nombre que ens guardi la millor que tenim fins al moment.

	gen(out, 0, C);

	escriu(out);
}












