all: bee

OBJS = parser.o  \
       codegen.o \
       main.o    \
       tokens.o  \
       corefn.o  \
	   native.o  \

CLANGLIBS = \
	-lclangTooling\
	-lclangFrontendTool\
	-lclangFrontend\
	-lclangDriver\
	-lclangSerialization\
	-lclangCodeGen\
	-lclangParse\
	-lclangSema\
	-lclangStaticAnalyzerFrontend\
	-lclangStaticAnalyzerCheckers\
	-lclangStaticAnalyzerCore\
	-lclangAnalysis\
	-lclangARCMigrate\
	-lclangRewrite\
	-lclangRewriteFrontend\
	-lclangEdit\
	-lclangAST\
	-lclangLex\
	-lclangBasic\
	-lcurses

LLVMCONFIG = llvm-config
CPPFLAGS = `$(LLVMCONFIG) --cppflags` -std=c++14
LDFLAGS = `$(LLVMCONFIG) --ldflags` -lpthread -ldl -lz -lncurses -rdynamic
LIBS = `$(LLVMCONFIG) --libs`

clean:
	$(RM) -rf parser.cpp parser.hpp tokens.cpp $(OBJS) 

parser.cpp: parser.y
	bison -d -o $@ $^
	
parser.hpp: parser.cpp

tokens.cpp: tokens.l parser.hpp
	flex -o $@ $^

%.o: %.cpp
	clang++ -gfull -c $(CPPFLAGS) -o $@ $<


bee: $(OBJS)
	clang++ -no-pie -gfull -o $@ $(OBJS) $(LIBS) $(LDFLAGS) $(CLANGLIBS)

test: bee test.b
	cat test.b | ./bee run
