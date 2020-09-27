#ifndef DFS_H
#define DFS_H

#include <vector>
#include <string>
#include "character.h"
#include "tile.h"
#include "helpers.h"


using namespace std;

class DFS{

public:
    int rows, cols;
    vector<vector<Tile>> data;
    pair<int,int>start;
    pair<int,int>goal;
    pair<int,int>down;
    pair<int,int>left;
    pair<int,int>up;
    pair<int,int>right;
    vector<vector<int>>unvisited;
    bool path;
    vector<pair<int,int>>parent;

    void unvisit();

    pair<int,int> backtrack();
        pair<int,int> moving();

    vector<std::pair<int,int>>getParent();
    int &is_unvisited(pair<int,int> coord);
    bool is_valid(pair<int,int> coord);

    DFS(vector<vector<Tile>> &maze, Character &Pacman,  Character &GhostR);
    bool search(pair<int,int>stat);
    //bool search();
};

#endif
