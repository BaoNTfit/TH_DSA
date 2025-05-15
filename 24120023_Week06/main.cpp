#include "function.h"
int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " ./MST.txt ./input.txt ./output.txt" << endl;
        return 1; 
    }

    ifstream input(argv[2]);
    ofstream output(argv[3]);
    if (!input.is_open() || !output.is_open()) {
        cerr << "Error opening files" << endl;
        return 1;
    }
    // Parse the input string into vector of Company structs
    vector<Company> companies = readCompanyList("MST.txt");
    HashTable* table = new HashTable;
    table = createHashTable(companies);
    string line;
    while (getline(input, line)) {
        Company* company = searchCompany(table,line);
        output << company->name << "|" << company->profit_tax << "|" << company->address << endl;
    }
    input.close();
    output.close();
    return 0;
}
