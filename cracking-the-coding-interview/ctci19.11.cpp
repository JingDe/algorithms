#include<stdio.h>
#include<algorithm>

// 输出数组中和为sum的整数对
void PrintPairSum(int arr[], int n, int sum)
{
	if(arr==NULL ||  n<2)
		return;
	
	std::sort(arr, arr+n);
	
	int low=0, high=n-1;
	while(low<high)
	{
		int add=arr[low]+arr[high];
		if(add>sum)
			--high;
		else if(add<sum)
			++low;
		else
		{
			printf("<%d, %d>\t", arr[low], arr[high]);
			--high;
			++low;
		}
	}
}

int main(){
    int n = 6, sum = 6;
    int a[] = {
        1, 2, 3, 4, 5, 6
    };
    PrintPairSum(a, n, sum);
    return 0;
}