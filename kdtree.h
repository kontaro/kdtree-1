#include "kdnode.h"

class KDTree {


public:

	KDTree();
	~KDTree();

	KDNode *root;

	short create(points data);
	std::vector<double> search(std::vector<double> data);
	short add(std::vector<double> data);


private:

	short k;
	double best_dist;
	std::vector<double> best_guess;
	void knn(KDNode *node, std::vector<double> q);
	KDNode *insert(KDNode *node, std::vector<double> data, short lev);
	KDNode *build(points *data, short lev);
	void sort(points *pts, short lev);
	double distance(std::vector<double> q, std::vector<double> p);
	void dispose(KDNode *node);
};

struct Compare
{
	short _k;
	bool operator()(const std::vector<double>& lhs,
		const std::vector<double>& rhs) const
	{
		return lhs[_k] < rhs[_k];
	}

	Compare(short k) :_k(k) {}
};
