#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/graph/isomorphism.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/fstream.hpp>
#include <string>
#include "minimum_spanning_tree.hpp"

using namespace minimum_spanning_tree;

BOOST_AUTO_TEST_CASE(test_1){
    BOOST_REQUIRE_EQUAL(1, 1);
}

BOOST_AUTO_TEST_CASE(construct_path){
    boost::filesystem::path path {"./test_files/gnp_n4_p90_wt.graph"};
    BOOST_REQUIRE_EQUAL(path.is_absolute(), false);
    BOOST_REQUIRE_EQUAL(path.is_relative(), true);    
}

BOOST_AUTO_TEST_CASE(read_file){
    boost::filesystem::path path {"./minimum_spanning_tree_test.cpp"};
    boost::filesystem::ifstream ifs {path};
    std::string top_line;
    std::getline(ifs, top_line);
    BOOST_REQUIRE_EQUAL(top_line, "#define BOOST_TEST_MAIN");
}

BOOST_AUTO_TEST_CASE(read_adj_list_polymorphs){
    std::string path_string = {"./test_files/gnp_n4_p90_wt.graph"};
    boost::filesystem::path path = {path_string};
    auto G1 = input::read_edge_list(path_string);
    auto G2 = input::read_edge_list(path);
    BOOST_REQUIRE(boost::isomorphism(G1, G2));
}

BOOST_AUTO_TEST_CASE(num_nodes_edges_test){
    boost::filesystem::path path = {"./test_files/gnp_n4_p90_wt.graph"};
    boost::filesystem::ifstream ifs{path};
    auto nodes_edges = input::num_nodes_and_edges(ifs);
    auto expected = std::make_pair(4, 5);
    BOOST_REQUIRE_EQUAL(nodes_edges.first, expected.first);
    BOOST_REQUIRE_EQUAL(nodes_edges.second, expected.second);    
}

BOOST_AUTO_TEST_CASE(missing_file){
    std::string path_string = {"./test_files/gnp_n4_p90.graph"};
    BOOST_REQUIRE_THROW(input::read_edge_list(path_string),
			file_not_found);
}

BOOST_AUTO_TEST_CASE(invalid_format1){
    std::string path_string = {"./test_files/malformed_file1.graph"};
    BOOST_REQUIRE_THROW(input::read_edge_list(path_string),
			bad_file_format);
}

BOOST_AUTO_TEST_CASE(invalid_format2){
    std::string path_string = {"./test_files/malformed_file2.graph"};
    BOOST_REQUIRE_THROW(input::read_edge_list(path_string),
			bad_file_format);
}

BOOST_AUTO_TEST_CASE(invalid_format3){
    std::string path_string = {"./test_files/malformed_file3.graph"};
    BOOST_REQUIRE_THROW(input::read_edge_list(path_string),
			bad_file_format);
}

BOOST_AUTO_TEST_CASE(read_edge_list_test){
    Graph G_test{4};
    boost::add_edge(0, 1, -1.1, G_test);
    boost::add_edge(0, 2, -1.5, G_test);
    boost::add_edge(0, 3, 0.32, G_test);
    boost::add_edge(1, 3, 1.5, G_test);
    boost::add_edge(2, 3, -0.98, G_test);    

    std::string path_string = {"./test_files/gnp_n4_p90_wt.graph"};
    auto G_read = input::read_edge_list(path_string);

    int count = 0;
    for(auto vp = boost::vertices(G_read); vp.first != vp.second; vp.first++)
	count++;

    BOOST_REQUIRE(count == 4);
    BOOST_REQUIRE(boost::isomorphism(G_test, G_read));
}

BOOST_AUTO_TEST_CASE(simple_mst){
    Graph G{4};
    boost::add_edge(0, 1, -1.1, G);
    boost::add_edge(0, 2, -1.5, G);
    boost::add_edge(0, 3, 0.32, G);
    boost::add_edge(1, 3, 1.5, G);
    boost::add_edge(2, 3, -0.98, G);    
    auto val = mst_value(G);
    BOOST_REQUIRE_CLOSE(val, -1.1 - 1.5 - 0.98, 0.0001);
}
