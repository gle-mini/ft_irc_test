######################################
#              COMMANDS              #
######################################
CXX         =   ${shell which c++}
LINK        =   ${shell which clang++}
MKDIR       =   ${shell which mkdir} -p
RM          =   ${shell which rm} -rf
CMAKE		=	${shell which cmake}

#######################################
#             DIRECTORIES             #
#######################################
OBJ_DIR     =   obj
TEST_DIR	=	tests
GTEST_DIR   =   googletest
GTEST_BUILD_DIR = ${GTEST_DIR}/build
GTEST_LIB_DIR = ${GTEST_BUILD_DIR}/lib/
GTEST_INC_DIR = ${GTEST_DIR}/googletest/include/

#######################################
#                FLAGS                #
#######################################
CXXFLAGS    =   -c
CXXFLAGS    +=  -Wall -Wextra -Werror
CXXFLAGS    +=  -MMD -MP
CXXFLAGS    +=  -Wshadow
CXXFLAGS 	+= -std=c++14
CXXFLAGS	+= -I${GTEST_INC_DIR}

ifeq (${DEBUG}, 1)
    CXXFLAGS    +=  -g
    CXXFLAGS    +=  -DDEBUG=1
endif

#######################################
#           GOOGLE TEST SETUP         #
#######################################
GTEST_A = \
	libgtest.a \
	libgtest_main.a

GTEST_A := ${addprefix ${GTEST_LIB_DIR}, ${GTEST_A}}

IRC_A = ../libirc.a

${IRC_A} :
	${MAKE} -C ${@D} ${@F}

# Fichiers de test source
SRC = \
	${addprefix ${TEST_DIR}/, \
		test1.cpp \
		test2.cpp \
	}
# Ajoutez vos fichiers de test ici

# Fichiers objet pour les tests
OBJ = ${SRC:.cpp=.o}
OBJ := ${addprefix ${OBJ_DIR}/, ${OBJ}}

# Exécutable de test
NAME = unit_tests

# Règle pour compiler les tests
$(NAME): LFLAGS = -lpthread 
$(NAME): $(OBJ) $(GTEST_A) ${IRC_A}
	$(LINK) $^ $(LFLAGS) $(OUTPUT_OPTION)

# Dépendances pour les tests
TEST_DEP = ${OBJ:.o=.d}

# Inclure les dépendances
-include $(TEST_DEP)

# Règle pour les fichiers objet de test
${OBJ_DIR}/${TEST_DIR}/%.o: ${TEST_DIR}/%.cpp
	@${MKDIR} ${@D}
	${CXX} $< ${CXXFLAGS} ${OUTPUT_OPTION}

${GTEST_A}:
	${CMAKE} -B ${GTEST_BUILD_DIR} ${GTEST_DIR}
	${MAKE} -C ${GTEST_BUILD_DIR}

# Règle pour exécuter les tests
all: $(NAME)
	./$(NAME)

clean:
	${RM} ${NAME} ${IRC_A} vgcore.*

fclean:
	${RM} ${OBJ_DIR} ${NAME} ${GTEST_BUILD_DIR} ${IRC_A} vgcore.*


.PHONY:	all clean fclean re  fre
