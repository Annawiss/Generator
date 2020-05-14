//
// Created by ssiwn on 07.05.2020.
//

#include "WorkWithNode.h"

namespace Project1 {

    static int countCycles = 1;

    Node_::Node_(const int num) {
        allowToAddEdge = true;
        allowToAddCycle = true;
        number = num;
    }

    /*GraphPrototype::GraphPrototype(int amount) {
        amountOfEdges = amount;
        Node newNode = *(new Node (0));
        newNode.cycleNumber = 0;
        if (amountOfEdges != 0)
        {
            myGraph.push_back(newNode);
        }
    }*/

    void AddNewCycle(int cycleLength, std::vector<Node_>& graph, int numberOfNode) {
        int numberOfAdd = graph.size();
        graph[numberOfNode].edges.push_back(numberOfAdd);
        graph[numberOfNode].edges.push_back(numberOfAdd + cycleLength - 2);
        graph[numberOfNode].cycleNumber = countCycles;
        graph[numberOfNode].allowToAddCycle = false;
        if (graph[numberOfNode].edges.size() == 3) {
            graph[numberOfNode].allowToAddEdge = false;
        }
        Node_ newNodeFirst(numberOfAdd);
        newNodeFirst.allowToAddCycle = false;
        newNodeFirst.cycleNumber = countCycles;
        newNodeFirst.edges.push_back(numberOfNode);
        newNodeFirst.edges.push_back(numberOfAdd + 1);
        graph.push_back(newNodeFirst);
        numberOfAdd++;
        for (int i = 1; i < cycleLength - 2; ++i) {
            Node_ newNode(numberOfAdd);
            newNode.allowToAddCycle = false;
            newNode.cycleNumber = countCycles;
            newNode.edges.push_back(numberOfAdd - 1);
            newNode.edges.push_back(numberOfAdd + 1);
            graph.push_back(newNode);
            numberOfAdd++;
        }
        Node_ newNodeLast(numberOfAdd);
        newNodeLast.allowToAddCycle = false;
        newNodeLast.cycleNumber = countCycles;
        newNodeLast.edges.push_back(numberOfAdd - 1);
        newNodeLast.edges.push_back(numberOfNode);
        graph.push_back(newNodeLast);
        countCycles++;
    }

    void AddNewEdge(std::vector<Node_>& graph, int numberOfNode)
    {
        Node_ newNode(graph.size());
        newNode.cycleNumber = graph[numberOfNode].cycleNumber;
        newNode.edges.push_back(numberOfNode);
        graph[numberOfNode].edges.push_back(newNode.number);
        if (graph[numberOfNode].edges.size() >= 2) {
            graph[numberOfNode].allowToAddEdge = false;
            graph[numberOfNode].allowToAddEdge = false;
        }
        graph.push_back(newNode);
    }

    bool AddEdgeInGraph(std::vector<Node_>& graph, int firstNode, int lastNode)
    {
        if (graph[firstNode].cycleNumber == graph[lastNode].cycleNumber)
        {
            return false;
        }
        if (!graph[firstNode].allowToAddEdge) {
            return false;
        }
        if (!graph[lastNode].allowToAddEdge) {
            return false;
        }
        graph[firstNode].edges.push_back(lastNode);
        if (graph[firstNode].edges.size() >= 2) {
            graph[firstNode].allowToAddEdge = false;
            graph[firstNode].allowToAddCycle = false;
        }
        graph[lastNode].edges.push_back(firstNode);
        if (graph[lastNode].edges.size() >= 2) {
            graph[lastNode].allowToAddEdge = false;
            graph[lastNode].allowToAddCycle = false;
        }
        return true;
    }

    void WorkWithNode(std::vector<std::vector<Node_>>& collection, std::vector<Node_>& currentVector, int currentNode, int edgesLeft)
    {
        if (edgesLeft == 0)
        {
            collection.push_back(currentVector); // если ребра кончились, граф готов
        }
        else
        {
            if (currentVector[currentNode].allowToAddCycle && edgesLeft > 2)
            {
                for (int i = 3; i <= edgesLeft; ++i)
                {
                    std::vector<Node_> curVec = currentVector;
                    AddNewCycle(i, curVec, currentNode);
                    WorkWithNode(collection, curVec, currentNode, edgesLeft - i); // добавиляем цикл всех возможных длин, продолжаем с той же вершины
                }
            }
            if (currentVector[currentNode].allowToAddEdge)
            {
                std::vector<Node_> curVec = currentVector;
                AddNewEdge(curVec, currentNode);
                WorkWithNode(collection, curVec, currentNode, edgesLeft - 1); // добавляем ребро в новую вершину
                for (int i = currentNode + 1; i < curVec.size() - 1; i++)
                {
                    std::vector<Node_> curVect = currentVector;
                    if (AddEdgeInGraph(curVect, currentNode, i)) {
                        WorkWithNode(collection, curVect, currentNode, edgesLeft - 1); // пробуем провести ребро между существующими
                    }
                }
            }
            if (currentNode < currentVector.size() - 1)
            {
                WorkWithNode(collection, currentVector, currentNode + 1, edgesLeft); // пропускаем вершину
            }
        }
    }

    std::vector<std::vector<Node_>> CreateGraphs_(int amountOfEdges)
    {
        std::vector<std::vector<Node_>> collection;
        std::vector<Node_> currentGraph;
        currentGraph.push_back(Node_(0));
        WorkWithNode(collection, currentGraph, 0, amountOfEdges);
        return collection;
    }

}