#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include <cstring>
using namespace std;

void temp(char* argv[], int size);

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "finnish");
	string searchFrom;
	string searchWith;
	int counter = -1;
	int x = 0;
	int lineLenght = 0;
	int searchLenght = 0;
	string line;
	switch (argc) {
	case 1: {
		cout << "Give a string from which to search for: ";
		getline(cin, searchFrom);
		cout << "Give search string: ";
		getline(cin, searchWith);

		size_t found = searchFrom.find(searchWith);
		if (found != string::npos) {
			cout << '"' << searchWith << '"' << " found in " << '"' << searchFrom << '"' << " in position " << found << "." << endl;
		}
		else {
			cout << '"' << searchWith << '"' << " not found in " << '"' << searchFrom << '"';
		}
		const char* arr = searchWith.c_str();
		x = found; // Tarkista löytyykö matcheja
		while (counter < x) { // Jos matcheja löytyy näytetään ne kaikki
			found = searchFrom.find(arr, found + 1);
			if (found != string::npos) {
				cout << '"' << searchWith << '"' << " found in " << '"' << searchFrom << '"' << " in position " << found << "." << endl;
			}
			else {
				x = counter + 1;
				counter++;
			}
		}
		break;
	}
	case 2: {
		cout << "Too few command line arguments!";
		break;
	}
	case 3: {
		searchWith = argv[1];
		string fileName = argv[2];
		int counter2 = 0;
		ifstream ReadFile(fileName);
		if (ReadFile.is_open()) {
			while (getline(ReadFile, line)) {
				size_t found = line.find(searchWith);
				if (found != string::npos) {
					cout << line << endl;
					counter2 = 1;
				}
			}
			if (counter2 == 0) {
				cout << '"' << searchWith << '"' << " not found in " << '"' << fileName << '"' << " at any position." << endl;
			}
			ReadFile.close();
		}
		else {
			cout << "Could not find out the size of file " << '"' << fileName << '"' << endl;
		}
		break;
	}
	case 4: {
		temp(argv, 4);
		break;
	}
	default:
		cout << "Too many command line arguments!";
	}
	return EXIT_SUCCESS;
}


void temp(char* argv[], int size) {
	string option = argv[1]; // Otetaan käyttäjän antama asetus muuttujaan
	option = option.erase(0, 2); // Poistetaan asaetuksesta -o osuus
	string searchWith = argv[2]; // Otetaan käyttäjän antama hakusana muuttujaan
	string fileName = argv[3]; // Otetaan käyttäjän antama tiedostonimi
	int lineLenght = 0;

	bool lines = false;
	bool occurances = false;
	bool reverse = false;
	bool insensitive = false;

	// Tarkistaa löytyykö hakuasetuksesta mitkä kirjaimet...
	size_t foundL = option.find('l');
	size_t foundO = option.find('o');
	size_t foundR = option.find('r');
	size_t foundI = option.find('i');

	// ... ja muuttaa kunki löydetyn kirjaimen bool muuttujan trueksi
	if (foundL != string::npos) {
		lines = true;
	}

	if (foundO != string::npos) {
		occurances = true;
	}

	if (foundR != string::npos) {
		reverse = true;
	}

	if (foundI != string::npos) {
		insensitive = true;
	}

	string line;
	int counter3 = 0;
	int lineCounter = 0;
	int foundCounter = 0;
	if (option != "") { // Tarkistaa ettei käyttäjän antama asetus ole liian lyhyt
		ifstream ReadFile(fileName);
		if (ReadFile.is_open()) {
			while (getline(ReadFile, line)) {
				if (insensitive) { // Tapahtuu jos hakuasetuksessa on I
					lineLenght = line.length();
					char* lineArray = new char[lineLenght + 1];
					// Muuta jokanen line char arrayks
					strcpy_s(lineArray, line.size() + 1, line.c_str());

					// Muuta char array lowercaseen
					for (int i = 0; i < lineLenght; i++) {
						lineArray[i] = tolower(lineArray[i]);
					}
					// Muuta yhden linen char array takas stringiksi
					string go = "";
					for (int i = 0; i < lineLenght; i++) {
						go = go + lineArray[i];
					}
					string searchWithTemp = searchWith;
					// Muuta searchWith lowercaseen
					std::for_each(searchWithTemp.begin(), searchWithTemp.end(), [](char& c) {
						c = ::tolower(c);
						});
					// Sama vanha haku
					size_t found = go.find(searchWithTemp);
					lineCounter++;
					if (reverse) { // Tapahtuu jos hakuasetuksessa on I ja R
						if (lines) { // Tapahtuu jos hakuasetuksessa on I, R ja L
							if (found == string::npos) {
								cout << lineCounter << ":\t" << line << endl;
								foundCounter++;
								counter3 = 1;
							}
						}
						else { // Tapahtuu jos hakuasetuksessa on I ja R
							if (found == string::npos) {
								cout << line << endl;
								foundCounter++;
								counter3 = 1;
							}
						}
					}
					else {
						if (lines) { // Tapahtuu jos hakuasetuksessa on I ja L
							if (found != string::npos) {
								cout << lineCounter << ":\t" << line << endl;
								foundCounter++;
								counter3 = 1;
							}
						}
						else { // Tapahtuu jos hakuasetuksessa on I
							if (found != string::npos) {
								cout << line << endl;
								foundCounter++;
								counter3 = 1;
							}
						}
					}
				}
				else { // Tapahtuu jos hakuasetuksessa ei ole I
					size_t found = line.find(searchWith);
					lineCounter++;
					if (reverse) { // Tapahtuu jos hakuasetuksessa on R
						if (lines) { // Tapahtuu jos hakuasetuksessa on R ja L
							if (found == string::npos) {
								cout << lineCounter << ":\t" << line << endl;
								foundCounter++;
								counter3 = 1;
							}
						}
						else { // Tapahtuu jos hakuasetuksessa on R
							if (found == string::npos) {
								cout << line << endl;
								foundCounter++;
								counter3 = 1;
							}
						}
					}
					else { // Tapahtuu jos hakuasetuksessa ei ole I tai R
						if (lines) { // Tapahtuu jos hakuasetuksessa on L
							if (found != string::npos) {
								cout << lineCounter << ":\t" << line << endl;
								foundCounter++;
								counter3 = 1;
							}
						}
						else { // Tapahtuu jos hakuasetuksessa ei ole I, R tai L
							if (found != string::npos) {
								cout << line << endl;
								foundCounter++;
								counter3 = 1;
							}
						}
					}
				}
			}
			if (counter3 == 0) { // Tapahtuu jos hakusanaa ei löydy koko tiedostosta
				cout << '"' << searchWith << '"' << " not found in " << '"' << fileName << '"' << " at any position." << endl;
			}
			if (occurances) { // Tapahtuu jos hakuasetuksessa on O
				if (reverse) { // Tapahtuu jos hakuasetuksessa on R ja O
					cout << endl << "Occurrences of lines NOT containing " << '"' << searchWith << '"' << ":" << " " << foundCounter << endl;
				}
				else { // Tapahtuu jos hakuasetuksessa on O
					cout << endl << "Occurrences of lines containing " << '"' << searchWith << '"' << ":" << " " << foundCounter << endl;
				}
			}
		}
		else {
		cout << "Could not find out the size of file " << '"' << fileName << '"';
		}
	}
	else { // Jos käyttäjän antama asetus on liian lyhyt ilmoitetaan käyttäjälle
	cout << "Too few search arguments!" << endl;
}
}