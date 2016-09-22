//
//  localize_tree.hpp
//  vacuum-world
//
//  Created by Daniel Gehrig on 22/09/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef localize_tree_hpp
#define localize_tree_hpp

#include <vector>

using namespace std;

class LocalizeTree:
{
public:
    /**
        Constructor of Tree searcher.
     
        @param: map: Wall map of the environment.
    */
    LocalizeTree(vector<vector<int>> map);
    
    /**
     Get the solution that is found after search. Calling this function
     before search returns an empty list of actions.
     
     @param: -
     */
    vector<char> GetSolution();
    
    /**
        Execute search for the goal and save the solution that is found that created it.
     
        @param: -
    */
    void Search();
    
    /**
        Clear the subtree under node and clear frontier.
     
        @param: node: clears the subtree under node.
    */
    void Clear(BeliefState* node);

private:

};
#endif /* localize_tree_hpp */
