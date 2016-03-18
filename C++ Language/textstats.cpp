#include "textstats.hpp"
#include <algorithm>
void get_tokens(const string &s, const unordered_set<char> &delimiters, vector<string> &tokens){
    int i, pos=0, len = 0, l = (int)s.length();
    for(i = 0; i<=l; i++, len++){
        if(delimiters.find(s[i])!=delimiters.end() || s[i]=='\0'){
            string s1 = s.substr(pos, len);
            if(len!=0){
                int l1 = (int)s1.length();
                for(int j = 0; j<l1; j++){
                    s1[j] = tolower(s1[j]);
                }
                tokens.push_back(s1);
            }
            len = -1;
            pos = i+1;
        }
    }
}
void get_type_freq(const vector<string> &tokens, map<string, int> &freqdi){
    for(string s : tokens){
        if(freqdi.find(s)!=freqdi.end()){
            freqdi[s]++;
        }
        else{
            freqdi.insert(pair<string, int>(s, 1));
        }
    }
}
void get_types(const vector<string> &tokens,vector<string> &wtypes){
    for(string s : tokens){
        bool push = true;
        int l = (int)wtypes.size();
        for(int i = 0; i<l; i++){
            if(wtypes[i]==s){
                push = false;
                break;
            }
        }
        if(push) wtypes.push_back(s);
    }
    sort(wtypes.begin(), wtypes.end());
}
void get_x_length_words(const vector<string> &wtypes, int x, vector<string> &words){
    for(string s : wtypes){
        if(s.length()>=x) words.push_back(s);
    }
}
void get_x_freq_words( const map<string, int> &freqdi, int x, vector<string> &words){
    for (auto it = freqdi.begin(); it != freqdi.end(); ++it){
        if(it->second>=x) words.push_back(it->first);
    }
}
void get_words_by_length_dict(const vector<string> &wtypes, map<int, vector<string> > &lengthdi){
    for(string s :wtypes){
        int l = (int)s.length();
        if(lengthdi.find(l)==lengthdi.end()){
            lengthdi.insert(pair<int, vector<string> >(l, vector<string>()));
            for(string s1 : wtypes){
                if(s1.length()==l) lengthdi[l].push_back(s1);
            }
        }
    }
}




