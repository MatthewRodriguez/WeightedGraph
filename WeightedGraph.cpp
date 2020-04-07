 //
//  WeightedGraph.cpp
//  WeightedGraph
//
//  Created by Matt Rodriguez on 4/2/20.
//  Copyright © 2020 Matthew Rodriguez. All rights reserved.
//

#include "WeightedGraph.h"

WeightedGraph::WeightedGraph(){
    nodes.clear();
}

void WeightedGraph::addNode(int val){
    Node *n = new Node(val);
    if (nodes.empty())
        nodes.push_back(n);
    else{
        for (int i = 0; i < nodes.size(); i++)
            if (nodes[i]->info == val)
                return;
        nodes.push_back(n);
    }
}

void WeightedGraph::addDirectedEdge(Node *first, Node *second, int weight){
    if (first->list.empty() && (first->info != second->info)){
        first->list.insert({second, weight});
    }
    else if(first->info == second->info){
        return;
    }
    else{
        unordered_map<Node*, int>::iterator it;
        for (it = first->list.begin(); it != first->list.end(); it++){
            if (it->first->info == second->info)
                return;
        }
        first->list.insert({second, weight});
    }
}

/*
void WeightedGraph::removeDirectedEdge(Node *first, Node *second){
    if (first->list.empty())
        return;
    unordered_map<Node*, int>::iterator it;
    int count = 0;
    for (it = first->list.begin(); it != first->list.end(); it++){
        if (it->first->info == second->info)
            it->first->list.erase(it->first->list.begin()+count);
    }
  
}
*/
void WeightedGraph::printNodes(){
    cout << " { ";
    for (int i = 0; i < nodes.size(); i++)
        cout << nodes[i]->info << " ";
    cout << " }" << endl;
}

void WeightedGraph::printU(){
    unordered_map<Node*, int>::iterator it;
    for (int i = 0; i < nodes.size(); i++){
        cout << nodes[i]->info << ": ";
        for (it = nodes[i]->list.begin(); it != nodes[i]->list.end(); it++){
            cout << "{" << it->first->info << ":" << it->second << "} ";
        }
        cout << endl;
    }
    cout << endl;
}

void WeightedGraph::clear(){
    nodes.clear();
}

void WeightedGraph::updateDistance(Node *f, Node *s, unordered_map<Node*, int> &umap){
    int min = 0, dist = 0;
    unordered_map<Node*, int>::iterator it;
    for (it = f->list.begin(); it != f->list.end(); it++){
        if (it->first->info == s->info)
            dist = it->second;
    }
    min = f->distance + dist;
    if (min < s->distance){
        s->distance = min;
        it = umap.find(s);
        it->second = min;
    }
}

Node* WeightedGraph::findMinDistance(unordered_map<Node*, int> umap){
    Node *n = nullptr;
    unordered_map<Node*, int>::iterator it;
    if (umap.empty())
        return nullptr;
    int minimum = INT_MAX;
    for (it = umap.begin(); it != umap.end(); it++){
        if (!it->first->visit)
            if (minimum > it->second)
                n = it->first;
    }
    return n;
}

void WeightedGraph::createRandomCompleteWeightedGraph(int n){
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, (n*n*n));
    int r, i;
    for (i = 0; i < n; i++)
        addNode(dist(mt));
    
    for (i = 0; i < nodes.size(); i++){
        for (int j = 0; j < nodes.size(); j++){
            if (nodes[i]->info == nodes[j]->info)
                continue;
            else{
                r = rand() % 15 + 1;
                addDirectedEdge(nodes[i], nodes[j], r);
            }
        }
    }
}

void WeightedGraph::createLinkedList(int n){
    int random, m = n*5;
    for (int i = 0; i < n; i++){
        random = rand() % m + 1;
        addNode(random);
        if (nodes.size() > 1)
            addDirectedEdge(nodes[nodes.size()-2], nodes[nodes.size()-1], 1);
    }
    
}

unordered_map<Node*, int> WeightedGraph::d(){
    return dijkstras(nodes[0]);
}

unordered_map<Node*, int> WeightedGraph::dijkstras(Node *start){
    unordered_map<Node*, int> m;
    unordered_map<Node*, int>::iterator it;
    vector<Node*> vec;
    Node *n;
    
    for (it = start->list.begin(); it != start->list.end(); it++)
        m.insert({it->first, it->first->distance});
    
    start->distance = 0;
    m.insert({start, start->distance});
    n = start;
    
    while (n != nullptr && n->distance != INT_MAX){
        n->visit = true;
        
        for (it = n->list.begin(); it != n->list.end(); it++){
            if (!it->first->visit){
                m.insert({it->first, it->first->distance});
                updateDistance(n, it->first, m);
            }
        }
        
        n = findMinDistance(m);
    }
    return m;
}
