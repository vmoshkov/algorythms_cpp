#include "vmHeap.h"


vmHeap::vmHeap()
{
    //ctor
}

vmHeap::~vmHeap()
{
    //dtor
}

/*
*  a - pointer to an array
*  n - length of an array
*/
void vmHeap::build_minheap(int* a, int n)
{
    //start is assigned the index in a of the last parent node
	//int start = (n - 2) / 2; //binary heap


    for(int start = n/2; start >= 0; start--)
    {
        min_heapify(a,start,n);

        for (int q = 0; q < 15; q++)
        {
             cout<<a[q]<<" ";
        }
        cout<<endl;
    }

}


/*
*  a - pointer to an array
*  i - current position in an array
*  size - length of an array
*/
void vmHeap::min_heapify(int *a,int i,int size)
{
    //end represents the limit of how far down the heap to shift
	int root = i;

	while((root * 2) < size){      //While the root has at least one child
		int child = root * 2;           //root*2 points to the left child
		//if the child has a sibling and the child's value is greater than its sibling's...
		if((child + 1 < size) && (a[child] > a[child + 1]))
			child = child + 1;           //... then point to the right child instead

		if(a[root] > a[child]){     //if current position value > value at child position, then swap
			int tmp = a[root];
			a[root] = a[child];
			a[child] = tmp;
			root = child;                //repeat to continue sifting down the child now
		}else
			return;
	}
    return;
}


void vmHeap::testMe()
{
        int a[15] = {7, 12, 76, 45, 23, 6, 9, 15, 40, 43, 12, 8, 13, 26, 10};
        for (int i = 0; i < 15; i++)
        {
            cout<<a[i]<<" ";
        }
        cout<<endl;

        this->build_minheap(a, 15);

        cout<<"Min Heap\n";
        for (int i = 0; i < 15; i++)
        {
            cout<<a[i]<<" ";
        }

        cout<<"\nend of min heap test\n";

}
