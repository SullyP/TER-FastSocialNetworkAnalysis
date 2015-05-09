// File: graph_binary.h
// -- graph handling header file
//-----------------------------------------------------------------------------
// Community detection 
// Based on the article "Fast unfolding of community hierarchies in large networks"
// Copyright (C) 2008 V. Blondel, J.-L. Guillaume, R. Lambiotte, E. Lefebvre
//
// This program must not be distributed without agreement of the above mentionned authors.
//-----------------------------------------------------------------------------
// Author   : E. Lefebvre, adapted by J.-L. Guillaume
// Email    : jean-loup.guillaume@lip6.fr
// Location : Paris, France
// Time	    : February 2008
//-----------------------------------------------------------------------------
// see readme.txt for more details

#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

#define WEIGHTED   0
#define UNWEIGHTED 1
#define EMPTY -1 

using namespace std;

class Graph {
 public:
  unsigned int nb_nodes;
  unsigned long nb_links_out;
  unsigned long nb_links_in;
  double total_weight, total_weight_out, total_weight_in;  

  vector<unsigned long> degrees_out;
  vector<unsigned long> degrees_in;
  vector<unsigned int> links;
  vector<unsigned int> links_in;
  vector<float> weights;
  
  vector<unsigned int> correspondance;

  /* Correspondance noeud communaute */
  //Vecteur de noeuds pour chaque communautés
  vector<vector<int> > communities;
  //Communauté a laquelle appartient le noeud i
  vector<unsigned int> map_communities;
  //Pour accélérer le calcul des mesures de guimera
  vector<float> avg_com_out;
vector<float> std_com_out;
vector<float> avg_com_in;
vector<float> std_com_in;
vector<unsigned int> degree_in_com;
vector<unsigned int> degree_out_com;

  Graph();

  struct setcomp {
  	bool operator() (const set<int>& lhs, const set<int>& rhs) const{return lhs.size() > rhs.size();}
  };


  // binary file format is
  // 4 bytes for the number of nodes in the graph
  // 8*(nb_nodes) bytes for the cumulative out degree for each node:
  //    deg(0)=degrees_out[0]
  //    deg(k)=degrees_out[k]-degrees_out[k-1]
  // 8*(nb_nodes) bytes for the cumulative in degree for each node:
  //    deg(0)=degrees_in[0]
  //    deg(k)=degrees_in[k]-degrees_in[k-1]
  // 4*(sum_degrees_out) bytes for the links
  // IF WEIGHTED 4*(sum_degrees_out) bytes for the weights in a separate file
  Graph(char *filename, char *filename_w, int type, bool renumbered);
  
  Graph(int nb_nodes, int nb_links, double total_weight, int *degrees_out, int *links, float *weights);

  void display(void);
  void display_reverse(void);
  void display_binary(char *outfile);
  bool check_symmetry();

  void writeFile(string outNeighbors, string inNeighbors);
  void computeOverlap(string fileName);
  void computeOverlap_new(string fileName);

   void readCommunity(string filename);
  float avg_degree_in_comm(int comm);
  float avg_degree_out_comm(int comm);
  float degree_out_comm(int node, int comm);
  float degree_in_comm(int node, int comm);

  double variane_out(int comm);
  double standard_deviation_out(int comm);

  double variane_in(int comm);
  double standard_deviation_in(int comm);

  double z_score_in(int node, int comm);
  double z_score_out(int node, int comm);

double participation_out(int node);
  double participation_in(int node);

  unsigned int diversite(int node, bool out);
  float avg_diversite(int comm, bool out);
  float variance_diversite(int comm, bool out);
  float standard_deviation_diversite(int comm, bool out);
  float z_diversite(int node, bool out);

  unsigned int intensite(int node, bool out);
  float avg_intensite(int comm, bool out);
  float variance_intensite(int comm, bool out);
  float standard_deviation_intensite(int comm, bool out);
  float z_intensite(int node, bool out);

  float homogeneite(int node, bool out);
  float avg_homogeneite(int comm, bool out);
  float variance_homogeneite(int comm, bool out);
  float standard_deviation_homogeneite(int comm, bool out);
  float z_homogeneite(int node, bool out);

  void writeGuimera(string filename);
  void writeGuimeraClassic(string filename);
  
  void p_scc(int s, int p, set<int>& composante);
  void p_scc_all(int p, int taille_minimum, string filename);

  float c_coefficient(int node, bool out);
  float c_coefficient(int node);

  void cap_sociaux_out(string file);
  void cap_sociaux_in(string file);
  void cap_sociaux_voisins_count(string file);


  // return the number of out neighbors (degree) of the node
  inline unsigned int nb_neighbors_out(unsigned int node);
  
  // return the number of out neighbors (degree) of the node
  inline unsigned int nb_neighbors_in(unsigned int node);

  // return the number of self loops of the node
  inline double nb_selfloops(unsigned int node);

  // return the weighted degree of the node
  inline double out_weighted_degree(unsigned int node);

  // return the weighted in-degree of the node
  inline double in_weighted_degree(unsigned int node);

  // return the total degree
  inline double weighted_degree(unsigned int node);

  // return pointers to the first out-neighbor and first weight of the node
  inline pair<vector<unsigned int>::iterator, vector<float>::iterator > neighbors(unsigned int node);

  // return pointers to the first in-neighbor and first weight of the node
  inline pair<vector<unsigned int>::iterator, vector<float>::iterator > in_neighbors(unsigned int node);
};


inline unsigned int
Graph::nb_neighbors_out(unsigned int node) {
  if (node < 0 || node >= nb_nodes)
	cout << node << endl;
  assert(node>=0 && node<nb_nodes);

  if (node==0)
    return degrees_out[0];
  else
    return degrees_out[node]-degrees_out[node-1];
}

inline unsigned int
Graph::nb_neighbors_in(unsigned int node) {
    if (node < 0 || node >= nb_nodes)
	cout << node << endl;
  assert(node>=0 && node<nb_nodes);

  if (node==0)
    return degrees_in[0];
  else
    return degrees_in[node]-degrees_in[node-1];
}

inline double
Graph::nb_selfloops(unsigned int node) {
  assert(node>=0 && node<nb_nodes);

  pair<vector<unsigned int>::iterator, vector<float>::iterator > p = neighbors(node);
  for (unsigned int i=0 ; i<nb_neighbors_out(node) ; i++) {
    if (*(p.first+i)==node) {
      if (weights.size()!=0)
	return (double)*(p.second+i);
      else 
	return 1.;
    }
  }
  return 0.;
}

inline double
Graph::out_weighted_degree(unsigned int node) {
  assert(node>=0 && node<nb_nodes);

  if (weights.size()==0)
    return (double)nb_neighbors_out(node);
  else {
    pair<vector<unsigned int>::iterator, vector<float>::iterator > p = neighbors(node);
    double res = 0;
    for (unsigned int i=0 ; i<nb_neighbors_out(node) ; i++) {
      res += (double)*(p.second+i);
    }
    return res;
  }
}

inline double
Graph::in_weighted_degree(unsigned int node) {
  assert(node>=0 && node<nb_nodes);

  if (weights.size()==0)
    return (double)nb_neighbors_in(node);
  else {
    pair<vector<unsigned int>::iterator, vector<float>::iterator > p = in_neighbors(node);
    double res = 0;
    for (unsigned int i=0 ; i<nb_neighbors_in(node) ; i++) {
      res += (double)*(p.second+i);
    }
    return res;
  }
}

inline double
Graph::weighted_degree(unsigned int node) {
  assert(node >=0 && node<nb_nodes);

  return out_weighted_degree(node) + in_weighted_degree(node);

}

/* Out-neighbors 
 * DONE: SI LE DEGRE NE CHANGE PAS ON RETOURNE 0 
 */
inline pair<vector<unsigned int>::iterator, vector<float>::iterator >
Graph::neighbors(unsigned int node) {
  assert(node>=0 && node<nb_nodes);

  if (node==0)
    return make_pair(links.begin(), weights.begin());
  else if (weights.size()!=0)
    return make_pair(links.begin()+degrees_out[node-1], weights.begin()+degrees_out[node-1]);
  else
    return make_pair(links.begin()+degrees_out[node-1], weights.begin());
}

/* In-neighbors 
 * TODO: ADAPTER POIDS OUT/IN
 */
inline pair<vector<unsigned int>::iterator, vector<float>::iterator >
Graph::in_neighbors(unsigned int node) {
  assert(node>=0 && node<nb_nodes);

  if (node==0)
    return make_pair(links_in.begin(), weights.begin());
  else if (weights.size()!=0)
    return make_pair(links_in.begin()+degrees_in[node-1], weights.begin()+degrees_in[node-1]);
  else 
	return make_pair(links_in.begin()+degrees_in[node-1], weights.begin());
}


#endif // GRAPH_H
