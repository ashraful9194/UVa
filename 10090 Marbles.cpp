/**
    UVa_10090 - Marbles
    Topic : EGCD............

*/
#include<bits/stdc++.h>
//pbds
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
template <typename T>   using orderedSet =tree<T, null_type, greater<T>,rb_tree_tag, tree_order_statistics_node_update>;
#define int long long
typedef unsigned long long ull;
typedef pair<int,int> pii;
#define pb push_back
//BFS+DFS
#define boundary(i,j) (i>=0 && i<n && j>=0 && j<m)
int X[]= {-1,1,0,0};
int Y[]= {0,0,1,-1};
int n;
int extended_euclid(int a,int b,int *x,int *y)
{
    if(b==0)
    {
        *x=1;
        *y=0;
        return a;
    }
    int x1,y1;
    int g=extended_euclid(b,a%b,&x1,&y1);
    *x=y1;
    *y=x1-(a/b)*y1;
    return g;
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while(cin>>n)
    {
        /**
          we know x and y using  extended eucledean method.........
          ax+by=g [by bezoults identity]
          so, a*(cx/g)+b*(cy/g)=c [c must be divisible by g]........
          Let x0=cx/g and y0=cy/g

          so, ax0+by0=c.............................(1)

          Now a*(x0+bk/g)+b*(y0-ak/g)=c..............(2) same as (1)

          As x0+bk/g>=0 and y0-ak/g>=0 so the range of k is (-gx0/b)<=k<=(gy0/a)........lo<=k<=hi

          Follow the below procedure to find lo and hi and to proceed further.
        */
        if(n==0)
            break;
        int c1,c2,n1,n2;
        int x,y;
        cin>>c1>>n1>>c2>>n2;
        int g=extended_euclid(n1,n2,&x,&y);

        if(n%g)
        {
            cout<<"failed"<<endl;
            continue;
        }

        int x0=(x*n)/g;
        int y0=(y*n)/g;
        ///Always use floor and ceil function for negative numbers just for safety.............
        int lo=ceil(-(double)(g*x0)/(double)n2);
        int hi=floor((double)(g*y0)/(double)n1);

        if(lo>hi)
        {
            cout<<"failed"<<endl;
            continue;
        }
        /**
        Why only use the lo and hi value as k????
        Ans : cause k*[c1*(n2/g)-c2*(n1/g)].........And the portion in third bracket can be either positive or negative
              Thats why we only use the lo and hi value as k to minimize or maximize our answer.
        */
        int cost1=c1*(x0+lo*(n2/g))+c2*(y0-lo*(n1/g));
        int cost2=c1*(x0+hi*(n2/g))+c2*(y0-hi*(n1/g));
        int res1,res2;
        if(cost1<cost2) res1=(x0+lo*(n2/g)),res2=(y0-lo*(n1/g));
        else res1=(x0+hi*(n2/g)),res2=(y0-hi*(n1/g));
        cout<<res1<<" "<<res2<<endl;
    }
}
