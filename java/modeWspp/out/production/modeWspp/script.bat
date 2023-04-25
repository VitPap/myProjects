@ECHO OFF

javac statWord.java
javac IntList.java
javac StringList.java
javac Wspp.java
javac WsppCountLastL.java
javac Scanner.java

PAUSE
java -ea -jar WsppTest.jar CountLastL
PAUSE
