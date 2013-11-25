#include <vector>
#include <boost/noncopyable.hpp>

namespace FireDoorEscaper {

///((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
/// \brief Class that implements a FireDoor
/// A FireDoor is a door that sometimes gets on fire. This doors
/// receive some values as input and get on fire depending on that
/// input.
///((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
class CFireDoor : private boost::noncopyable {
public:
  friend class CGame;                      // CGame is only class able to create FireDoors

  //---- Constants and types
  enum EModel { M_LINEAR, M_POLINOMIAL };  //< Model of input interpretation of the door
  typedef std::vector<double> TVecDoubles; //< Type defining a std::vector of doubles

  //---- Methods
  inline bool         isOnFire() const;
  inline unsigned     getSteps() const;
  inline unsigned     getDimension() const;
  inline const TVecDoubles& getNextStepInputs() const;
  void                doNextFireStep();

  TVecDoubles m_weights;    //< Weights of the Door Model

private:
  bool        m_onFire;     //< True if the door is on fire
  EModel      m_model;      //< Selects the model of input interpretation of the Door
  unsigned    m_steps;      //< Steps played with this firedoor
  unsigned    m_dimension;  //< Dimension of the weight space
  double      m_rangei;     //< Input range for current door
  TVecDoubles m_nextInputs; //< Next inputs to the Door

  explicit    CFireDoor(unsigned dim);
  inline void setModel(EModel m);
  void        initialize();
  void        createNewPattern();
  bool        validatePattern(double threshold, unsigned n=100);
};

////
//// INLINE METHODS
////

/////////////////////////////////////////////////////////
/// \brief Method to check if the door is on fire
/// \return True if the door is on fire, false otherwise
/////////////////////////////////////////////////////////
inline bool
CFireDoor::isOnFire() const { return m_onFire; }

/////////////////////////////////////////////////////////
/// \brief Method to check the number of steps
/// \return Number of steps played with this door
/////////////////////////////////////////////////////////
inline unsigned
CFireDoor::getSteps() const { return m_steps; }

/////////////////////////////////////////////////////////
/// \brief Check the dimension of this door
/// \return Number of dimensions of the input space of this door
/////////////////////////////////////////////////////////
inline unsigned
CFireDoor::getDimension() const { return m_dimension; }

/////////////////////////////////////////////////////////
/// \brief Check the dimension of this door
/// \return Number of dimensions of the input space of this door
/////////////////////////////////////////////////////////
const CFireDoor::TVecDoubles&
CFireDoor::getNextStepInputs() const { return m_nextInputs; }

/////////////////////////////////////////////////////////
/// \brief Sets the model for input interpretation
/// \param m  New model for input interpretation
/////////////////////////////////////////////////////////
void
CFireDoor::setModel(CFireDoor::EModel m) { m_model = m; }


}
