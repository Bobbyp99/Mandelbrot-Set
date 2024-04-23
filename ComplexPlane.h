const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

using namespace std;
using namespace sf;

enum class State { CALCULATING, DISPLAYING };

// If program starts or user clicks mouse to move, we will be CALCULATING the complex plane display
// When done, set the state variable back to DISPLAYING

VertexArray m_vArray;
State m_state;

