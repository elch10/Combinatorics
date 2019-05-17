#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <iostream>

struct Edge {
  int from, to, weight;
};

struct OrderedEdge : public Edge {
  size_t orderNumber;

  OrderedEdge();
  OrderedEdge(const Edge &edge, size_t number);
};

enum EdgeNodeRelationship {
  EDGE_COMING_IN = -1,
  HAVE_NOT_EDGE = 0,
  EDGE_COMING_OUT = 1
};

bool operator< (const Edge &lhs, const Edge &rhs);
std::istream &operator>> (std::istream &istream, Edge &Edge);


class OrientedMultiGraph
{
public:
  OrientedMultiGraph();
  OrientedMultiGraph(std::vector<OrderedEdge> &edges);
  
  int getCost() const;
  const std::vector<OrderedEdge> &getArcs() const;
  const std::vector<OrderedEdge> &getChords() const;
  size_t getAmountOfVertexs() const;
  size_t getAmountOfEdges() const;

private:
  std::vector<OrderedEdge> arcs_, chords_;
  int ostovCost_;
  size_t amountOfVertexs_, amountOfEdges_;

  std::vector< std::vector<EdgeNodeRelationship> > incedenceMatrix_;

  void kruskalAlgorithm(std::vector<OrderedEdge> &edges);
  void findAmountOfVertex(std::vector<OrderedEdge> &edges);
  void buildIncedenceMatrix(const std::vector<OrderedEdge> &edges);


  friend std::istream &operator>> (std::istream &istream, OrientedMultiGraph &multiGraph);
  friend std::ostream &operator<< (std::ostream &ostream, const OrientedMultiGraph &multiGraph);
};

std::istream &operator>> (std::istream &istream, OrientedMultiGraph &multiGraph);
std::ostream &operator<< (std::ostream &ostream, const OrientedMultiGraph &multiGraph);

#endif //GRAPH_H
