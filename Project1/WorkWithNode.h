//
// Created by ssiwn on 07.05.2020.
//

#pragma once

#ifndef COURSE_WORK_WORKWITHNODE_H
#define COURSE_WORK_WORKWITHNODE_H

#endif //COURSE_WORK_WORKWITHNODE_H

#include "iostream"
#include "vector"

namespace Project1 {

    class Node_
    {
    public:
        bool allowToAddEdge;
        bool allowToAddCycle;
        int cycleNumber;
        int number;
        std::vector<int> edges;
        Node_(const int num);
    };
    /*
    class GraphPrototype
    {
        //int amountOfEdges;

        //GraphPrototype(int amountOfEdges);

    public:
        std::vector<Node> myGraph;
        GraphPrototype(std::vector<Node> nodes);
    };
    */

    void AddNewCycle(int cycleLength, std::vector<Node_>& graph, int numberOfNode);

    void AddNewEdge(std::vector<Node_>& graph, int numberOfNode);

    bool AddEdgeInGraph(std::vector<Node_>& graph, int firstNode, int lastNode);

    void WorkWithNode(std::vector<std::vector<Node_>>& collection, std::vector<Node_>& currentVector, int currentNode, int edgesLeft);

    std::vector<std::vector<Node_>> CreateGraphs_(int amountOfEdges);

}