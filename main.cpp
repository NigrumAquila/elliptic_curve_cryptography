#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include "src/EllipticCurve.h"
#include "src/ElGamal.h"
#include "src/ECDSA.h"
#include "src/ECDH.h"

using namespace std;


int main()
{
    auto filename = "data/png.png";

    ifstream in(filename,ios::binary);
    vector<unsigned short> res;
    short x;
    while(in.read(reinterpret_cast<char*>(&x), sizeof(x)))
        res.push_back(x);
    for(int i = 0; i < 300; i++)
        cout << res[i] << endl;

    EllipticCurve ec;

    cin.get();
    return 0;
}