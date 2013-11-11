#include "include/cgame.h"
#include "include/cfiredoor.h"
#include <iostream>

using namespace FireDoorEscaper;


struct Sample{
	std::vector<double> input;
	bool burn;
};

class GodMachine {
public:
	GodMachine(){}
	virtual ~GodMachine(){}
	void addTrainingSample(Sample sample){
		trainingSet.push_back(sample);
	}
	bool isTrainingReady(){
		return trainingSet.size()==5;
	}
	void clearTrainingSet(){
		trainingSet.clear();
	}
private:
	std::vector<Sample> trainingSet;
};




// Print Game Status Values
void
printGameStatus(const CGame& g) {
    const CFireDoor& fd = g.getCurrentFireDoor();
    const CFireDoor::TVecDoubles& inp = fd.getNextStepInputs();
    std::cout   << "Lvl: " << g.getLevel()
                << " | Steps: " << g.getSteps()
                << " | Score: " << g.getScore()
                << " | Door: " << g.getDoorsPassed() + 1
                << " | DSteps: " << fd.getSteps()
                << " | OnFire?: " << ((fd.isOnFire()) ? "yes" : "no")
                << std::endl
                << "=========================================================================\n"
                << "Next Inputs: [ ";
    for (unsigned i=0; i < inp.size(); i++)
        std::cout << inp[i] << " ";
    std::cout << "] \n";
}

int
main(void) {
    // Create a new game starting at level 0, and staying at the same level all the time.
    // Use GDM_LEVELUP for increasing level of difficulty
	GodMachine machine;
    CGame *game = new CGame(0);
    game->setGameDifficultyMode(CGame::GDM_SAMELEVEL);
    Sample s;


    // Main loop: stay will the game is on (i.e. the player is alive)
    while (game->getGameStatus() == CGame::GS_PLAYING) {
    	machine.clearTrainingSet();

        const CFireDoor& fd = game->getCurrentFireDoor();

        // Do some game steps and print values
    	while(!machine.isTrainingReady()){
        //for (unsigned i=0; i < 5; i++) {

            printGameStatus(*game);
            s.burn=fd.isOnFire();
            s.input=fd.getNextStepInputs();
            machine.addTrainingSample(s);
            game->nextStep();
        }

        // Try to cross the current FireDoor
        printGameStatus(*game);
        std::cout << "**** TRYING TO CROSS THE DOOR ****\n";
        game->crossFireDoor();
        if (game->getGameStatus() != CGame::GS_PLAYING)
            std::cout << "!!!!!!!!!!! PLAYER GOT BURNED OUT !!!!!!!!!!!!!!\n";
        else
            std::cout << "****** DOOR PASSED *****\n";
    }

    // Game Over
    delete game;
    return 0;
}
