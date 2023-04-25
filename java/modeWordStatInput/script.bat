@ECHO OFF

javac WordStatInput.java
javac WordStatWordsShingles.java
PAUSE
java -ea -jar WordStatTest.jar Shingles
PAUSE