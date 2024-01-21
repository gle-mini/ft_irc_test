######################################
#              COMMANDS              #
######################################
CXX         =   ${shell which c++}
LINK        =   ${shell which clang++}
MKDIR       =   ${shell which mkdir} -p
RM          =   ${shell which rm} -rf
CMAKE		=	${shell which cmake}

######################################
#             EXECUTABLE             #
######################################
NAME = unit_tests

#######################################
#             DIRECTORIES             #
#######################################
OBJ_DIR     =   obj
SRC_DIR		=	tests
GTEST_DIR   =   googletest
GTEST_BUILD_DIR = ${GTEST_DIR}/build
GTEST_LIB_DIR = ${GTEST_BUILD_DIR}/lib/
GTEST_INC_DIR = ${GTEST_DIR}/googletest/include/

#######################################
#              LIBRARIES              #
#######################################
GTEST_A = \
	libgtest.a \
	libgtest_main.a

GTEST_A := ${addprefix ${GTEST_LIB_DIR}, ${GTEST_A}}

IRC_A = ../libirc.a

######################################
#            SOURCE FILES            #
######################################
SRC = \
		test1.cpp \
		test2.cpp \

#######################################
#                FLAGS                #
#######################################
CXXFLAGS    =   -c
CXXFLAGS    +=  -Wall -Wextra -Werror
CXXFLAGS    +=	-MMD -MP
CXXFLAGS    +=	-Wshadow
CXXFLAGS 	+=	-std=c++14
CXXFLAGS	+=	-I${GTEST_INC_DIR}

LFLAGS 		+=	-lpthread

ifeq (${DEBUG}, 1)
    CXXFLAGS    +=  -g
    CXXFLAGS    +=  -DDEBUG=1
endif

######################################
#            OBJECT FILES            #
######################################
OBJ = ${SRC:.cpp=.o}
OBJ := ${addprefix ${OBJ_DIR}/, ${OBJ}}

TEST_DEP = ${OBJ:.o=.d}

#####################################
#           	RULES        		#
##################################### 
${NAME}: ${OBJ} ${GTEST_A} ${IRC_A}
	${LINK} $^ ${LFLAGS} ${OUTPUT_OPTION}

all: ${NAME}

-include ${TEST_DEP}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp
	@${MKDIR} ${@D}
	${CXX} $< ${CXXFLAGS} ${OUTPUT_OPTION}

${GTEST_A}:
	${CMAKE} -B ${GTEST_BUILD_DIR} ${GTEST_DIR}
	${MAKE} -C ${GTEST_BUILD_DIR}

${IRC_A} :
	${MAKE} -C ${@D} ${@F}

clean:
	${RM} ${NAME} ${IRC_A} vgcore.*

fclean:
	${RM} ${OBJ_DIR} ${NAME} ${GTEST_BUILD_DIR} ${IRC_A} vgcore.*

re: clean all

fre: fclean all

.PHONY:	all clean fclean re fre
