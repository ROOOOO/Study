#include <iostream>
#include <vector>
using namespace std;

class Vertex;
class Edge;
void dfs(Vertex *v, vector<Vertex> *new_automat);

class Vertex{
    public:
    int state, new_state;
    vector<Edge> next;
    Vertex(int state);
    bool used;
};
Vertex::Vertex(int state){
    this->state = state;
    used = false;
}
class Edge{
    public:
    char in, out;
    Vertex *to;
    Edge(Vertex *to, char in, char out);
};
Edge::Edge(Vertex *to, char in, char out){
    this->to = to;
    this->in = in;
    this->out = out;
}
int n_states = 0;
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
    vector<Vertex> automat;
    for(int i = 0; i<states; i++) automat.push_back(Vertex(i));
    for(int i = 0; i<states; i++){
        for(int j = 0; j<out; j++) automat[i].next.push_back(Edge(&automat[delta[i][j]], i+97, f[i][j]));
    }
    vector<Vertex> new_automat;
    dfs(&automat[start], &new_automat);
    cout << n_states << endl;
    cout << out << endl;
    cout << 0 << endl;
    for(int i = 0; i<n_states; i++){
        int l = new_automat[i].next.size();
        for(int j = 0; j<l; j++) cout << new_automat[i].next[j].to->new_state << " ";
        cout << endl;
    }
    for(int i = 0; i<n_states; i++) {
        for (int j = 0; j < out; j++) cout << f[new_automat[i].state][j] << " ";
        cout << endl;
    }
    return 0;
}
void dfs(Vertex *v, vector<Vertex> *new_automat){
    v->used = true;
    v->new_state = n_states++;
    new_automat->push_back(*v);
    int l = v->next.size();
    for(int i = 0; i<l; i++){
        if(!v->next[i].to->used) dfs(v->next[i].to, new_automat);
    }
}