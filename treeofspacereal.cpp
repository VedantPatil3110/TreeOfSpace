#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m,q;
	cin>>n>>m>>q;
	vector<string>names(n);
	unordered_map<string,int>mp;
	for(int i=0;i<n;i++){
		cin>>names[i];
		mp[names[i]]=i;
	}
	vector<vector<int>>children(n);
	vector<int>parent(n,-1);
	for(int i=1;i<n;i++){
		parent[i]=(i-1)/m;
		children[parent[i]].push_back(i);
	}
	vector<int>lockstatus(n,-1);
	vector<int>desc_locked(n,0);
	while(q--){
		int type,uid;
		string nodename;
		cin>>type>>nodename>>uid;
		int node=mp[nodename];
		bool success=false;
		if(type==1){
			if(lockstatus[node]==-1&&desc_locked[node]==0){
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
					lockstatus[node]=uid;
					temp=parent[node];
					while(temp!=-1){
						desc_locked[temp]++;
						temp=parent[temp];
					}
					success=true;
				}
			}
		}
		else if(type==2){
			if(lockstatus[node]==uid){
				lockstatus[node]=-1;
				int temp=parent[node];
				while (temp!=-1) {
					desc_locked[temp]--;
					temp=parent[temp];
				}
				success=true;
			}
		}
		else if(type==3){
			if(lockstatus[node]==-1&&desc_locked[node]>0){
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
					queue<int>q;
					q.push(node);
					vector<int>tounlock;
					while(!q.empty()){
						int u=q.front();
						q.pop();
						if(lockstatus[u]!=-1){
							if(lockstatus[u]==uid){
								tounlock.push_back(u);
							}
							else{
								found=true;
								break;
							}
						}
						for(auto v:children[u]){
							q.push(v);
						}
					}
						if(!found && !tounlock.empty()){
							for(auto u:tounlock){
								lockstatus[u]=-1;
								int temp2=parent[u];
								while(temp2!=-1){
									desc_locked[temp2]--;
									temp2=parent[temp2];
								}
							}
							lockstatus[node]=uid;
							temp=parent[node];
							while(temp!=-1){
								desc_locked[temp]++;
								temp=parent[temp];
							}
							success=true;
						}
				}
			}
		}
		cout<<(success?"true":"false")<<'\n';
	}
	return 0;
}