# Get Next Line tests

Place the `tests` folder at the root of the project repository where all the turned-in files must be located. If the file structure is different, modify their path in the Makefile. 

## Mandatory part

Run one of the following :
```
make 
make OPTION=-DBUFFER_SIZE=42
```
`./gnl` : test with standard input \
`./gnl <n>`: test with standard input and print only the first n lines \
`./gnl file.txt` : test with file `file.txt` \
`./gnl file.txt <n>` : test with file `file.txt` and print only the first n lines

## Bonus part

Run one of the following :
```
make bonus
make bonus OPTION=-DBUFFER_SIZE=42
```
`./gnl` : test with standard input \
`./gnl file.txt` : test with file `file.txt` \
`./gnl file1.txt file2.txt` : test with files `file1.txt` and `file2.txt` printing one line from each file at a time. More files can be added.

