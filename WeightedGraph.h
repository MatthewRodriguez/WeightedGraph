//
//  WeightedGraph.h
//  WeightedGraph
//
//  Created by Matt Rodriguez on 4/2/20.
//  Copyright © 2020 Matthew Rodriguez. All rights reserved.
//

//https://users.cs.fiu.edu/~weiss/dsaa_c++4/code/TestRandom.cpp
#ifndef WeightedGraph_h
#define WeightedGraph_h
#include <iostream>
#include <vector>
#include <climits>
#include <random>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct Node{
    int info;
    int distance;
    bool visit;
    Node *parent;
    unordered_map<Node*, int> list;
    Node(int i, int d = INT_MAX, bool v = false) : info(i), distance(d), visit(v){}
};

class WeightedGraph{
    vector<Node*> nodes;
public:
    WeightedGraph();
    void addNode(int val);
    void addDirectedEdge(Node *first, Node *second, int weight);
    void removeDirectedEdge(Node *first, Node *second);
    unordered_set<Node*> getAllNodes();
    void createRandomCompleteWeightedGraph(int n);
    void createLinkedList(int n);
    unordered_map<Node*, int> dijkstras(Node *start);
    unordered_map<Node*, int> d();
    void updateDistance(Node *first, Node *second, unordered_map<Node*, int> &umap);
    Node* findMinDistance(unordered_map<Node*, int> v);
    void printNodes();
    void printU();
    void clear();
};

#endif /* WeightedGraph_h */
