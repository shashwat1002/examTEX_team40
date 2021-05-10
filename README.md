# Small protocols to keep in mind

- Always start work on a new branch and make a pull request after you're done. 
- Create an issue if you want to work on something that isn't already and issue. 
- If you start working on an issue ask to be assigned or assign yourself. 
- Please write nice commit messages. Give it a heading and explain why you've made certain changes.

- Put function declarations in header files. 
- Always protect your header files.


# Git and GitHub basics
- after you're happy with a file, save it and `git add <file-name>`
- Then commit it using `git commit -m "<small commit message>"` or just `git commit` and hit ENTER, you'll be led to window where you can write a bigger commit message.
- Then `git push origin <branch name>`.


# instructions to build the project. 

This assumes you have bash commands available 

For the build, `cmake` will be required.

Get cmake for your distribution here from the downloads page: <https://cmake.org/download/>

- `cd build` and then run `cmake ..`
- and then run `cmake --build .`
- these steps should lead to the executable in the `build` directory.

# Notes on running the program

- The question bank should be of the name `questionBank.txt`
- The questions file should be named `sample_questions_file.in`
- both the files should be in the same folder as the executable
- at which point the executable will generate the number of question papers asked for in the file.