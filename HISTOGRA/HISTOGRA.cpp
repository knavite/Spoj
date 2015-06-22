#include <iostream>
#include <stack>
using namespace std;
int main()
{
	while(1)
	{
		int n;
		cin>>n;
		if(n==0)
			break;
		long long a[n];
		for(int i=0;i<n;i++)
			cin>>a[i];
		stack<int> mystack;
		long long maxArea=0;
		for(int i=0;i<n;i++)
		{
			if(mystack.empty() || a[mystack.top()]<a[i])
				mystack.push(i);
			else if(mystack.empty() || a[mystack.top()]==a[i]) {
				mystack.pop();
				mystack.push(i);
			}
			else
			{
				while(!mystack.empty() && a[mystack.top()]>a[i])
				{
					int index = mystack.top();
					mystack.pop();
					long long area;
					if(mystack.empty())
						area = a[index]*(i);
					else
						area = a[index]*(i-mystack.top()-1);
					if(area>maxArea)
						maxArea=area;
					
				}
				mystack.push(i);
			} //cout<<maxArea<<"r"<<mystack.size()<<endl;
		}				
		if(!mystack.empty()) {
			int tindex = mystack.top();
			while(!mystack.empty()) 
			{
				int index = mystack.top();
				long long area;
				mystack.pop();
				int pindex;
				if(!mystack.empty()) 
					pindex = mystack.top();
				else
					pindex = -1;
				area = a[index]*(tindex-pindex);
				
				if(area>maxArea)
					maxArea=area;
					//cout<<tindex<<" ZZ"<<index<<endl;
			}
		}
		cout<<maxArea<<endl;
	}
	return 0;
}