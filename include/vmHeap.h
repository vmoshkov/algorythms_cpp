#ifndef VMHEAP_H
#define VMHEAP_H

#include <iostream>

using namespace std;

class vmHeap
{
    public:
        vmHeap();
        virtual ~vmHeap();
        void build_minheap(int *a, int n);
        void testMe();

    protected:

    private:
        void min_heapify(int *a,int i,int n);
};

#endif // VMHEAP_H
