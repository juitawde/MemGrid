#include <iostream>
using namespace std;
#define BLUE    "\033[34m"
#define BOLD    "\033[1m"
#define RESET   "\033[0m"

// void C() {
//     cout << "Inside C\n";
// }

// void B() {
//     C();
//     cout << "Back in B\n";
// }

// void A() {
//     B();
//     cout << "Back in A\n";
// }

// int main() {
//     A();
//     cout << "Back in main\n";
// }

// void f(int n)
// {
//     if(n == 0)
//         return;

//     cout << n << " "<<endl;
//     f(n - 1);
// }

// int main()
// {
//     int n = 5;
//     f(n);
//     cout << "\nBack in main\n";
// }

void displayBanner()
{
    cout << BLUE << BOLD;

    cout << R"(

    hello

)";
cout << RESET;
}

int main()
{
    displayBanner();
    return 0;
}