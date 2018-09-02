#ifndef __minimum_spanning_tree_hpp__
#define __minimum_spanning_tree_hpp__

#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/filesystem.hpp>

namespace minimum_spanning_tree{
    class bad_file_format: public std::logic_error{
	using std::logic_error::logic_error;
    };

    class file_not_found: public std::logic_error{
	using std::logic_error::logic_error;
    };

    typedef boost::vecS edge_storage_t;
    typedef boost::vecS node_storage_t;
    typedef float edge_weight_t;;
    typedef boost::property<boost::vertex_index_t, int> vertex_t;
    typedef boost::property<boost::edge_weight_t, edge_weight_t> edge_t;
    typedef boost::adjacency_list<edge_storage_t, node_storage_t,
				  boost::bidirectionalS,
				  vertex_t, edge_t> Graph;

    typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
    typedef boost::graph_traits<Graph>::edge_descriptor Edge;

    namespace input{
	void add_edge_from_string(const std::string& line,
				  Graph& G);
	
	std::pair<unsigned long, unsigned long> num_nodes_and_edges(
	    boost::filesystem::ifstream& ifs);

	Graph read_edge_list(const std::string& path);
	Graph read_edge_list(const boost::filesystem::path& path);
    }

    float mst_value(const std::string path);
    float mst_value(const Graph& G);
}

#endif
