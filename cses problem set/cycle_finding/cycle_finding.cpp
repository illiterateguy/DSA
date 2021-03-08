/*  problem is that i was tracking only 1 parent dist relaxation for decreasing the loop length but we have to check for all 
edges involving the loop . thus certain structure could be made by which if  dist of vertice decreased 
all loops involving that vertice be decreased and checked for negative.
*/

#include <bits/stdc++.h>
using namespace std;

#define minll (long long int)(-1e15)
#define maxll (long long int)(1e15)
#define F first 
#define S second 
#define arrsize (int)(2505)

set<pair<int,int>> g[arrsize];
vector <bool> vis(arrsize,false);
vector <bool> temp_vis(arrsize,false);
//vector <int> level(arrsize,-1);
vector <pair <long long int,int>> loop(arrsize,{maxll,0});
vector <long long int> prefix_sum(arrsize,maxll);
vector <int> parent(arrsize,0);
bool has_loop = false;
int n,m;

void printloop(long long count, int x , int y)
{
    if (count < 0)
    {
        // print loop
        cout << "YES" << endl;
        cout << x << " ";
        stack <int> s;
        while(x != 0 && x != y)
        {
            s.push(x);
            x = parent[x];
        }       
        cout << y << " ";
        while(!s.empty())   
        {
            cout << s.top() << " ";
            s.pop();  
        }	     
        
        has_loop = true;
    }
}

void dfs(int i)
{   
    cout << "running node: " << i << endl;    
    
    
    for (pair <int,int>  j : g[i])
    {
    	if (!has_loop)
        {
            if (!temp_vis[j.S])
            {
                //level[j.S] = level[i] + 1;
                cout << "visiting : " << j.S << endl;

                if (!vis[j.S])
                {
                    prefix_sum[j.S] = prefix_sum[i] + j.F; 
                    parent[j.S] = i;
                    vis[j.S] = true;
                    temp_vis[j.S] = true;
                    //cout << j.S << " " << level[j.S] << " " << prefix_sum[level[j.S]] << " " <<  endl;
                    dfs(j.S);
                
                    prefix_sum[j.S] = maxll; 
                    //level[j.S] = -1;
                    parent[j.S] = 0;
                    temp_vis[j.S] = false;
                }
                else if(loop[j.S] != make_pair(maxll,0) && prefix_sum[i] + j.F < prefix_sum[j.S]) 
                {
                    loop[j.S].F += prefix_sum[i] + j.F - prefix_sum[j.S];
                    prefix_sum[j.S] = prefix_sum[i] + j.F; 
                    //parent[j.S] = i;

                    cout << "loop value decreased to : " << loop[j.S].F << endl;

                    printloop(loop[j.S].F,loop[j.S].S,j.S);
                    if (has_loop)
                        return;
                }
            }    
            else
            {
                // check if there is a loop with i and j by checking that if j is a parent of i
                cout << "checking loop :" << endl;
                cout << "x = " << i << " y = " << j.S << endl;
                int x = i ,y = j.S;
                //cout << x << " " << y << " " << level[x] << " " << level[y] << " " << prefix_sum[level[x]] << " " << prefix_sum[level[y]] << endl;
                long long count = prefix_sum[x] - prefix_sum[y] + j.F;

                if (count < loop[j.S].F)
                    loop[j.S] = {count,i};
                cout << "count " << count << endl;
                
                printloop(count,x,y);
                if (has_loop)
                    return;
                
            }
        }
    }
}

int main()
{
    int a,b,c;
    cin >> n >> m;
    
    for(int j = 0; j < m; j++)
    {
        cin >> a >> b >> c;
        g[a].insert({c,b});
    }
    
    // print the graph
    cout << "graph : " << endl; 
    for (int i = 1; i <= n; i++)
    {
        cout << i << " : ";
        for (auto j : g[i])
            cout << j.S << "," << j.F << "  ";
        cout << endl;    
    }
    cout << endl;

   	for (int i = 1; i <= n; i++)
   	{
   		if (!vis[i])
    	{
    	    vis[i] = true;
            temp_vis[i] = true;
            //level[i] = 1;
    	    //cout << "dfs on :" << i << endl;
    	    dfs(i);
            //level[i] = -1;
            temp_vis[i] = false;
    	}    
    }    
    
    if (!has_loop)
    	cout << "NO" << endl;
}
