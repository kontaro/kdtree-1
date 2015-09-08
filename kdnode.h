#pragma once
#include <vector>

typedef std::vector< std::vector<double> > points;

struct KDNode {
	int axis;
	KDNode  *left;
	KDNode  *right;
	std::vector<double> data;
};
