#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vll vector<ll>
#define pll pair<ll,ll>

int cmp(pair<ll,pll> a, pair<ll,pll> b)
{
    if (a.second.first == b.second.first)
        return (b.second.second > a.second.second);
    else
        return (a.second.first < b.second.first);
}

vll create_sfxarr(string s)
{
    ll n = s.size();
    vector<pair<ll, pll>> val(n);
    vll index(n);
    for (ll i=0;i<n;i++)      
    {
        ll rank = s[i];           
        ll next_rank=-1;
        if (i+1<n)
            next_rank =s[i + 1];
        val[i] = {i,{rank,next_rank}};
    }

    sort(val.begin(),val.end(), cmp);

    for (ll k=4; k<(n<<1); k<<=1)
    {
        ll r=0;
        ll p_r=val[0].second.first;
        val[0].second.first = r;
        index[val[0].first] = 0;

        for (ll i=1;i<n;i++)
        {
            if (val[i].second.first == p_r && val[i].second.second == val[i - 1].second.second)
            {
                p_r = val[i].second.first;
                val[i].second.first = r;
            }
            else
            {
                p_r = val[i].second.first;
                val[i].second.first = ++r;
            }
            index[val[i].first] = i;
        }

        for (ll i=0;i<n;i++)
        {
            ll nextindex = val[i].first + k / 2;
            if (nextindex < n)
                val[i].second.second = val[index[nextindex]].second.first;

            else
                val[i].second.second = -1;
        }
        sort(val.begin(),val.end(), cmp);
    }
    vll ans;
    for (auto i:val)
    {
        ans.push_back(i.first);
    }
    return ans;
}
vll find_rank(vll suffixArr){
    ll n=suffixArr.size();
    vll rank(n,0);
    ll i;
    for(i=0;i<n;i++){
        rank[suffixArr[i]]=i;
    }
    return rank;
}
vll find_lcp(string s, vll suffixArr) 
{ 
    ll n = suffixArr.size();  
    vll lcp(n,0); 
    vll invSuff(n,0); 
    for (ll i=0;i<n;i++) 
        invSuff[suffixArr[i]]=i; 
    ll k=0;
    for (ll i=0;i<n;i++) 
    { 
        if(invSuff[i]==n-1) 
        { 
            k = 0; 
            continue; 
        } 
        ll j = suffixArr[invSuff[i]+1]; 
        while (i+k<n && j+k<n && s[i+k]==s[j+k]) 
            k++; 
  
        lcp[invSuff[i]] = k; 
        if (k>0) 
            k--; 
    } 
    return lcp; 
}
void build(vll &a, vll &tree, ll start, ll end,ll treenode){
if(start==end)
{
tree[treenode]=a[start];
return;
}
ll mid;
mid=(start+end)/2;
build(a,tree,start,mid,2*treenode);
build(a,tree,mid+1,end,2*treenode+1);
tree[treenode]=min(tree[2*treenode],tree[2*treenode+1]);
return;
}

ll query(vll &tree, ll start, ll end, ll l, ll r,ll treenode){
if(start>r||end<l)
return INT_MAX;
if(start>=l&&end<=r)
return tree[treenode];
ll mid;
mid=(start+end)/2;
ll e=query(tree,start,mid,l,r,2*treenode);
ll f=query(tree,mid+1,end,l,r,2*treenode+1);
return min(e,f);
}

ll rangemin(vll &tree,ll start,ll end, ll i, ll j,ll treenode) {
        if(i > j) {
            ll t = i;
            i = j;
            j = t;
        }
        return query(tree,start,end, i, j - 1,treenode);
}

int main(){
    string s;
    cin>>s;
    string k=s;
    ll n=s.size();
    string s_a=s;
    reverse(s_a.begin(),s_a.end());
    s=s+'#'+s_a;
    ll n2=s.size();
    vll ans=create_sfxarr(s);
    vll rank=find_rank(ans);
    vll lcp=find_lcp(s,ans);

    // for(int i=0;i<n;i++){
    //     cout<<ans[i]<<endl;
    // }
    ll length=0;
    ll pos=0;
    vll tree(4*n2);
    build(lcp,tree,0,n2-1,1);
    for(ll i=0;i<n;i++)
    { ll len=rangemin(tree,0,n2-1,rank[i],rank[n2-i-1],1);
        if(len*2-1>length){
              length=len*2-1;
              pos=i-len+1;
        }
        if(len*2-1==length){
            if(s.substr(pos,length)>s.substr(i-len+1,length)){
                pos=i-len+1;
            }
        }
        if(i!=0){
                len = rangemin(tree,0,n2-1,rank[i],rank[n2-i],1);
                if(len*2>length) {
                    length=len*2;
                    pos=i-len;
                }
                if(len*2==length){
                    if(s.substr(pos,length)>s.substr(i-len,length)){
                        pos=i-len;
                    }
                }
            }
    }
  cout<<s.substr(pos,length)<<endl;
}
