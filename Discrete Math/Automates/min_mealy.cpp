#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Vertex;
class Edge;
int split1(vector<Vertex*> & automat, vector<int> & pi);
int split(vector<Vertex*> & automat, vector<int> & pi);
void aufenkampHohn(vector<Vertex*> & automat, vector<Vertex*> & min_automat);
void dfs(Vertex * v);
int states, out, start, n_state = 0;
class Vertex{
    public:
    int state, depth;
    bool used, used_for_build;
    vector<Edge> next;
    Vertex * parent;
    Vertex(int state);
    Vertex & find();
    bool equal(Vertex & elem);
    void unite(Vertex * elem);
    void reuse();
};
Vertex::Vertex(int state){
    this->state = state;
    this->parent = this;
    this->depth = 0;
    this->used = this->used_for_build = false;
}
void Vertex::reuse(){
    this->parent = this;
    this->depth = 0;
}
Vertex & Vertex::find() {
    if (this->parent != this) {
        this->parent = & this->parent->find();
    }
    return *this->parent;
}
void Vertex::unite(Vertex * elem) {
    Vertex & x = this->find();
    Vertex & y = elem->find();
    if(x.depth<y.depth){
        x.parent = & y;
    }
    else{
        y.parent = & x;
        if((x.depth==y.depth)&&(&x!=&y)){
            x.depth++;
        }
    }
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
int main() {
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
    vector<Vertex*> automat;
    for(int i = 0; i<states; i++) automat.push_back((new Vertex(i)));
    for(int i = 0; i<states; i++) {
        for (int j = 0; j < out; j++) automat[i]->next.push_back(Edge(automat[delta[i][j]], j + 97, f[i][j]));
    }
    vector<Vertex*> min_automat;
    aufenkampHohn(automat, min_automat);
    int l = (int)min_automat.size();
    cout<< "digraph {"<<"\n\trankdir = LR"<<"\n\tdummy [label = \"\", shape = none]"<<endl;
    for(int i = 0; i<l; i++) if(min_automat[i]->used)cout<<"\t"<<min_automat[i]->state<<" [shape = circle]"<<endl;
    cout<<"\tdummy -> 0"<<endl;
    for(int i = 0; i<l; i++){
        if(min_automat[i]->used){
            for(int j = 0; j<out; j++){
                cout<<"\t"<<min_automat[i]->state<<" -> "<<min_automat[i]->next[j].to->state<<" [label = \""<<min_automat[i]->next[j   ].in<<"("<<min_automat[i]->next[j].out<<")\"]"<<endl;
            }
        }
    }
    cout<<"}"<<endl;
    for(int i = 0; i<automat.size(); i++){
        delete automat[i];
    }
    return 0;
}
int split1(vector<Vertex*> & automat, vector<int> & pi){
    int m,l = (int)automat.size();
    m = l;
    for(int i = 0; i<l; i++){
        for(int j = 0; j<l; j++){
            if(i==j) continue;
            bool eq = true;
            for(int k = 0; k<out; k++){
                for(int m = 0; m<out; m++){
                    if (automat[i]->next[k].in == automat[j]->next[m].in && automat[i]->next[k].out != automat[j]->next[m].out) eq = false;
                }
            }
            if(eq){
                automat[i]->unite(automat[j]);
                m--;
            }
            
        }
    }
    for(int i = 0; i<l; i++) pi.push_back(automat[i]->find().state);
    return m;
}
int split(vector<Vertex*> & automat, vector<int> & pi){
    int m,l = (int)automat.size();
    m = l;
    for(int i = 0; i<l; i++) automat[i]->reuse();
    for(int i = 0; i<l; i++){
        for(int j = 0; j<l; j++){
            if(pi[i]==pi[j] && &automat[i]->find()!=&automat[j]->find()){
                bool eq = true;
                for(int k = 0; k<out; k++){
                    for(int m = 0; m<out; m++){
                        if (automat[i]->next[k].in == automat[j]->next[m].in && pi[automat[i]->next[k].to->state] != pi[automat[j]->next[m].to->state]) eq = false;
                    }
                }
                if(eq){
                    automat[i]->unite(automat[j]);
                    m--;
                }
            }
        }
    }
    pi.clear();
    for(int i = 0; i<l; i++) pi.push_back(automat[i]->find().state);
    return m;
}
void aufenkampHohn(vector<Vertex*> & automat, vector<Vertex*> & min_automat){
    vector<int> pi;
    int _m, m = split1(automat, pi), l = (int)automat.size();
    for(;;){
        _m = split(automat, pi);
        if(m == _m) break;
        m = _m;
    }
    for(int i = 0; i<l; i++){
        if(!automat[pi[i]]->used_for_build){
            min_automat.push_back(automat[pi[i]]);
            automat[pi[i]]->used_for_build = true;
        }
    }
    for(int i = 0; i<m; i++){
        for(int j = 0; j<out; j++){
            int k, s = pi[automat[min_automat[i]->state]->next[j].to->state];
            for(k = 0; k<m; k++) if(min_automat[k]->state==s) break;
            min_automat[i]->next[j].to = min_automat[k];
        }
    }
    int k;
    for(k = 0; k<m; k++) if(min_automat[k]->state==pi[start]) break;
    dfs(min_automat[k]);
}
void dfs(Vertex * v){
    v->used = true;
    v->state = n_state++;
    for(int i = 0; i<out; i++){
        if(!v->next[i].to->used){
            dfs(v->next[i].to);
        }
    }
}