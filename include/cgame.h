#ifndef CGAME_H
#define CGAME_H

#include <vector>
#include <boost/noncopyable.hpp>

namespace FireDoorEscaper {

// Forward Declarations
class CFireDoor;

///((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
/// \brief Class that implements the game of FireDoorEscaper
///((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
class CGame : private boost::noncopyable {
public:
  //---- Public Constants
  /// Status of the Game
  enum EGameStatus {
    GS_PLAYING,   //< The game is still in play. Player is alive.
    GS_FINISHED   //< The game is finished. Player is burned.
  };
  /// Different modes of game difficulty
  enum EGameDifficultyMode {
    GDM_SAMELEVEL,  //< The game is allways played in the same level of difficulty
    GDM_LEVELUP     //< The difficulty level grows up as the player advances through the game
  };
  const unsigned mc_maxLevel;       //< Maximum difficulty level
  const unsigned mc_doorsPerLevel;

  //---- Methods
  explicit            CGame(unsigned level);
                      ~CGame();
  void                nextStep();
  void                crossFireDoor();
  inline unsigned     getLevel() const;
  inline unsigned     getSteps() const;
  inline double       getScore() const;
  inline unsigned     getDoorsPassed() const;
  inline EGameStatus  getGameStatus() const;
  inline EGameDifficultyMode getGameDifficultyMode() const;
  inline void         setGameDifficultyMode(EGameDifficultyMode m);
  const CFireDoor&    getCurrentFireDoor() const;

private:
  unsigned    m_level;            //< Difficulty level
  unsigned    m_steps;            //< Total game steps
  unsigned    m_doorsPassed;      //< Total number of doors passed
  EGameStatus m_gameStatus;       //< Status of the current Game
  double      m_score;            //< Player score
  EGameDifficultyMode m_gameDifficultyMode; //< Game Difficulty Mode
  CFireDoor   *m_currentFireDoor; //< Current FireDoor being faced by the player

  void        setUpNextFireDoor();
  void        destroyCurrentFireDoor();
};


////////////////////////////////////////////////////////
/// \brief Returns the current level of difficulty
/// \returns Current level of difficulty
////////////////////////////////////////////////////////
inline unsigned
CGame::getLevel() const { return m_level; }

////////////////////////////////////////////////////////
/// \brief Returns the number of steps played this game
/// \returns A unsigned value with the number of steps
////////////////////////////////////////////////////////
inline unsigned
CGame::getSteps() const { return m_steps; }

////////////////////////////////////////////////////////
/// \brief Returns the score of the player of this game
/// \returns Score of the player up to now
////////////////////////////////////////////////////////
inline double
CGame::getScore() const { return m_score; }

////////////////////////////////////////////////////////
/// \brief Returns the number of doors passed this game
/// \returns Total number of doors passed this game
////////////////////////////////////////////////////////
inline unsigned
CGame::getDoorsPassed() const { return m_doorsPassed; }

////////////////////////////////////////////////////////
/// \brief Check the current status of the game
/// \returns Current status of the game
////////////////////////////////////////////////////////
CGame::EGameStatus
CGame::getGameStatus() const { return m_gameStatus; }

////////////////////////////////////////////////////////
/// \brief Check the selected game difficulty mode
/// \returns Current game difficulty mode
////////////////////////////////////////////////////////
CGame::EGameDifficultyMode
CGame::getGameDifficultyMode() const { return m_gameDifficultyMode; }

////////////////////////////////////////////////////////
/// \brief Sets the game difficulty mode
/// \param m  New game difficulty mode selected
////////////////////////////////////////////////////////
void
CGame::setGameDifficultyMode(CGame::EGameDifficultyMode m) {
  m_gameDifficultyMode = m;
}

} // Namespace

#endif // CGAME_H
