#include "RangeTree.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
    vector<pair<int,int>> data;
    srand(time(NULL));

    //FOR 10 ELEMENTS

    /*
    int num, num2;
    for(long int i = 0; i < 10 ; i++){
        num = rand()%(101-1);
        num2 = rand()%(101-1);
        data.push_back(make_pair(num, num2));
    }
    sort(data.begin(), data.end(), sortbyfirst);
    Nodo2D * root = create_range_tree(data, 0, 9);
    */

    //FOR 100 ELEMENTS

    /*
    int num, num2;
    for(long int i = 0; i < 100 ; i++){
        num = rand()%(101-1);
        num2 = rand()%(101-1);
        data.push_back(make_pair(num, num2));
    }
    sort(data.begin(), data.end(), sortbyfirst);
    Nodo2D * root = create_range_tree(data, 0, 99);
    */

    //FOR 1000 ELEMENTS

    /*
    int num, num2;
    for(long int i = 0; i < 1000 ; i++){
        num = rand()%(101-1);
        num2 = rand()%(101-1);
        data.push_back(make_pair(num, num2));
    }
    sort(data.begin(), data.end(), sortbyfirst);
    Nodo2D * root = create_range_tree(data, 0, 999);
    */

    //FOR 10 000 ELEMENTS


    int num, num2;
    for(long int i = 0; i < 10000 ; i++){
        num = rand()%(101-1);
        num2 = rand()%(101-1);
        data.push_back(make_pair(num, num2));
    }
    sort(data.begin(), data.end(), sortbyfirst);
    Nodo2D * root = create_range_tree(data, 0, 9999);
    


    //FOR 100 000 ELEMENTS

    /*
    int num, num2;
    for(long int i = 0; i < 100000 ; i++){
        num = rand()%(101-1);
        num2 = rand()%(101-1);
        data.push_back(make_pair(num, num2));
    }
    sort(data.begin(), data.end(), sortbyfirst);
    Nodo2D * root = create_range_tree(data, 0, 99999);
    */

    auto start = high_resolution_clock::now();



    vector<pair<int,int>> test = range_search(10, 40, 20, 70, root);

    auto stop = high_resolution_clock::now();

    for(auto a : test){
        cout << a.first << " " << a.second << endl;
    };

    cout << endl;
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "elapsed time: " << duration.count() << "ms\n";


    return 0;
}
