#pragma once
#pragma warning(suppress : 4996)
#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<cstdio>
#include<Windows.h>
#include"prototypes.h"
using namespace std;

//ALL CLASSES AND FUNCTIONS IMPLEMENTATIONS

//HUFF NODE FUNCTIONS AND CONSTRUCTORS
Huff_node::Huff_node() {
	data = counter = 0;
	next = left = right = NULL;
	code_str = "";
}

//HUFFMAN TREE FUNCTIONS AND CONSTRUCTORS
void Huffman::assign_code(Huff_node* current, string str) {
	if (current != NULL) {
		if (current->left == NULL && current->right == NULL) {
			current->code_str = str;
		}
		assign_code(current->left, str + '0');
		assign_code(current->right, str + '1');
	}
}
void Huffman::inorder(Huff_node* current) {
	if (current != NULL) {
		inorder(current->left);
		cout << current->data << " " << current->counter << " " << current->code_str << endl;
		inorder(current->right);
	}
}
Huff_node* Huffman::delete_huff(Huff_node* current) {
	if (current != NULL) {
		current->left = delete_huff(current->left);
		current->right = delete_huff(current->right);
		delete current;
		current = NULL;
		return current;
	}
	else return NULL;
}
void Huffman::encode_alpha(char alpha, Huff_node* current, string& code) {
	if (current != NULL) {
		if (current->data == alpha) {
			code = current->code_str;
		}
		else {
			encode_alpha(alpha, current->left, code);
			encode_alpha(alpha, current->right, code);
		}
	}
}
void Huffman::decode_alpha(Huff_node* curr, string coded_str, string& uncoded, int& index) {
	if (curr == NULL) {
		return;
	}
	if (curr->left == NULL && curr->right == NULL)
	{
		uncoded += curr->data;
		return;
	}

	if (coded_str[index] == '0')
	{
		index += 1;
		decode_alpha(curr->left, coded_str, uncoded, index);
	}
	else
	{
		index += 1;
		decode_alpha(curr->right, coded_str, uncoded, index);
	}
	return;
}
void Huffman::store_encoded(string& coded_str, string file_name) {
	file_name += "compressed.txt";
	ofstream fout(file_name);
	fout << coded_str;
}
bool Huffman::retrieve_encoded(string& code_str, string file_name) {
	file_name += "compressed.txt";
	ifstream fin(file_name);

	if (fin.is_open()) {
		int counter = 0;
		char temp;

		while (!fin.eof()) {
			fin >> temp;
			counter++;
		}
		fin.close();
		if (counter > 1) {
			fin.open(file_name);
			fin >> code_str;
			fin.close();
			return true;
		}
	}
	else return false;
}
bool Huffman::is_empty() {
	return (front == NULL);
}
Huff_node* Huffman::get_top() {
	return front;
}
void Huffman::make_huff() {
	Huff_node* l = NULL, * r = NULL, * temp = NULL;
	int sum = 0;

	if (is_empty()) {
		return;
	}
	while (front->next != NULL) {
		temp = get_top();
		r = new Huff_node;
		l = new Huff_node;
		l->data = temp->data;
		l->counter = temp->counter;
		l->left = temp->left;
		l->right = temp->right;
		l->next = NULL;
		dequeue();
		temp = get_top();
		r->data = temp->data;
		r->counter = temp->counter;
		r->left = temp->left;
		r->right = temp->right;
		r->next = NULL;
		dequeue();
		sum = l->counter + r->counter;
		enqueue('\0', sum, l, r);
	}
	assign_code(front, "");
}
void Huffman::enqueue(char value, int num, Huff_node* l, Huff_node* r) {
	Huff_node* temp = new Huff_node;

	temp->data = value;
	temp->counter = num;
	temp->right = r;
	temp->left = l;
	if (is_empty()) {
		front = temp;
	}
	else {
		Huff_node* current = front;

		while (current->next != NULL && current->next->counter <= num) {
			current = current->next;
		}
		if (current->counter > num)
		{
			temp->next = current;
			front = temp;
			current = temp;
		}
		else
		{
			temp->next = current->next;
			current->next = temp;
		}
	}

}
void Huffman::dequeue() {
	if (is_empty()) {
		return;
	}
	else {
		Huff_node* current = front;

		front = front->next;
		delete current;
		current = NULL;
	}
}
void Huffman::delete_tree() {
	front = delete_huff(front);
}
void Huffman::make_list(string str) {
	int* arr = new int[30];
	for (int i = 0; i < 30; i++) {
		arr[i] = 0;
	}
	alphabet_counter(str, arr);

	for (int i = 0; i < 30; i++) {
		if (arr[i] != 0) {
			if (i == 26) {
				enqueue(' ', arr[i], NULL, NULL);
			}
			else if (i == 27) {
				enqueue('.', arr[i], NULL, NULL);
			}
			else if (i == 28) {
				enqueue(',', arr[i], NULL, NULL);
			}
			else if (i == 29) {
				enqueue('?', arr[i], NULL, NULL);
			}
			else {
				int temp = int_to_char(i);
				enqueue(temp, arr[i], NULL, NULL);
			}
		}
	}
}
void Huffman::store_encryption(string file_name) {
	file_name += "code.txt";
	ofstream fout(file_name);
	Huff_node* current = front;

	while (current != NULL) {
		if (current->data == ' ') {
			fout << '!';
		}
		else {
			fout << current->data;
		}
		fout << current->counter;
		current = current->next;
	}
	fout.close();
}
bool Huffman::retrieve_encryption(string file_name) {
	file_name += "code.txt";
	ifstream fin(file_name);

	if (fin.is_open()) {
		char alpha;
		int num = 0;
		char temp;

		while (!fin.eof()) {
			fin >> temp;
			num++;
		}
		fin.close();
		if (num > 1) {
			fin.open(file_name);
			while (!fin.eof()) {
				fin >> alpha;
				if (alpha == '!') {
					alpha = ' ';
				}
				fin >> num;
				enqueue(alpha, num, NULL, NULL);
			}
			fin.close();
		}
		return true;
	}
	else {
		return false;
	}
}
void Huffman::encode_str(string& str) {
	string code_str = "", temp;

	for (int i = 0; i < str.length(); i++) {
		temp = "";
		encode_alpha(str[i], get_top(), temp);
		code_str += temp;
	}
	str = code_str;
}
void Huffman::decode_str(string& str) {
	string temp = "";
	int i = 0;

	while (i < str.length()) {
		decode_alpha(get_top(), str, temp, i);
	}
	str = temp;
}
Huffman::Huffman() {
	front = nullptr;
}
void Huffman::display() {
	if (is_empty()) {
		cout << "Tree Is Empty!" << endl;
	}
	else {
		cout << "Displaying The Huffman Tree ::" << endl << endl;
		inorder(front);
	}
}
void Huffman::store_data(string file, string data) {
	make_list(data);
	store_encryption(file);
	make_huff();
	encode_str(data);
	store_encoded(data, file);
	delete_tree();
}
string Huffman::retrieve_data(string file) {
	string str;

	if (retrieve_encryption(file)) {
		make_huff();
		if (retrieve_encoded(str, file)) {
			decode_str(str);
			delete_tree();
			return str + " ";
		}
		else {
			return "";
		}
	}
	else {
		return "";
	}
}

//TRIE NODE FUNCTIONS AND CONSTRUCTORS
Trie_node::Trie_node() {
	leaf = false;
	for (int i = 0; i < 26; i++) {
		next[i] = NULL;
	}
}

//TRIE TREE FUNCTIONS AND CONSTRUCTORS
void Trie_tree::pre_order(Trie_node* n, string& word, string*& arr, int& s, int& iter, int num) {
	if (iter != s) {
		if (n != NULL) {
			word += int_to_char(num);
			if (n->leaf == true) {
				arr[iter] = word;
				iter++;
			}
			for (int i = 0; i < 25; i++) {
				pre_order(n->next[i], word, arr, s, iter, i);
			}

			string temp_word = "";
			for (int i = 0; i < word.length() - 1; i++) {
				temp_word += word[i];
			}
			word = temp_word;
		}
	}
}
Trie_tree::Trie_tree() {
	head = new Trie_node;
}
void Trie_tree::insertion(string word) {
	Trie_node* current = head;

	for (int i = 0, index; true; i++) {
		check_case_char(word[i]);
		index = char_to_int(word[i]);
		if (current->next[index] == NULL) {
			current->next[index] = new Trie_node;
		}
		current = current->next[index];
		if (i == word.length() - 1) {
			current->leaf = true;
			break;
		}
	}
}
bool Trie_tree::load_trie_tree(string file_name) {
	file_name += ".txt";
	string temp;
	ifstream words(file_name);

	if (words.is_open()) {
		for (int i = 0; !words.eof(); i++) {
			words >> temp;
			check_special_char(temp);
			insertion(temp);
		}
		words.close();
		return true;
	}
	else return false;
}
void Trie_tree::suggestion(string start, string*& word, int& size_str) {
	int iterator = 0, index = 0;
	bool flag = true;
	string temp;
	Trie_node* current = head;

	for (int i = 0; i < start.length() - 1; i++) {
		if (current->next[char_to_int(start[i])] == NULL) {
			flag = false;
			break;
		}
		current = current->next[char_to_int(start[i])];
		temp += start[i];
	}
	if (flag) {
		index = char_to_int(start[start.length() - 1]);
		pre_order(current->next[index], temp, word, size_str, iterator, index);
	}
	int count = 0;
	while (word[count] != "" && count < size_str) {
		count++;
	}
	size_str = count;
}

//GENERIC FUNCTIONS
int char_to_int(char data) {
	return (data - 'a');
}
void alphabet_counter(string str, int*& arr)
{
	for (int i = 0; i < 30; i++)
	{
		arr[i] = 0;
	}
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			arr[26] += 1;
			continue;
		}
		else if (str[i] == '.')
		{
			arr[27] += 1;
			continue;
		}
		else if (str[i] == ',')
		{
			arr[28] += 1;
			continue;
		}
		else if (str[i] == '?')
		{
			arr[29] += 1;
			continue;
		}
		else {
			arr[char_to_int(str[i])] += 1;
		}
	}
}
bool check_special_char(string& x) {
	for (int i = 0; i < x.length(); i++) {
		if (x[i] >= 65 && x[i] <= 91 || x[i] >= 97 && x[i] <= 123) {
			continue;
		}
		else {
			return true;
		}
	}
	return false;
}
bool check_input(char data) {
	if (('a' <= data && 'z' >= data) || ('A' <= data && 'Z' >= data) || data == ' ' || data == ';' || data == '/' || data == '=' || data == '.' || data == ',' || data == '?') {
		return true;
	}
	else return false;
}
char int_to_char(int data) {
	return ('a' + data);
}
void check_case_char(char& data) {
	if (data >= 65 && data <= 91) {//small case ascii check
		data += 32;
	}
}
void check_case_str(string& str) {
	for (int i = 0; i < str.length(); i++) {
		check_case_char(str[i]);
	}
}
void animation() {
	string animate1 = R"(

$$$$$$$$\ $$$$$$$$\ $$\   $$\ $$$$$$$$\       $$$$$$$$\ $$$$$$$\  $$$$$$\ $$$$$$$$\  $$$$$$\  $$$$$$$\  
\__$$  __|$$  _____|$$ |  $$ |\__$$  __|      $$  _____|$$  __$$\ \_$$  _|\__$$  __|$$  __$$\ $$  __$$\ 
   $$ |   $$ |      \$$\ $$  |   $$ |         $$ |      $$ |  $$ |  $$ |     $$ |   $$ /  $$ |$$ |  $$ |
   $$ |   $$$$$\     \$$$$  /    $$ |         $$$$$\    $$ |  $$ |  $$ |     $$ |   $$ |  $$ |$$$$$$$  |
   $$ |   $$  __|    $$  $$<     $$ |         $$  __|   $$ |  $$ |  $$ |     $$ |   $$ |  $$ |$$  __$$< 
   $$ |   $$ |      $$  /\$$\    $$ |         $$ |      $$ |  $$ |  $$ |     $$ |   $$ |  $$ |$$ |  $$ |
   $$ |   $$$$$$$$\ $$ /  $$ |   $$ |         $$$$$$$$\ $$$$$$$  |$$$$$$\    $$ |    $$$$$$  |$$ |  $$ |
   \__|   \________|\__|  \__|   \__|         \________|\_______/ \______|   \__|    \______/ \__|  \__|
                                                                                                        
                                                                                                        
                                                                                                        

)";
	string animate2 = R"(
 $$$$$$\    $$\   $$$$$$$$\      $$$$$$\   $$$$$$\   $$$$$$\  $$$$$$$$\ 
$$  __$$\ $$$$ |  $$  _____|    $$  __$$\ $$  __$$\ $$$ __$$\ \____$$  |
\__/  $$ |\_$$ |  $$ |          $$ /  $$ |\__/  $$ |$$$$\ $$ |    $$  / 
 $$$$$$  |  $$ |  $$$$$\ $$$$$$\\$$$$$$$ | $$$$$$  |$$\$$\$$ |   $$  /  
$$  ____/   $$ |  $$  __|\______|\____$$ |$$  ____/ $$ \$$$$ |  $$  /   
$$ |        $$ |  $$ |          $$\   $$ |$$ |      $$ |\$$$ | $$  /    
$$$$$$$$\ $$$$$$\ $$ |          \$$$$$$  |$$$$$$$$\ \$$$$$$  /$$  /     
\________|\______|\__|           \______/ \________| \______/ \__/      
                                                                        
                                                                        
                                                                        
 $$$$$$\    $$\   $$$$$$$$\      $$$$$$\    $$\   $$$$$$$$\   $$\       
$$  __$$\ $$$$ |  $$  _____|    $$  __$$\ $$$$ |  \____$$  |$$$$ |      
\__/  $$ |\_$$ |  $$ |          $$ /  $$ |\_$$ |      $$  / \_$$ |      
 $$$$$$  |  $$ |  $$$$$\ $$$$$$\\$$$$$$$ |  $$ |     $$  /    $$ |      
$$  ____/   $$ |  $$  __|\______|\____$$ |  $$ |    $$  /     $$ |      
$$ |        $$ |  $$ |          $$\   $$ |  $$ |   $$  /      $$ |      
$$$$$$$$\ $$$$$$\ $$ |          \$$$$$$  |$$$$$$\ $$  /     $$$$$$\     
\________|\______|\__|           \______/ \______|\__/      \______|    
                                                                        
                                                                        
                                                                        
 $$$$$$\    $$\   $$$$$$$$\      $$$$$$\    $$\   $$$$$$\  $$$$$$$$\    
$$  __$$\ $$$$ |  $$  _____|    $$  __$$\ $$$$ | $$$ __$$\ \____$$  |   
\__/  $$ |\_$$ |  $$ |          $$ /  $$ |\_$$ | $$$$\ $$ |    $$  /    
 $$$$$$  |  $$ |  $$$$$\ $$$$$$\\$$$$$$$ |  $$ | $$\$$\$$ |   $$  /     
$$  ____/   $$ |  $$  __|\______|\____$$ |  $$ | $$ \$$$$ |  $$  /      
$$ |        $$ |  $$ |          $$\   $$ |  $$ | $$ |\$$$ | $$  /       
$$$$$$$$\ $$$$$$\ $$ |          \$$$$$$  |$$$$$$\\$$$$$$  /$$  /        
\________|\______|\__|           \______/ \______|\______/ \__/         
                                                                        
                                                                        
                                                                        
)";
	cout << animate1 << endl;
	system("pause");
	system("cls");
	cout << animate2 << endl;
	system("pause");
}
void input_data(string& final_str, Trie_tree& obj) {
	system("cls");
	string* suggestion_arr = NULL, user = "";
	int size_str = 0;
	char c = ' ';
	bool flag = true;

	suggestion_arr = new string[10];

	cout << final_str;
	while (flag) {
		do {
			c = _getch();
		} while (!check_input(c));
		if (c != '/' && c != ' ' && c != '=') {
			for (int i = 0; i < 10; i++) {
				suggestion_arr[i] = "";
			}
			system("cls");
			user += c;
			cout << final_str;
			cout << user;
			size_str = 10;
			check_case_str(user);
			obj.suggestion(user, suggestion_arr, size_str);
			cout << endl;
			for (int i = 0; i < size_str; i++) {
				cout << suggestion_arr[i] << endl;
			}
		}
		else if (c == ' ' || c == ',' || c == '.' || c == '?') {
			final_str += user + c;
			user = "";
		}
		else if (c == '=') {
			final_str += user;
			flag = false;
			break;
		}
		else {
			for (int i = 0; c == '/' && i < size_str; i++) {
				system("cls");
				for (int j = 0; j < size_str; j++) {
					cout << suggestion_arr[j];
					if (j == i) {
						cout << "  <-";
					}
					cout << endl;
				}
				do {
					c = _getch();
				} while (!check_input(c));
				if (c == ';') {
					if (suggestion_arr[i] != " ") {
						user = suggestion_arr[i];
						system("cls");
						cout << final_str;
						cout << user;
						break;
					}
				}
			}
		}
	}
}
void write_mode(Huffman& huff, Trie_tree& trie, int mode) {
	string user = "", file_name;
	ifstream fin;

	system("cls");
	cout << "Enter The File Name : ";
	cin >> file_name;
	fin.open(file_name + "code.txt");
	if (fin.is_open() || mode) {
		user = huff.retrieve_data(file_name);
		input_data(user, trie);
		huff.store_data(file_name, user);
		cout << "\nFile Saved Successfuly!" << endl;
	}
	else {
		cout << "File Can Not Be Opened!" << endl;
	}
	system("pause");
}
void display_mode(Huffman& huff) {
	system("cls");
	string display_str, file_name;
	ifstream fin;

	cout << "Enter The File Name : ";
	cin >> file_name;
	fin.open(file_name + "code.txt");
	if (fin.is_open()) {
		display_str = huff.retrieve_data(file_name);
		system("cls");
		cout << "Your File Data Is As Following ::" << endl << endl;
		cout << display_str << endl;
	}
	else {
		cout << "File Does Not Exist!" << endl;
	}
	system("pause");
}
void deletion_mode() {
	system("cls");
	string file_name = "";
	ifstream fin;

	cout << "Enter The File Name : ";
	cin >> file_name;
	fin.open(file_name + "code.txt");
	if (fin.is_open()) {
		fin.close();
		string temp = file_name + "code.txt";
		char* file_arr = new char[temp.length() + 1];
		for (int i = 0; i < temp.length(); i++) {
			file_arr[i] = temp[i];
		}
		file_arr[temp.length()] = '\0';
		remove(file_arr);
		delete[] file_arr;
		temp = file_name + "compressed.txt";
		file_arr = new char[temp.length() + 1];
		for (int i = 0; i < temp.length(); i++) {
			file_arr[i] = temp[i];
		}
		file_arr[temp.length()] = '\0';
		remove(file_arr);
		delete[] file_arr;
		file_arr = NULL;
		cout << "File Deleted Successfuly!" << endl;
	}
	else {
		cout << "File Does Not Exist!" << endl;
	}
	system("pause");
}