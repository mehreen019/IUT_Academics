#include<bits/stdc++.h>
using namespace std;
const int sz=1005;
char r[sz][sz];
bool vis[sz][sz]={{0}};
vector<pair<int,int>> pos;
int srcx, srcy ,arrn, arrm;
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};

bool checker(int u,int v){
    if(u>=0 && u<arrn && v>=0 && v<arrm && !vis[u][v] && r[u][v]!='#') return true;
    else return false;
}

void bfs(int x,int y){
    queue<pair<int,int>> q;
    vis[x][y]=true;
    q.push({x,y});
    while(!q.empty()){
        auto t=q.front();
        q.pop();
        int u=t.first, v=t.second;
        for(int i=0;i<4;i++){
            int tu=u+dx[i];
            int tv=v+dy[i];

            if(checker(tu,tv) ){
                vis[tu][tv]=true;
                q.push({tu,tv});
                //cout<<tu<<tv<<" "<<r[tu][tv]<<" "<<dist[u][v]<<endl;
            }
        }

    }
}

int main(void){
        int n,m,cou=0;
        cin>>n>>m;
        arrn=n; arrm=m;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cin>>r[i][j];
                vis[i][j]=false;
                if(r[i][j]=='.'){
                    pos.push_back({i,j});
                }
            }
        }
        for(int i=0;i<pos.size();i++){
            int uk=pos[i].first, vk=pos[i].second;
            if(!vis[uk][vk]){ bfs(uk,vk); cou++;  }
        }
        cout<<cou<<endl;
}
