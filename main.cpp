//
//  main.cpp
//  WeightedGraph
//
//  Created by Matt Rodriguez on 4/2/20.
//  Copyright © 2020 Matthew Rodriguez. All rights reserved.
//

#include "WeightedGraph.h"

int main(int argc, const char * argv[]) {

    WeightedGraph g;
    unordered_map<Node*, int> umap;
    unordered_map<Node*, int>::iterator it;
    g.createLinkedList(10);
    cout << "LinkedList";
    g.printNodes();
    g.printU();
    g.clear();
    g.createRandomCompleteWeightedGraph(10);
    cout << "Graph";
    g.printNodes();
    g.printU();
  
    umap = g.d();
    cout << "Disjktra's: ";
    for (it = umap.begin(); it != umap.end(); it++)
        cout << "{" << it->first->info << ":" << it->second << "}" << " ";
    cout << endl;
    return 0;
}
