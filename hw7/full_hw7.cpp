#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <climits>
#include <functional>

// Task1. Поиск компонент связности

void dfs1(std::unordered_map<int, std::vector<int>>& graph,
         int v,
         std::unordered_map<int, bool>& visited,
         std::vector<int>& component)
{
    visited[v] = true;
    component.push_back(v);
    
    std::vector<int> it = graph[v];
    for (int i : it) {
        if (!visited[i])
            dfs1(graph, i, visited, component);
    }
}

std::vector<std::vector<int>> 
    find_connected_components1(std::unordered_map<int, std::vector<int>>& graph)
{
    std::unordered_map<int, bool> visited;
    for (auto pair : graph)
        visited[pair.first] = false;
    
    std::vector<std::vector<int>> connected_components;
    
    for (auto& pair : visited) {
        int node = pair.first;
        if (!visited[node]) {
            std::vector<int> component;
            dfs1(graph, node, visited, component);
            connected_components.push_back(component);
        }
    }
    
    return connected_components;
}


// Task2. Поиск компонент связности: Раскраска графа

void dfs2(std::unordered_map<int, std::vector<int>>& graph,
         int v,
         std::unordered_map<int, int>& visited,
         int color)
{
    visited[v] = color;
    
    std::vector<int> it = graph[v];
    for (int i : it) {
        if (!visited[i])
            dfs2(graph, i, visited, color);
    }
}

std::unordered_map<int, int>
    find_connected_components2(std::unordered_map<int, std::vector<int>>& graph)
{
    std::unordered_map<int, int> visited;
    for (auto pair : graph)
        visited[pair.first] = 0;
    
    int color = 0;
    
    for (auto pair : graph) {
        int node = pair.first;
        if (!visited[node]) {
            color++;
            dfs2(graph, node, visited, color);
        }
    }
    
    return visited;
}


// Task3. Поиск цикла в графе

bool dfs3(std::unordered_map<int, std::vector<int>>& graph,
         int vertex, int parent,
         std::unordered_set<int>& visited)
{
    visited.insert(vertex);
    auto graph_it = graph.find(vertex);

    for (int neighbor : graph_it->second) {
        if (neighbor == parent)
            continue;
        
        if (visited.find(neighbor) != visited.end())
            return true;
        
        if (dfs3(graph, neighbor, vertex, visited))
            return true;
    }
    
    return false;
}

bool has_cycle(std::unordered_map<int, std::vector<int>>& graph)
{
    std::unordered_set<int> visited;
    
    for (auto& pair : graph) {
        int node = pair.first;
        
        if (visited.find(node) == visited.end()) {
            if (dfs3(graph, node, -1, visited))
                return true;
        }
    }
    
    return false;
}


// Task4. Является ли граф деревом

bool isTree(std::unordered_map<int, std::vector<int>>& graph, int start)
{
    std::unordered_set<int> visited;
    std::queue<int> q;
    q.push(start);
    
    std::unordered_map<int, int> parent;
    parent[start] = -1;
    
    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        
        visited.insert(vertex);
        
        for (int neighbor : graph[vertex]) {
            if (visited.find(neighbor) == visited.end()) {
                q.push(neighbor);
                parent[neighbor] = vertex;
            } else {
                if (parent[vertex] != neighbor) 
                    return false;
            }
        }
    }
    
    return visited.size() == graph.size();
}


// Task5. Алгоритм Дейкстры

std::unordered_map<int, int> dijkstra(
        std::unordered_map<int, std::unordered_map<int, int>>& graph, 
        int start) 
{
    std::unordered_map<int, int> distances;
    for (auto pair : graph)
        distances[pair.first] = INT_MAX;
    distances[start] = 0;
    
    using Pair = std::pair<int, int>;
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;
    pq.emplace(0, start);
    
    while (!pq.empty()) {
        auto pair = pq.top();
        pq.pop();
        
        if (pair.first > distances[pair.second])
            continue;

        for (auto [neighbor, weight] : graph[pair.second]) {
            int distance = pair.first + weight;
            
            if (distance < distances[neighbor]) {
                distances[neighbor] = distance;
                pq.emplace(distance, neighbor);
            }
        }
    }
    
    return distances;
}


// Task6. Проверка на двудольность BFS

bool isBipartite_bfs(std::unordered_map<int, std::vector<int>>& graph) 
{
    int n = graph.size();
    std::vector<int> colors(n, 0);
    
    auto bfs = [&](int start) 
    {
        std::queue<int> q;
        q.push(start);
        colors[start] = 1;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (int neighbor : graph[node]) {
                if (colors[neighbor] == 0) { 
                    colors[neighbor] = -colors[node];
                    q.push(neighbor);
                } else {
                    if (colors[neighbor] == colors[node]) 
                        return false;
                }
            }
        }
        return true;
    };
    
    for (int i = 0; i < n; i++) {
        if (colors[i] == 0) { 
            if (!bfs(i))
                return false;
        }
    }
    
    return true;
}

// Task7. Проверка на двудольность DFS

bool isBipartite_dfs(std::unordered_map<int, std::vector<int>>& graph) 
{
    int n = graph.size();
    std::unordered_map<int, int> colors;
    
    std::function<bool(int, int)> dfs = [&](int node, int c) 
    {
        colors[node] = c;
        
        for (int neighbor : graph[node]) {
            if  (colors.find(neighbor) == colors.end()) { 
                if (!dfs(neighbor, -c))
                    return false;
            } else {
                if (colors[neighbor] == colors[node])
                    return false;
            }
        }
        return true;
    };
    
    for (auto pair : graph) {
        if (colors.find(pair.first) == colors.end()) { 
            if (!dfs(pair.first, 1))
                return false;
        }
    }
    
    return true;
}


int main()
{
    std::unordered_map<int, std::vector<int>> graph = {
        {1, {2, 3}},
        {2, {1, 3}},
        {3, {1, 2}},
        {4, {6, 7}},
        {5, {6, 7}},
        {6, {4, 5, 7}},
        {7, {4, 5, 6}},
        {8, {11}},
        {9, {10, 11}},
        {10, {9}},
        {11, {8, 9}}
    };
    
    std::vector<std::vector<int>> con_comps1 = find_connected_components1(graph);
    for (size_t i = 0; i < con_comps1.size(); ++i) {
        std::cout << "";
        for (size_t j = 0; j < con_comps1[i].size(); ++j)
            std::cout << con_comps1[i][j] << " ";
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
    
    std::unordered_map<int, int> con_comps2 = find_connected_components2(graph);
    for (auto pair : con_comps2)
        std::cout << "v" << pair.first << " -> c" << pair.second << std::endl;
        
    std::cout << std::endl;
    
    std::cout << has_cycle(graph) << std::endl;
    std::cout << isTree(graph, 1) << std::endl;
    
    std::cout << std::endl;
    
    std::unordered_map<int, std::unordered_map<int, int>> graph1 = {
        {1, {{2, 7}, {3, 9}, {6, 14}}},
        {2, {{1, 7}, {3, 10}, {4, 15}}},
        {3, {{1, 9}, {2, 10}, {4, 11}, {6, 2}}},
        {4, {{2, 15}, {3, 11}, {5, 6}}},
        {5, {{4, 6}, {6, 9}}},
        {6, {{1, 14}, {3, 2}, {5, 9}}}
    };
    
    std::unordered_map<int, int> distances = dijkstra(graph1, 1);
    for (auto pair : distances)
        std::cout << "v" << pair.first << " : " << pair.second << std::endl;
        
    std::cout << std::endl;
     
    std::cout << isBipartite_bfs(graph) << std::endl;
    std::cout << isBipartite_dfs(graph) << std::endl;
    
    return 0;
}