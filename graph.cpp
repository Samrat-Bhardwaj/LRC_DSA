#include<iostream>
#include<priority_queue>

using namespace std;

// bfs to get cycle 

void bfs(vector<vector<int>>& graph, int src){
    queue<int> q;

    q.push(src);

    int level=0;
    while(q.size()){
        int s=q.size();

        cout<<level<<"-> ";
        while(s--){
            int t=q.front();
            q.pop();

            cout<<t<<" ";

            for(int nbr:graph[t]){
                q.push(nbr);
            }
        }
        cout<<endl;
        level++;
    }
}

// cycle detection
void bfs(vector<vector<int>>& graph, int src){
    queue<int> q;
    vector<bool> vis(graph.size(),false);

    q.push(src);

    bool cycle =false;

    int level=0;

    while(q.size()){
        int s=q.size();

        cout<<level<<"-> ";
        while(s--){
            int t=q.front();
            q.pop();
            
            if(vis[t]) cycle=true;

            vis[t]=true;

            cout<<t<<" ";

            for(int nbr:graph[t]){
                q.push(nbr);
            }
        }
        cout<<endl;
        level++;
    }
}

// topo sort with cycle 
void dfs_topo(vector<vector<innt>>& graph, int src,vector<int>& ans,vector<int >& vis){
   vis[src]=1;

   for(int nbr:graph[src]){
       if(vis[nbr]==0){
           dfs_topo(graph,nbr,ans,vis);
       } else if(vis[nbr]==1){
           cycle=true;
       } else {
           continue;
       }
   } 

    vis[src]=2;
   ans.push_back(src);
}

vector<int> topo_sort(vector<vector<int>>& graph,int N){
    vector<int> vis(N,0);

    vector<int> ans;

    for(int i=0; i<N; i++){
        if(!vis[i]){
            dfs_topo(graph,i,ans,vis);
        }
    }

    reverse(ans.begin(),ans.end());

    return ans;

}

// 
void dfs_topo(vector<vector<innt>>& graph, int src,vector<int>& ans,vector<bool>& vis){
   vis[src]=true;

   for(int nbr:graph[src]){
       if(!vis[nbr]){
           dfs_topo(graph,nbr,ans,vis);
       }
   } 

   ans.push_back(src);
}

vector<int> topo_sort(vector<vector<int>>& graph,int N){
    vector<bool> vis(N,false);

    vector<int> ans;

    for(int i=0; i<N; i++){
        if(!vis[i]){
            dfs_topo(graph,i,ans,vis);
        }
    }

    reverse(ans.begin(),ans.end());

    return ans;

}

// leet 802 ========================================================= 
class Solution {
public:
    bool dfs(vector<vector<int>>& graph, int src,vector<int>& vis,vector<int>& ans){
        vis[src]=1;
        
        for(int nbr:graph[src]){
            if(vis[nbr]==0){
                if(dfs(graph,nbr,vis,ans)){
                    return true;
                }
            } else if(vis[nbr]==1){
                return true;
            } 
        }
        
       
        vis[src]=2;
        return false;
    }
    
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n=graph.size();
        
        vector<int> vis(n,0);
        vector<int> ans;
        
        for(int i=0; i<n; i++){
            if(vis[i]==0){
               bool cycle= dfs(graph,i,vis,ans);
                if(!cycle){
                    ans.push_back(i);
                }
            } else if(vis[i]==2){
                ans.push_back(i);
            }
        }
        
        return ans;
    }
};




// kahn's algorithm 

vector<int> kahn_topo(vector<vector<int>>& graph){
    int n=graph.size();

    vector<int> indegree(n,0);

    for(int i=0; i<n; i++){
        for(int nbr:graph[i]){
            indegree[nbr]++;
        }
    }

    queue<int> q;
    for(int  i=0; i<n; i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }

    vector<int> ans;

    while(q.size()){
        int u=q.front();
        q.pop();

        ans.push_back(t);
        for(int v:graph[u]){
            indegree[v]--;
            if(indegree[v]==0){
                q.push(v);
            }
        }
    }

    if(ans.size()!=n){
        cout<<"cycle!!!!"<<"\n";
    } 

    return ans;
}


// leet 329 =======================

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        
        
        int n=matrix.size();
        int m=matrix[0].size();
        
        vector<vector<int>> indegree(n,vector<int>(m,0));
        
        vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};
        
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                for(auto dir:dirs){
                    int x=i+dir[0];
                    int y=j+dir[1];
                    
                    if(x>=0 && y>=0 && x<n && y<m && matrix[x][y]>matrix[i][j]){    
                        indegree[x][y]++;
                    }
                }
            }
        }

        queue<int> q;

        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(indegree[i][j]==0){
                      q.push(i*m+j);  
                }
            }
        }

        int level=1;

        while(q.size()){
            int size=q.size();
            while(size--){
                int idx=q.front();
                q.pop();

                int i=idx/m;
                int j=idx%m;

                for(auto &dir:dirs){
                    int x=i+dir[0];
                    int y=j+dir[1];
                    
                    if(x>=0 && y>=0 && x<n && y<m && matrix[x][y]>matrix[i][j]){    
                        indegree[x][y]--;

                        if(indegree[x][y]==0){
                            q.push(x*m+y);
                        }
                    }
                }
            }
            level++;
        }

        return level-1;
    }
};

// leet 210 ============

class Solution {
public:
    vector<int> findOrder(int n, vector<vector<int>>& edges) {
        vector<int> indegree(n,0);
        vector<vector<int>> graph(n);
        
        for(auto e:edges){
            int u=e[0];
            int v=e[1];
            
            indegree[v]++;
            graph[u].push_back(v);
        }
        
        queue<int> q;
        vector<int> ans;
        
        for(int i=0; i<n; i++){
            if(indegree[i]==0){
                q.push(i);
            }
        }


        while(q.size()){
            int u=q.front();
            q.pop();

            ans.push_back(u);

            for(int v:graph[u]){
                indegree[v]--;
                if(indegree[v]==0){
                    q.push(v);
                }
            }

        }

        if(ans.size()!=n){
            return {};
        } else {
            return ans;
        }
    }
};


// kosaraju algo===================

void dfs_kosa(int src, vector<vector<int>>& graph,vector<bool>& vis,stack<int>& st){
    vis[src]=true;

    for(int nbr:graph[src]){
        if(!vis[nbr]){
            dfs_kosa(nbr,graph,vis,st);
        }
    }

    st.push(src);
}

void dfs_kosa_2(vector<vector<int>>& ngraph, vector<bool>& vis,int src){
    vis[src]=true;

    for(int nbr:graph[src]){
        if(!vis[nbr]){
            dfs_kosa_2(ngraph,vis,nbr);
        }
    }
}

int kosaraju(vector<vector<int>>& graph){
    int n=graph.size();

    stack<int> st;
    vector<bool> vis(n,false);

    for(int i=0; i<n; i++){
        if(!vis[i]){
            dfs_kosa(i,graph,vis,st);
        }
    }


    int count=0;
    vis.resize(n,false);

    vector<vector<int>> ngraph(n);

    for(int i=0; i<n; i++){
        int u=i;
        for(int v:graph[u]){
            ngraph[v].push_back(u);
        }
    }

    while(st.size()){
        int t=st.top();
        st.pop();

        if(!vis[t]){
            count++;
            dfs_kosa_2(ngraph,vis,t);
        }
    }

    return count;
}


// leet 130 ==========================================

void dfs(int i, int j, vector<vector<char>>& board){
    board[i][j]='#';
        
    int n=board.size();
        int m=board[0].size();

    vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};

    for(auto dir:dirs){
        int x=i+dir[0];
        int y=j+dir[1];

        if(x>=0 && y>=0 && x<n && y<m && board[x][y]=='O'){
            dfs(x,y,board);
        }
    }
}

void solve(vector<vector<char>>& board) {
    int n=board.size();
    int m=board[0].size();

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(i==0 || j==0 || i==n-1 || j==m-1){
                if(board[i][j]=='O')
                    dfs(i,j,board);
            }
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(board[i][j]=='#'){
                board[i][j]='O';
            } else if(board[i][j]=='O'){
                board[i][j]='X';
            }
        }
    }
}

// leet 1162

int maxDistance(vector<vector<int>>& grid) {
    queue<int> q;

    int n=grid.size();
    int m=grid[0].size();

     vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j]==1){
                q.push(i*m+j);
            }
        }
    }

    if(q.size()==n*m || q.size()==0) return -1;


    int level=0;
    while(q.size()){
        int s=q.size();
        while(s--){
            int idx=q.front();
            q.pop();

            int i=idx/m;
            int j=idx%m;

            for(auto dir:dirs){
                int x=i+dir[0];
                int y=j+dir[1];

                if(x>=0 && y>=0 && x<n && y<m && grid[x][y]==0){
                    q.push(x*m+y);
                    grid[x][y]=1;
                }
            }
        }
        level++;
    }

    return level-1;
}

// leet 841 =================================================== 
void dfs_cvr(int src,vector<vector<int>>& rooms, vector<bool>& vis){
    vis[src]=true;

    for(int nbr:rooms[src]){
        if(!vis[nbr]){
            vis[nbr]=true;
            dfs_cvr(nbr,rooms,vis);
        }
    }
}

bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n=rooms.size();

        vector<bool> vis(n,false);

        dfs_cvr(0,rooms,vis);

        for(int i=0; i<n; i++){
            if(vis[i]==false) return false;
        }

        return true;
}

// https://www.lintcode.com/problem/663/

void wallsAndGates(vector<vector<int>> &rooms) {
        int n=rooms.size();
        int m=rooms[0].size();

        queue<int> q;
     vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};


        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(roooms[i][j]==0){
                    q.push(i*m+j);

                }
            }
        }

        int level=0;
        while(q.size()){
            int s=q.size();
            while(s--){
                int idx=q.front();
                q.pop();
                
                int i=idx/m;
                int j=idx%m;

            for(auto dir:dirs){
                int x=i+dir[0];
                int y=j+dir[1];

                if(x>=0 && y>=0 && x<n && y<m && rooms[x][y]==INT_MAX){
                    q.push(x*m+y);
                    rooms[x][y]=level+1;
                }
            }
        }
        level++;
    }
}

// leet 127 ===================================================== 

bool isOneDiff(string& a, string& b){
    int i=0;
    int c=0;

    while(i<a.size()){
        if(a[i]!=b[i]) c++;
        i++;    
    }

    return c==1;
}

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    int n=wordList.size();

    vector<bool> vis(n,false);

    queue<string> q;

    q.push(beginWord);

    int level=1;
    while(q.size()){
        int size=q.size();

        while(size--){
            string a=q.front();
            q.pop();


            for(int i=0; i<n; i++){
                if(!vis[i]){
                    if(isOneDiff(a,wordList[i])){
                        if(wordList[i]==endWord) return level+1;
                        vis[i]=true;
                        q.push(wordList[i]);
                    }
                }
            }
        }

        level++;
    }

    return 0;
}


// leet 126 ================================= 

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
    queue<vector<string>> q;

    q.push({beginWord});
    int spl=-1;  // shortest path length
    vector<vector<string>> ans;

    while(q.size()){
        int s=q.size();

        while(s--){
            auto top=q.front();

            q.pop();

            auto lw=top[top.size()-1];

            for(auto i=wordList.begin(); i!=wordList.end(); i++){
                if(*i==lw){
                    wordList.erase(i);
                    i--;
                }
            }

            for(int i=0; i<wordList.size(); i++){
                if(isOneDiff(lw,wordList[i])){
                    auto dup=top;

                    dup.push_back(wordList[i]);

                    if(wordList[i]==endWord){
                        if(spl==-1){
                            spl=dup.size();
                            ans.push_back(dup);
                        } else if(dup.size()==spl){
                            ans.push(dup);
                        }
                    } else {
                        q.push(dup);
                    }   
                }
            }

        }
    }
    return ans;
}

// is bipartite graph (leet 785) =================================== 

bool isOddCycle(vector<vector<int>>& graph, int src,vector<int>& vis){
    queue<int> q;

    q.push(src);

    int color=0;
    while(q.size()){
        int size=q.size();

        while(size--){
            int top=q.front();
            q.pop();

            if(vis[top]!=-1 && vis[top]!=color){
                return true;
            }

            vis[top]=color;

            for(int nbr:graph[top]){
                if(vis[nbr]==-1){
                    q.push(nbr);
                }
            }
        }
        color=(color+1)%2;
    }
    return false;
}

bool isBipartite(vector<vector<int>>& graph) {
    int n=graph.size();
    vector<int> vis(n,-1);

    for(int i=0; i<n; i++){
        if(vis[i]==-1){
            if(isOddCycle(graph,i,vis)) return false;
        }
    }

    return true;
}

// https://www.hackerrank.com/challenges/journey-to-the-moon/problem

int dfs(int src,vector<vector<int>>& graph, vector<bool>& vis){
    vis[src]=true;

    int size=0;
    
    for(int nbr:graph[src]){
        if(!vis[nbr]){
            size+=dfs(nbr,graph,vis);
        }
    }

    return size+1;
}

long long journeyToMoon(int n, vector<vector<int>> astronaut) {
    vector<vector<int>> graph(n);

    for(auto edge:astronaut){
        int u=edge[0];
        int v=edge[1];

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<bool> vis(n,false);

    vector<int> sizes;

    for(int i=0; i<n; i++){
        if(!vis[i]){
            int size=dfs(i,graph,vis);
            sizes.push_back(size);
        }
    }

    long long ans=0;
    long long csum=sizes[0];
    for(int i=1; i<sizes.size(); i++){
        ans+=(csum*sizes[i]);
        csum+=sizes[i];
    }

    return ans;
}

// leet 463 =================================================================================== 

int islandPerimeter(vector<vector<int>>& grid) {
    int ans=0;

    vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};

    for(int i=0; i<grid.size(); i++){
        for(int j=0; j<grid[i].size(); j++){
            if(grid[i][j]==1){
                int nbrs=0;
                for(auto dir:dirs){
                    int x=i+dir[0];
                    int y=j+dir[1];

                    if(x>=0 && y>=0 && x<grid.size() && y<grid[0].size() && grid[x][y]==1){
                        nbrs++;
                    }
                }

                ans+=(4-nbrs);
            }
        }
    }
    return ans;        
}

// union find ======================================== 
vector<int> parent;
vector<int> size;

int findPar(int u){
    if(parent[u]==u) return u;

    return parent[u]=findPar(parent[u]);
}

void merge(int par1, int par2){
    if(size[par1]<size[par2]){
        parent[par1]=par2;
        size[par2]+=size[par1];
    } else {
        parent[par2]=par1;
        size[par1]+=size[par2];
    }
}

vector<vector<int>> union_find(int n, vector<vector<int>>& edges){
    parent.resize(n,0);
    size.resize(n,0);

    for(int i=0; i<n; i++){
        parent[i]=i;
        size[i]=1;
    }

    for(vector<int>& edge:edges){
        int u=edge[0];
        int v=edge[1];

        int par1=findPar(u);
        int par2=findPar(v);

        if(par1!=par2)
            merge(par1,par2);
    }
    
}


// leet 684 ===========================================================

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n=edges.size();

    for(int i=0; i<=n; i++){
        parent.push_back(i);
        size.push_back(1);
    }
    vector<int> ans;
    
    for(auto & edge:edges){
        int u=edge[0];
        int v=edge[1];

        int p1=findPar(u);
        int p2=findPar(v);

        if(p1==p2){
            ans=edge;
        } else {
            merge(p1,p2);
        }
    }

    return ans;
}

// leet 1061 ========================


string smallestEquivalentString(string s1, string s2, string baseStr) {
    par.resize(26,0);

    for(int i=0; i<26; i++){
        par[i]=i;
    }

    for(int i=0; i<s1.size(); i++){
        int p1=findPar(s1[i]-'a');
        int p2=findPar(s2[i]-'a');

        if(p1!=p2){
            if(p1<p2){
                par[p2]=p1;
            } else {
                par[p1]=p2;
            }
        }
    }

    string ans="";

    for(int i=0; i<baseStr.size(); i++){
        int par=findPar(baseStr[i]-'a');

        ans+=(par+'a');
    }

    return ans;
}

// leet 695 ============================================= 
vector<int> par;
vector<int> size;

int fp(int u){
    return par[u] == u ? u : par[u] = fp(par[u]);
}

int maxAreaOfIsland(vector<vector<int>>& grid) {
    int n=grid.size();
    int m=grid[0].size();

    par.resize(n*m,1);
    size.resize(n*m,0);

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            int idx=i*m+j;
            if(grid[i][j]==1){
                par[idx]=idx;
                size[idx]=1;
            } else {
                par[idx]=-1;
            }
        }
    }

    vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j]==1){
                int idx=i*m+j;

                int p1=fp(idx);

                for(vector<int>& dir:dirs){
                    int x=i+dir[0];
                    int y=j+dir[1];

                    if(x>=0 && y>=0 && x<n && y<m && grid[x][y]==1){
                        int jdx=x*m+y;

                        int p2=fp(jdx);

                        if(p1!=p2){
                            par[p2]=p1;
                            size[p1]+=size[p2];
                        }
                    }
                }
            }
        }
    }

    int max_area=0;
    for(int i=0; i<n*m; i++){
        if(par[i]==i){
            max_area=max(max_area,size[i]);
        }
    }

    return max_area;
}

// leet 839 =============================================== 

unordered_map<string,string> par;

string find_par(string u){
    return par[u]==u ? u : par[u] = find_par(par[u]);
}

bool isSimilar(string& a, string& b){
    int count=0;

    for(int i=0; i<a.size(); i++){
        if(a[i]!=b[i]) count++;
    }

    return count==2 || count==0;
}

int numSimilarGroups(vector<string>& strs) {
    for(auto s:strs){
        par[s]=s;
    }

    for(int i=0; i<strs.size(); i++){
        string p1=find_par(strs[i]);
        for(int j=i+1; j<strs.size(); j++){
            if(isSimilar(strs[i],strs[j])==false) continue;

            string p2=find_par(strs[j]);

            if(p1!=p2){
                par[p2]=p1;
            }
        }
    }


    int comps=0;
    for(auto i:par){
        if(i.first==i.second) comps++;
    }
    return comps;
}

// leet 1905 =========================================================================== 

bool isValid(vector<vector<int>>& grid1, vector<vector<int>>& grid2, int i, int j, int n, int m){
    vector<vector<int>> dirs={{0,1},{1,0},{-1,0},{0,-1}};

    grid2[i][j]=0;

    bool ans=true;
    
    for(auto dir:dirs){
        int x=i+dir[0];
        int y=j+dir[1];

        if(x>=0 && y>=0 && x<n && y<m && grid2[x][y]==1){
            if(grid1[x][y]!=1) ans=false;
            
            ans=isValid(grid1,grid2,x,y,n,m) && ans;
        }
    }

    return ans;
}

int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
    int n=grid.size();
    int m=grid[0].size();

    int count=0;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid2[i][j]==1 && grid1[i][j]==1){
                bool valid=isValid(grid1,grid2,i,j,n,m);

                if(valid==true) count++;
            }
        }
    }

    return count;
}

// leet 305 =================================================== 
vector<int> par;

int findPar(int u){
    return par[u]==u ? u : par[u] = findPar(par[u]);
}

vector<int> numIslands2(int n, int m, vector<vector<int>>& positions) {
    par.resize(n*m,-1);

    int count=0;
    vector<int> ans;
    vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};

    for(vector<int>& pos:positions){
        int x=pos[0];
        int y=pos[1];

        int idx=x*m+y;

        if(par[idx]!=-1){
            ans.push_back(count);
            continue;
        }

        count++;
        par[idx]=idx;

        for(vector<int>& dir:dirs){
            int i=x+dir[0];
            int j=y+dir[1];

            if(i>=0 && j>=0 && i<n && j<m && par[i*m+j]!=-1){
                int p1=findPar(i*m+j);
                int p2=findPar(idx);

                if(p1!=p2){
                    par[p2]=p1;
                    count--;
                }
            }
        }

        ans.push_back(count);
    }

    return ans;
}


// Kruskal algo =================================================================== 
vector<int> par;

int findPar(int u){
    return par[u]==u? u: par[u]=findPar(par[u]);
}

vector<vector<int>> spanning_tree_creation(int N,vector<vector<int>>& edges){
    vector<vector<int>> st(N); // spanning tree

    par.resize(N,0);

    for(int i=0; i<N; i++){
        par[i]=i;
    }

    for(vector<int>& edge:edges){
        int u=edge[0];
        int v=edge[1];

        int p1=findPar(u);
        int p2=findPar(v);

        if(p1!=p2){
            par[p2]=p1;
            st[u].push_back(v);
            st[v].push_back(u);
        }
    }

    return st;
}


// creation of MST =========================================================

vector<int> par;
vector<int> size;

int findPar(int u){
    return par[u]==u? u: par[u]=findPar(par[u]);
}

void merge(int p1, int p2){
    if(size[p1]<size[p2]){
        par[p1]=p2;
        size[p2]+=size[p1];
    } else {
        par[p2]=p1;
        size[p1]+=size[p2];
    }
}

vector<vector<int>> spanning_tree_creation(int N,vector<vector<int>>& edges){
    vector<vector<int>> mst(N); // spanning tree

    par.resize(N,0);

    for(int i=0; i<N; i++){
        par[i]=i;
    }

    sort(edges.begin(),edges.end(),[&](vector<int> a,vector<int> b){
        return a[2] < b[2];
    });

    for(vector<int>& edge:edges){
        int u=edge[0];
        int v=edge[1];

        int p1=findPar(u);
        int p2=findPar(v);

        if(p1!=p2){
            par[p2]=p1;
            mst[u].push_back(v);
            mst[v].push_back(u);
        }
    }

    return mst;
}

// leet 1584 ============================================= 

int getDis(vector<int>& point1, vector<int>& point2){
    return abs(point1[0]-point2[0]) + abs(point1[1]-point2[1]);
}

int minCostConnectPoints(vector<vector<int>>& points) {
    vector<vector<int>> edges;

    for(int i=0; i<points.size(); i++){
        for(int j=i+1; j<points.size(); j++){
            int dis=getDis(points[i],points[j]);

            edges.push_back({dis,i,j});
        }
    }

    sort(edges.begin(),edges.end());

    par.resize(n,-1);
    int n=points.size();

    for(int i=0; i<n; i++){
        par[i]=i;
    }

    int cost=0;
    for(auto& e:edges){
        int u=e[1];
        int v=e[2];

        int p1=findPar(u);
        int p2=findPar(v);

        if(p1!=p2){
            par[p1]=p2;
            cost+=e[0];
        }
    }

    return cost;
}

// leet 1168 (Optimize Water Distribution in a Village) ===========================================

int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
    for(int i=0; i<n; i++){
        pipes.push_back({0,i+1,wells[i]});
    }

    sort(pipes.begin(),pipes.end(),[&](vector<int> a, vector<int> b){
        return a[2] < b[2];
    });

    par.resize(n+1,-1);

    for(int i=0; i<=n; i++){
        par[i]=i;
    }

    int cost=0;
    for(auto& e:pipes){
        int u=e[0];
        int v=e[1];

        int p1=findPar(u);
        int p2=findPar(v);

        if(p1!=p2){
            par[p1]=p2;
            cost+=e[2];
        }
    }

    return cost;
}

// leet 1135 ================================================================== 

int minimumCost(int n, vector<vector<int>>& connections) {
    sort(pipes.begin(),pipes.end(),[&](vector<int> a, vector<int> b){
        return a[2] < b[2];
    });

    par.resize(n+1,-1);
    size.resize(n+1,1);

    for(int i=0; i<=n; i++){
        par[i]=i;
    }

    int comp=n;

    int cost=0;
    for(auto& e:pipes){
        int u=e[0];
        int v=e[1];

        int p1=findPar(u);
        int p2=findPar(v);

        if(p1!=p2){
            merge(p1,p2);
            cost+=e[2];
            comp--;
        }
    }

    return comp==1 ? cost : -1;
}

// leet 990 ============================================ 

vector<int> par;
vector<int> size;

int findPar(int u){
    return par[u]==u? u: par[u]=findPar(par[u]);
}

void merge(int p1, int p2){
    if(size[p1]<size[p2]){
        par[p1]=p2;
        size[p2]+=size[p1];
    } else {
        par[p2]=p1;
        size[p1]+=size[p2];
    }
}

bool equationsPossible(vector<string>& equations) {
    par.resize(26,-1);
    size.resize(26,1);

    for(int i=0; i<26; i++){
        par[i]=i;
    }

    for(string eq:equations){
        if(eq[1]=='='){
            int u=eq[0]-'a';
            int v=eq[3]-'a';

            int p1=findPar(u);
            int p2=findPar(v);

            if(p1!=p2){
                merge(p1,p2);
            }
        }
    }

    for(string eq:equations){
        if(eq[1]=='!'){
            int u=eq[0]-'a';
            int v=eq[3]-'a';

            int p1=findPar(u);
            int p2=findPar(v);

            if(p1==p2){
                return false;
            }
        }
    }
    return true;        
}


// leet 1319 ======================================================

vector<int> par;
vector<int> size;

int findPar(int u){
    return par[u]==u? u: par[u]=findPar(par[u]);
}

void merge(int p1, int p2){
    if(size[p1]<size[p2]){
        par[p1]=p2;
        size[p2]+=size[p1];
    } else {
        par[p2]=p1;
        size[p1]+=size[p2];
    }
}

int makeConnected(int n, vector<vector<int>>& connections) {
    if(connections.size()<n-1) return -1;

    int comps=n;
    par.resize(n,-1);
    size.resize(n,1);

    for(int i=0; i<n; i++){
        par[i]=i;
    }

    for(auto const& c:connections){
        int u=c[0];
        int v=c[1];

        int p1=findPar(u);
        int p2=findPar(v);

        if(p1!=p2){
            comps--;
            merge(p1,p2);
        }
    }

    return comps-1;
}

// leet 1202 ========================================================================= 

vector<int> par;
vector<int> size;

int findPar(int u){
    return par[u]==u? u: par[u]=findPar(par[u]);
}

void merge(int p1, int p2){
    if(size[p1]<size[p2]){
        par[p1]=p2;
        size[p2]+=size[p1];
    } else {
        par[p2]=p1;
        size[p1]+=size[p2];
    }
}

string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
    par.resize(s.size(),-1);
    size.resize(s.size(),1);

    int n=s.size();
    for(int i=0; i<n; i++){
        par[i]=i;
    }

    for(auto const& p:pairs){
        int u=p[0];
        int v=p[1];

        int p1=findPar(u);
        int p2=findPar(v);

        if(p1!=p2) merge(p1,p2);
    }

    unordered_map<int,string> m;

    for(int i=0; i<n; i++){
        int p=findPar(i);

        m[p]+=s[i];
    }

    for(auto &key:m){
        string &s=key.second;

        sort(s.begin(),s.end());   
    }

    unordered_map<int,int> pos;
    string ans="";

    for(int i=0; i<n; i++){
        int p=findPar(i);

        if(pos.count(p)==0){ // contains 
            ans+=m[p][0];
            pos[p]=1;
        } else {
            int idx=pos[p];
            ans+=m[p][idx];

            pos[p]++;
        }
    }

    return ans;
}


// leet 1202 ========================================================================= 

vector<int> par;
vector<int> size;

int findPar(int u){
    return par[u]==u? u: par[u]=findPar(par[u]);
}

void merge(int p1, int p2){
    if(size[p1]<size[p2]){
        par[p1]=p2;
        size[p2]+=size[p1];
    } else {
        par[p2]=p1;
        size[p1]+=size[p2];
    }
}

string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
    par.resize(s.size(),-1);
    size.resize(s.size(),1);

    int n=s.size();
    for(int i=0; i<n; i++){
        par[i]=i;
    }

    for(auto const& p:pairs){
        int u=p[0];
        int v=p[1];

        int p1=findPar(u);
        int p2=findPar(v);

        if(p1!=p2) merge(p1,p2);
    }

    unordered_map<int,string> m;

    for(int i=0; i<n; i++){
        int p=findPar(i);

        m[p]+=s[i];
    }

    for(auto &key:m){
        string &s=key.second;

        sort(s.rbegin(),s.rend());   
    }

    string ans="";

    for(int i=0; i<n; i++){
        int p=findPar(i);

        ans+=m[p].back();

        m[p].pop_back();
    }

    return ans;
}


// dijkstra algorithm ============================================================== 

class diPair{
    public:
    int par;
    int vtx;
    int w;
    int wsf;

    diPair(int par, int vtx, int w, int wsf){
        this->par=par;
        this->vtx=vtx;
        this->w=w;
        this->wsf=wsf;
    }
};

struct comp {
    bool operator()(diPair& a, diPair& b){
        return a.wsf < b.wsf;
    }
};

vector<vector<pair<int,int>>> graph(int N, vector<vector<pair<int,int>>>& graph, int src){
    priority_queue<diPair,vector<diPair>,comp> pq;

    pq.push({-1,src,0,0});
    vector<int> dis(N,(int)(1e8));

    int edgeCount=0;

    vector<int> parent(N,-1);

    vector<vector<pair<int,int>>> ngraph(N);

    while(edgeCount<=N-1){
        diPair top=pq.top(); pq.pop();

        int p=top.par;
        int u=top.vtx;
        int w=top.w;
        int wsf=top.wsf;

        if(dis[u]!=(int)(1e8)) continue;
        dis[u]=wsf;
        
        if(p!=-1){
            parent[u]=p;
            edgeCount++;
            ngraph[p].push_back({u,w});
        }

        for(auto nbr_pair:graph[u]){
            int nbr=nbr_pair.first;
            int weight=nbr_pair.second;

            if(dis[nbr]==(int)(1e8)){
                pq.push({u,nbr,weight,wsf+weight});
            }
        }

    }

}

// prim's algortihm ================================================================

class prims_pair{
    public:
    int par;
    int u;
    int wt;

    prims_pair(int par, int u, int wt){
        this->par=par;
        this->u=u;
        this->wt=wt;
    }
};

struct comp{
    bool operator()(prims_pair& a, prims_pair& b){
        return a.wt < b.wt;
    }
};

vector<vector<pair<int,int>> prims_algo(int n,vector<vector<pair<int,int>>& graph){
    vector<vector<pair<int,int>>> mst;

    priority_queue<prims_pair, vector<prims_pair>, comp > pq;

    int edgeCount=0;

    pq.push({-1,0,0}); 
    vector<bool> vis(n,false);
    vector<int> dis(n,(int)1e8);

    while(edgeCount<n-1){
        auto top=pq.top(); pq.pop();

        int wt=top->wt
        int u=top->u;
        int p=top->par;

        if(vis[u]) continue;
        vis[u]=true;
        if(par!=-1)
            mst[p].push_back({u,wt});

        for(auto nbr_pair:graph[u]){
            int nbr=nbr_pair.first;
            int weight=nbr_pair.second;

            if(!vis[nbr]){
                pq.push({u,nbr,weight});
            }
        }
    }

    return mst;
}


// leet 743 ============================================================ 

int dijkstra_743(vector<vector<pair<int,int>>>& graph, int n, int src){
    priority_queue<  pair<int,int>,  vector<pair<int,int>> ,   greater<pair<int,int>>   > pq;

    vector<int> dis(n+1,-1);
    vector<bool> vis(n+1,false);

    pq.push({0,src});  // wsf, src

    while(pq.size()){
        auto top=pq.top(); pq.pop();

        int wsf=top.first;
        int u=top.second;

        if(vis[u]) continue;

        vis[u]=true;
        dis[u]=wsf;

        for(auto &nbr_pair:graph[u]){
            int wt=nbr_pair.second;
            int nbr=nbr_pair.first;

            if(!vis[nbr]){
                pq.push({wsf+wt,nbr});
            }
        }
    }

    int ans=0;
    for(int i=1; i<=n; i++){
        if(dis[i]==-1) return -1;
        ans=max(ans,dis[i]);
    }

    return ans;
}

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    vector<vector<pair<int,int>>> graph(n+1);

    for(auto const &t:times){
        int u=t[0];
        int v=t[1];
        int w=t[2];

        graph[u].push_back({v,w});
    }        

    return dijkstra_743(graph,n,k);
}



// leet 1631 ===========================================================

int minimumEffortPath(vector<vector<int>>& heights) {
    int n=heights.size();
    int m=heights[0].size();

    vector<vector<bool>> vis(n,vector<bool>(m,false));

    priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>> > pq;

    pq.push({0,0}); // effort, index

    vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};

    while(pq.size()){
        auto top=pq.top(); pq.pop();

        int effort=top.first;
        int idx=top.second;

        int i=idx/m;
        int j=idx%m;

        if(vis[i][j]) continue;

        if(i==n-1 && j==m-1) return effort;
        vis[i][j]=true;

        for(auto const& dir: dirs){
            int r=i+dir[0];
            int c=j+dir[1];

            if(r>=0 && c>=0 && r<n && c<m && !vis[r][c]){
                int nEffort=max(effort,abs(heights[r][c]-heights[i][j]));
                pq.push({nEffort,r*m+c});
            }
        }
    }

    return 1000;
}

// bellman ford ================================================================= 

vector<int> bellman_ford(int N,vector<vector<int>>& edges, int src){
    vector<int> dis(N,(int)1e8);
    dis[src]=0;
    bool negativeCycle=false;

    for(int i=1; i<=N; i++){
        vector<int> ndis=dis;

        bool isAnyUpdate=false;

        for(vector<int>& edge:edges){
            int u=edge[0];
            int v=edge[1];
            int w=edge[2];

            if(dis[u]+w < ndis[v]){
                ndis[v]=dis[u]+w;
                isAnyUpdate=true;
            }
        }

        if(!isAnyUpdate) break;

        if(i==N && isAnyUpdate){
            negativeCycle=true;
        }

        dis=ndis;
    }

    if(negativeCycle) return {};

    return dis;
}


// leet 787 ===================================================

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<int> dis(n,(int)1e8);
    dis[src]=0;

    for(int i=1; i<=k+1; i++){
        vector<int> ndis=dis;

        for(vector<int>& edge:flights){
            int u=edge[0];
            int v=edge[1];
            int w=edge[2];

            if(dis[u]+w < ndis[v]){
                ndis[v]=dis[u]+w;
                isAnyUpdate=true;
            }
        }

        dis=ndis;
    }

    return dis[dest]==(int)1e8 ? -1  : dis[dest];
}


// leet 490 (lint 787)=============================================================================== 

bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    int n=maze.size();
    int m=maze[0].size();

    int sr=start[0];
    int sc=start[1];

    vector<vector<bool>> vis(n,vector<bool>(m,false));

    int dr=destination[0];
    int dc=destination[1];

    queue<int> q;
    q.push(sr*m+sc);
    vis[sr][sc]=true;
    vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};

    while(q.size()){
        int idx=q.front(); q.pop();

        int i=idx/m;
        int j=idx%m;

        for(auto const& dir:dirs){
            int r=i;
            int c=j;

            while(r>=0 && c>=0 && r<n && c<m && maze[r][c]==0){
                r+=dir[0];
                c+=dir[1];
            }

            r-=dir[0];
            c-=dir[1];

            if(vis[r][c]) continue;

            vis[r][c]=true;
            if(r==dr && c==dc) return true;
            q.push(r*m+c);
        }
    }
    return false;        
}


// leet 505 (lint 788) ===================================================================== 

class myPair{
    public:
    int row;
    int col;
    int steps;

    myPair(int row, int col, int steps){
        this->row=row;
        this->col=col;
        this->steps=steps;
    }
};

struct comp{
    bool ()(myPair& a, myPair& b){
        return a.steps > b.steps; /// whyyyy
    }
};


int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    int n=maze.size();
    int m=maze[0].size();

    int sr=start[0];
    int sc=start[1];

    vector<vector<bool>> vis(n,vector<bool>(m,false));

    int dr=destination[0];
    int dc=destination[1];

    vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};

    priority_queue<myPair, vector<myPair>, comp> pq;

    pq.push({sr,sc,0});
    vis[sr][sc]=true;

    while(pq.size()){
        auto top=pq.top(); pq.pop();

        int i=top.row;
        int j=top.col; 
        int steps=top.steps;

        if(i==dr && j==dc) return steps;

        if(vis[i][j]) continue;
        vis[i][j]=true;

        for(auto const& dir:dirs){
            int r=i;
            int c=j;
            int s=steps;

            while(r>=0 && c>=0 && r<n && c<m && maze[r][c]==0){
                r+=dir[0];
                c+=dir[1];
                s++;
            }

            r-=dir[0];
            c-=dir[1];
            s--;

            
            pq.push({r,c,s});
        }
    }
    return -1;
}




int main(){

}