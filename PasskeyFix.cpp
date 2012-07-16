#include "world.h"

using namespace std;

string checkSpace (string inp) {

	string res = "";

	bool flag = false;
	unsigned int len = inp.length();
	char ch = ' ';

	for (unsigned int i = 0; i <= len; i++) {

	cout <<"CHARACTER: "<<inp[i]<<"\n";
	ch = inp[i];

	if(ch == ' ') {
	flag = true;
	break;
	}
	//if(flag) break;
	}

	cout <<"REACHED FIRST RETURN\n";

	if(!flag) return inp;

	for (int i = 0; i <= len; i++) {

	cout<<"CHARACTER: "<<inp[i]<<"\n";
	if(inp[i] != ' ')
		cout <<"CHARACTER ADDED: "<<inp[i]<<"\n";
		res+=inp[i];
	}

	cout <<"REACHED SECOND RETURN\n";
	//inp = res;
	return res;
}


int main () {

	string inp= "Hello";

	string jnp= "Hello World";

	string knp= "Hello! World";

	cout<<checkSpace(inp)<<"\n\n";
	cout<<checkSpace(jnp)<<"\n\n";
	cout<<checkSpace(knp)<<"\n\n";

	return 0;

	}
