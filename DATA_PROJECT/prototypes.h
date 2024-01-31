#pragma once
#pragma warning(suppress : 4996)
#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<cstdio>
#include<Windows.h>
using namespace std;

//ALL CLASSES AND FUNCTIONS PROTOTYPES

//HUFFMAN NODE CLASS
struct Huff_node {
	char data;
	int counter;
	string code_str;
	Huff_node* next, * left, * right;

	Huff_node();
};

//HUFFMAN TREE CLASS
class Huffman {
private:
	Huff_node* front;

	void assign_code(Huff_node* current, string str);
	void inorder(Huff_node* current);
	Huff_node* delete_huff(Huff_node* current);
	void encode_alpha(char alpha, Huff_node* current, string& code);
	void decode_alpha(Huff_node* curr, string coded_str, string& uncoded, int& index);
	void store_encoded(string& coded_str, string file_name);
	bool retrieve_encoded(string& code_str, string file_name);
	bool is_empty();
	Huff_node* get_top();
	void make_huff();
	void enqueue(char value, int num, Huff_node* l, Huff_node* r);
	void dequeue();
	void delete_tree();
	void make_list(string str);
	void store_encryption(string file_name);
	bool retrieve_encryption(string file_name);
	void encode_str(string& str);
	void decode_str(string& str);
public:
	Huffman();
	void display();
	void store_data(string file, string data);
	string retrieve_data(string file);
};

//TRIE NODE CLASS
struct Trie_node {
	bool leaf;
	Trie_node* next[26];
	Trie_node();
};

//TRIE TREE CLASS
class Trie_tree {
	Trie_node* head;
	void pre_order(Trie_node* n, string& word, string*& arr, int& s, int& iter, int num);
public:
	Trie_tree();
	void insertion(string word);
	bool load_trie_tree(string file_name);
	void suggestion(string start, string*& word, int& size_str);
};

//GENERIC FUNCTIONS PROTOTYPES
int char_to_int(char data);
void alphabet_counter(string str, int*& arr);
bool check_special_char(string& x);
bool check_input(char data);
char int_to_char(int data);
void check_case_char(char& data);
void check_case_str(string& str);
void animation();
void input_data(string& final_str, Trie_tree& obj);
void write_mode(Huffman& huff, Trie_tree& trie, int mode);
void display_mode(Huffman& huff);
void deletion_mode();