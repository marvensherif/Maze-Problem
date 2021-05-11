#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <sstream>
#define INFINITY 1000000
using namespace std;

std::string toString(auto &i)
{
    std::stringstream ss;
    ss << i;

    return ss.str();
}

stack <string> mazeIndexStack;
int row = 0;
int column = 0;
struct Dlist
{
    struct Dlist *down;
    struct Dlist *up;
    struct Dlist *left;
    struct Dlist *right;
    int data;
    int visted;
}*pHead,*pTail,*pUpper;

struct Dlist *createNode(int data)
{
    struct Dlist * L = (struct Dlist*)malloc(sizeof(struct Dlist));
    L->data = data;
    L->visted = 0;
    L->down = NULL;
    L->up = NULL;
    L->left = NULL;
    L->right = NULL;
    return L;
}

void addNode(struct Dlist *L,int data,int i,int j)
{

    L = createNode(data);
    if(i == 0 && j == 0)
    {
        pHead=L;
        pTail=L;
        pUpper=L;
    }
    else if ( i < j && i == 0 )
    {
        pTail->right = L;
        L->left = pTail;
        pTail = L;
    }
    else if ( i > j && j == 0)
    {
        pUpper->down = L;
        L->up = pUpper;
        pTail = L;
        if(pUpper->right!= NULL);
        pUpper = pUpper->right;
    }
    else if (i >= j)
    {
        pUpper->down = L;
        L->up = pUpper;
        pTail->right = L;
        L->left = pTail;
        pTail = L;
        if(pUpper->right!= NULL);
        pUpper = pUpper->right;
    }
    else if( i <= j)
    {
        pUpper->down = L;
        L->up = pUpper;
        pTail->right = L;
        L->left = pTail;
        pTail = L;
        if(pUpper->right != NULL)
        {
            pUpper = pUpper->right;
        }
        else
        {
            pUpper = pUpper->down;
            while( pUpper->left != NULL)
            {
                pUpper = pUpper->left;
            }
        }
    }

}
void findPath(stack <struct Dlist *> &s, struct Dlist *L)
{

    L->visted = 1;

    if( L->down == NULL && L->right == NULL)
    {
        cout<<"YOUR PATH IS : ";
    }
    else
    {
        {

            if(L->up != NULL && L->up->data != 1 && L->up->visted != 1)
            {


                row--;
                string z = "("+toString(row)+","+toString(column)+")";
                mazeIndexStack.push(z);
                L = L->up;
                s.push(L);
                findPath(s,L);
            }
            else if(L->right != NULL && L->right->data != 1  && L->right->visted != 1)
            {
                L = L->right;
                column++;
                string z = "("+toString(row)+","+toString(column)+")";
                mazeIndexStack.push(z);
                s.push(L);
                findPath(s,L);
            }
            else if(L->down != NULL && L->down->data != 1  && L->down->visted != 1)
            {
                L = L->down;
                row++;
                string z = "("+toString(row)+","+toString(column)+")";
                mazeIndexStack.push(z);
                s.push(L);
                findPath(s,L);
            }
            else if(L->left != NULL && L->left->data !=1 && L->left->visted != 1)
            {
                L= L->left;
                column--;
                string z = "("+toString(row)+","+toString(column)+")";
                mazeIndexStack.push(z);
                s.push(L);
                findPath(s,L);
            }
            else
            {

                s.pop();
                mazeIndexStack.pop();

                if(!s.empty())
                {

                    string p  = mazeIndexStack.top();

                    int pos = p.find("(");
                    int pos2= p.find(",");
                    int pos3 = p.find(")");
                    string sub = p.substr(pos+1,pos2-1);
                    string sub2 = p.substr(pos2+1,pos3-3);
                    stringstream index(sub);
                    index >> row;
                    stringstream index2(sub2);
                    index2 >> column;
                    findPath(s,s.top());
                }
                else
                {
                    mazeIndexStack.pop();
                    cout << "NO PATH FOUND TO REACH END OF THE MAZE";
                }
            }

        }
    }
}
void PrintStack(stack<string> s2)
{
    if (s2.empty())
        return;


    string  z= s2.top();

    s2.pop();

    PrintStack(s2);

    cout << z << " ";

    s2.push(z);
}


int main()
{   struct Dlist *L;
   int m;
   int x;
   stack <struct Dlist*> s;
   cout<<"Please Enter Maze Dimensions M X M : ";
   cin>>m;
   int arr[m][m];
   cout<<"Please Enter Maze Walls In Form Of 1 And Path In Form Of 0\n";
   for(int i=0 ; i<m ; i++)
   {
       for(int j=0 ; j<m ; j++)
       {
           cin>>x;
           arr[i][j]=x;
       }
   }


   for(int i=0 ; i<m ; i++)
   {
       for(int j=0 ; j<m ; j++)
       {

           addNode(L,arr[i][j],i,j);
       }

   }
   if(pHead->data != 1)
   {
       mazeIndexStack.push("(0,0)");
       findPath(s,pHead);
       PrintStack(mazeIndexStack);
       cout<<"\n";
   }
   else
   {
       cout << "Can't Start Because It Is A Wall";
   }



}
