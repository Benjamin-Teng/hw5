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
int n, l, r, c;

int min(int a, int b){
    if(a <= b)
        return a;
    else
        return b;
}

void memoryfree(Node* (*arr)[HALF_MAX] , int n){
    for(int i = 0 ; i <= n / 2 ; i++){
        for(Node* ptr = (*arr)[i]->next ; ptr != nullptr ; ){
            Node* tmp = ptr->next;
            delete ptr;
            ptr = tmp;
        }
        (*arr)[i]->next = nullptr;
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

void initialization(int in[] , int n)
{
    for(int i = 0 ; i < n ; i++){
        cin >> in[i];
    }

    mysort<int>(in, 0, n - 1);
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

int* build_hashtable(int input[] , int n){
    int* arr = new int[(n / 2)];
    for(int i = 0 , j = 0 , k = 0 ; i < n / 2 ; i = j , k++){ // build look-up table for left gloves and right gloves
        arr[k] = input[i];
        for (; j < n / 2; j++)
        {
            if(input[j] != arr[k]){
                break;
            }
        }
    }
    return arr;
}

void linear_scan(int* tmp[], int* arr[], int tmpsize, int arrsize){
    int* newt;
    int* newr;
}

int hashing(Node* table[], int g, int n){
    for(int i = 0 ; i <= n / 2 ; i++){
        for (Node* ptr = table[i]->next ; ptr != nullptr; ptr = ptr->next)
        {
            if(ptr->key < g){
                break;
            }
            if(ptr->key == g){
                return i;
            }
        }
    }
    return 0;
}

int difference(int gl , int gr){
    int minimum = min(gl,gr);
    return (gl - minimum);
}

void solve()
{

    int* input_left;
    int* input_right;
    int* gems = new int[1]();
    long long int total_cost = 0;

    cin >> n >> l >> r >> c;

    input_left = new int[l]();
    input_right = new int[r]();
    initialization(input_left, l);
    initialization(input_right, r);

    if(min(l,r) == l){
        linear_scan(&input_left , &input_right , l , r);
    }
    else {
        linear_scan(&input_right , &input_left , r , l);
    }

    //////////////////////////// fixed below //////////////////////////////
    gems = build_hashtable(input_left, n); // important!!! using input_left as template to calculate difference
    
    for(int i = 0 ; i < n / 2 ; i++){
        if(gems[i] == 0){
            break;
        }
        int geml = hashing(table_left, gems[i], n);
        int gemr = hashing(table_right, gems[i], n);
        total_cost += difference(geml , gemr) * c;
    }

    long long int rlcost = abs(l - r) * c / 2; // cost for exchanging left to right gloves
    total_cost += rlcost;

    cout<<total_cost<<endl;

    return;
}