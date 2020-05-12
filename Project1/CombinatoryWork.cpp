//
// Created by ssiwn on 11.05.2020.
//



#include "iostream"
#include "vector"
#include "CombinatoryWork.h"
#include "algorithm"

namespace Project1
{

    std::vector<std::vector<std::pair<int, int>>> ConvertIntoPairs(std::vector<std::vector<Node_>>& graphs) {
        std::vector<std::vector<std::pair<int, int>>> vectorOfGraphs;
        for (unsigned int i = 0; i < graphs.size(); ++i) {
            std::vector<std::pair<int, int>> oneGraph;
            for (unsigned int j = 0; j < graphs[i].size(); j++) {
                for (unsigned int k = 0; k < graphs[i][j].edges.size(); k++) {
                    if (j < graphs[i][j].edges[k]) {
                        oneGraph.push_back(std::pair<int, int>(j, graphs[i][j].edges[k]));
                    }
                }
            }
            vectorOfGraphs.push_back(oneGraph);
        }
        return vectorOfGraphs;
    }

    void swap(std::vector<double>& a, int i, int j)
    {
        int s = a[i];
        a[i] = a[j];
        a[j] = s;
    }

    bool NextSet(std::vector<std::vector<double>>& transpositions, std::vector<double>& currTrans, int amountOfEdges)
    {
        int j = amountOfEdges - 2;
        while (j != -1 && currTrans[j] >= currTrans[j + 1])
        {
            j--;
        }
        if (j == -1) {
            return false; // больше перестановок нет
        }
        int k = amountOfEdges - 1;
        while (currTrans[j] >= currTrans[k]) {
            k--;
        }
        swap(currTrans, j, k);
        int l = j + 1, r = amountOfEdges - 1; // сортируем оставшуюся часть последовательности
        while (l < r) {
            swap(currTrans, l++, r--);
        }
        transpositions.push_back(currTrans);
        return true;
    }

    std::vector<std::vector<double>> CreateTranspositions(std::vector<double>& edges, int amountOfEdges)
    {
        std::vector<std::vector<double>> trans;
        std::sort(edges.begin(), edges.end());
        trans.push_back(edges);
        while (NextSet(trans, edges, amountOfEdges));
        return trans;
    }
}