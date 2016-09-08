//
//  visualizer.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 27/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//
#include "vaccuumworld/visualizer.hpp"

using namespace std;

void Visualizer::visualizeSensors(bool dirt, array<bool, 4> proximity,
                             array<bool, 4> directions, array<int, 2> location)
{
    array<char, 4> letters = {'u', 'r', 'd', 'l'};
    
    cout << "Sensors: " << "dirt: " << dirt << " Proximity: ";
    for (int i = 0; i < letters.size(); i++)
    {
        if (proximity[i])
        {
            cout << letters[i];
        }
    }
    
    cout << " Directions: ";
    for (int i = 0; i < letters.size(); i++)
    {
        if (directions[i])
        {
            cout << letters[i];
        }
    }
    cout << endl;
}

void Visualizer::visualizeAction(char action)
{
    cout << "--> action: " << action << endl;
}

void Visualizer::visualizeMap(vector<vector<int>> map, array<int, 2> loc)
{
    cout << "MAP AFTER ACTION: " << endl;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            if (loc[0] == i && loc[1] == j)
            {
                (map[i][j] == 0) ? cout << 'Q' : cout << 'J';
            }
            else if (map[i][j] == -1)
            {
                cout << 'x';
            }
            else
            {
                cout << map[i][j];
            }
        }
        cout << endl;
    }
}

void Visualizer::visualizeTree(State root, int indent)
{
    // print blanks
    string blanks(indent, ' ');
    cout << blanks;
    
    // print coordinates of node
    for (int i : root.getLocation())
    {
        if (i < 10)
        {
            cout << 0;
        }
        cout << i << ',';
    }
    cout << ' ';
    
    // print total estimated pathcost
    int totalCost = root.getTotalCost();
    if (totalCost < 10)
    {
        cout << 0;
    }
    cout << totalCost << ' ';
    
    // print children
    for (State* child : root.getChildren())
    {
        visualizeTree(*child, indent + 9);
        cout << endl;
    }
}
