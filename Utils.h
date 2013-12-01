#ifndef UTILS_H_
#define UTILS_H_

#include <vector>

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
};

#endif /* SAMPLE_H_ */
