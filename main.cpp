#include "include/cgame.h"
#include "include/cfiredoor.h"
#include "GodMachine.h"
#include <iostream>

using namespace FireDoorEscaper;

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
    std::cout << "Empezamos el juego: " << std::endl;
    while (game->getGameStatus() == CGame::GS_PLAYING) {
    	machine.clearTrainingSet();

        const CFireDoor& fd = game->getCurrentFireDoor();
        printGameStatus(*game);

        //Almacenamos el conjunto de entrenamiento
    	while(!machine.isTrainingReady()){
        //for (unsigned i=0; i < 5; i++) {
            printGameStatus(*game);
            s.input=fd.getNextStepInputs();
            game->nextStep();
            s.burn=fd.isOnFire();
            machine.addTrainingSample(s);
        }
    	while(!machine.isReadyToCross() || machine.isDoorOnFire(fd.getNextStepInputs()[0])){
    		printGameStatus(*game);
            s.input=fd.getNextStepInputs();
            game->nextStep();
            s.burn=fd.isOnFire();
            machine.classifySample(s);
            machine.addTrainingSample(s);
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
