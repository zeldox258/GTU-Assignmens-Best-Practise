JC = javac
JFLAGS = -classpath .
JD = javadoc
JDFLAGS = -protected -splitindex -use -author -version -d ./javadoc
RM = rm
JR = java

CLASSES = \
		HW6.java \
		Collection.java \
		Set.java \
		List.java \
		Queue.java \
		HashSet.java \
		ArrayList.java \
		Iterator.java \
		Itr.java \
		LinkedList.java

all : HW6.class

run : 
	$(JR) HW6

classes : $(CLASSES:.java=.class)

%.class : %.java
	$(JC) $(JFLAGS) $<

doc:
	$(JD) $(JDFLAGS) *.java 

clean:
	$(RM) *.class 

cleandoc:
	$(RM) -r ./javadoc