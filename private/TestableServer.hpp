#include "Server.hpp" // Assurez-vous que le chemin est correct

class TestableServer : public Server {
public:
    // Expose _pass pour les tests
    using Server::_pass;
};