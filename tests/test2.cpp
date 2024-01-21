#include "gtest/gtest.h"

TEST(HelloTest, OutputsHelloWorld) {
    // Sauvegarder l'ancien buffer
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();

    // Créer un stringstream pour capturer la sortie
    std::ostringstream strCout;
    std::cout.rdbuf(strCout.rdbuf());

    // Appeler la fonction qui imprime sur la sortie standard
    hello();

    // Restaurer l'ancien buffer
    std::cout.rdbuf(oldCoutStreamBuf);

    // Vérifier la sortie capturée
    EXPECT_EQ(strCout.str(), "hello world\n");
}
