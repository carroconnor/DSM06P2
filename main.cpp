#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
#include "graph.h"

// For this assignment, you will be given a file routes.txt that contains a list of IP addresses, 
// and an adjacency list for a graph. You will need to read the file line by line and use regular 
// expressions to determine if the line contains an IP address or part of the adjacency list. 
// Store the list of IP addresses in a vector in the graph class. The index of the IP address matches 
// with the index of the adjacency list. Create a function in the graph class that finds a path between 
// two IP addresses. 

// In the main prompt the user for a starting IP address and an ending IP address. 
// Use the function you added to the graph class to determine the path from the starting IP to the ending IP.

int main(){
    //example ip address: 150.136.66.185
    //example adjacency list item: 0 1 8 5 -999
    //create regular expressions to match IP addresses and adjacency list
    graphType graph;
    graph.createGraph("routes.txt");
    //store the ip addresses in a vector in the graph class

    //store the adjacency list in the graph class

    //prompt the user for a starting IP address and an ending IP address

    //use the function you added to the graph class to determine the path from the starting IP to the ending IP

    while(true){
        std::string start_ip;
        std::string end_ip;
        std::cout << "Enter the starting IP address: ";
        std::cin >> start_ip;
        std::cout << "Enter the ending IP address: ";
        std::cin >> end_ip;
        std::cout << "Path from " << start_ip << " to " << end_ip << ": " << graph.findPath(start_ip, end_ip) << std::endl;
    }
    return 0;
}