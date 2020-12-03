#include<bits/stdc++.h>
using namespace std;
struct trie
{
   long long val;
   trie *decendent[2];
};
trie *create()
{
   trie * head=new trie;
   head->val=0;
   head->decendent[0]=NULL;
   head->decendent[1]=NULL;
   return head;
}
void insert(trie * head, long long v)
{
   trie * temp=head;
   for (long long i=63;i>= 0;i--)
   {
      bool point=v&(1<<i);
      if (temp->decendent[point]==NULL)
         {temp->decendent[point]=create();}
      temp=temp->decendent[point];
   }
   temp->val=v;
}
long long Maxi(trie * head, long long a)
{
   trie * temp=head;
   for (long long i=63;i>=0;i--)
   {
      bool dot=a&(1<<i);
      if (temp->decendent[1-dot]!=NULL)
         temp=temp->decendent[1-dot];
      else
         temp=temp->decendent[dot];
   }
   return(a^temp->val);
}
int main()
{
	long long n,q,a;
	cin>>n>>q;
	vector<long long>v;
	for(long long i=0;i<n;i++)
	{
		cin>>a;
		v.push_back(a);
	}
	trie * root=create();
	for(long long i=0;i<n;i++)
	{
		insert(root,v[i]);
	}
	for(long long i=0;i<q;i++)
	{
		cin>>a;
		cout<<Maxi(root,a)<<endl;
	}
}