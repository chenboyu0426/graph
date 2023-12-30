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

struct kingdom{ //��a 
	double area; //���n
	bool use; // ���L�Q�ɼuŧ�� 
	int top; 
	vector<int> CH;
	kingdom(){
		area = 0;
		top = 1;
		CH.clear();
		CH.resize(maxn);
		CH[0] = 0;
		CH[1] = 1;
		use = false; //��l ���Q�ɼu���� 
	}
};

vector<p> P, M; // �{���I��  �ɼu
vector< vector<p> > kdNode; // ������a�I����T
vector<kingdom> KD; // ��a 
int n;
double ansArea = 0; //����o�q�ϰ쭱�n 
void Input(){
	double x, y;
	P.clear();

	if(n != -1){
		for(int i = 0; i < n; i++)
		{
			scanf("%f%f", &x, &y);
			P.push_back(p(x, y)); // �@�Ӱ�a���Ҧ��I�� 
		}
		kdNode.push_back(P); //�����IŪ�� �A��i��a 
	}
	else{
		while(cin >> x >> y){ // �ɼu��m 
			M.push_back(p(x, y)); // ��i�ɼu vector 
		}
	} 
}
// �D�Y�] 
bool cmp(p a, p b){
	if(a.y == b.y) return a.x < b.x;
	return a.y < b.y;
}

// �P�_�V�qp2-pp�O�_�b�V�qp1-p2�k��(�k��)
bool turnRight(p p1, p p2, p pp){
	const double eps = 1e-20;
	if((p2.x - p1.x)*(pp.y - p2.y) - (pp.x - p2.x)*(p2.y - p1.y) <= eps) return true;
	return false;
} 

// �p��e�n
double multi(p p0, p p1, p p2){
	return (p1.x - p0.x)*(p2.y - p0.y) - (p2.x - p0.x)*(p1.y - p0.y);
} 

void Compute(){
	// �p��C�Ӱ�a���Y�]
	for(int k = 0; k < kdNode.size(); k++){
		sort(kdNode[k].begin(), kdNode[k].end(), cmp);
		KD.push_back(kingdom());
		// �q�_�I 0 ��Ƨǳ̫��I�@�Y�]�k��
		for(int i = 2; i < kdNode[k].size(); i++){

			while( KD[k].top && turnRight(kdNode[k][KD[k].CH[KD[k].top-1]], kdNode[k][KD[k].CH[KD[k].top]], kdNode[k][i]) ){
				
				KD[k].top--;
			}
			KD[k].CH[++KD[k].top] = i;
		} 
		//cout << KD[k].top-1 << endl;
		// �p��C�Ӱ�a�Y�]���n
		for(int i = 1; i < KD[k].top-1; i++){
			KD[k].area += multi(kdNode[k][KD[k].CH[0]], kdNode[k][KD[k].CH[i]], kdNode[k][KD[k].CH[i+1]]);
			cout << KD[k].area << endl;
		}
			//�P�_�ɼu�O�_ŧ����e��a
			for(int m=0; m<M.size(); m++){
			   if(KD[k].use)  break;  //�Ӱ�a���e�w�Q�ɼu�R��
			   for(int i=0; i<KD[k].top-1; i++){
				   if(!turnRight(kdNode[k][KD[k].CH[i]], kdNode[k][KD[k].CH[(i+1)%KD[k].top]], M[m])){//�Y�IM[m]�b�Y�]�䥪��
					  KD[k].use = true; //�Ӱ�a�i��|�Qŧ��
					}
				   else{
				      KD[k].use = false; //�IM[m]���b�Y�]�����A�ɼu�L�kŧ��
					  break;
				   }
			   }
			   if(KD[k].use){  //�Ӱ�a�w�Q��e�ɼu�R��
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
