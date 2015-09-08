#include <iostream>
#include "kdtree.h"
#include "helper.h"
#include <string.h>


int main(int argc, char* argv[])
{
	std::string pts_file = "data/data";
	std::string qry_file = "data/query";
	std::string qry_results_file= "data/query_results";
	std::string kdtree_file = "data/kdtree";

	bool dynin = false;
	bool testkdt = false;
	bool query = false;
	bool verbose = false;

	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i],"-i") == 0)
		{
			dynin = true;
		}

        else if (strcmp(argv[i],"-f") == 0)
		{
			if (argv[i + 1] != NULL)
			{
				pts_file = argv[i + 1];
			}
		}

        else if (strcmp(argv[i],"-t") == 0)
		{
			testkdt = true;
		}

        else if (strcmp(argv[i],"-q") == 0)
		{
			query = true;
		}

        else if (strcmp(argv[i],"-v") == 0)
		{
			verbose = true;
		}

		else

		{
		}
	}

    std::cout << "loading points" << '\n';
	points pts;
    getpts(pts_file, pts);

	if (pts.size() == 0)

	{
		std::cout << "no points" << '\n';
		return 0; //no points, exit

	}

	std::cout << "points loaded. creating tree" << '\n';

	KDTree *kdtree = new KDTree;

	if (dynin)
	{
	std::cout << "dynamic insert on" << '\n';
		for (unsigned int idx = 0; idx < pts.size(); idx++)
		{
			kdtree->add(pts.at(idx)); //dynamically insert points

			if (verbose)
			{
                std::cout << "inserting point [";

                for (std::vector<double>::const_iterator i = pts.at(idx).begin(); i != pts.at(idx).end(); ++i)
                {
                    std::cout << *i << ' ';
                }

                std::cout << "]\n";

			}
		}
	}

	else

	{

		kdtree->create(pts);

	}


	if (query)
	{

		points qry_pts;
		getpts(qry_file, qry_pts);

		points qry_res_pts;


		if (qry_pts.size() > 0)
		{
			for (unsigned int idx = 0; idx < qry_pts.size(); idx++)
			{

				std::vector<double> res_p = kdtree->search(qry_pts.at(idx));

				if (res_p.size() > 0)
				{
					qry_res_pts.push_back(qry_pts.at(idx));
					qry_res_pts.push_back(res_p);
				}

			}

			std::ofstream qry_out(qry_results_file);
			serialize(qry_res_pts, qry_out);


		}
	}


	if (testkdt)
	{
		std::cout << "isvalid = " << isvalid(kdtree->root) << "\n";
	}

	std::ofstream out(kdtree_file);

	serialize(kdtree->root, out);

	delete kdtree;

	std::cout << "all done. \n";

	//std::string usrinput;
	//std::cin >> usrinput;

	return 0;
}



