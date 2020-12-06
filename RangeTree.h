//
// Created by jpalexander1706 on 2020-12-05.
//

#ifndef RANGETREE_RANGETREE_H
#define RANGETREE_RANGETREE_H

#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <utility>
using namespace std;

bool sortbysec(const pair<int,int> &a,
               const pair<int,int> &b)
{
    return (a.second < b.second);
}

bool sortbyfirst(const pair<int,int> &a,
                 const pair<int,int> &b)
{
    return (a.first < b.first);
}


struct Nodo2D{
    int x;
    int y;
    Nodo2D * m_pSon[2];
    Nodo2D * next;
    Nodo2D * prev;
    Nodo2D * ROOTY;

    Nodo2D(int n, int m){
        x = n;
        y = m;
        m_pSon[0]=0;
        m_pSon[1]=0;
        next = nullptr;
        prev = nullptr;
        ROOTY = nullptr;
    }
};

Nodo2D * buscarHoja_Izquierda(Nodo2D * node){
    if (node->m_pSon[0]== nullptr){
        return node;
    }
    return buscarHoja_Izquierda(node->m_pSon[0]);
}

Nodo2D * buscarHoja_Derecha(Nodo2D * node){
    if (node->m_pSon[1]== nullptr){
        return node;
    }
    return buscarHoja_Derecha(node->m_pSon[1]);
}

Nodo2D * create_range_treeY(vector<pair<int, int>> v, int l, int h ){
    if(l==h){
        Nodo2D * padre = new Nodo2D(v[l].first, v[l].second);
        padre->m_pSon[0] = new Nodo2D(v[l].first, v[l].second);
        padre->m_pSon[1] = 0;
        return padre;
    }

    if(l+1==h){
        Nodo2D * padre = new Nodo2D((v[l].first + v[h].first)/2, (v[l].second + v[h].second)/2);
        padre->m_pSon[0] = new Nodo2D(v[l].first, v[l].second);
        padre->m_pSon[1] = new Nodo2D(v[h].first, v[h].second);
        padre->m_pSon[0]->next = padre->m_pSon[1];
        padre->m_pSon[1]->prev = padre->m_pSon[0];
        return padre;
    }

    int m = (l + h)/2;
    Nodo2D * pl = create_range_treeY(v,l, m);
    Nodo2D * pr = create_range_treeY(v,m+1, h );

    Nodo2D * hijoIzq = buscarHoja_Derecha(pr);
    Nodo2D * hijoDer = buscarHoja_Izquierda(pl);

    hijoDer->next = hijoIzq;
    hijoIzq->prev = hijoDer;


    Nodo2D * padre = new Nodo2D((pl->x + pr->x)/2, (pl->y + pr->y)/2);
    padre->m_pSon[0] = pl;
    padre->m_pSon[1] = pr;

    return padre;
}


Nodo2D * create_range_tree(vector<pair<int, int>> v, int l, int h ){

    vector<pair<int, int>> ysorted = v;

    sort(ysorted.begin(), ysorted.end(), sortbysec);

    if(l==h){
        Nodo2D * padre = new Nodo2D(v[l].first, v[l].second);
        padre->m_pSon[0] = new Nodo2D(v[l].first, v[l].second);
        padre->ROOTY = create_range_treeY(ysorted,l, h );
        return padre;
    }
    if(l+1==h){
        Nodo2D * padre = new Nodo2D((v[l].first + v[h].first)/2, (v[l].second + v[h].second)/2);
        padre->m_pSon[0] = new Nodo2D(v[l].first, v[l].second);
        padre->m_pSon[1] = new Nodo2D(v[h].first, v[h].second);
        padre->m_pSon[0]->next = padre->m_pSon[1];
        padre->m_pSon[1]->prev = padre->m_pSon[0];
        padre->ROOTY = create_range_treeY(ysorted,l, h );
        return padre;
    }

    int m = (l + h)/2;
    Nodo2D * pl = create_range_tree(v,l, m);
    Nodo2D * pr = create_range_tree(v,m+1, h );


    Nodo2D * Y_tree = create_range_treeY(ysorted,l, h );

    Nodo2D * hijoIzq = buscarHoja_Derecha(pr);
    Nodo2D * hijoDer = buscarHoja_Izquierda(pl);

    hijoDer->next = hijoIzq;
    hijoIzq->prev = hijoDer;


    Nodo2D * padre = new Nodo2D((pl->x + pr->x)/2, (pl->y + pr->y)/2);
    padre->m_pSon[0] = pl;
    padre->m_pSon[1] = pr;
    padre->ROOTY=Y_tree;

    return padre;
}

void print(Nodo2D * r){
    if(!r) return;
    print(r->m_pSon[0]);
    if(!r->m_pSon[0] && !r->m_pSon[1])
        cout<<r->x<<" ";
    print(r->m_pSon[1]);

}

vector<pair<int,int>> range_search(int infx, int supx, int infy, int supy,  Nodo2D * root){

    queue<Nodo2D * > cola;
    vector<pair<int, int>> ans;
    Nodo2D * node = root;

    while(infx < node->x && supx < node->x){
        node = node->m_pSon[0];
    }

    while(infx > node->x && supx > node->x){
        node = node->m_pSon[1];
    }
    if (node == nullptr) return ans;

    while( node->m_pSon[0] != nullptr){
        if(infx < node->x){
            node = node->m_pSon[0];
            if(node->m_pSon[1] != nullptr)
                cola.push(node->m_pSon[1]);
        }else{
            node = node->m_pSon[1];
        }
    }

    if (node == nullptr) return ans;

    while( node->m_pSon[1] != nullptr){
        if(supx > node->x){
            node = node->m_pSon[1];
            cola.push(node->m_pSon[0]);
        }else{
            node = node->m_pSon[0];
        }
    }

    while(!cola.empty()){

        Nodo2D * node_temp = cola.front();
        cola.pop();

        while( node_temp->m_pSon[0] != nullptr){
            if(infy <= node_temp->y){
                node_temp = node_temp->m_pSon[0];
            }else{
                node_temp = node_temp->m_pSon[1];
            }
        }

        while(node_temp != nullptr && node_temp->y <= supy){
            ans.push_back(make_pair(node_temp->x, node_temp->y));
            node_temp = node_temp->next;
        }

    }

    return ans;

}



struct Nodo{
    int x;
    Nodo * m_pSon[2];
    Nodo * next;
    Nodo * prev;

    Nodo(int n){
        x = n;
        m_pSon[0]=0;
        m_pSon[1]=0;
        next = nullptr;
        prev = nullptr;
    }
};

Nodo * buscarHoja_Izquierda(Nodo * node){
    if (node->m_pSon[0]== nullptr){
        return node;
    }
    return buscarHoja_Izquierda(node->m_pSon[1]);
}

Nodo * buscarHoja_Derecha(Nodo * node){
    if (node->m_pSon[0]== nullptr){
        return node;
    }
    return buscarHoja_Derecha(node->m_pSon[0]);
}

Nodo * create_range_tree(vector<int> v,int l, int h){

    if(l==h){
        Nodo * padre = new Nodo(v[l]);
        padre->m_pSon[0] = new Nodo(v[l]);
        return padre;
    }
    if(l+1==h){
        Nodo * padre = new Nodo((v[l] + v[h])/2);
        padre->m_pSon[0] = new Nodo(v[l]);
        padre->m_pSon[1] = new Nodo(v[h]);
        padre->m_pSon[0]->next = padre->m_pSon[1];
        padre->m_pSon[1]->prev = padre->m_pSon[0];
        return padre;
    }
    int m = (l + h)/2;
    Nodo * pl = create_range_tree(v,l, m);
    Nodo * pr = create_range_tree(v,m+1, h );

    Nodo * hijoIzq = buscarHoja_Derecha(pr);
    Nodo * hijoDer = buscarHoja_Izquierda(pl);

    hijoDer->next = hijoIzq;
    hijoIzq->prev = hijoDer;


    Nodo * padre = new Nodo((pl->x + pr->x)/2);
    padre->m_pSon[0] = pl;
    padre->m_pSon[1] = pr;
    return padre;
}

vector<int> range_search(int inf, int sup, Nodo *root){
    vector<int> ans;
    Nodo * node = root;

    while( node->m_pSon[0] != nullptr){
        if(inf < node->x){
            node = node->m_pSon[0];
        }else{
            node = node->m_pSon[1];
        }
    }

    while(node->x < sup){
        ans.push_back(node->x);
        node = node->next;
    }

    return ans;
}

void print(Nodo * r){
    if(!r) return;
    print(r->m_pSon[0]);
    if(!r->m_pSon[0] && !r->m_pSon[1])
        cout<<r->x<<" ";
    print(r->m_pSon[1]);

}

#endif //RANGETREE_RANGETREE_H
