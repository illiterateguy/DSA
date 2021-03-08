#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define minll (long long int)(-1e15)
#define maxll (long long int)(1e15)
#define F first 
#define S second 
#define arrsize (int)(2505)

struct edge
{
    int a,b,cost;
};

vector <edge> edges(arrsize * 2);
//vector <bool> visited (arrsize,false);
vector <int> parent(arrsize,0);
vector <ll> dist(arrsize,maxll);
int n,m;

bool bellman_ford(int i)
{
    dist[i] = 0;
    //cout << "dist " << i <<  " decreased to " << dist[i] << endl;
    int count = 0;
    int last;

    for (;;)
    {
        bool find_any = false;
        count++;

        for (int j = 0; j < m; j++)
        {
            auto it = edges[j];
            //cout << "checking edge : " << it.a << " " << it.b << " " << it.cost << endl;
            //cout << "dist "  << it.a  << " = " << dist[it.a] << " " << it.b << " = " << dist[it.b] << endl;  

            if (dist[it.a] != maxll)
            {
                if (dist[it.a] + it.cost < dist[it.b])
                {
                    dist[it.b] = dist[it.a] + it.cost;
                    parent[it.b] = it.a; 
                    //cout << "dist " << it.b <<  " decreased to " << dist[it.b] << endl;
                    find_any = true;
                    last = it.b;
                }    
            }
        }    

        if (!find_any || count >= n)
            break;     
    }

    if (count >= n)
    {
        //cout << "last : " << last << endl;

        for (int i = 0; i < n; i++)
            last = parent[last];

        int another = last;    
        another = parent[another];

        
        // print the loop
        cout << "YES" << endl;
        cout << last << " ";

        vector <int> ans;
        while(another != last)
        {
            ans.push_back(another);
            another = parent[another];
        }
        reverse(ans.begin(),ans.end());

        for (auto it : ans)
            cout << it << " ";
        cout << last << endl;



        return true;
    }
    else
    {
        return false;
    }
}

int main()
{    
    edge temp;
    cin >> n >> m;
    //cout << "n : " << n << " m : "  << m << endl;

    for (int i =0; i < m; i++)
    {
        cin >> temp.a >> temp.b >> temp.cost;
        edges[i] = temp; 
    }

    /*cout << "edges : " << endl;
    for (int i = 0; i < m; i++)
        cout << edges[i].a << " " << edges[i].b << " " << edges[i].cost << endl;
    cout << endl; 
    */

    bool did_find = false;

    for (int i =1 ; i <= n; i++)
    {
        if (dist[i] == maxll && !did_find)
        {    
            //cout << "performing bellman_ford on " << i << endl;
            did_find = bellman_ford(i);
        }    
    }

    if (!did_find)
        cout << "NO" << endl;

}