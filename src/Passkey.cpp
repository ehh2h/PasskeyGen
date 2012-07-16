/*
 * Passkey.cpp
 *
 *  Created on: 11-Jul-2012
 *      Author: shantanu
 */

#include "Passkey.h"
using namespace std;

class Passkey {

public:
	int flag;
	bool success;
	Passkey ();
	~Passkey ();
	void input (bool repeat);
	void createKey();

private:
	string pswd;
	string inp;
	unsigned int len;
	int shift;
	string numShift ();
	string wordShift ();
	string specialShift ();
	bool checkInput ();
	void flagMessage ();
	char solve (int o, int n, int m);
	void checkPassword();
	void generate ();
};

Passkey::Passkey () {

	cout <<"\n\n\n";

	bool proceed;

	ifstream file_I("./README.txt"); 			//Creating input buffer channel

	proceed = file_I.is_open();	   				//Checking file status

	if(!proceed) {
		cout<<"\n\nTerminating program!\n\nFATAL ERROR: Missing README file\n";
		cout<<"Assert abort\n\n";  				//Aborting execution; file missing
		assert(!true);
	}

	string line;
	while(getline(file_I, line)) {
		cout<<line<<"\n";		   				//Display README.txt
	}

	file_I.close();								//Destroying input buffer channel



}

Passkey::~Passkey () {

	cout<<"\n\n\n";

	if(!success) {
		cout << "Writing Password to the file failed.\nPlease try again\n";
		cout << "_______________________________________________________\n";
	}

	else {
		cout << "Writing Password to the file succeeded.\n";
		cout << "_______________________________________________________\n";
	}


}

void Passkey::createKey () {

	generate();									//Create a strong password

	bool proceed;

	ofstream file_O("./psky.txt");				//Creating output buffer channel

	proceed = file_O.is_open();

	if(!proceed) {
		cout<<"\n\nTerminating program!\n\nFATAL ERROR: Missing files\n";
		cout<<"Assert abort\n\n";  				//Aborting execution; file missing
		assert(!true);
	}

	file_O <<"PASSWORD: "<<pswd<<endl;			//Writing the password to psky.txt

	file_O.close();								//Destroying output buffer channel

	success = true;

}

void Passkey::input (bool repeat) {

	cout <<"\n\n";
	cout <<"Enter a world/sentence \n";
	getline (cin, inp);
	cin.clear();

	len = inp.length();

	cout <<"Enter a shift change number \n";
	cin >> shift;
	cin.clear();
	cin.ignore(100,'\n');						//Clear console

	bool proceed = checkInput ();				//Check input validity
	if(!proceed==true) {
		flagMessage();
	}

	if(repeat) return;							//Avoid multiple printing of confirmation

	cout <<"Values entered: "<<inp<<" and "<<shift<<endl;
}

bool Passkey::checkInput () {

	unsigned int count = 0;
	char res= ' ';

	if(len<8) {									//Checking length of input
		flag = 0;
		return false;
	}

	for (unsigned int i = 0; i < len; i++) {				//Checking if repetition is in limit

		count = 0;
		res = inp[i];

		for (unsigned int j = i; j <len; j++) {			//Secondary loop counting repetitions
			if(res==inp[j]) count+=1;
		}

		if(count >= len/2) {					//Analyzing if repetition is in limit
			flag = 1;
			return false;
		}
	}

	string rev = "";

	for (unsigned int i = 0; i < len; i++) {

		if ( inp[i] != ' ' ) rev+= pswd[i];
	}

	inp = rev;

	return true;
}

void Passkey::flagMessage () {

	if (flag == 0)
		cout <<"Length of string less than 8, optimum security not possible\nPlease re-enter\n\n";
	if (flag == 1)
		cout <<"Too many character repeated in string, passkey prone to be of weak security, Please re-enter\n\n";

	input(true);								//Resolving Input Errors
}

char Passkey::solve (int o, int n, int m) {

	char org= (char) o;
        char nex= (char) n; 			 		//Original Word and modified word


	char res= nex; 								//Store resolved character
	int bench_l = 0; int bench_u = 0;  			//Store limits for the type case of original character

	if(islower(org)) bench_l= 97;				//Determining lower limit
	else bench_l = 65;
	bench_u = bench_l+25;	     				//Determining upper limit

	if(n<bench_l || n>bench_u) {		 		//Determining if the modified word faults the limit

	if(shift>0) n-=26;			  				//Reevaluating the variable according to the shift value
	else n+=26;

	res = (char) n;			   					//Converting & storing new value to character
	}

	return res;     							//Returning resolved character
}

string  Passkey::wordShift () {

	string wordKey= ""; 						//Reserved for decoded string
	char res=' '; 								//Reserved for characters of original string
	//srand ( time(NULL) );						//Set new random value according to time
	int modValue = 0;					 		//Generate random modification value in range

	for (unsigned int i=0; i<len; i++) {

	modValue = rand() % shift;
	res= inp[i];			        			//Storing current character

	if(!isalpha(res))							//Leaving unchanged if special character is encountered
	{wordKey= wordKey+res; continue;}

	res= (char)(res+modValue);					//Modifying character according to the shift value
	res= solve((int)inp[i],(int)res,modValue);	//Resolving errors if encountered

	wordKey= wordKey+res;						//Concatenating the decoded character to the decoded string
	}

	return wordKey;
}

string Passkey::numShift () {

	unsigned int min = 0;

	if(shift <= 3)								//Defining minimum quantity of numbers to be appended
		min = 3;
	else
		min = shift/2+1;						//Defining numbers to be appended

	int exc = shift - 7;
	if (exc > 0) min = 7;						//Checking limit of numbers being appended

	string arr [] = {"0","1","2","3","4","5","6","7","8","9"};

	//srand ( time(NULL) );
	int genKey = rand() % 10;					//Random start point in the array
	int genInc = rand() % 4;					//Random increment value for array
	if (genInc==0) genInc+=1;

	string numKey = "";

	while (numKey.length()!= min) {				//Appending random numbers
		numKey+= arr[genKey];
		genKey +=genInc;
		if (genKey > 9) genKey-=9;
	}

	return numKey;
}

string Passkey::specialShift () {

	int count = 0;
	for (unsigned int i = 0; i < len; i++) {				//Checking for any special character that are present
		if (!isalpha(inp[i])) count+=1;
	}

	string arr[] = {"!","@","#","/","&"};		//Defining a list of special characters widely accepted
	string specialKey = "";


	if (count==0) {
		specialKey+= arr[rand() % 5];			//Generating a special character randomly from the list
	}

	return specialKey;
}

void Passkey::checkPassword () {

	int count = 0;
	unsigned int l = pswd.length();

	for (unsigned int i =0; i < l; i++) {				//Precautionary check of special character length

		if(!isalpha(pswd[i])) count+=1;
	}

	if(count == 0) pswd +=  "@";				//If faults, append a standard special character

	count = 0;

	for (unsigned int i =0; i < l; i++) {				//Checking presence of upper-case character
		if(isupper(pswd[i]))
			count+=1;
	}

	if(count == 0) {							//If faults, morph one character to an upper case
		pswd[3] = toupper(pswd[3]);
		pswd[4] = tolower(pswd[4]);
	}
}

void Passkey::generate () {

	pswd = "";									//Intializing empty string to store password

	pswd += wordShift();						//Adding words to the password
	pswd += specialShift();						//Adding special character to the password
	pswd += numShift();							//Adding numbers to the password

	checkPassword();							//Making sure the password is strong
}

int main () {

	Passkey Password;							//Creating an object of the class
	Password.input (false);						//Taking input for the first time, hence repeat is set to false
	Password.createKey ();						//Generating and writing the password to a file

}


