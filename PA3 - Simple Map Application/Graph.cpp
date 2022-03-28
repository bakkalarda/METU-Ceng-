#include "Graph.h"
#include "GraphExceptions.h"

#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>

// Literally do nothing here
// default constructors of the std::vector is enough
Graph::Graph()
{}

Graph::Graph(const std::string& filePath)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    // Tokens
    std::string tokens[3];

    std::ifstream mapFile(filePath.c_str());
    // Read line by line
    std::string line;
    while (std::getline(mapFile, line))
    {
        // Empty Line Skip
        if(line.empty()) continue;
        // Comment Skip
        if(line[0] == '#') continue;

        // Tokenize the line
        int i = 0;
        std::istringstream stream(line);
        while(stream >> tokens[i]) i++;

        // Single token (Meaning it is a vertex)
        if(i == 1)
        {
            InsertVertex(tokens[0]);
        }
        // Exactly three tokens (Meaning it is an edge)
        else if(i == 3)
        {
            int weight = std::atoi(tokens[0].c_str());
            if(!ConnectVertices(tokens[1], tokens[2], weight))
            {
                std::cerr << "Duplicate edge on "
                          << tokens[0] << "-"
                          << tokens[1] << std::endl;
            }
        }
        else std::cerr << "Token Size Mismatch" << std::endl;
    }
}

void Graph::InsertVertex(const std::string& vertexName)
{
    bool dup = false;       
    for(int i=0; i<(int)vertexList.size(); i++)
    {
        if(vertexList[i].name == vertexName)
        {
            dup = true;
        }
    }
    if(dup == true)
    {
        throw DuplicateVertexNameException();
    }
    else{
        struct GraphVertex new_vertex;
        new_vertex.edgeCount = 0;
        new_vertex.name = vertexName;
        vertexList.push_back(new_vertex);
    }
}

bool Graph::ConnectVertices(const std::string& fromVertexName,
                            const std::string& toVertexName,
                            int weight)
{
    bool fvertex = false;
    int findex = 0;
    int tindex = 0;
    bool tvertex = false;
    for(int i=0; i<(int)vertexList.size();i++)
    {
        if(vertexList[i].name == fromVertexName)
        {
            fvertex = true;
            findex = i;
        }
        if (vertexList[i].name == toVertexName)
        {
            tvertex = true;
            tindex = i;
        }
    }
    if(fvertex == false || tvertex == false)
    {
        throw VertexNotFoundException();
    }
    if(findex == tindex)
    {
        return false;
    }
    bool is_edge = false;
    for(int m=0; m<(int)edgeList.size();m++)
    {
        if(edgeList[m].vertexId0 == findex)
        {
            if(edgeList[m].vertexId1 == tindex)
            {
                is_edge = true;
            }
        }
        if(edgeList[m].vertexId0 == tindex)
        {
            if(edgeList[m].vertexId1 == findex)
            {
                is_edge = true;
            }
        }
    }
    if(is_edge == true)
    {
        return false;
    }
    if(vertexList[findex].edgeCount+1 > MAX_EDGE_PER_VERTEX)
    {
        throw TooManyEdgeOnVertexExecption();
    }
    if(vertexList[tindex].edgeCount+1 > MAX_EDGE_PER_VERTEX)
    {
        throw TooManyEdgeOnVertexExecption();
    }
    vertexList[findex].edgeCount++;
    vertexList[findex].edgeIds[vertexList[findex].edgeCount-1] = (int)edgeList.size();
    vertexList[tindex].edgeCount++;
    vertexList[tindex].edgeIds[vertexList[tindex].edgeCount-1] = (int)edgeList.size();
    struct GraphEdge new_edge;
    new_edge.weight = weight;
    new_edge.vertexId0 = findex;
    new_edge.vertexId1 = tindex;
    new_edge.masked = false;
    edgeList.push_back(new_edge);    
    return true;
}

bool Graph::ShortestPath(std::vector<int>& orderedVertexIdList,
                         const std::string& from,
                         const std::string& to) const
{
    orderedVertexIdList.clear();
    bool is_findex = false;
    bool is_tindex = false;
    int findex = 0;
    int tindex = 0;
    for(int i=0; i<(int)vertexList.size();i++)
    {
        if(vertexList[i].name == from)
        {
            is_findex = true;
            findex = i;
        }
        if(vertexList[i].name == to)
        {
            is_tindex = true;
            tindex = i;
        }
    }
    if(is_findex == false || is_tindex == false)
    {
        throw VertexNotFoundException();
    }
    if(findex == tindex)
    {
        return false;
    }
    std::priority_queue<DistanceVertexIdPair> pq;
    std::vector<int> distances;
    distances.resize((int)vertexList.size());
    std::vector<int> previous;
    previous.resize((int)vertexList.size());
    for(int j=0; j<(int)vertexList.size(); j++)
    {
        distances[j] = LARGE_NUMBER;;
        previous[j] = INVALID_INDEX;
    }
    distances[findex] = 0;
    for(int k=0; k<(int)vertexList.size(); k++)
    {
        DistanceVertexIdPair new_vertex(k, LARGE_NUMBER);
        new_vertex.vId = k;
        new_vertex.currentWeight = LARGE_NUMBER;
        pq.push(new_vertex);   
    }
    pq.push(DistanceVertexIdPair(findex, 0));
    while(!pq.empty())
    {
        DistanceVertexIdPair vertex(0, 0);
        vertex = pq.top();
        pq.pop();
        for(int m=0; m<(int)edgeList.size(); m++)
        {
            int new_distance;
            if(edgeList[m].vertexId0 == vertex.vId && edgeList[m].masked == false)
            {
                new_distance = distances[vertex.vId] + edgeList[m].weight;
                if(new_distance < distances[edgeList[m].vertexId1])
                {
                    distances[edgeList[m].vertexId1] = new_distance;
                    previous[edgeList[m].vertexId1] = edgeList[m].vertexId0;
                    DistanceVertexIdPair new_vertexx(edgeList[m].vertexId1, new_distance);
                    pq.push(new_vertexx);
                }
            }
            if(edgeList[m].vertexId1 == vertex.vId && edgeList[m].masked == false)
            {
                new_distance = distances[vertex.vId] + edgeList[m].weight;
                if(new_distance < distances[edgeList[m].vertexId0])
                {
                    distances[edgeList[m].vertexId0] = new_distance;
                    previous[edgeList[m].vertexId0] = edgeList[m].vertexId1;
                    DistanceVertexIdPair new_vertexx(edgeList[m].vertexId0, new_distance);
                    pq.push(new_vertexx);
                }
            }
        }
    }
    int test = 1;
    orderedVertexIdList.push_back(tindex);
    while(test)
    {
        if(tindex == findex)
        {
            test = 0;
            break;
        }
        if(previous[tindex] == -1)
        {
            
            return false;
        }
        orderedVertexIdList.insert(orderedVertexIdList.begin(), 1, previous[tindex]);
        tindex = previous[tindex];
    }
    return true;
}

int Graph::MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,
                              const std::string& from,
                              const std::string& to,
                              int numberOfShortestPaths)
{
    UnMaskAllEdges();
    bool is_findex = false;
    bool is_tindex = false;
    for(int i=0; i<(int)vertexList.size();i++)
    {
        if(vertexList[i].name == from)
        {
            is_findex = true;
        }
        if(vertexList[i].name == to)
        {
            is_tindex = true;
        }
    }
    if(is_findex == false || is_tindex == false)
    {
        throw VertexNotFoundException();
    }
    std::vector<int> shortestpath;
    bool path;
    path = ShortestPath(shortestpath, from, to);
    if(path == false)
    {
        return 0;
    }
    orderedVertexIdList.push_back(shortestpath);
    int number_of_path = 1;
    for(int j=0; j<numberOfShortestPaths-1; j++)
    {
        int max_weight = 0;
        std::string maxv1 = "";
        std::string maxv2 = "";
        for(int k=0; k<(int)shortestpath.size()-1; k++)
        {
            int v1 = shortestpath[k];
            int v2 = shortestpath[k+1];
            for(int l=0; l<(int)edgeList.size();l++)
            {
                if(edgeList[l].vertexId0 == v1)
                {
                    if(edgeList[l].vertexId1 == v2)
                    {
                        if(edgeList[l].weight > max_weight)
                        {
                            maxv1 = vertexList[v1].name;
                            maxv2 = vertexList[v2].name;
                            max_weight = edgeList[l].weight;
                        }
                    }
                }
                if(edgeList[l].vertexId0 == v2)
                {
                    if(edgeList[l].vertexId1 == v1)
                    {
                        if(edgeList[l].weight > max_weight)
                        {
                            maxv1 = vertexList[v1].name;
                            maxv2 = vertexList[v2].name;
                            max_weight = edgeList[l].weight;
                        }
                    }
                }
            }
        }
        std::vector<StringPair> to_be_masked;
        StringPair mystring(maxv1, maxv2);
        to_be_masked.push_back(mystring);
        MaskEdges(to_be_masked);
        bool test = ShortestPath(shortestpath, from, to);
        if(test == false)
        {
            break;
        }
        number_of_path++;
        orderedVertexIdList.push_back(shortestpath);
    }
    UnMaskAllEdges();
    return number_of_path;
}

void Graph::MaskEdges(const std::vector<StringPair>& vertexNames)
{
    for(int i=0; i<(int)vertexNames.size(); i++)
    {
        std::string name1 = vertexNames[i].s0;
        std::string name2 = vertexNames[i].s1;
        bool name_1 = false;
        int name1_index = 0;
        int name2_index = 0;
        bool name_2 = false;
        for(int j=0; j<(int)vertexList.size();j++)
        {
            if(vertexList[j].name == name1)
            {
                name_1 = true;
                name1_index = j;
            }
            if(vertexList[j].name == name2)
            {
                name_2 = true;
                name2_index = j;
            }
        }
        if(name_1 == false || name_2 == false)
        {
            throw VertexNotFoundException();
        }
        if(name1_index == name2_index)
        {
            continue;
        }
        for(int k=0; k<(int)edgeList.size();k++)
        {
            if(edgeList[k].vertexId0 == name1_index)
            {
                if(edgeList[k].vertexId1 == name2_index)
                {
                    edgeList[k].masked = true;
                }
            }
            if(edgeList[k].vertexId0 == name2_index)
            {
                if(edgeList[k].vertexId1 == name1_index)
                {
                    edgeList[k].masked = true;
                }
            }
        }
    }
}

void Graph::UnMaskEdges(const std::vector<StringPair>& vertexNames)
{
    for(int i=0; i<(int)vertexNames.size(); i++)
    {
        std::string name1 = vertexNames[i].s0;
        std::string name2 = vertexNames[i].s1;
        bool name_1 = false;
        int name1_index = 0;
        int name2_index = 0;
        bool name_2 = false;
        for(int j=0; j<(int)vertexList.size();j++)
        {
            if(vertexList[j].name == name1)
            {
                name_1 = true;
                name1_index = j;
            }
            if(vertexList[j].name == name2)
            {
                name_2 = true;
                name2_index = j;
            }
        }
        if(name_1 == false || name_2 == false)
        {
            throw VertexNotFoundException();
        }
        if(name1_index == name2_index)
        {
            continue;
        }
        for(int k=0; k<(int)edgeList.size();k++)
        {
            if(edgeList[k].vertexId0 == name1_index)
            {
                if(edgeList[k].vertexId1 == name2_index)
                {
                    edgeList[k].masked = false;
                }
            }
            if(edgeList[k].vertexId0 == name2_index)
            {
                if(edgeList[k].vertexId1 == name1_index)
                {
                    edgeList[k].masked = false;
                }
            }
        }
    }
}

void Graph::UnMaskAllEdges()
{
    for(int i=0; i<(int)edgeList.size();i++)
    {
        edgeList[i].masked = false;
    }
}

void Graph::MaskVertexEdges(const std::string& name)
{
    bool is_vertex = false;
    int vertex_index = 0;
    for(int i=0; i<(int)vertexList.size();i++)
    {
        if(vertexList[i].name == name)
        {
            is_vertex = true;
            vertex_index = i;
        }
    }
    if(is_vertex == false)
    {
        throw VertexNotFoundException();
    }
    else{
        for(int j=0; j<(int)edgeList.size();j++)
        {
            if(edgeList[j].vertexId0 == vertex_index || edgeList[j].vertexId1 == vertex_index)
            {
                edgeList[j].masked = true;
            }
        }
    }
}

void Graph::UnMaskVertexEdges(const std::string& name)
{
    bool is_vertex = false;
    int vertex_index = 0;
    for(int i=0; i<(int)vertexList.size();i++)
    {
        if(vertexList[i].name == name)
        {
            is_vertex = true;
            vertex_index = i;
        }
    }
    if(is_vertex == false)
    {
        throw VertexNotFoundException();
    }
    else{
        for(int j=0; j<(int)edgeList.size();j++)
        {
            if(edgeList[j].vertexId0 == vertex_index || edgeList[j].vertexId1 == vertex_index)
            {
                edgeList[j].masked = false;
            }
        }
    }
}

void Graph::ModifyEdge(const std::string& vName0,
                       const std::string& vName1,
                       float newWeight)
{
    bool indx0 = false;
    bool indx1 = false;
    int vertex_index0 = 0;
    int vertex_index1 = 0;
    for(int i=0; i<(int)vertexList.size();i++)
    {
        if(vertexList[i].name == vName0)
        {
            indx0 = true;
            vertex_index0 = i;
        }
        if(vertexList[i].name == vName1)
        {
            indx1 = true;
            vertex_index1 = i;
        }
    }
    if(indx0 == false || indx1 == false)
    {
        throw VertexNotFoundException();
    }
    else
    {
        ModifyEdge(vertex_index0, vertex_index1, newWeight);
    }
    return;
}

void Graph::ModifyEdge(int vId0, int vId1,
                       float newWeight)
{
    int test=0;
    for(int i=0; i<(int)edgeList.size();i++)
    {
        if(edgeList[i].vertexId0 == vId0)
        {
            if(edgeList[i].vertexId1 == vId1)
            {
                test = 1;
            }
        }
        if(edgeList[i].vertexId0 == vId1)
        {
            if(edgeList[i].vertexId1 == vId0)
            {
                test = 1;
            }
        }
    }
    if(test == 0)
    {
        return;
    }
    else{
        for(int j=0; j<(int)edgeList.size();j++)
        {
            if(edgeList[j].vertexId0 == vId0)
            {
                if(edgeList[j].vertexId1 == vId1)
                {
                    edgeList[j].weight = (int)newWeight;
                }
            }
            if(edgeList[j].vertexId0 == vId1)
            {
                if(edgeList[j].vertexId1 == vId0)
                {
                    edgeList[j].weight = (int)newWeight;
                }
            }
        }
    }
}

void Graph::PrintAll() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    for(size_t i = 0; i < vertexList.size(); i++)
    {
        const GraphVertex& v = vertexList[i];
        std::cout << v.name << "\n";
        for(int j = 0; j < v.edgeCount; j++)
        {
            int edgeId = v.edgeIds[j];
            const GraphEdge& edge = edgeList[edgeId];
            // Skip printing this edge if it is masked
            if(edge.masked)
                continue;

            // List the all vertex names and weight
            std::cout << "-" << std::setfill('-')
                             << std::setw(2) << edge.weight
                             << "-> ";
            int neigVertexId = (static_cast<int>(i) == edge.vertexId0)
                                 ? edge.vertexId1
                                 : edge.vertexId0;
            std::cout << vertexList[neigVertexId].name << "\n";
        }
    }
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

void Graph::PrintPath(const std::vector<int>& orderedVertexIdList,
                      bool sameLine) const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this file !       //
    // ============================= //
    for(size_t i = 0; i < orderedVertexIdList.size(); i++)
    {
        int vertexId = orderedVertexIdList[i];
        if(vertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        const GraphVertex& vertex = vertexList[vertexId];
        std::cout << vertex.name;
        if(!sameLine) std::cout << "\n";
        // Only find and print the weight if next is available
        if(i == orderedVertexIdList.size() - 1) break;
        int nextVertexId = orderedVertexIdList[i + 1];
        if(nextVertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        // Find the edge between these two vertices
        int edgeId = INVALID_INDEX;
        if(vertexId     < static_cast<int>(vertexList.size()) &&
           nextVertexId < static_cast<int>(vertexList.size()))
        {
            // Check all of the edges of vertex
            // and try to find
            const GraphVertex& fromVert = vertexList[vertexId];
            for(int i = 0; i < fromVert.edgeCount; i++)
            {
                int eId = fromVert.edgeIds[i];
                // Since the graph is not directional
                // check the both ends
                if((edgeList[eId].vertexId0 == vertexId &&
                    edgeList[eId].vertexId1 == nextVertexId)
                ||
                   (edgeList[eId].vertexId0 == nextVertexId &&
                    edgeList[eId].vertexId1 == vertexId))
                {
                    edgeId = eId;
                    break;
                }
            }
        }
        if(edgeId != INVALID_INDEX)
        {
            const GraphEdge& edge = edgeList[edgeId];
            std::cout << "-" << std::setfill('-')
                      << std::setw(2)
                      << edge.weight << "->";
        }
        else
        {
            std::cout << "-##-> ";
        }
    }
    // Print endline on the last vertex if same line is set
    if(sameLine) std::cout << "\n";
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

int Graph::TotalVertexCount() const
{
    return (int)vertexList.size();
}

int Graph::TotalEdgeCount() const
{
    return (int)edgeList.size();
}

std::string Graph::VertexName(int vertexId) const
{
    std::string result = "";
    if(vertexId < (int)vertexList.size())
    {
        result = vertexList[vertexId].name;
    }
    return result;
}

int Graph::TotalWeightInBetween(std::vector<int>& orderedVertexIdList)
{
    int total_weight = 0;
    int test;
    for(int i=0; i<(int)orderedVertexIdList.size()-1; i++)
    {
        int j = i+1;
        test = 0;
        for(int k=0; k<(int)edgeList.size();k++)
        {
            if(edgeList[k].vertexId0 == orderedVertexIdList[i])
            {
                if(edgeList[k].vertexId1 == orderedVertexIdList[j])
                {
                    test = 1;
                    total_weight = total_weight + edgeList[k].weight;
                }
            }
            if(edgeList[k].vertexId0 == orderedVertexIdList[j])
            {
                if(edgeList[k].vertexId1 == orderedVertexIdList[i])
                {
                    test = 1;
                    total_weight = total_weight + edgeList[k].weight;
                }
            }
        }
        if(test == 0)
        {
            return -1;
        }
    }
    return total_weight;
}