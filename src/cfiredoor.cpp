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
  m_nextInputs.clear();
  m_onFire = false;
  do createNewPattern(); while (!validatePattern(0.4));
  //CRNDGEN.uniformRandomDoubleVector(m_nextInputs, m_dimension, -m_rangei, m_rangei);
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
  CRNDGEN.uniformRandomDoubleVector(m_nextInputs, m_dimension, -m_rangei, m_rangei);

  // Update steps
  m_steps++;
}

////////////////////////////////////////////////////////////
/// \brief Creates a new pattern of weights for the door.
////////////////////////////////////////////////////////////
void
CFireDoor::createNewPattern() {
    m_weights.clear();
    m_rangei = CRNDGEN.uniformRandomDouble(10, 10000);
    double rangew = m_rangei / 10; //CRNDGEN.uniformRandomDouble(m_rangei/10, m_rangei/2);
    CRNDGEN.uniformRandomDoubleVector(m_weights,  m_dimension+1, -rangew, rangew);
    //m_weights[m_weights.size()-1] *= 0.1;
}

////////////////////////////////////////////////////////////
/// \brief Validates the new pattern of weights
/// It checks the proportion of nofire events for the
/// actual fire pattern of the door and validates it if
/// the proportion is above the threshold.
/// \param threshold 0-1 minimum acceptable proportion of nofire events
/// \param n             number of samples to test
/// \returns true if the proportion is above threshold
////////////////////////////////////////////////////////////
bool
CFireDoor::validatePattern(double threshold, unsigned n) {
    // Count nofire events in n samples
    unsigned nofire = 0;
    for (unsigned i=0; i < n; i++) {
        doNextFireStep();
        if (!m_onFire) nofire++;
    }
    // Restore used steps
    m_steps -= n;

    // Return if nofire events proportion is above threshold
    return ( (double(nofire) / double(n)) > threshold );
}

}
