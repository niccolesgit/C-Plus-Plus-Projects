#include <iostream>
#include <vector>
using namespace std; 
int main(){ 
    int m = 2, n = 5;

    std::vector<vector<int>> vect(m, vector<int> (n, 0));

    for (unsigned int i = 0; i < vect.size(); i++)
    {
        for (unsigned int j = 0; j < vect[i].size(); j++)
        {
            cout << vect[i][j] << " ";
        }   
        cout << endl;
    }
 
    return 0;
}
