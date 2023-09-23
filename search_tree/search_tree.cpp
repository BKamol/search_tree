#include <fstream>
#include <iostream>

using namespace std;

struct node
{
    char info;
    node* left;
    node* right;
};
typedef node* tinfo;

struct elem
{
    tinfo info;
    elem* next;
};

struct Queue
{
    int size;
    elem* first;
    elem* last;
};

void enQueue(Queue* q, tinfo x)
{
    q->last->next = new elem;
    q->last = q->last->next;
    q->last->next = NULL;
    q->last->info = x;
    q->size++;
}

tinfo deQueue(Queue* q)
{
    elem* el = q->first;
    q->first = q->first->next;
    tinfo info = el->next->info;
    delete el;
    q->size--;
    return info;
}

bool isEmpty(Queue* q)
{
    return q->first == q->last;
}

Queue* create_queue()
{
    Queue* q = new Queue;
    q->first = new elem;
    q->first->next = NULL;
    q->last = q->first;
    q->size = 0;
    return q;
}

node* create_node(char c)
{
    node* p = new node;
    p->info = c;
    p->left = NULL;
    p->right = NULL;

    return p;
}

node* create_tree()
{
    string alphabet = "!ETIANMSURWDKGO";
    node* root = create_node('!');
    int curr = 1;
    int next = 0;
    int i = 1;
    node* p;

    Queue* q = create_queue();
    enQueue(q, root);

    while (i < alphabet.length()-1)
    {
        p = deQueue(q);
        p->left = create_node(alphabet[i]);
        p->right = create_node(alphabet[i+1]);
        i += 2;
        enQueue(q, p->left);
        enQueue(q, p->right);
    }

    return root;
}

char find_letter(node* root, string morze)
{
    node* p = root;
    int i = 0;

    while (i < morze.length())
    {
        if (morze[i] == '-' && p->right)
        {
            p = p->right;
        }
        else if (morze[i] == '.' && p->left)
        {
            p = p->left;
        }
        else
        {
            cout << "Wrong code!" << endl;
        }
        i++;
    }

    return p->info;
}

void BFS(node* root)
{
    node* p;
    Queue* q = create_queue();
    int cur = 1;
    int next = 0;
    enQueue(q, root);

    while (!isEmpty(q))
    {
        p = deQueue(q);
        cur--;
        cout << p->info << ' ';
        if (p->left)
        {
            enQueue(q, p->left);
            next++;
        }
        if (p->right)
        {
            enQueue(q, p->right);
            next++;
        }
         
        if (cur == 0)
        {
            cout << endl;
            cur = next;
            next = 0;
        }

    }
    cout << endl;
}

int main()
{
    node* root;
    root = create_tree();
    BFS(root);

    cout << find_letter(root, "..-");

}

