//
//  localize_tree.cpp
//  vacuum-world
//
//  Created by Daniel Gehrig on 22/09/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "localize_tree.hpp"

LocalizeTree::LocalizeTree(vector<vector<int>> map)
{
    root_node_.Initialize(map);
    visited_states_[location[0]][location[1]] = true;
    
    frontier_.push(&root_node_);
}