@ECHO OFF

javac Reverse.java 
javac ReverseOctAbc.java 
javac WordStatInput.java
javac Scaner.java
PAUSE
java -ea -jar FastReverseTest.jar OctAbc
java -ea -jar WordStatTest.jar Base
PAUSE