#include<iostream>
#include<cstdio>
#define MAX 50010 
using namespace std;
int A[MAX];
typedef struct node {
	int sum,maxl,maxr,maxs;
} Node;

int maxxx(int a,int b)
{
	return a>b?a:b;
}

Node tree[4*MAX];

void maketree(int root,int a,int b) {
//cout<<a<<" "<<b<<" "<<endl;
	if(a==b) {
		tree[root].sum=tree[root].maxl=tree[root].maxr=tree[root].maxs=A[a-1];
	}
	else {
		int mid = (a+b)>>1;
		int left = root<<1;
		int right = (root<<1)+1;
		maketree(left,a,mid);
		maketree(right,mid+1,b);
		tree[root].sum=tree[left].sum+tree[right].sum;
		tree[root].maxl= maxxx(tree[left].maxl,tree[left].sum+tree[right].maxl);
		tree[root].maxr= maxxx(tree[right].maxr,tree[right].sum+tree[left].maxr);
		tree[root].maxs=maxxx(maxxx(tree[left].maxs,tree[right].maxs),tree[left].maxr+tree[right].maxl);
	}
}

Node query(int root,int i,int j,int a,int b,Node &res) {
//cout<<i<<" "<<j<<a<<" "<<b<<" "<<endl;
	if(a>=i && b<=j) {
		res = tree[root];
	}
	else {
		int mid = (a+b)>>1;
		int left = root<<1;
		int right = (root<<1)+1;
		if(j<=mid) {
			query(left,i,j,a,mid,res);
		}
		else if(i>mid) {
			query(right,i,j,mid+1,b,res);
		}
		else {
			Node leftNode,rightNode;
			query(left,i,mid,a,mid,leftNode);
			query(right,mid+1,j,mid+1,b,rightNode);
			res.sum=leftNode.sum+rightNode.sum;
			res.maxl= maxxx(leftNode.maxl,leftNode.sum+rightNode.maxl);
			res.maxr= maxxx(rightNode.maxr,rightNode.sum+leftNode.maxr);
			res.maxs=maxxx(maxxx(leftNode.maxs,rightNode.maxs),leftNode.maxr+rightNode.maxl);
		}
	}
}
int main() {
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&A[i]);
	maketree(1,1,n);
	
	/*for(int i=0;i<4*n;i++)
		printf("%d %d %d %d\n",tree[i].maxs,tree[i].maxl,tree[i].maxr,tree[i].sum);
	cout<<endl;*/
		
	int m;
	scanf("%d",&m);
	for(int i=0;i<m;i++) {
		Node res;
		int s,e;
		scanf("%d%d",&s,&e);
		query(1,s,e,1,n,res);
		printf("%d\n", res.maxs);
	}
	return 0;
}