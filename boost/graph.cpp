/**
Good tutorial: http://www.informit.com/articles/article.aspx?p=673259
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

#include <boost/config.hpp>
//-lboost_graph
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>

int main() {

    /*
    #Graph

        The following class hierarchy exists:

            BidirectionalGraph -------- Incience ---------+
                                                          |
                                        Adjacency --------+
                                                          |
            VertexAndEdgeList ----+---- VertexList -------+---- Graph
                                  |                       |
                                  +---- EdgeList ---------+
                                                          |
                                        AdjacenyMatrix ---+
    */
    {
        /*
        #properties

            Properties are values associated to edges and vertices.
        */
        {
            /*
            There are a few predefined properties which you should use whenever possible
            as they are already used in many algorithms, but you can also define your own properties.

            Predefined properties include:

            - `edge_weight_t`. Used for most algorithms that have a single value associated to each
                edge such as Dijikstra.

            - `vertex_name_t`
            */
            {
                typedef boost::property<boost::vertex_name_t, std::string> VertexProperties;
                typedef boost::property<boost::edge_weight_t, int> EdgeProperties;
            }

            /*
            Multiple properties can be specified either by:

            - using a custom class as the property type. TODO is there any limitation to this?
            - chaining multile properties
            */
            {
            }

            /*
            The absense of a property is speficied by boost::no_property.
            */
            {
                typedef boost::no_property VertexProperties;
            }

        }

        typedef boost::property<boost::vertex_name_t, std::string> VertexProperties;
        typedef boost::property<boost::edge_weight_t, int> EdgeProperties;
        typedef boost::adjacency_list<
            // Data structure to represent the out edges for each vertex.
            // Possibilities:
            //
            // #vecS selects std::vector.
            // #listS selects std::list.
            // #slistS selects std::slist.
            // #setS selects std::set.
            // #multisetS selects std::multiset.
            // #hash_setS selects std::hash_set.
            //
            // `S` standas for Selector.
            boost::vecS,

            // Data structure to represent the vertex set.
            boost::vecS,

            // Directed type.
            // #bidirectionalS: directed graph with access to in and out edges
            // #directedS:      directed graph with access only to out-edges
            // #undirectedS:    undirected graph
            boost::bidirectionalS,

            // Optional.
            VertexProperties,

            // Optional.
            EdgeProperties
        > Graph;
        //typedef boost::graph_traits<Graph>::vertex_iterator VertexIter;
        //typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
        //typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

        // Fix number of vertices, and add one edge at a time.
        int num_vertices = 3;
        Graph g(num_vertices);
        boost::add_edge(0, 1, g);
        boost::add_edge(1, 2, g);

        // Fix number of vertices, and add one edge array.
        {
            int num_vertices = 3;
            typedef std::pair<int, int> Edge;
            std::vector<Edge> edges{
                {0, 1},
                {1, 2},
            };
            Graph g(edges.data(), edges.data() + edges.size(), num_vertices);
        }

        // It is also possible to add vertices with #add_vertex.

        //#vertices
        {
            // Number of vertices.
            boost::graph_traits<Graph>::vertices_size_type num_vertices = boost::num_vertices(g);
            assert(num_vertices == 3u);

            //#vertices() Returns a begin() end() vertex iterator pair so we know where to stop.
            {
                typedef std::vector<boost::graph_traits<Graph>::vertex_descriptor> Vertices;
                Vertices vertices;
                vertices.reserve(num_vertices);
                //IndexMap
                auto index = boost::get(boost::vertex_index, g);
                //std::pair<vertex_iter, vertex_iter> vp
                for (auto vp = boost::vertices(g); vp.first != vp.second; ++vp.first) {
                    // Vertex
                    auto v = *vp.first;
                    vertices.push_back(index[v]);
                }
                assert((vertices == Vertices{0, 1, 2}));
            }

            // The iterator is a ranom access iterator.
            {
                auto index = boost::get(boost::vertex_index, g);
                auto it = boost::vertices(g).first;
                assert(index[it[2]] == 2);
                assert(index[it[1]] == 1);
            }
        }

        //#edges
        {
            // It seems that only AdjencyMatrix has a method to get an edge given two vertices:
            //edge(u, v, g)
        }
    }

    //#source is also a global function: <http://stackoverflow.com/questions/16114616/why-is-boost-graph-librarys-source-a-global-function>

    //#dijikstra
    std::cout << "#dijkstra" << std::endl;
    {
        typedef boost::adjacency_list<
            boost::listS,
            boost::vecS,
            boost::directedS,
            boost::no_property,
            boost::property<boost::edge_weight_t, int>
        > Graph;
        typedef boost::graph_traits<Graph>::vertex_descriptor vertex_descriptor;
        typedef boost::graph_traits<Graph>::edge_descriptor edge_descriptor;
        typedef std::pair<int, int> Edge;

        // Model inputs.
        const int num_nodes = 5;
        const int sorce = 0;
        std::vector<Edge> edges{
            {0, 2}, {1, 1}, {1, 3}, {1, 4}, {2, 1},
            {2, 3}, {3, 4}, {4, 0}, {4, 1}
        };
        std::vector<int> weights{
            1, 2, 1, 2, 7,
            3, 1, 1, 1
        };

        // Solve.
        Graph g(edges.data(), edges.data() + edges.size(), weights.data(), num_nodes);
        std::vector<vertex_descriptor> p(num_vertices(g));
        std::vector<int> d(num_vertices(g));
        vertex_descriptor s = vertex(sorce, g);
        dijkstra_shortest_paths(g, s,
            predecessor_map(boost::make_iterator_property_map(
                p.begin(),
                boost::get(boost::vertex_index, g)
            )).distance_map(boost::make_iterator_property_map(
                d.begin(),
                boost::get(boost::vertex_index, g)
            ))
        );

        // Print solution to stdout.
        std::cout << "node | distance from source | parent" << std::endl;
        boost::graph_traits<Graph>::vertex_iterator vi, vend;
        for (boost::tie(vi, vend) = vertices(g); vi != vend; ++vi)
            std::cout << *vi << " " << d[*vi] << " " << p[*vi] << std::endl;
        std::cout <<std::endl;

        // Generate a .dot graph file with shortest path highlighted.
        // To PNG with: dot -Tpng -o outfile.png input.dot
        boost::property_map<Graph, boost::edge_weight_t>::type weightmap = boost::get(boost::edge_weight, g);
        std::ofstream dot_file("dijkstra.dot");
        dot_file << "digraph D {\n"      << "  rankdir=LR\n"           << "  size=\"4,3\"\n"
                 << "  ratio=\"fill\"\n" << "  edge[style=\"bold\"]\n" << "  node[shape=\"circle\"]\n";
        boost::graph_traits <Graph>::edge_iterator ei, ei_end;
        for (std::tie(ei, ei_end) = boost::edges(g); ei != ei_end; ++ei) {
            edge_descriptor e = *ei;
            boost::graph_traits<Graph>::vertex_descriptor
                u = boost::source(e, g), v = boost::target(e, g);
            dot_file << u << " -> " << v << "[label=\"" << boost::get(weightmap, e) << "\"";
            if (p[v] == u)
                dot_file << ", color=\"black\"";
            else
                dot_file << ", color=\"grey\"";
            dot_file << "]";
        }
        dot_file << "}";

        // Construct forward path to a destination.
        int dest = 4;
        int cur = dest;
        std::vector<int> path;
        path.push_back(cur);
        while(cur != sorce) {
            cur = p[cur];
            path.push_back(cur);
        }
        std::reverse(path.begin(), path.end());
        // Print.
        std::cout << "Path to node " << std::to_string(dest) << ":" << std::endl;
        for(auto& node : path) {
            std::cout << node << std::endl;
        }
    }
}
