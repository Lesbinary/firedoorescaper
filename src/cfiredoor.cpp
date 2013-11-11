#include <cmath>
#include <cfiredoor.h>
#include <crandomgenerator.h>

namespace FireDoorEscaper {

////////////////////////////////////////////////////////////
/// \brief Constructs a FireDoor
////////////////////////////////////////////////////////////
CFireDoor::CFireDoor(unsigned dim)
  : m_onFire(false), m_model(M_LINEAR),
    m_steps(0), m_dimension(dim)
{
  initialize();
}

////////////////////////////////////////////////////////////
/// \brief Initializes the FireDoor
////////////////////////////////////////////////////////////
void
CFireDoor::initialize() {
  m_weights.clear();
  m_nextInputs.clear();
  m_onFire = false;
  double rangei = CRNDGEN.uniformRandomDouble(10, 10000);
  double rangew = CRNDGEN.uniformRandomDouble(rangei/500, rangei/50);
  CRNDGEN.uniformRandomDoubleVector(m_weights,  m_dimension+1, -rangew, rangew);
  CRNDGEN.uniformRandomDoubleVector(m_nextInputs, m_dimension, -rangei, rangei);
}

////////////////////////////////////////////////////////////
/// \brief Does the next time step for the FireDoor
/// It simulates what the FireDoor does in the next timestep
/// taking into account inputs received from the previous
/// timestep
////////////////////////////////////////////////////////////
void
CFireDoor::doNextFireStep() {
  // Calculate inner product and get the sign for setting on fire
  double sum = 0.0;
  m_nextInputs.push_back(1.0);
  for(unsigned i=0; i < m_dimension+1; i++) {
    double x = m_nextInputs[i];
    if (m_model != M_LINEAR) x = pow(m_nextInputs[i], m_dimension-i-1);
    sum += m_weights[i] * x;
  }
  m_onFire = (sum > 0);

  // Create a new set of random inputs for the next step
  m_nextInputs.clear();
  CRNDGEN.uniformRandomDoubleVector(m_nextInputs, m_dimension, -100.0, 100.0);

  // Update steps
  m_steps++;
}

}
