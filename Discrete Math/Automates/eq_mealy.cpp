#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Vertex;
class Edge;
int split1(vector<Vertex*> & automat, vector<int> & pi, int out);
int split(vector<Vertex*> & automat, vector<int> & pi, int out);
void aufenkampHohn(vector<Vertex*> & automat, vector<Vertex*> & min_automat, int out, int start);
void dfs(Vertex * v, int out);
int n_state = 0;
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
    int states1, out1, start1, states2, out2, start2;
    cin>>states1;
    cin>>out1;
    cin>>start1;
    int delta1[states1][out1];
    char f1[states1][out1];
    for(int i = 0; i<states1; i++){
        for(int j = 0; j<out1; j++) cin>>delta1[i][j];
    }
    for(int i = 0; i<states1; i++){
        for(int j = 0; j<out1; j++) cin>>f1[i][j];
    }
    vector<Vertex*> automat1;
    for(int i = 0; i<states1; i++) automat1.push_back((new Vertex(i)));
    for(int i = 0; i<states1; i++) {
        for (int j = 0; j < out1; j++) automat1[i]->next.push_back(Edge(automat1[delta1[i][j]], j + 97, f1[i][j]));
    }
    cin>>states2;
    cin>>out2;
    cin>>start2;
    int delta2[states2][out2];
    char f2[states2][out2];
    for(int i = 0; i<states2; i++){
        for(int j = 0; j<out2; j++){
            cin>>delta2[i][j];
        }
    }
    for(int i = 0; i<states2; i++){
        for(int j = 0; j<out2; j++){
            cin>>f2[i][j];
        }
    }

    vector<Vertex*> automat2;
    for(int i = 0; i<states2; i++) automat2.push_back((new Vertex(i)));
    for(int i = 0; i<states2; i++) {
        for (int j = 0; j < out2; j++) automat2[i]->next.push_back(Edge(automat2[delta2[i][j]], j + 97, f2[i][j]));
    }
    
    
    vector<Vertex*> min_automat1;
    vector<Vertex*> min_automat2;
    
    aufenkampHohn(automat1, min_automat1, out1, start1);
    sort(min_automat1.begin(), min_automat1.end(), [](Vertex *a, Vertex *b) { return a->state < b->state; });
    n_state = 0;
    aufenkampHohn(automat2, min_automat2, out2, start2);
    sort(min_automat2.begin(), min_automat2.end(), [](Vertex *a, Vertex *b) { return a->state < b->state; });
    int l1 = (int)min_automat1.size();
    int l2 = (int)min_automat2.size();
    bool eq = true;
    if(l1!=l2){
        cout<<"NOT EQUAL";
        eq = false;
    }
    else{
        for(int i = 0; i<l1; i++){
            if(min_automat1[i]->used || min_automat2[i]->used){
                if(min_automat2[i]->state!=min_automat1[i]->state){
                    cout<<"NOT EQUAL";
                    eq = false;
                    break;
                }
                else{
                    int k = (int)min_automat1[i]->next.size();
                    for(int j = 0; j<k; j++){
                        if(min_automat1[i]->next[j].to->state != min_automat2[i]->next[j].to->state || min_automat1[i]->next[j].out!=min_automat2[i]->next[j].out || min_automat1[i]->next[j].in!=min_automat2[i]->next[j].in){
                            cout<<"NOT EQUAL";
                            eq = false;
                            break;
                        }
                    }
                    if(!eq) break;
                }
            }
        }
    }
    if(eq)cout<<"EQUAL";
    for(int i = 0; i<automat1.size(); i++){
        delete automat1[i];
    }
    for(int i = 0; i<automat2.size(); i++){
        delete automat2[i];
    }
    return 0;
}

int split1(vector<Vertex*> & automat, vector<int> & pi, int out){
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
int split(vector<Vertex*> & automat, vector<int> & pi, int out){
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
void aufenkampHohn(vector<Vertex*> & automat, vector<Vertex*> & min_automat, int out, int start){
    vector<int> pi;
    int _m, m = split1(automat, pi, out), l = (int)automat.size();
    for(;;){
        _m = split(automat, pi, out);
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
    dfs(min_automat[k], out);
}
void dfs(Vertex * v, int out){
    v->used = true;
    v->state = n_state++;
    for(int i = 0; i<out; i++){
        if(!v->next[i].to->used){
            dfs(v->next[i].to, out);
        }
    }
}