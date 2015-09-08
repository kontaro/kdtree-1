#include "kdtree.h"
#include <math.h>
#include <algorithm>
#include <limits>

KDTree::KDTree() { root = NULL; }

KDTree::~KDTree() {
	dispose(this->root);
}

void KDTree::dispose(KDNode *node)
{
	if (node != NULL)
	{
		dispose(node->left);
		dispose(node->right);
		delete node;
	}
}
short KDTree::create(points pts)
{
	if (pts.empty()) return 0;

	k = pts.at(0).size();

	root = build(&pts, 0);

	return 1;

}

short KDTree::add(std::vector<double> data)
{
	k = data.size();
	if (root == NULL)
	{
		root = new KDNode;
		root->axis = 0;
		root->data = data;
		root->left = NULL;
		root->right = NULL;
	}
	else
	{
		insert(root, data, root->axis);
	}

	return 1;
}

KDNode *KDTree::insert(KDNode *node, std::vector<double> data, short lev)
{
	if (node == NULL)
	{
		node = new KDNode;
		node->axis = lev == k ? 0 : lev;
		node->data = data;
		node->left = NULL;
		node->right = NULL;
	}

	else
	{
		if (node->data == data)
		{
			return node;
		}

		if (data.at(node->axis) <= node->data.at(node->axis))
		{
			node->left = insert(node->left, data, node->axis + 1);
		}

		else
		{
			node->right = insert(node->right, data, node->axis + 1);
		}
	}

	return node;
}

std::vector<double> KDTree::search(std::vector<double> data)
{
	best_dist = std::numeric_limits<double>::infinity();
	knn(root, data);
	return best_guess;

}

void KDTree::knn(KDNode *node, std::vector<double> q)
{

	//better to use locality - sensitive hashing(LSH)

	if (!node) return;

	double dist = distance(q, node->data);

	if (dist < best_dist)

	{
		best_guess = node->data;
		best_dist = dist;
	}


	KDNode *nearest_kd = q.at(node->axis) < node->data.at(node->axis) ? node->left : node->right;
	KDNode *further_kd = q.at(node->axis) < node->data.at(node->axis) ? node->right : node->left;

	knn(nearest_kd, q);

	if (abs(q.at(node->axis) - node->data.at(node->axis) >= best_dist))
	{
		return;

	}

	knn(further_kd, q);

}


void KDTree::sort(points *pts, short lev)
{
	std::sort(pts->begin(), pts->end(), Compare(lev));
}

KDNode *KDTree::build(points *pts, short lev)
{

	KDNode *node = NULL;


	double pivot = 0;

	if (pts > 0 && pts->size() > 0)
	{

		points *ldata = NULL;
		points *rdata = NULL;

		if (lev == k) { lev = 0; }

		if ((int)pts->size() > 1) //not a leaf
		{
			sort(pts, lev);

			double med = (double)(pts->size() / 2);

			pivot = floor(med);

			ldata = new points(pts->begin(), pts->begin() + pivot);
			rdata = new points(pts->begin() + pivot + 1, pts->end());

		}

		node = new KDNode;
		node->axis = lev;
		lev++;
		node->left = build(ldata, lev);
		node->right = build(rdata, lev);
		node->data = pts->at(pivot);

	}

	return node;
}

double KDTree::distance(std::vector<double> q, std::vector<double> p)
{
	double v = 0;

	for (int idx = 0; idx < k; idx++)
	{
		v += pow(q.at(idx) - p.at(idx), 2); // Must be a faster way to get distance.
	}

	return abs(sqrt(v));
}

