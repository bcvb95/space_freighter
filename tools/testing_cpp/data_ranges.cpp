#include <limits>
#include <iostream>
using namespace std;
int main () {
    cout << "signed short: " << sizeof(short) << " bytes\n[" << numeric_limits<short>::min() << ", " << numeric_limits<short>::max() << "]" << endl << endl;
    cout << "unsigned short: " << sizeof(unsigned short) << " bytes\n[" << numeric_limits<unsigned short>::min() << ", " << numeric_limits<unsigned short>::max() << "]" << endl << endl;

    cout << "signed int: " << sizeof(int) << " bytes\n[" << numeric_limits<int>::min() << ", " << numeric_limits<int>::max() << "]" << endl << endl;
    cout << "unsigned int: " << sizeof(unsigned int) << " bytes\n[" << numeric_limits<unsigned int>::min() << ", "  << numeric_limits<unsigned int>::max() << "]" << endl << endl;

    cout << "signed long int: " << sizeof(long int) << " bytes\n[" << numeric_limits<long int>::min() << ", "  << numeric_limits<long int>::max() << "]" << endl << endl;
    cout << "unsigned long int: " << sizeof(unsigned long int) << " bytes\n[" << numeric_limits<unsigned long int>::min() << ", "  << numeric_limits<unsigned long int>::max() << "]" << endl << endl;

    cout << "signed long long int: " << sizeof(long long int) << " bytes\n[" << numeric_limits<long long int>::min() << ", "  << numeric_limits<long long int>::max() << "]" << endl << endl;
    cout << "unsigned long long int: " << sizeof(unsigned long long int) << " bytes\n[" << numeric_limits<unsigned long long int>::min() << ", "  << numeric_limits<unsigned long long int>::max() << "]" << endl << endl;

    cout << "float: " << sizeof(float) << " bytes\n[" << numeric_limits<float>::min() << ", " << numeric_limits<float>::max() << "]" << endl << endl;
    cout << "double: " << sizeof(double) << " bytes\n[" << numeric_limits<double>::min() << ", " << numeric_limits<double>::max() << "]" << endl << endl;
    cout << "long double: " << sizeof(long double) << " bytes\n[" << numeric_limits<long double>::min() << ", " << numeric_limits<long double>::max() << "]" << endl;
    
    return 0;
}