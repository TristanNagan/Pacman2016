#include "DFS.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

DFS::DFS(vector<vector<Tile>> &maze, Character &Pacman, Character &GhostR)
    :/*path(true),*/ data(maze)
{
    rows = maze.size();
    cols = maze[0].size();

    goal={Pacman.y/20, Pacman.x/20};
    start={GhostR.y/20, GhostR.x/20};

    unvisit();
}

void DFS::unvisit(){
    unvisited.clear();
    for(int i = 0; i < rows ; i++){
        unvisited.emplace_back(cols, 0);
    }
}

bool DFS::search(pair<int,int>stat){
        cout <<"Stat Coordinate:("<< stat.first << "," << stat.second <<")"<< endl;
        cout <<"Unvisited Size: "<<unvisited.size()<<endl;
        pair<int,int>curr;
    if(stat != goal){
        unvisited[stat.first][stat.second] = 1;
        down = {stat.first + 1, stat.second};
        left = {stat.first, stat.second - 1};
        up = {stat.first - 1, stat.second};
        right = {stat.first, stat.second + 1};

        if(is_valid(down) && is_unvisited(down) == 0){
            cout<<"Down"<<endl;
            parent.push_back(stat);
            is_unvisited(down) = 1;
            if(search(down)){
                curr=parent.back();
                cout<<"Parent back:("<<curr.first<<","<<curr.second<<")"<<endl;
                path=true;
                return true;

            }
        }

       if(is_valid(left) && is_unvisited(left) == 0){
            cout<<"Left"<<endl;
            parent.push_back(stat);
            is_unvisited(left) = 1;
            if(search(left)){
                curr=parent.back();
                cout<<"Parent back:("<<curr.first<<","<<curr.second<<")"<<endl;
                path=true;
                return true;
            }
        }

       if(is_valid(up) && is_unvisited(up) == 0/* && is_valid(right)==1*/){
           cout<<"Up"<<endl;
            parent.push_back(stat);
            is_unvisited(up) = 1;
            if(search(up)){
                curr=parent.back();
                cout<<"Parent back:("<<curr.first<<","<<curr.second<<")"<<endl;
                path=true;
                return true;
            }
        }

      if(is_valid(right) && is_unvisited(right) == 0){
            cout<<"Right"<<endl;
            parent.push_back(stat);
            is_unvisited(right) = 1;
            if(search(right)){
                curr=parent.back();
                cout<<"Parent back:("<<curr.first<<","<<curr.second<<")"<<endl;
                path=true;
                return true;
            }
        }
	path=false;
        return false;
    }
    else{
	path=true;
        return true;
    }
}

/*bool DFS::search()
{
    return search(start);
}*/

pair<int,int> DFS::moving(){
    pair<int,int> offspring;

    while(parent.size() != 1){
        offspring = parent.back();
        parent.pop_back();
}
    cout<<"Offspring Coordinates:("<<offspring.first<<","<<offspring.second<<")"<<endl;
    parent.clear();
    return offspring;
}

pair<int,int> DFS::backtrack(){

    pair<int,int>roots;
    roots = parent.back();
    parent.pop_back();
    return roots;
}

vector<pair<int,int>> DFS::getParent()
{
    return parent;
}

int &DFS::is_unvisited(pair<int, int> coord)
{
    return unvisited[coord.first][coord.second];
}

bool DFS::is_valid(pair<int, int> coord)
{
    return coord.first >= 0 && coord.first < rows &&
            coord.second >= 0 && coord.second < cols &&
            data[coord.first][coord.second].myType != Wall;
}
