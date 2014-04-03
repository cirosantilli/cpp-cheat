#include <iostream>
#include <fstream>

#include <boost/config.hpp>
//-lboost_graph
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>

int main(int, char *[]) {
    // #dijikstra
    {
        typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int>> graph_t;
        typedef boost::graph_traits<graph_t>::vertex_descriptor vertex_descriptor;
        typedef boost::graph_traits<graph_t>::edge_descriptor edge_descriptor;
        typedef std::pair<int, int> Edge;

        // Model inputs.
        const int num_nodes = 5;
        Edge edge_array[] = {
            {0, 2}, {1, 1}, {1, 3}, {1, 4}, {2, 1},
            {2, 3}, {3, 4}, {4, 0}, {4, 1}
        };
        int weights[] = {
            1, 2, 1, 2, 7,
            3, 1, 1, 1
        };

        // Solve
        int num_arcs = sizeof(edge_array) / sizeof(Edge);
        graph_t g(edge_array, edge_array + num_arcs, weights, num_nodes);
        std::vector<vertex_descriptor> p(num_vertices(g));
        std::vector<int> d(num_vertices(g));
        vertex_descriptor s = vertex(0, g);
        dijkstra_shortest_paths(g, s,
            predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, g))).
            distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, g))));

        // Print solution to stdout.
        std::cout <<"distances and parents:" <<std::endl;
        boost::graph_traits<graph_t>::vertex_iterator vi, vend;
        for (boost::tie(vi, vend) = vertices(g); vi != vend; ++vi) {
            std::cout << "distance(" << *vi << ") = " << d[*vi] << ", "
                      << "wparent("  << *vi << ") = " << p[*vi] << std::endl;
        }
        std::cout <<std::endl;

        // Generate a .dot graph file with shortest path highlighted.
        // To png with: dot -Tpng -o outfile.png input.dot
        boost::property_map<graph_t, boost::edge_weight_t>::type weightmap = get(boost::edge_weight, g);
        std::ofstream dot_file("dijkstra.dot");
        dot_file << "digraph D {\n"      << "  rankdir=LR\n"           << "  size=\"4,3\"\n"
                 << "  ratio=\"fill\"\n" << "  edge[style=\"bold\"]\n" << "  node[shape=\"circle\"]\n";
        boost::graph_traits <graph_t>::edge_iterator ei, ei_end;
        for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
            edge_descriptor e = *ei;
            boost::graph_traits<graph_t>::vertex_descriptor
                u = source(e, g), v = target(e, g);
            dot_file << u << " -> " << v << "[label=\"" << get(weightmap, e) << "\"";
            if (p[v] == u)
                dot_file << ", color=\"black\"";
            else
                dot_file << ", color=\"grey\"";
            dot_file << "]";
        }
        dot_file << "}";
    }
}
