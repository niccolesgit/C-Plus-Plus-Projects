
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    string s;
    map<string, int> counters;
    
    // check 1
    /*
    while(cin >> s) {
        ++counters[s];
    }
    
    int mode = 0;
    map<string, int>::iterator it;
    for( it = counters.begin(); it != counters.end(); it++) {
        if(it->second > mode) {
            mode = it->second;
        }
    }
    
    for( it = counters.begin(); it != counters.end(); it++) {
        if(it->second == mode) {
            cout << it->first << ' ';
        }
    }
    cout << endl;*/

    // check 2
    while(cin >> s) {
        map<string, int>::iterator it = counters.find(s);
        if(it == counters.end()) {
            //uses insert here:
            counters.insert(make_pair(s,1));
        } else {
            it -> second++;
        }
    }
    
    int mode = 0;
    map<string, int>::iterator it2;
    for( it2 = counters.begin(); it2 != counters.end(); it2++) {
        if(it2->second > mode) {
            mode = it2->second;
        }
    }
    
    for( it2 = counters.begin(); it2 != counters.end(); it2++) {
        if(it2->second == mode) {
            cout << it2->first << ' ';
        }
    }
    cout << endl;

    
    return 0;
}
