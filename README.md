# AStarAlgorithmTesterApp
A simple interactive app aiming to show in the simplest and most intuitive way how the fundamental A Star Algorith works and manages to find the best path possible.
A 12x6 grid is present where:
Nodes can be placed using left click, removing nodes using right click.
"Start Node" (color orange), the node which the algorithm will start searching from. Clicking on another grid node will "move" the start node, as there can't be more than 1 starting positions at a time.
"End Node" (color blue),the node which is the algorithm's destination goal. Clicking on another grid node will "move" the end node, as there can't be more than 1 destination positions at a time.
"Obstacle Node" (color black), this node acts as a barrier, the algorithm cannot move through that node.

"Start Test" and "End Test" buttons activate and deactivate the algorithm respectively.
While the algorithm is running, gray boxes with the shape of nodes, will start showing up showing which neighbor nodes the algorithm is currently searching, showcasing gCost,hCost,fCost.
gCost: The cost to move from the starting node to another node using the path which has been selected so far. This path may not be necessarily the final path. That means the gCost of any node can change at any time because we might find a better path towards that node.
hCost: The cost to move from one node to the end node. This cost is constant.
fCost: the sum of gCost and hCost.
After the algorithm has finished searching the best path, it creates "Steps" ( green boxes with the shape of nodes ), which show what path the algorithm managed to find.
If the algorithm fails to find a path, the user will be notified.
Extra capabilities:
Clear Grid Button: Pressing it will clear the grid.
Undo Last Action Button: Works just like any other Undo Button present in any other app, it "undos" the last action that the user made.
Save Current Instance Button: Saves the current set up of the grid. This is done by saving the actions done by the user on a .txt file saved on the bin/assets folder named "FileManagerOutput.txt".
Load Last Saved Instance Button: Loads the last instance which the user saved by pressing the Save Current Instance button. This is done by decoding the FileManagerOutput.txt file's data and applying them into the application.

This application was made by Helio Zhuleku on December of 2025 with the C++ Programming Language using the SGG Graphics Library, more info on the library can be found here --> https://github.com/cgaueb/sgg/tree/main
