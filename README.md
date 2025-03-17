# Simple Shell

This is a project in which I create my own command line interpreter.

The implementation is quite simple. I capture user input and tokenize it. I then create the child process and call execvp() to execute the command/program that the user specified to execute, such as “ls” or “echo”. I then wait for the child process to terminate and print its exit status. 

To compile it, type "make" in the Linux terminal:
![image](https://github.com/user-attachments/assets/b7297192-8276-46f4-9da4-b6d50ceaeed8)

To run, type "make run".


The user’s POV is quite the same as it would be for Linux’s built-in shell. They are prompted for a command to execute and it is executed. The output is similar to the output of the built-in shell. Here is an example:
![image](https://github.com/user-attachments/assets/b001451a-ad2b-4984-be69-6ad34be4f305)
Built-in CLI (command line interpreter):
![image](https://github.com/user-attachments/assets/007043eb-4255-40ba-9676-9a5d0b2d12b0)

Here is another example:
![image](https://github.com/user-attachments/assets/c2d328d9-6aee-444f-a55f-93fe3a0d476a)

