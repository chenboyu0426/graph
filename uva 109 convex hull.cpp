#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 110;

struct p{
	double x, y;
	p(double x, double y): x(x), y(y){}
};

struct kingdom{ //國家 
	double area; //面積
	bool use; // 有無被導彈襲擊 
	int top; 
	vector<int> CH;
	kingdom(){
		area = 0;
		top = 1;
		CH.clear();
		CH.resize(maxn);
		CH[0] = 0;
		CH[1] = 1;
		use = false; //初始 未被導彈擊中 
	}
};

vector<p> P, M; // 臨時點集  導彈
vector< vector<p> > kdNode; // 紀錄國家點的資訊
vector<kingdom> KD; // 國家 
int n;
double ansArea = 0; //不能發電區域面積 
void Input(){
	double x, y;
	P.clear();

	if(n != -1){
		for(int i = 0; i < n; i++)
		{
			scanf("%f%f", &x, &y);
			P.push_back(p(x, y)); // 一個國家的所有點集 
		}
		kdNode.push_back(P); //全部點讀完 再放進國家 
	}
	else{
		while(cin >> x >> y){ // 導彈位置 
			M.push_back(p(x, y)); // 放進導彈 vector 
		}
	} 
}
// 求凸包 
bool cmp(p a, p b){
	if(a.y == b.y) return a.x < b.x;
	return a.y < b.y;
}

// 判斷向量p2-pp是否在向量p1-p2右側(右轉)
bool turnRight(p p1, p p2, p pp){
	const double eps = 1e-20;
	if((p2.x - p1.x)*(pp.y - p2.y) - (pp.x - p2.x)*(p2.y - p1.y) <= eps) return true;
	return false;
} 

// 計算叉積
double multi(p p0, p p1, p p2){
	return (p1.x - p0.x)*(p2.y - p0.y) - (p2.x - p0.x)*(p1.y - p0.y);
} 

void Compute(){
	// 計算每個國家的凸包
	for(int k = 0; k < kdNode.size(); k++){
		sort(kdNode[k].begin(), kdNode[k].end(), cmp);
		KD.push_back(kingdom());
		// 從起點 0 到排序最後點作凸包右鏈
		for(int i = 2; i < kdNode[k].size(); i++){

			while( KD[k].top && turnRight(kdNode[k][KD[k].CH[KD[k].top-1]], kdNode[k][KD[k].CH[KD[k].top]], kdNode[k][i]) ){
				
				KD[k].top--;
			}
			KD[k].CH[++KD[k].top] = i;
		} 
		//cout << KD[k].top-1 << endl;
		// 計算每個國家凸包面積
		for(int i = 1; i < KD[k].top-1; i++){
			KD[k].area += multi(kdNode[k][KD[k].CH[0]], kdNode[k][KD[k].CH[i]], kdNode[k][KD[k].CH[i+1]]);
			cout << KD[k].area << endl;
		}
			//判斷導彈是否襲擊當前國家
			for(int m=0; m<M.size(); m++){
			   if(KD[k].use)  break;  //該國家之前已被導彈摧毀
			   for(int i=0; i<KD[k].top-1; i++){
				   if(!turnRight(kdNode[k][KD[k].CH[i]], kdNode[k][KD[k].CH[(i+1)%KD[k].top]], M[m])){//若點M[m]在凸包邊左側
					  KD[k].use = true; //該國家可能會被襲擊
					}
				   else{
				      KD[k].use = false; //點M[m]不在凸包內部，導彈無法襲擊
					  break;
				   }
			   }
			   if(KD[k].use){  //該國家已被當前導彈摧毀
				   ansArea += KD[k].area;cout << KD[k].area << endl;
				   break;
			   }
			}
	} 
	printf("%.2lf\n", ansArea/2);
}



int main()
{
	
	while(scanf("%d", &n)){
		Input();
		if(n == -1) Compute();
	}
	
}
