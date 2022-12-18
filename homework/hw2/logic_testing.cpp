#include <string> //string header file
#include <vector> //vector header file
#include <algorithm>
#include<iostream>
using namespace std;

// Driver Code
int main()
{
    std::vector<string> vect = {"AFG", "HYH", "DRG", "BUBR"};
    sort(vect.begin(), vect.end());
    for (unsigned int i = 0;i<vect.size();i++){
       cout << vect[i] << endl;
    }
     
    return 0;
}