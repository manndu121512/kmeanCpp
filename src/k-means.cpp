//============================================================================
// Name        : k-means.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <string>
#include <math.h>
#include <tgmath.h>
#include <vector>
#include <limits>
using namespace std;

/*
 * In this programming assignment, you are required to implement the k-means algorithm and apply it to a real-life data set.
 * The provided input file ("places.txt") consists of the locations of 300 places in the US. Each location is a two-dimensional
 * point that represents the longitude and latitude of the place.
 * The output file named "clusters.txt" contains exactly 300 lines, where each line represents the cluster label of each location.
 * Every line should be in the format: location_id cluster_label.
 * e.g.
 * 0 1
 * 1 3
 * 2 0
 * 3 2
 */

struct Stats {
	double sum;
	int count;
	double x_cls;
	double y_cls;
	double chg;
};

struct Place {
	double longitude;
	double latitude;
    int clusterId;
    int seqId;

public:
    Place(){
    	this->latitude = -1;
    	this->longitude = -1;
    	this->clusterId = -1;
    	this->seqId = -1;
    }

    Place(double lgd, double ltt)
    {
    	this->longitude = lgd;
    	this->latitude = ltt;
    }

    inline void setseqId(int seq) {
    	this->seqId = seq;
    }

    inline int getseqId()
    {
    	return this->seqId;
    }

    inline void setClusterId(int &cluId)
    {
    	this->clusterId = cluId;
    }

    inline int getClusterId()
    {
    	return this->clusterId;
    }



	/* define an operator >> to read in file with data seperated by  a charactor*/
	friend std::istream & operator >>(std::istream & in, Place & p) {
		char c;
		in >> p.longitude >> c >> p.latitude ;
		return in;
	};
};

struct Cluster {

	int clusterId;
	Place centroid;
	double distanceFromAPlace(Place &p);   // distance = sqrt((xi-x0)**2+(yi-y0)**2 )

	void setCentroid( Place const & p);

};

double Cluster::distanceFromAPlace(Place &p)  //note: it is distance square
{
	double dist_square;
	dist_square = pow(p.longitude - this->centroid.longitude,2.0) + pow (p.latitude - this->centroid.latitude,2.0 );
   // printf("distanceFromAPlace: distance is %f\n", abs(dist));
	return dist_square;
}

void Cluster::setCentroid(Place const &p)
{
	this->centroid = p;
}


int main(int argc, char *argv[])
{
	ofstream outputFile;
	outputFile.open("kmeanOutput.txt");
	float SPEC = 0.0001;  // criteria of exiting loops: change in cluster centerol distances
	ifstream Infile("places.txt");
	if (!Infile) {
		cout << "Cannot open file places.txt\n";
		return 1; }
	Place data[300]; //TODO: change to 300 below TODO too
	for( int i = 0; i<300; i++) {
		Infile >> data[i];
		int r = rand() % 3;
		data[i].setClusterId(r);
		data[i].setseqId(i);
		//printf("%f, %f, %d, %d\n",data[i].longitude, data[i].latitude, data[i].seqId, data[i].clusterId );
	}



	Cluster cltr[3] = {
			{0, Place(-132, 33)},
			{1, Place(-80,  35)},
			{2, Place(-75,  43)}
	};
	/*Cluster cltr[3] = {
				{0, Place(-100, 0)},
				{1, Place(-80,  20)},
				{2, Place(-20,  50)}
		};*/


	printf("Initial clusters: \n");
	for (int i = 0; i< 3; i++){
		printf("cluster[%d]: clusterId: %d, centroid: (%f, %f)\n", i, cltr[i].clusterId, cltr[i].centroid.longitude, cltr[i].centroid.latitude);
	}

	double d[3];

	Stats stats[3] = {
			{0, 0, 0, 0, 0.0},
			{0,0,0,0, 0.0},
			{0,0,0,0, 0.0} };
	double change =100;
	int iter = 0;
	while( change > SPEC)
	{
		for (int j = 0; j<300; j++)  //TODO: change to 300
		{
			double d_min = 1000;
			int new_cls = 0;
			for (int i = 0; i<3; i++)
			{
				d[i] = cltr[i].distanceFromAPlace(data[j]);
				// find the closest cluster and re-assign the clusterId to the place
				if (d[i]< d_min)
				{
					new_cls = i;
					d_min = d[i];
				}
				//printf("%d, d[%d] = %f, d_min = %f new_cls = %d\n",i, i, d[i], d_min, new_cls );
				data[j].setClusterId(new_cls);
			}
			switch(new_cls){
			case 0: stats[0].sum += d_min; stats[0].count++;
			stats[0].x_cls += data[j].longitude;
			stats[0].y_cls += data[j].latitude;
			break;
			case 1: stats[1].sum += d_min; stats[1].count++;
			stats[1].x_cls += data[j].longitude;
			stats[1].y_cls += data[j].latitude;
			break;
			case 2: stats[2].sum += d_min; stats[2].count++;
			stats[2].x_cls += data[j].longitude;
			stats[2].y_cls += data[j].latitude;
			break;
			default: break;
			}
		}

		printf("iterations:\n");
		for (int i = 0; i < 3; i ++)
		{   printf(" %d, count=%d, x_cls = %f, y_cls = %f\n", i, stats[i].count,stats[i].x_cls, stats[i].y_cls  );
		if(stats[i].count != 0 ) {
			double new_x = stats[i].x_cls/stats[i].count;
			double new_y = stats[i].y_cls/stats[i].count;


		//printf("** %f\n", pow(cltr[i].centroid.longitude-new_x, 2.0));
		stats[i].chg = sqrt(pow(cltr[i].centroid.longitude-new_x, 2.0)+ pow(cltr[i].centroid.latitude-new_y, 2.0));
		cltr[i].centroid.longitude = new_x;
		cltr[i].centroid.latitude = new_y;
		printf("new_x= %f, new_y=%f\n", new_x, new_y);
		}
		printf("cluster[%d]: clusterId: %d, centroid: (%f, %f), chg: %f\n", i, cltr[i].clusterId, cltr[i].centroid.longitude, cltr[i].centroid.latitude, stats[i].chg);
		}

		change = stats[0].chg+ stats[1].chg+stats[2].chg;
		iter ++;
		printf("%d, change= %f\n", iter, change);


	}
	for (int i = 0; i<300; i++) //TODO: change to 300
	{
		printf("%f, %f, %d, %d\n",data[i].longitude, data[i].latitude, data[i].seqId, data[i].clusterId );
		outputFile << data[i].seqId << " " << data[i].clusterId <<endl;
	}
    outputFile.close();
	return 0;
}

