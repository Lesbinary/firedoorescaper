#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <iostream>
#include <fstream>

class Utils{
public:
	static double getElement(std::vector<double> vect, std::vector<int> info, int l, int j, int k){
		int index = 0;
		int i;

		for(i = 0; i < l; i++){
			index += info[i]*info[i+1];
		}

		index += j*info[i];

		index += k;

		return vect[index];
	}

	static void setElement(std::vector<double> vect, std::vector<int> info, int l, int j, int k, double element){
		int index = 0;
		int i;

		for(i = 0; i < l; i++){
			index += info[i]*info[i+1];
		}

		index += j*info[i];

		index += k;

		vect[index] = element;
	}

	static void plotData(std::vector<double> x, std::vector<double> y){
		std::ofstream myfile;
		myfile.open ("dataset.dat");
		for(int i = 0; i < x.size(); i++)
			myfile << x[i] << " " << y[i] << std::endl;
		myfile.close();
		system("gnuplot -persist -e \"plot './datafile.dat' using 1:2 title 'X' with linespoints, './datafile.dat' using 1:2 title 'Y' with points\"");
	}
};

#endif /* SAMPLE_H_ */
