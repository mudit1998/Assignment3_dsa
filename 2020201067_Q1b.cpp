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
int main()
{
    string s;
    ll k;
    cin>>s>>k;
    ll n=s.size();
    vll ans=create_sfxarr(s);
    ll final=-1;
    for( ll i=0;i<(n-k+1);i++)
    {
        ll j=i+k-1;
        ll count=0;
        ll ans_i =ans[i];
        ll ans_j =ans[j];
        while((ans_j<n)&&(ans_i<n)&&s[ans_i]==s[ans_j])
        {
            count++;
            ans_i++;
            ans_j++;
        } 
        if(count!=0&&final<count)final=count;
    }
    cout<<final<<endl;
    return 0;
}