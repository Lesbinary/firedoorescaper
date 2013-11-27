
#ifndef IMACHINE_H_
#define IMACHINE_H_

#include "Sample.h"

class IMachine {
public:
	virtual void addTrainingSample(Sample sample)=0;
	virtual bool isTrainingReady()=0;
	virtual bool isReadyToCross()=0;
	virtual void classifySample(Sample sample)=0;
	virtual bool isDoorOnFire(double input[])=0;
	virtual void clearTrainingSet()=0;
	virtual void pedirParametros();
};

#endif
