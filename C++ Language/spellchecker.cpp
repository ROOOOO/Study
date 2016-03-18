#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>

using namespace std;
void divide_word(set<string> & bigrams, string word){
    int l = (int)word.length();
    if(l<=2){
        bigrams.insert(word);
        return;
    }
    for(int i = 0; i<l-1; i++){
        bigrams.insert(word.substr(i, 2));
    }
}
float words_sim(set<string> & bigramsw1, set<string> & bigramsw2){
    set<string> res;
    int inters_l, union_l;
    set_intersection(bigramsw1.begin(), bigramsw1.end(), bigramsw2.begin(), bigramsw2.end(), inserter(res, res.begin()));
    inters_l = (int)res.size();
    res.clear();
    if(inters_l==0) return 0;
    set_union(bigramsw1.begin(), bigramsw1.end(), bigramsw2.begin(), bigramsw2.end(), inserter(res, res.begin()));
    union_l = (int)res.size();
    return (float)inters_l/union_l;
}
int main(int argc, const char * argv[]) {
    ifstream big_count("count_big.txt");
    map<string, pair<int, set<string>>> dictionary;
    string word;
    int freq;
    while (big_count >> word >> freq){
        set<string> bigrams;
        divide_word(bigrams, word);
        dictionary.insert(pair<string, pair<int, set<string>>>(word, pair<int, set<string>>(freq, bigrams)));
    }
    while(cin>>word){
        set<string> bigrams;
        divide_word(bigrams, word);
        string ans = word;
        float ans_similarity = 0;
        int ans_freq = 0;
        for(auto i = dictionary.begin(); i!=dictionary.end(); i++){
            float similarity = words_sim(bigrams, i->second.second);
            if(ans_similarity<similarity){
                ans_similarity = similarity;
                ans_freq = i->second.first;
                ans = i->first;
            }
            else if (ans_similarity==similarity && similarity!=0){
                if(ans_freq<i->second.first){
                    ans_similarity = similarity;
                    ans_freq = i->second.first;
                    ans = i->first;
                }
                else if(ans_freq==i->second.first && ans > i->first){
                    ans_similarity = similarity;
                    ans_freq = i->second.first;
                    ans = i->first;
                }
            }
        }
        cout << ans <<endl;
    }
    return 0;
}