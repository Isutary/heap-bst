#include<iostream>
#include<ctime>
#include "stablo.h"
#include "stablo.cpp"
using namespace std;


int main() {
    srand(time(0));

    /*Stablo<int> a;
    a.myAdd(0);
    a.myAdd(1);
    a.myAdd(2);
    a.myAdd(5);
    a.myAdd(9);
    a.myAdd(7);
    a.myAdd(13);

    a.preOrder();
    pair<Stablo<int>, Stablo<int>> b = a.myDivide(24);
    cout << endl;
    b.first.preOrder();
    cout << endl;
    b.second.preOrder();
    Stablo<int> c;
    c = myUnite(b.first, b.second);
    cout << endl;
    c.preOrder();*/
    Stablo<int> a;
    a.myAdd(7);
    a.myAdd(3);
    a.myAdd(9);
    a.myAdd(5);
    a.preOrder();
    Stablo<int> b;
    b.myAdd(4);
    b.myAdd(1);
    b.myAdd(8);
    b.myAdd(6);
    cout << endl;
    b.preOrder();
    Stablo<int> c = myUnion(a, b);
    cout << endl;
    c.preOrder();




    return 0;
}
