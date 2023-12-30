#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

struct edge{
	int from, to, cost;
	edge(int from, int to, int cost): from(from), to(to), cost(cost){}
	bool operator< (const edge &tmp)const{
		return tmp.cost < cost; //小的放最上面 
	}
};

vector<edge> G[105];
vector<edge> sorting;
vector<edge> path[105];
queue<edge> qu;
int parent[105];
int c, s, q; // 點數 邊樹 搜尋次數 

int findroo(int n){
	if(parent[n] < 0){
		return n;
	}
	else{
		return findroo(parent[n]);
	}
}

bool union2(int a, int b){
	int pa = findroo(a);//printf("%d %d ", a, pa);
	
	int pb = findroo(b);//printf("%d %d\n", b, pb);
	
	if(pa == pb) return false;
	else{
		if(parent[pa] <= parent[pb]){ //pa 子節點較多 
			parent[pa] += parent[pb];
			parent[pb] = pa;
		}
		else{
			parent[pb] += parent[pa];
			parent[pa] = pb;
		}
		return true;
	}
}

void MST(int e){ // e 邊數 
	int count = 0, idx = 0;
	bool b = true;//printf("\n");
	while(count < e && idx < s)
	{	
		edge tmp = sorting[idx];
		idx++;
		int a = tmp.from;
		int b = tmp.to;
		int cost = tmp.cost;
		if(union2(a, b)){
			count++;//cout << a << " " << b << " " << cost << endl;
			path[a].push_back(edge(a, b, cost));
			path[b].push_back(edge(b, a, cost));
			qu.push(edge(a, b, cost));
		} 
		else{
			continue;
		}
		
	}
	//printf("%d %d\n", count, idx);
}

int DFSUtil(int s, int e, bool visit[], bool *found){
	visit[s] = true;
	int m = 0;
	
	vector<edge>::iterator i;
	
	for(i = path[s].begin(); i != path[s].end(); i++){
		//printf("%d %d\n", (*i).to, (*i).cost);
		if(!visit[(*i).to] && (*i).to == e){
			*found = true;
			return((*i).cost);
		}
		else if(!visit[(*i).to]){
			m = DFSUtil((*i).to, e, visit, found);
			if(*found) return (m > (*i).cost ? m : (*i).cost); // 回傳 m 或 (*i).cost 看哪個比較大 
		}
	}
	if(!(*found)) return 0; 
}

int DFS(int s, int e){
	bool *visit = new bool[c+1];
	bool found = false;
	memset(visit, 0, sizeof(visit));
	
	return DFSUtil(s, e, visit, &found);
}

bool Wcomp(edge &tmp1, edge &tmp2){
	return tmp1.cost < tmp2.cost;
}

int main()
{
	int cas = 0;
	while(scanf("%d%d%d", &c, &s, &q) && c != 0){
		cas++;
		printf("Case #%d\n", cas);
		for(int i = 0; i < 105; i++){
			G[i].clear();
			path[i].clear();
		}
		sorting.clear();
		while(!qu.empty()){
			qu.pop();
		}
		memset(parent, -1, sizeof(parent));
		
		int a, b, cost;
		for(int i = 1; i <= s; i++){
			scanf("%d%d%d", &a, &b, &cost);
			G[a].push_back(edge(a, b, cost));
			sorting.push_back(edge(a, b, cost));
		}
		sort(sorting.begin(), sorting.end(), Wcomp);
		MST(c-1);
		/*for(int i = 0; i < c-1; i++){
			edge tmp = qu.front(); qu.pop(); a = tmp.from, b = tmp.to, cost = tmp.cost;
			printf("%d %d %d\n", a, b, cost);
		}*/
		
		for(int i = 0; i < q; i++){
			scanf("%d %d", &a, &b);
			int ans = DFS(a, b);
			if(ans > 0) printf("%d\n", DFS(a, b));
			else printf("no path\n");
		}
		printf("\n");
	}
}
