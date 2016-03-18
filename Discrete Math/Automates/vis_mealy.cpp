#include <iostream>
using namespace std;
int main() {
    int states, out, start;
    cin>>states;
    cin>>out;
    cin>>start;
    int delta[states][out];
    char f[states][out];
    for(int i = 0; i<states; i++){
        for(int j = 0; j<out; j++) cin>>delta[i][j];
    }
    for(int i = 0; i<states; i++){
        for(int j = 0; j<out; j++) cin>>f[i][j];
    }
    cout << "digraph {" << endl << "\trankdir = LR" << endl << "\tdummy [label = \"\", shape = none]" << endl;
    for(int i = 0; i<states; i++) cout << "\t" << i << " [shape = circle]" << endl;
    cout << "\tdummy -> " << start << endl;
    for(int i = 0; i<states; i++){
        for(int j = 0; j<out; j++) cout << "\t" << i << " -> " << delta[i][j] << " [label = \"" << (char)(j+97) << "(" << f[i][j] << ")\"]" << endl;
    }
    cout<<"}";
    return 0;
}