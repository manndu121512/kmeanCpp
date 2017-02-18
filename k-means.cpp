/*
 * k-means.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: v712995
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;
/*
 * This is to implement the k-means algorithm and apply it to a real-life data set
 * 
 * The provided input file ("places.txt") consists of the locations of 300 places in the US. 
 * Each location is a two-dimensional point that represents the longitude and latitude of the place. 
 * For example, "-112.1,33.5" means the longitude of the place is -112.1, and the latitude is 33.5.
 * 
 * K-means algorithm is used to cluster the 300 locations into three clusters, such that the locations in the same 
 * cluster are geographically close to each other. The output file "clusters.txt" should contain exactly 300 lines, 
 * where each line represents the cluster label of each location. Every line should be in the format: location_id cluster_label.
 * An example snippet of the output "clusters.txt" file is provided below: 
 *  0 1
 *  1 0
 *  2 1
 *  3 2
 * 
 */

int main(int argc, char *argv[])
{
      if (argc != 2) {
            cout << "Usage: executable_name places.txt\n";
            return 1; }
      ifstream Infile(argv[1]);
      if (!Infile) {
            cout << "Cannot open file\n";
            return 1; }
      char LineBuf[300];
      char d[] = ",";
      int i=0;
      while (Infile.getline(LineBuf, 100) && !Infile.eof()) {
            struct AirShipFile data;
            data.Type = atoi(strtok(LineBuf, d));
            switch (data.Type) {


