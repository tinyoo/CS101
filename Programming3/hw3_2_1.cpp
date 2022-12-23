#include<bits/stdc++.h>
#define ll long long
#define paa pair<ll,pair<int,int> >
using namespace std;
priority_queue<paa,vector<paa>,greater<paa> >q;
map<int,ll>mp[200004];
int n,m,k;
int getu(paa A){
    return A.second.first;
}
int getv(paa A){
    return A.second.second;
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    while(!q.empty())q.pop();
    for(int i=1;i<=n;i++)mp[i].clear();
    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        q.push({1LL*w,{u,v}});
    }
    ll ans=0;
    while(k&&(!q.empty())){
        paa now=q.top();q.pop();
        int u=getu(now),v=getv(now);
        if(mp[u].count(v))continue;
        for(auto x:mp[u]){
            q.push({x.second+now.first,{v,x.first}});
        }
        for(auto x:mp[v]){
            q.push({x.second+now.first,{u,x.first}});
        }
        mp[v][u]=mp[u][v]=now.first;
        ans=now.first;
        k--;
    }
    printf("%lld\n",ans);
    return 0;
}