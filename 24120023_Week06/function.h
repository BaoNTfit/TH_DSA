#ifndef FUNCTION
#define FUNCTION
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
struct Company
{
    string name;
    string profit_tax;
    string address;
};
struct HashTable
{
    vector< vector<Company> > companies;
    int size;
};
// 1. Read the companies information from a given file:
vector<Company> readCompanyList(string file_name);
// 2. Hash a string (company name) function:
long long hashString(string company_name);
HashTable* createHashTable(vector<Company> list_company);
bool insert(HashTable* table, Company company);
Company* search(HashTable* table, string company_name);
#endif