#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>

namespace gfx {

/**
 * A Component provides internal functionality beyond
 * Entity to Entity communication.  This includes
 * rendering, collision, and AI control.
 * */
class Component {

protected:
    /** We use this wrapper instead of directly calling the Entity's
     * post() function because the messaging system may change later
     * and we don't want to have to rip apart a bunch of Component
     * code to fix it. */
    void post();
};

class Entity {

public:
    void post(/** address and message */);
};

}
#endif
