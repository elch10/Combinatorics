#include "Graph.h"
#include <algorithm>
#include <iterator>
#include <iomanip>

using namespace std;

bool operator< (const Edge &lhs, const Edge &rhs)
{
  return lhs.weight < rhs.weight;
}

istream &operator>> (istream &istream, Edge &edge)
{
  istream >> edge.from >> edge.to >> edge.weight;
  return istream;
}


istream &operator>> (istream &istream, OrientedMultiGraph &multiGraph)
{
  vector<Edge> edges;
  copy(istream_iterator<Edge>(istream), istream_iterator<Edge>(), back_inserter(edges));

  vector<OrderedEdge> orderedEdges(edges.size());
  for (size_t i = 0; i < edges.size(); ++i) {
    orderedEdges[i] = OrderedEdge(edges[i], i+1);
  }

  multiGraph = OrientedMultiGraph(orderedEdges);
  return istream;
}

std::ostream &operator<< (std::ostream &ostream, const OrientedMultiGraph &multiGraph)
{
  const int wordWide = 3;

  ostream << "Amount of vertex = " << multiGraph.amountOfVertexs_ 
          << " and amount of edges = " << multiGraph.amountOfEdges_ << endl;
  ostream << "\tArcs | Chords\nVertexs\n" << string(wordWide+1, ' ');
  for (size_t i = 0; i < multiGraph.arcs_.size(); ++i) {
    ostream << setw(wordWide) << multiGraph.arcs_[i].orderNumber;
    if (i != multiGraph.arcs_.size() - 1) {
      ostream << ' ';
    }
  }
  ostream << '|';

  for (size_t i = 0; i < multiGraph.chords_.size(); ++i) {
    ostream << setw(wordWide) << multiGraph.chords_[i].orderNumber << ' ';
  }

  for (size_t i = 0; i < multiGraph.incedenceMatrix_.size(); ++i) {
    ostream << setw(wordWide) << i << ' ';
    for (size_t j = 0; j < multiGraph.incedenceMatrix_[i].size(); ++j) {
      ostream << setw(wordWide) << multiGraph.incedenceMatrix_[i][j] << ' ';
    }
    ostream << endl;
  }

  return ostream;
}

OrderedEdge::OrderedEdge(const Edge &edge, size_t number)
{
  from = edge.from;
  to = edge.to;
  weight = edge.weight;
  orderNumber = number;
}

OrderedEdge::OrderedEdge()
{
  from = to = weight = orderNumber = 0;
}

OrientedMultiGraph::OrientedMultiGraph()
{}

OrientedMultiGraph::OrientedMultiGraph(vector<OrderedEdge> &edges)
{
  amountOfEdges_ = edges.size();
  findAmountOfVertex(edges);
  kruskalAlgorithm(edges);
  buildIncedenceMatrix(edges);
}

void OrientedMultiGraph::kruskalAlgorithm(vector<OrderedEdge> &edges)
{
  sort(edges.begin(), edges.end());

  vector<int> treeId(amountOfVertexs_);
  for (size_t i = 0; i < treeId.size(); ++i) {
    treeId[i] = i;
  }

  for (size_t i = 0; i < edges.size(); ++i) {
    const OrderedEdge &edge = edges[i];

    if (treeId[edge.from] != treeId[edge.to]) {
      ostovCost_ += edge.weight;
      arcs_.push_back(edge);

      int oldId = treeId[edge.to], newId = treeId[edge.from];
      for (int j = 0; j < treeId.size(); ++j) {
        if (treeId[j] == oldId) {
          treeId[j] = newId;
        }
      }
    } else {
      chords_.push_back(edge);
    }
  }
}

void OrientedMultiGraph::buildIncedenceMatrix(const vector<OrderedEdge> &edges)
{
  incedenceMatrix_ = vector< vector<EdgeNodeRelationship> >(amountOfVertexs_, 
                                                            vector<EdgeNodeRelationship>(amountOfEdges_));

  for (size_t i = 0; i < arcs_.size(); ++i) {
    incedenceMatrix_[arcs_[i].from][i] = EDGE_COMING_OUT;
    incedenceMatrix_[arcs_[i].to][i] = EDGE_COMING_IN;
  }

  for (size_t i = 0; i < chords_.size(); ++i) {
    incedenceMatrix_[chords_[i].from][arcs_.size() + i] = EDGE_COMING_OUT;
    incedenceMatrix_[chords_[i].to][arcs_.size() + i] = EDGE_COMING_IN;
  }
}

void OrientedMultiGraph::findAmountOfVertex(vector<OrderedEdge> &edges)
{
  int mx = 0;
  for (int i = 0; i < edges.size(); ++i) {
    mx = max(mx, max(edges[i].from, edges[i].to));
  }
  amountOfVertexs_ = mx+1;
}


int OrientedMultiGraph::getCost() const
{
  return ostovCost_;
}

const vector<OrderedEdge> &OrientedMultiGraph::getArcs() const
{
  return arcs_;
}

const vector<OrderedEdge> &OrientedMultiGraph::getChords() const
{
  return chords_;
}

size_t OrientedMultiGraph::getAmountOfVertexs() const
{
  return amountOfVertexs_;
}

size_t OrientedMultiGraph::getAmountOfEdges() const
{
  return amountOfEdges_;
}
