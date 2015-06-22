#include <iostream>
#include <cmath>
#include <climits>
#include<cstdio>
#define gc getchar_unlocked
using namespace std;

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}

typedef struct nodeee {
	int maxSum,maxLeft,maxRight,sum;
} Node;

int maxx(int a,int b) {
	return a>b?a:b;
}

Node makeTree(int node, int A[], Node segmentTree[], int a, int b) {
	if(a==b) {
		segmentTree[node].maxSum=segmentTree[node].maxLeft=segmentTree[node].maxRight=segmentTree[node].sum=A[a-1];
		return segmentTree[node];
	}
	Node left = makeTree((node<<1),A,segmentTree,a,(a+b)>>1);
	Node right = makeTree((node<<1)+1,A,segmentTree,((a+b)>>1)+1,b);
	segmentTree[node].maxSum=maxx(maxx(left.maxSum,right.maxSum),left.maxRight+right.maxLeft);
	segmentTree[node].maxLeft=maxx(left.maxLeft,left.sum+right.maxLeft);
	segmentTree[node].maxRight=maxx(right.maxRight,right.sum+left.maxRight);
	segmentTree[node].sum=left.sum+right.sum;
	return segmentTree[node];
}
int pa=-1,pb=-1,pi=-1,pj=-1;
Node query(int node,Node segmentTree[],int i,int j,int a,int b) {
	//cout<<a<<" "<<b<<" "<<i<<" "<<j<<endl;
	int k=0;
	if(pa==a && pb==b && pi==i && pj==j)
		1/k;
	pa=a,pb=b,pi=i,pj=j;
	if(i==a && j==b) {
		return segmentTree[node];
	}
	int mid = (a+b)>>1;
	Node left,right;
	
	if(j<=mid) {
		left = query((node<<1),segmentTree,i,j,a,mid);
		return left;
	}
	if(i>mid){
		right = query((node<<1)+1,segmentTree,i,j,mid+1,b);
		return right;
	}
	else {
		left = query((node<<1),segmentTree,i,mid,a,mid);
		right = query((node<<1)+1,segmentTree,mid+1,j,mid+1,b);
		Node temp;
		temp.maxSum=maxx(maxx(left.maxSum,right.maxSum),left.maxRight+right.maxLeft);
		temp.maxLeft=maxx(left.maxLeft,left.sum+right.maxLeft);
		temp.maxRight=maxx(right.maxRight,right.sum+left.maxRight);
		temp.sum=left.sum+right.sum;
		return temp;
	}
	
}

int main() {
	int n;
	scanint(n);
	int A[n];
	for(int i=0;i<n;i++)
		scanint(A[i]);
	/*int treeHeight = (int) ceil(log2(n));
	int treeSize = (int) 2 * pow(2,treeHeight) - 1;*/
	int treeSize = n<<2;
	Node segmentTree[treeSize];
	makeTree(1,A,segmentTree,1,n);
/*	for(int i=0;i<treeSize;i++)
		cout<<segmentTree[i].maxLeft<<" "<<segmentTree[i].maxRight<<" "<<segmentTree[i].maxSum<<" "<<segmentTree[i].sum<<" \n";*/
	int m;
	cin>>m;
	
	for(int i=0;i<m;i++) {
		int s,e;
		cin>>s>>e;
		Node v = query(1,segmentTree,s,e,1,n);
		cout<<v.maxSum<<endl;
	}
	return 0;
}