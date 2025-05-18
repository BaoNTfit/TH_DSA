#include"sort.h"
int main(int argc, char* argv[])
{
    //Read input argument
    if(argc!=7) {
        cout << "Unidentify command!" << endl;
        cout << "Try again with this format: ./main -a [type-sort] -i [input file name] -o [output file name ]"<< endl;
        return 0;
    }
    string sortType, input, output;
    for(int i = 1; i < argc; i++) {
        string arg = argv[i];
        if(arg == "-a" && i+1 < argc) sortType = argv[++i];
        if(arg == "-i" && i+1 < argc) input = argv[++i];
        if(arg == "-o" && i+1 < argc) output = argv[++i];
    }
    /*Tao file text random data

    ofstream out("input.txt");
    if ( out.is_open() == false ) {
        cout << "Can Open The File";
        return 0;
    }
    else {
        int *a = new int[1000];
	    GenerateData(a, 1000, 0);
	    for (int i = 0; i < 1000; i++) out << a[i] << " ";
        delete[] a;
    }
    out.close()
    */
    ifstream inp(input);
    ofstream out(output);
    if ( inp.is_open() == false || out.is_open() == false) {
        cout << "Can Open The File";
        return 0;
    }
    else {
        int n;
        inp >> n;
        int *a = new int[n];
	    for (int i = 0; i < n; i++) inp >> a[i];
        if(sortType=="bubble-sort")  bblSort(a,n);
        if(sortType=="selection-sort") SelSort(a,n);
        if(sortType=="insertion-sort") insSort(a,n);
        if(sortType=="heap-sort") heapSort(a,n);
        if(sortType=="merge-sort") mrgSort(a,n);
        if(sortType=="shaker-sort") shakerSort(a, n);
        if(sortType=="shell-sort") shellSort(a, n);
        if(sortType=="counting-sort") countingSort(a, n);
        if(sortType=="radix-sort") radixSort(a, n);
        if(sortType=="quick-sort") quickSort(a, 0, n - 1);
        if(sortType=="flash-sort") flashSort(a, n);
        display(a,n,output);
        delete[] a;
    }
    inp.close();
    out.close();
    return 0;
	/*
    ./main -a bubble-sort -i input.txt -o out1
	./main -a selection-sort -i input.txt -o out2
	./main -a insertion-sort -i input.txt -o out3
	./main -a heap-sort -i input.txt -o out4
	./main -a merge-sort -i input.txt -o out5
	./main -a shaker-sort -i input.txt -o out6
	./main -a shell-sort -i input.txt -o out7
	./main -a counting-sort -i input.txt -o out8
	./main -a radix-sort -i input.txt -o out9
	./main -a quick-sort -i input.txt -o out10
	./main -a flash-sort -i input.txt -o out11
    */
}