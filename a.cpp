#include <bits/stdc++.h>

vector<string> restoreIpAddresses(string s) {
        int maxip = 255;

        vector<string> ans;
        backtrack(ans, s, 0, 0);

        return ans;
    }

bool isvalid(string s){
        if(s[0] == 0 && s.length() > 1) return false;

        int ip = stoi(s.c_str());
        if(ip > 255) return false; 

        return true;
    }

void backtrack(vector<string> &ans, string curans, int pos, int numdot){
        
    if(pos == curans.length() && numdot == 4){
        //bug
        ans.push_back(curans);
        return;
    }else if(numdot >= 4){
        return;
    }

    for(int end = pos; end < pos+3; end++){
        string tmp = curans.substr(pos, end-pos+1);
        if(isvalid(tmp)){
            int newpos = pos+2; // 255 --> 2.55
            string newans = curans;
            newans.insert(pos+1, ".");

            backtrack(ans, newans, newpos, numdot+1);
        }else{
            return;
        }

    }

  
}

int main(){
    vector<string> s;
    restoreIpAddresses("25525511135");
    return 0;
}