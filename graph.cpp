#include <regex>
#include "graph.h"

bool graphType::isEmpty() const
{
    return gSize == 0;
}

void graphType::createGraph(std::string filename)
{
    std::ifstream file(filename);
    int vertex;
    int adjcentVertex;

    clearGraph();
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open input file.");
    }

    delete[] graph;    
    graph = new unorderedLinkedList<int>[150];  //maxSize
    
    std::regex regex_ip("^(?:(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])(\\.(?!$)|$)){4}$"); 
    std::string line;
    while(std::getline(file, line)){
        std::smatch match;
        if(std::regex_search(line, match, regex_ip)){
            //ip address found
            ip_addresses.push_back(match.str());
        } else {
            //adjacency list found
            std::istringstream iss(line);
            while(iss >> adjcentVertex){
                std::cout << "Read value: " << adjcentVertex << std::endl; // Debugging line
                if(adjcentVertex != -999){
                    std::cout << "Inserting value: " << adjcentVertex << std::endl; // Debugging line
                    graph[vertex].insert(adjcentVertex);
                }
            }
            vertex++;
        }
    }

    file.close();
}

std::string graphType::findPath(std::string start_ip, std::string end_ip){
    //find the index of the starting and ending IP addresses
    auto it = find(ip_addresses.begin(), ip_addresses.end(), start_ip);
    if(it == ip_addresses.end()){
        return "Starting IP address not found.";
    }
    auto it2 = find(ip_addresses.begin(), ip_addresses.end(), end_ip);
    if(it2 == ip_addresses.end()){
        return "Ending IP address not found.";
    }
    int start = it - ip_addresses.begin();
    int end = it2 - ip_addresses.begin();

    std::string path = "";
    linkedQueue<int> queue;
    bool *visited;
    visited = new bool[gSize];
    for (int i = 0; i < gSize; i++)
        visited[i] = false;
    linkedListIterator<int> graphIt;
    queue.enqueue(start);
    visited[start] = true;
    while(!queue.isEmptyQueue()){
        int u = queue.dequeue();
        for (graphIt = graph[u].begin(); graphIt != graph[u].end(); ++graphIt)
        {
            int w = *graphIt;
            if (!visited[w])
            {
                queue.enqueue(w);
                visited[w] = true;
                if(w == end){
                    path += std::to_string(w);
                    return path;
                }
                path += std::to_string(w) + " ";
            }
        }
    }
    return path;
}

void graphType::clearGraph()
{
    for (int i = 0; i < gSize; i++)
    {
        graph[i].destroyList();
    }
    gSize = 0;
}

std::string graphType::printGraph() const
{
    std::ostringstream out;
    for (int i = 0; i < gSize; i++)
    {
        out << i << " ";
        graph[i].print(out);
        out << std::endl;
    }
    out << std::endl;
    return out.str();
}

graphType::graphType(int size)
{
    maxSize = size;
    gSize = 0;
    graph = new unorderedLinkedList<int>[size];
}

graphType::~graphType()
{
    clearGraph();
    delete[] graph;
}

std::string graphType::depthFirstTraversal()
{
    bool *visited;
    visited = new bool[gSize];
    std::string out = "";
    for (int i = 0; i < gSize; i++)
        visited[i] = false;
    for (int i = 0; i < gSize; i++)
    {
        if (!visited[i])
            dft(i, visited, out);
    }
    delete[] visited;
    return out;
}

std::string graphType::dftAtVertex(int vertex)
{
    bool *visited;
    visited = new bool[gSize];
    for (int i = 0; i < gSize; i++)
        visited[i] = false;
    std::string out = "";
    dft(vertex, visited, out);
    delete[] visited;
    return out;
}

std::string graphType::breadthFirstTraversal()
{
    linkedQueue<int> queue;
    bool *visited;
    visited = new bool[gSize];
    for (int i = 0; i < gSize; i++)
        visited[i] = false;
    std::string out = "";
    linkedListIterator<int> graphIt;
    for (int i = 0; i < gSize; i++)
    {
        if (!visited[i])
        {
            queue.enqueue(i);
            visited[i] = true;
            out = out + " " + std::to_string(i) + " ";
            while (!queue.isEmptyQueue())
            {
                int u = queue.dequeue();
                for (graphIt = graph[u].begin(); graphIt != graph[u].end(); ++graphIt)
                {
                    int w = *graphIt;
                    if (!visited[w])
                    {
                        queue.enqueue(w);
                        visited[w] = true;
                        out = out + " " + std::to_string(w) + " ";
                    }
                }
            }
        }
    }
    delete[] visited;
    return out;
}

void graphType::dft(int v, bool visited[], std::string &output)
{
    visited[v] = true;
    output = output + " " + std::to_string(v) + " ";
    linkedListIterator<int> graphIt;
    for (graphIt = graph[v].begin(); graphIt != graph[v].end(); ++graphIt)
    {
        int w = *graphIt;
        if (!visited[w])
            dft(w, visited, output);
    }
}
