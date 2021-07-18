![normv3](https://github.com/busshi/pipex/actions/workflows/norm.yml/badge.svg) ![checker](https://github.com/busshi/pipex/actions/workflows/checker.yml/badge.svg)


--- PIPEX ---

The execution of the pipex program should do the same as the next shell command:
< infile1 cmd1 | cmd2 > outfile


Mandatory: ./pipex infile cmd1 cmd2 outfile


Bonus: multipipe
./pipex infile cmd1 cmd2 ... cmdn outfile
