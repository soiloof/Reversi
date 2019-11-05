// import
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>

//  名前空間指定
using namespace std;

int main(){
    enum EDirection{
        E_Left = 0,
        E_Right = 1,
    };
    cout << E_Left << endl;
    int i=1;
    i+=97;
    char c = (char)i;
    cout << c << endl;
}