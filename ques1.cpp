#include<bits/stdc++.h>
using namespace std;
int main(){
    int n=5;
    vector<vector<int>>v;
    vector<int>ip(n);
    sort(ip.begin(),ip.end());
    for(int i=0;i<n;i++){
        cin>>ip[i];
    }
    int sum=0;
    // for(int i=0;i<5;i++){
    //     for(int j=i;j<n;j++){
    //         int mini=INT_MAX;
    //         for(int k=i;k<=j;k++){
    //             mini=min(mini,ip[k]);
    //         }
    //         sum+=mini;
    //     }
    // }
    for(int i=0;i<5;i++){
        int mini=ip[i];
        for(int j=i;j<n;j++){
            mini=min(ip[j],mini);
            sum+=mini;
        }
    }
    cout<<sum;
}