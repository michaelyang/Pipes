# Pipes
Process creation and inter-process communication usage with pipes

The program's intent is to construct a "pipeline" of processes to exchange lines of text from the terminal to the screen.


To do this program, you will construct a "pipeline" of processes to exchange lines of text from the terminal to the screen. As the term is used here, a pipeline refers to an organization of processes 

wherein each process inputs data from a source (either the terminal or shared pipe) and outputs 

data to a sink (which is either the screen or shared pipe). Each process will perform some 

operation on this text string. You will implement this assignment using C processes (fork) and 

pipes.

An example of the pipeline is illustrated below. For example, as a process pipeline your first 

process reads a line of characters from a file. It passes this line to the second process (via shared 

pipe) and the second process changes the case of each letter (upper to lower, lower to upper). 

Finally, the last process writes it to a file. Your goal is to maximize how the data flows through the 

pipe. That means, when process 1 writes the first line to process 2 (via a pipe), process 2 should 

return an acknowledgement to process 1 indicating that process 2 has received a line. It then 

processes it, sends the processed line to process 3, waits for an acknowledgement from process 

3, then goes back to read the next line from process 1. This is known as a stop and wait protocol 

between two pairs of processes. You will need probably 4 pipes to do this and a good 

understanding of your protocol. You will also need to design a way for the first process to inform 

the second process that the last line of the file is being sent (this will also have to be passed from 

the second process to the third process). Good luck.
