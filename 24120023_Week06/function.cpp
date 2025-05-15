#include "function.h"
// 1. Read the companies information from a given file:
int p = 31;
int m = 2000;
vector<Company> readCompanyList(string file_name)
{
    ifstream inp(file_name);
    if (!inp.is_open())
    {
        cout << "Can't open the input file";
    }
    vector<Company> data;
    string line;
    getline(inp, line);
    while (getline(inp, line))
    {
        Company company;
        size_t first = line.find_first_of("|");
        company.name = line.substr(0, first);

        company.profit_tax = line.substr(first + 1, 10);
        size_t second = line.find_last_of("|");
        company.address = line.substr(second + 1);
        data.push_back(company);
    }
    inp.close();
    return data;
}
void Printf(string input)
{
    vector<Company> companies = readCompanyList(input);
    for (const auto &company : companies)
    {
        cout << "Name: " << company.name << endl;
        cout << "Profit Tax: " << company.profit_tax << endl;
        cout << "Address: " << company.address << endl;
        cout << "----------------------------" << endl;
    }
    return;
}
long long hashString(string company_name)
{
    int n = 20;
    if (company_name.length() > 20)
    {
        size_t first = company_name.length() - 20;
        company_name = company_name.substr(first);
    }
    long long ans = 0;
    for (int i = 0; i < company_name.length(); i++)
    {
        int temp = company_name[i];
        // Ham mu
        for (int j = 1; j <= i; j++)
        {
            if (temp > m)
                temp = temp % m;
            temp = temp * p;
        }
        ans = (ans + temp) % m;
    }
    return ans;
}
HashTable* createHashTable(vector<Company> list_company){
    // create a hash table of size 2000, generated from the Companies list
    // Separate Chaining
    HashTable* table = new HashTable;
    table->companies.resize(m); // m = 2000
    table->size = m;

    for (const Company& company : list_company) {
        long long index = hashString(company.name);
        table->companies[index].push_back(company);
    }

    return table;
}
bool insertCompany(HashTable* hash_table, Company company) {
    long long index = hashString(company.name);

    // Tránh chèn trùng tên công ty
    for (const Company& c : hash_table->companies[index]) {
        if (c.name == company.name) {
            return false; // đã tồn tại
        }
    }

    hash_table->companies[index].push_back(company);
    return true;
}

Company* searchCompany(HashTable* hash_table, string company_name) {
    long long index = hashString(company_name);

    for (Company& c : hash_table->companies[index]) {
        if (c.name == company_name) {
            return &c;
        }
    }

    return nullptr; // không tìm thấy
}

