#include "cgame.h"
#include <cfiredoor.h>
#include <crandomgenerator.h>
#include <cmath>

namespace FireDoorEscaper {

////////////////////////////////////////////////////////////
/// \brief Creates a new Game
/// \param level  Starting difficulty level of the game
////////////////////////////////////////////////////////////
CGame::CGame(unsigned level)
  : mc_maxLevel(10), mc_doorsPerLevel(12),  m_level(level),
    m_steps(0),      m_doorsPassed(0),
    m_gameStatus(GS_PLAYING),  m_score(0.0),
    m_gameDifficultyMode(GDM_LEVELUP),
    m_currentFireDoor(0)
{
  // Do not surpass Max Level of Difficulty
  if (m_level > mc_maxLevel)
    m_level = mc_maxLevel;

  // Create the first firedoor
  setUpNextFireDoor();
}

////////////////////////////////////////////////////////////
/// \brief Destroys the Game
////////////////////////////////////////////////////////////
CGame::~CGame() {
  destroyCurrentFireDoor();
}

////////////////////////////////////////////////////////////
/// \brief Obtain the current FireDoor Object
/// \return A constant reference to the current FireDoor Object
////////////////////////////////////////////////////////////
const CFireDoor&
CGame::getCurrentFireDoor() const {
  return *m_currentFireDoor;
}

////////////////////////////////////////////////////////////
/// \brief Sets up the next FireDoor to be played
////////////////////////////////////////////////////////////
void
CGame::setUpNextFireDoor() {
  typedef CFireDoor::EModel EModel;

  // Pick up model and dimension
  const EModel km[2] = { CFireDoor::M_LINEAR, CFireDoor::M_POLINOMIAL };
  EModel m = km[0];
  unsigned dim;
  switch (m_level) {
    case 0: { dim = 1; break; }
    case 1: { dim = 2; break; }
    case 2: { dim = 4; break; }
    case 3: { dim = CRNDGEN.uniformRandomInt(4,10); break; }
    case 4: { dim = 3; m = km[1]; break; }
    case 5: { dim = 4; m = km[1]; break; }
    case 6: { dim = 6; m = km[1]; break; }
    case 7: { dim = CRNDGEN.uniformRandomInt(3,12); m = km[1]; break; }
    case 8: { dim = 5; m = km[CRNDGEN.uniformRandomInt(0,1)]; break; }
    case 9: { dim = CRNDGEN.uniformRandomInt(4,12);
              m = km[CRNDGEN.uniformRandomInt(0,1)]; break; }
    case 10:{ dim = CRNDGEN.uniformRandomInt(10,25);
              m = km[CRNDGEN.uniformRandomInt(0,1)]; break; }
  }
  destroyCurrentFireDoor();
  m_currentFireDoor = new CFireDoor(dim);
  m_currentFireDoor->setModel(m);
}

////////////////////////////////////////////////////////////
/// \brief Destroys the current FireDoor
////////////////////////////////////////////////////////////
void
CGame::destroyCurrentFireDoor() {
  // Delete current Firedoor if there still is one
  if (m_currentFireDoor) {
    delete m_currentFireDoor;
    m_currentFireDoor = 0;
  }
}

////////////////////////////////////////////////////////////
/// \brief Advances the game one step further
/// The game advances one step further without moving the
/// player (i.e. staying in front of the current FireDoor)
////////////////////////////////////////////////////////////
void
CGame::nextStep() {
  // Cannot play in Finished Status
  if (m_gameStatus == GS_FINISHED)
    return;

  // Next step and update FireDoor
  m_steps++;
  m_currentFireDoor->doNextFireStep();
}

////////////////////////////////////////////////////////////
/// \brief Try to cross the FireDoor
/// When the player calls this method, they give the order
/// of trying to pass the firedoor. If it passes, the game
/// continues and the score is updated. If the door is on
/// fire, the player dies and the game ends.
////////////////////////////////////////////////////////////
void
CGame::crossFireDoor() {
  // Cannot play in Finished Status
  if (m_gameStatus == GS_FINISHED)
    return;

  // Next step and check if player is burned
  nextStep();
  if (m_currentFireDoor->isOnFire()) {
    // Player gets burned
    m_gameStatus = GS_FINISHED;
  } else {
    // Player passes and gets points
    unsigned doorsteps = m_currentFireDoor->getSteps();
    m_score += 60+2*pow(m_level, 3) - 2*sqrt(mc_maxLevel * doorsteps);
    m_doorsPassed++;

    // Check for level up
    if (m_gameDifficultyMode == GDM_LEVELUP &&
        m_level < mc_maxLevel) {
      unsigned calc_level = m_doorsPassed / mc_doorsPerLevel;
      if (calc_level > m_level && calc_level < mc_maxLevel)
        m_level = calc_level;
    }

    // Prepare next door
    setUpNextFireDoor();
  }
}


} // Namespace
