//
//  visualizer.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 27/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//
#include "vaccuumworld/visualizer.hpp"

using namespace std;

void Visualizer::VisualizeSensors(bool dirt, array<bool, 4> proximity,
                                  array<bool, 4> directions, array<int, 2> location)
{
    array<char, 4> letters = {'u', 'r', 'd', 'l'};
    
    cout << "Sensors: " << "dirt: " << dirt << " Proximity: ";
    for (int direction= 0; direction < letters.size(); direction++)
    {
        if (proximity[direction])
        {
            cout << letters[direction];
        }
    }
    
    cout << " Directions: ";
    for (int direction = 0; direction < letters.size(); direction++)
    {
        if (directions[direction])
        {
            cout << letters[direction];
        }
    }
    cout << endl;
}

void Visualizer::VisualizeAction(char action)
{
    cout << "--> action: " << action << endl;
}

void Visualizer::VisualizeMap(vector<vector<int>> map, array<int, 2> location)
{
    cout << "MAP AFTER ACTION: " << endl;
    for (int x_coordinate = 0; x_coordinate < map.size(); x_coordinate++)
    {
        for (int y_coordinate = 0; y_coordinate < map[0].size(); y_coordinate++)
        {
            if (location[0] == x_coordinate && location[1] == y_coordinate)
            {
                cout << (!map[x_coordinate][y_coordinate] ? 'Q' : 'J');
            }
            else if (map[x_coordinate][y_coordinate] == -1)
            {
                cout << 'x';
            }
            else
            {
                
                cout << map[x_coordinate][y_coordinate];
            }
        }
        cout << endl;
    }
}