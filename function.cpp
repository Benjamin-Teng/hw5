#include "function.h"
#include <iostream>
#include <algorithm>
#include <math.h>
#define HALF_MAX 100001
#define N_MAX 200000

using namespace std;

class Node
{
public:
    Node(){}
    Node(int key) :key(key){}
    ~Node(){};

    int key = -1;
    Node *next = nullptr;
};

Node *table_left[HALF_MAX] = {nullptr};
Node *table_right[HALF_MAX] = {nullptr};
int input_left[N_MAX / 2] = {0};
int input_right[N_MAX / 2] = {0};
int n, l, r, c;

int min(int a, int b)
{
    if (a <= b)
        return a;
    else
        return b;
}

void memoryfree(Node* arr[] , int n){
    for(int i = 0 ; i <= n ; i++){
        for(Node* ptr = arr[i]->next ; ptr != nullptr ; ){
            Node* tmp = ptr->next;
            delete ptr;
            ptr = tmp;
        }
    }
    return;
}

void insertion(Node* p, Node* q){
    if(p->next == nullptr){
        p->next = q;
        return;
    }
    Node* tmp = p->next;
    p->next = q;
    q->next = tmp;
    return;
}

template <class T>
void mysort(T arr[], int f, int l)
{
    if (f >= l)
        return;
    int pivot = arr[f], i = f, j = l;
    while (i < j)
    {
        while (arr[j] >= pivot)
        {
            j = j - 1;
            if (j == i)
                break;
        }
        swap(arr[i], arr[j]);
        while (arr[i] < pivot)
        {
            i = i + 1;
        }
        swap(arr[i], arr[j]);
    }
    mysort(arr, f, j - 1);
    mysort(arr, j + 1, l);
    return;
}

void initialization()
{
    cin >> n >> l >> r >> c;
    for(int i = 0 ; i < n / 2 ; i++){
        cin >> input_left[i];
    }
    for(int i = 0 ; i < n / 2 ; i++){
        cin >> input_right[i];
    }
    mysort<int>(input_left, 0, n / 2 - 1);
    mysort<int>(input_right, 0, n / 2 - 1);
    for(int i = 0 ; i < HALF_MAX ; i++){
        if(table_left[i] == nullptr){
            table_left[i] = new Node;
        }
        if(table_right[i] == nullptr){
            table_right[i] = new Node;
        }
    }
    return;
}

void build_table(Node* arr[] , int input[], int n){
    for(int i = 0 , j = 0 ; i < n / 2 ; i = j){ // build look-up table for left gloves and right gloves
        int count = 0;
        int key = input[i];
        for (; j < n / 2; j++)
        {
            if(input[j] == key){
                count++;
            }
            else {
                break;
            }
        }
        Node* q = new Node(key);
        insertion(arr[count], q);
    }
}

void solve()
{
    initialization();
    build_table(table_left, input_left, n);
    build_table(table_right, input_right, n);

    for(int i = 0 ; i <= n ; i++){
        if(table_left[i]->next == nullptr){
            cout << "head" << i << endl;
        }
        else{
            cout << "head" << i << " -> ";
            for(Node* ptr = table_left[i]->next ; ptr != nullptr ; ptr = ptr->next){
                cout << ptr->key << " -> ";
            }
            cout << "end" << endl;
        }
    }

    for(int i = 0 ; i <= n ; i++){
        if(table_right[i]->next == nullptr){
            cout << "head" << i << endl;
        }
        else{
            cout << "head" << i << " -> ";
            for(Node* ptr = table_right[i]->next ; ptr != nullptr ; ptr = ptr->next){
                cout << ptr->key << " -> ";
            }
            cout << "end" << endl;
        }
    }

    int rlcost = abs(l - r) * c / 2; // cost for exchanging left to right gloves

    return;
}