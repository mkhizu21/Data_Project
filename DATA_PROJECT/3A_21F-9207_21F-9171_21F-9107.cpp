#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<cstdio>
#include<Windows.h>
#include"implementations.h"
using namespace std;

int main() {//MAIN FUNCTION
	Trie_tree obj_trie;
	Huffman obj_huff;
	int option = 0;
	string opt = "";//VARIABLE DECLARATIONS

	animation();//ANIMATION FUNCTION CALL
	do {//SELECTION OF MODE
		system("cls");
		cout << "Select Screen Mode!" << endl << endl;
		cout << "1) Light Mode" << endl;
		cout << "2) Dark Mode" << endl;
		cout << "Enter Here : ";
		cin >> opt;
	} while (opt > "2" || opt < "1");
	if (opt == "1") {
		system("color 70");
	}
	else {
		system("color 07");
	}

	if (obj_trie.load_trie_tree("dictionary")) {//MAIN MENU
		do {
			system("cls");
			cout << "Welcome To Text Editor In CPP!" << endl << endl;
			cout << "0) To Exit" << endl;
			cout << "1) To Enter Writing Mode" << endl;
			cout << "2) To Enter Display Mode" << endl;
			cout << "3) To Enter Deletion Mode" << endl;
			cout << "Enter Here : ";
			cin >> option;
			switch (option) {
			case 0: {
				system("cls");
				cout << "Thanks For Using The Program!" << endl;
				exit(0);
				break;
			}
			case 1: {
				string opt = "";

				do {
					system("cls");
					cout << "Welcome To Writing Mode!" << endl << endl;
					cout << "Please Select The Mode!" << endl;
					cout << "0) Write In The Saved File" << endl;
					cout << "1) Write In the New File" << endl;
					cout << "2) To Exit" << endl;
					cout << "Enter Here : ";
					cin >> opt;
					if (opt < "0" || opt > "2") {
						cout << "Invalid Input!" << endl;
						system("pause");
					}
				} while (opt < "0" || opt > "2");
				if (option == 2) {
					break;
				}
				else write_mode(obj_huff, obj_trie, option);
				break;
			}
			case 2: {
				cout << "Welcome To Display Mode!" << endl << endl;
				display_mode(obj_huff);
				break;
			}
			case 3: {
				deletion_mode();
				break;
			}
			}
		} while (true);
	}
	else {
		cout << "Suggestions Loading Error!" << endl;
	}

	system("pause");
	return 0;
}