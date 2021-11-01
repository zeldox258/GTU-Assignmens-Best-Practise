JC = javac
JFLAGS = -classpath .
JD = javadoc
JDFLAGS = -protected -splitindex -use -author -version -d ./javadoc
RM = rm
JR = java

CLASSES = \
		HW7.java \
		Cell.java \
		gameScreen.java \
		Hex.java \
		mainScreen.java \
		myButton.java \
		hexGame.java \
		point.java

all : HW7.class

run : 
	$(JR) HW7

classes : $(CLASSES:.java=.class)

%.class : %.java
	$(JC) $(JFLAGS) $<

doc:
	$(JD) $(JDFLAGS) *.java 

clean:
	$(RM) *.class 

cleandoc:
	$(RM) -r ./javadoc
