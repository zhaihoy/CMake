#include <iostream>
#include "func/func.h"
using std::cout; // 只引入 cout
using std::endl; // 只引入 endl

int main() {
    int sum = add(3,4);
 cout << "Hello " << sum << endl;
    return 0;
}