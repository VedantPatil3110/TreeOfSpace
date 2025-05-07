#include<bits\stdc++.h>
using namespace std;
int main(){
    int n,m,q;
    cout<<"enter n";
    cin>>n;
    cout<<"enter m ";
    cin>>m;
    cout<<"enter q";
    cin>>q;
    vector<string>name(n);
    unordered_map<string,int>mp;
    for(int i=0;i<n;i++){
        cout<<"enter alphabet ";
        cin>>name[i];
        mp[name[i]]=i;
    }
    vector<vector<int>>children(n);
    vector<int>parent(n,-1);
    for(int i=1;i<n;i++){
        parent[i]=(i-1)/m;
        children[parent[i]].push_back(i);
    }
    vector<int>lockstatus(n,-1);
    vector<int>desc_lock(n,0);
    while(q--){
        int type,uid;
        string nodename;
        cout<<"enter type ";
        cin>>type;
        cout<<"int uid ";
        cin>>uid;
        cout<<"enter nodename ";
        cin>>nodename;
        int node=mp[nodename];
        bool success=false;
        if(type==1){
            if(lockstatus[node]==-1&&desc_lock[node]==0){
                int temp=parent[node];
                bool found=false;
                while(temp!=-1){
                    if(lockstatus[temp]==-1){
                        found=true;
                        break;
                    }
                    temp=parent[temp];
                }
                if(found==false){
                    lockstatus[node]=uid;
                    temp=parent[node];
                    while(temp!=-1){
                        desc_lock[temp]++;
                        temp=parent[temp];
                    }
                    success=true;
                }
            }
        }
        else if(type==2){
            if(lockstatus[node]==uid){
                lockstatus[node]=-1;
                int temp=node;
                while(temp!=-1){
                    desc_lock[temp]--;
                    temp=parent[temp];
                }
                success=true;
            }
        }
        else{
            if(lockstatus[node]==-1&&desc_lock[node]>0){
                int temp=parent[node];
                bool found=false;
                while(temp!=-1){
                    if(lockstatus[temp]!=-1){
                        found=true;
                        break;
                    }
                    temp=parent[temp];
                }
                if(!found){
                    queue<int>qu;
                    qu.push(node);
                    vector<int>unlock;
                    while(!qu.empty()){
                        int u=qu.front();
                        qu.pop();
                        if(lockstatus[u]!=-1){
                            if(lockstatus[node]==uid){
                                unlock.push_back(u);
                            }
                            else{
                                found=true;
                                break;
                            }
                        }
                        for(auto v:children[u]){
                            qu.push(v);
                        }
                    }
                    if(!found && !unlock.empty()){
                        for(auto a:unlock){
                            lockstatus[a]=-1;
                            int temp2=parent[a];
                            while(temp2!=-1){
                                desc_lock[temp2]--;
                                temp2=parent[temp2];
                            }
                        }
                        lockstatus[node]=uid;
                        temp=parent[node];
                        while(temp!=-1){
                            desc_lock[temp]++;
                            temp=parent[temp];
                        }
                        success=true;
                    }
                }
            }
        }
        if(success==true){
            cout<<"true";
        }
        else{
            cout<<"false";
        }
    }
    return 0;
}