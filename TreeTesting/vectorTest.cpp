#include <iostream>
#include <vector>

using namespace std;

int main(){

    vector<int> v1 = {1,2,3,4};
    vector<int> v2 = {1,2,3,4,5,6,7};

    v1.insert(v1.end(), v2.begin(), v2.end());

    for(int v : v1){
        cout<<v;
    }
    
}