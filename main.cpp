#include "include/cgame.h"
#include "include/cfiredoor.h"
#include "GodMachine.h"
#include <stdlib.h>
#include <iostream>
#include <vector>


using namespace FireDoorEscaper;

//TODO: Métodos de clasificación a implementar
//Fáciles
// - Lineal (Perceptron, Regresión Lineal, etc)
// - Lineal con transoformaciones no lineales

//Medios
// - Regresión logística
// - Redes neuronales
//     - Feed-Forward (Backpropagation)
//     - Recurrentes / Generales (Genéticos u otros) <- Medio-difícil

//Difíciles
// - Support Vector Machines
//     - Kernel Methods (Difícil++)
// - Radial Basis Functions  (Difícil--)


//TODO: Técnicas de clasficiación a implementar
// - Regularización <- Medio
// - Reducción de dimensionalidad
//      - Recomendado: PCA <- Medio-difícil
//      - Alternativo: Aprendizaje no-supervisado (k-means, etc)


//Niveles para la nota de la práctica:
//·Básico: 2 modelos (fácil y media como mínimo)
//         1 técnica
// Nota razonable: 3 modelos (Medio y difícil)
//                 1-2 técnicas

//Para la optimizacion avanzada meto aquí el enlace, creo que me decanto por esta por simplicidad
//Cuando pueda hago una implementación, pero la documentacion es sencillita: http://www.chokkan.org/software/liblbfgs/

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
main(int argvc, char *argv[]) {
    // Create a new game starting at level 0, and staying at the same level all the time.
    // Use GDM_LEVELUP for increasing level of difficulty
	GodMachine *machine;
    CGame *game;
    int minDoorsToNextLevel = 100; // Esto también se debería de pasar por parámetro o algo


	 int nivelDeJuego;
	 int maquinaElegida;
	 double lambda;




    // Obtengo parametros e inicializo
    if(argvc > 1){ // Para una ejecución rápida... más o menos: firebitch initLevel machine [los parámetros que puedan requerir cada máquina]
    	int level = atoi(argv[1]); // Nivel inicial del juego
    	game = new CGame(level);
    	int machineType = atoi(argv[2]); // Tipo de máquina
    	switch(machineType){
    	case 0: // KVecinos o lo que sea eso
    		machine = new GodMachine(KVecinos);
    		break;
    	case 1: // Logistic regression
    		machine = new GodMachine(LogisticRegresion);

    		break;
    	default: // Por defecto
    		machine = new GodMachine(LogisticRegresion);
    		break;
    	}

    } else{ // Aquí lo ideal sería es que si no se pasan parámetros se inicien parámetros por defecto y salga un menú con las opciones


    	 std::cout << "Seleccionar el nivel inicial del juego(0-9): ";
    	 std::cin >> nivelDeJuego;

    	 game = new CGame(nivelDeJuego);

    	 system("cls");

    	 std::cout << "1.KVecinos " << std::endl;
    	 std::cout << "2.LogisticRegresion " << std::endl;
    	 std::cout << "3.Neural network " << std::endl;
    	 std::cout << "4.Support vector machines " << std::endl;
    	 std::cout << "Selecciona la maquina: ";
    	 std::cin >> maquinaElegida;

    	 system("cls");

    	 std::cout << "Introduce el lambda: ";
    	 std::cin >> lambda; //es un double?

    	 system("cls");

    	switch(maquinaElegida){
    	case 1: // KVecinos
    		machine = new GodMachine(KVecinos);
    	break;
    	case 2: //LogisticRegresion
    		machine = new GodMachine(LogisticRegresion);
    		machine->pedirParametros();
    	break;
    	case 3: // Neural network
        	machine = new GodMachine(neuralNetwork);
        	machine->pedirParametros();
    	break;
    	case 4: //Support vector machines
    		std::cout << "Tico tico tico tico tico tico tico tico tico";
    	break;
    	}
    }

    game->setGameDifficultyMode(CGame::GDM_SAMELEVEL);
    // Main loop: stay will the game is on (i.e. the player is alive)
    std::cout << "Empezamos el juego: " << std::endl;
    while (game->getGameStatus() == CGame::GS_PLAYING) {
    	machine->clearTrainingSet();
    	if(game->getDoorsPassed() + 1 > minDoorsToNextLevel){
    		int cLevel = game->getLevel();
    		game = new CGame(cLevel+1);
    	}

        const CFireDoor& fd = game->getCurrentFireDoor();
        printGameStatus(*game);

        //Almacenamos el conjunto de entrenamiento
    	while(!machine->isTrainingReady()){
    		Sample s;
            printGameStatus(*game);
            s.input=fd.getNextStepInputs();
            game->nextStep();
            s.burn=fd.isOnFire();
            machine->addTrainingSample(s);
        }
    	//Hago esto para obtener un vector de doubles de los input
    	std::vector<double> vIn = fd.getNextStepInputs();
    	double* in = &vIn[0];
    	while(!machine->isReadyToCross() || machine->isDoorOnFire(in)){
    		Sample s;
    		printGameStatus(*game);
            s.input=fd.getNextStepInputs();
            game->nextStep();
            s.burn=fd.isOnFire();
            machine->classifySample(s);
            vIn = fd.getNextStepInputs();
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
