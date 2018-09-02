#include "minimum_spanning_tree.hpp"
#include <unordered_map>
#include <boost/filesystem/fstream.hpp>
#include <boost/tokenizer.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/edge_list.hpp>
#include <utility>  // std::pair
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <vector>

using namespace minimum_spanning_tree;

Graph minimum_spanning_tree::input::read_edge_list(
    const boost::filesystem::path& path){

    boost::filesystem::ifstream ifs{path};
    if(!boost::filesystem::exists(path))
	throw file_not_found{"Given path does not exist"};

    auto nodes_edges = input::num_nodes_and_edges(ifs);
    Graph G = {nodes_edges.first};

    for(std::string line; std::getline(ifs, line);){
	input::add_edge_from_string(line, G);
    }
    return G;
}

void minimum_spanning_tree::input::add_edge_from_string(
        const std::string& line,
	Graph& G){

    boost::tokenizer< boost::char_separator<char> > string_splitter = {
	line, boost::char_separator<char> {" "}};
    
    auto get_edge_params = [string_splitter](){
	std::vector<std::string> line_vec = {string_splitter.begin(),
					     string_splitter.end()};
	if(line_vec.size() != 2 and line_vec.size() != 3)
	    throw bad_file_format(
		"edge lines must have 2 or 3 space separated values.");
	auto line_it = line_vec.begin();
	
	auto u = std::stoi(*line_it++);
	auto v = std::stoi(*line_it++);
	auto w = 0.0;
	if(line_it != line_vec.end())
	    w = std::stof(*line_it++);

	return std::make_tuple(u, v, w);
    };

    auto u_v_w = get_edge_params();
    boost::add_edge(std::get<0>(u_v_w),
		    std::get<1>(u_v_w),
		    std::get<2>(u_v_w),
		    G);
}

std::pair<unsigned long,
	  unsigned long> minimum_spanning_tree::input::num_nodes_and_edges(
        boost::filesystem::ifstream &ifs){
    std::string line;
    std::getline(ifs, line);

    boost::tokenizer<> string_splitter = {line};

    std::vector<std::string> line_vec = {string_splitter.begin(),
					 string_splitter.end()};
    if(line_vec.size() != 2)
	throw bad_file_format{
    	    "Line must contain only 2 space separated ints."};
    auto line_it = line_vec.begin();

    auto num_nodes = std::stoul(*line_it++);
    auto num_edges = std::stoul(*line_it++);
    auto ret = std::make_pair(num_nodes, num_edges);
    return ret;
}

Graph minimum_spanning_tree::input::read_edge_list(const std::string& path){
    boost::filesystem::path p = {path};
    return read_edge_list(p);
}

float minimum_spanning_tree::mst_value(const std::string path){
    const auto G = input::read_edge_list(path);
    return mst_value(G);
}

float minimum_spanning_tree::mst_value(const Graph& G){
    std::vector<Edge> spanning_tree;
    boost::kruskal_minimum_spanning_tree(G, std::back_inserter(spanning_tree));
    const boost::property_map<
	Graph, boost::edge_weight_t>::const_type edge_weight_map =
	boost::get(boost::edge_weight, G);

    float value = 0.0;
    for(auto e: spanning_tree){
	value += edge_weight_map[e];
    }
    return value;
}
