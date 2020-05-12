//
// Created by ssiwn on 11.05.2020.
//

#ifndef COURSE_WORK_COMBINATORYWORK_H
#define COURSE_WORK_COMBINATORYWORK_H


//#include "iostream"
//#include "vector"
#include "WorkWithNode.h"

namespace Project1
{

	//std::vector<std::vector<std::vector<int>>> ConvertIntoMatrix(std::vector<std::vector<Node>> graphs);

	std::vector<std::vector<std::pair<int, int>>> ConvertIntoPairs(std::vector<std::vector<Node_>>& graphs);

	std::vector<std::vector<double>> CreateTranspositions(std::vector<double>& edges, int amountOfEdges);

	//std::vector<std::vector<std::vector<int>>> PlaceEdges(std::vector<int> edgesLength, std::vector<std::vector<std::vector<int>>> prototypes);

}
#endif //COURSE_WORK_COMBINATORYWORK_H
