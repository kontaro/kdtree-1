#include "kdnode.h"
#include <sstream>
#include <fstream>

points getpts(const std::string &filename, points &pts);
void serialize(KDNode *root, std::ofstream &out);
void serialize(points pts, std::ofstream &out);
bool isvalid(KDNode *root);



