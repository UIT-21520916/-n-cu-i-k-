#include <bits/stdc++.h>
using namespace std;

int N, m, n, k, num_crelist = 0;

struct node
{
    int arr[32][32];
    int value;
    node *next;
};
struct linkedlist
{
    node *head;
    node *tail;
};

node *createnode(int dataa, int ar[32][32])
{
    node *node1 = new node;
    node1->value = dataa;

    for (int l = 0; l < m; l++)
    {
        for (int k = 0; k < n; k++)
            node1->arr[l][k] = ar[l][k];
    }
    node1->next = NULL;
    return node1;
}

void createlist(linkedlist &l)
{
    ++num_crelist;
    l.head = NULL;
    l.tail = NULL;
}
void addhead(linkedlist &l, node *node1)
{
    if (l.head == NULL)
    {
        l.head = node1;
        l.tail = node1;
    }
    else
    {
        node1->next = l.head;
        l.head = node1;
    }
}

void addtail(linkedlist &l, node *node1)
{

    if (l.head == NULL)
    {
        l.head = node1;
        l.tail = node1;
    }
    else
    {
        l.tail->next = node1;
        l.tail = node1;
    }
}

void solve(linkedlist *arr_list, int mdd, int ar[32][32])
{
    for (int i = 0; i < num_crelist; i++)
    {
        int upd = 0;
        node *a = arr_list[i].head;
        while (a != NULL)
        {
            int cntdff = 0;
            for (int l = 0; l < m; l++)
                for (int k = 0; k < n; k++)
                    if (ar[l][k] != a->arr[l][k])
                        cntdff++;
            upd = cntdff;
            if (cntdff > k)
                break;

            a = a->next;
        }
        if (upd <= k)
        {
            node *d = createnode(mdd, ar);
            addtail(arr_list[i], d);
            return;
        }
    }
    int cc = num_crelist;
    createlist(arr_list[cc]);
    node *d = createnode(mdd, ar);
    addtail(arr_list[cc], d);
    return;
}

void quickSort(linkedlist *arr_list, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = arr_list[(i + j) / 2].head->value;
    node *abc = new node;
    while (i <= j)
    {
        while (arr_list[i].head->value < pivot)
            i++;
        while (arr_list[j].head->value > pivot)
            j--;
        if (i <= j)
        {
            abc = arr_list[i].head;
            arr_list[i].head = NULL;
            addtail(arr_list[i], arr_list[j].head);
            arr_list[j].head = NULL;
            addtail(arr_list[j], abc);
            abc = NULL;

            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(arr_list, low, j);
    if (i < high)
        quickSort(arr_list, i, high);
}
void SortList(linkedlist &list)
{

    for (node *Tmp = list.head; Tmp != NULL; Tmp = Tmp->next)
        for (node *Tmp2 = Tmp->next; Tmp2 != NULL; Tmp2 = Tmp2->next)
            if (Tmp->value > Tmp2->value)
            {
                int t = Tmp->value;
                Tmp->value = Tmp2->value;
                Tmp2->value = t;
            }
}
void process_Output(linkedlist *arr_list)
{
    for (int i = 0; i < num_crelist; i++)
        SortList(arr_list[i]);
    quickSort(arr_list, 0, num_crelist - 1);
}
void PrintList(linkedlist *arr_list)
{
    process_Output(arr_list);
    cout << endl;
    for (int i = 0; i < num_crelist; i++)
    {
        if (arr_list[i].head != NULL)
        {
            node *Node = arr_list[i].head;
            while (Node != NULL)
            {
                cout << Node->value << " ";
                Node = Node->next;
            }
        }
        cout << endl;
    }
}

int main()
{
    int mdd, ar[32][32];
    cin >> N >> m >> n >> k;

    linkedlist *arr_list = new linkedlist[1000];

    for (int i = 0; i < N; i++)
    {
        cin >> mdd;
        for (int l = 0; l < m; l++)
            for (int k = 0; k < n; k++)
                cin >> ar[l][k];
        if (i != 0)
        {
            solve(arr_list, mdd, ar);
        }
        else
        {
            createlist(arr_list[0]);
            node *d = createnode(mdd, ar);
            addtail(arr_list[0], d);
        }
    }

    PrintList(arr_list);
    delete[] arr_list;
}
