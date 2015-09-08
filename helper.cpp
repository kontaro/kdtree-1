#include <iterator>
#include "helper.h"

points getpts(const std::string &filename, points &pts)
{
	std::ifstream file(filename);
	std::string line;

	while (getline(file, line))
	{
		std::stringstream ss(line);
		std::string token;
		std::vector<double> p;

		while (getline(ss, token, ' '))
		{
			p.push_back(stod(token));
		}


		pts.push_back(p);

	}

	return pts;

}


void serialize(KDNode *root, std::ofstream &out)

{

	if (!root) {
		out << "# ";
	}
	else {
		out << "[";
		for (std::vector<double>::const_iterator i = root->data.begin(); i != root->data.end(); ++i) {
			out << *i << ' ';
		}
		out << "]";

		serialize(root->left, out);
		serialize(root->right, out);
	}
}


void serialize(points qry_pts, std::ofstream &out)

{
	for (unsigned int idx = 0; idx < qry_pts.size(); idx++)
	{
		if (idx % 2 != 0)
		{
			out << '[';
		}

		for (std::vector<double>::const_iterator i = qry_pts.at(idx).begin(); i != qry_pts.at(idx).end(); ++i)
		{
			out << *i << ' ';

		}


		if (idx % 2 != 0)
		{
			out << ']';
		}

	}
}



bool isvalid(KDNode *root)

{

	if (!root)
	{
		return false;
	}

	else

	{

		if (root->left != NULL)
		{
			if (root->data.at(root->axis) <= root->left->data.at(root->axis))
			{
				return false;
			}
		}

		if (root->right != NULL)
		{
			if (root->data.at(root->axis) > root->right->data.at(root->axis))
			{
				return false;
			}
		}



	}

	isvalid(root->left);
	isvalid(root->right);

	return true;
}

