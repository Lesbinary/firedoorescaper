#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <iostream>
#include <fstream>
#include "float.h"
#include <boost/algorithm/string.hpp>

class Utils{
public:
	static double getElement(std::vector<double> vect, std::vector<int> info, int l, int j, int k){
		int index = 0;
		int i;

		for(i = 0; i < l; i++){
			index += info[i]*info[i+1];
		}

		index += j*info[i+1];

		index += k;

		return vect[index];
	}

	static void setElement(std::vector<double> &vect, std::vector<int> info, int l, int j, int k, double element){
		int index = 0;
		int i;

		for(i = 0; i < l; i++){
			index += info[i]*info[i+1];
		}

		index += j*info[i+1];

		index += k;

		vect[index] = element;
	}

	static void plotData(std::vector<double> x, std::vector<double> y){
		std::ofstream myfile;
		myfile.open ("dataset.dat");
		for(int i = 0; i < x.size(); i++)
			myfile << x[i] << " " << y[i] << std::endl;
		myfile.close();
		system("gnuplot -persist -e \"plot './datafile.dat' using 1:2 title 'Point'\"");

	}

	static void plotDataFunction(std::vector<double> x1, std::vector<double> y1, std::vector<double> x2, std::vector<double> y2, std::string function){
		boost::replace_all(function, "^", "**");

		std::ofstream myfile;
		myfile.open ("dataset1.dat");
		for(int i = 0; i < x1.size(); i++)
			myfile << x1[i] << " " << y1[i] << std::endl;
		myfile.close();
		myfile.open ("dataset2.dat");
		for(int i = 0; i < x2.size(); i++)
			myfile << x2[i] << " " << y2[i] << std::endl;
		myfile.close();
		std::string command = "gnuplot -persist -e \"plot './datafile1.dat' using 1:2 title 'Points dataset 1', './datafile2.dat' using 1:2 title 'Points dataset 2', " + function + "\"";
		system(command.c_str());

	}

	static void doShit(){

	}

	static void scalation(std::vector<Sample> &trainingSet){
		double absolMax = DBL_MIN;

		for(int i = 0; i < trainingSet.size(); i++){
			for(int j = 0; j < trainingSet[i].input.size(); j++){
				double num = trainingSet[i].input[j];

				if(num < 0){
					num *= -1.0;
				}

				if(num > absolMax){
					absolMax = num;
				}
			}
		}

		for(int i = 0; i < trainingSet.size(); i++){
			for(int j = 0; j < trainingSet[i].input.size(); j++){
				trainingSet[i].input[j] /= absolMax;
			}
		}
	}
};

#endif /* SAMPLE_H_ */
