pipex_mgo

/*
	Examples

	---
	Mandatory
	$> ./pipex infile "ls -l" "wc -l" outfile
	should be the same as: 
	“< infile ls -l | wc -l > outfile”

	$> ./pipex infile "grep a1" "wc -w" outfile
	should be the same as: 
	“< infile grep a1 | wc -w > outfile”


	---
	Bonus
	(Handle multiple pipes.)
	$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
	should behave like: 
	"< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2"

	(Support << and >> when the first parameter is "here_doc".
	$> ./pipex here_doc LIMITER cmd cmd1 file
	should behave like: 
	"cmd << LIMITER | cmd1 >> file"


	----
	Tester:
	https://github.com/vfurmane/pipex-tester
	https://github.com/mariadaan/PIPEXaminator
*/

/*
command

### awk_1
./pipex infile "grep Hello" "awk '{count++} END {print count}'" outfile
< infile grep Hello | awk '{count++} END {print count}' > outfile
#### result_1
(none)

### awk_2
./pipex infile "grep Hello" "awk \"{count++} END {print count}\"" outfile
< infile grep Hello | awk \"{count++} END {print count}\" > outfile
#### result_2
awk: non-terminated string {count++}... at source line 1
 context is
	 >>>  <<<
awk: giving up
 source line number 2

### awk_3
./pipex infile "grep Hello" "awk '\"{count++} END {print count}\"'" outfile
< infile grep Hello | awk '\"{count++} END {print count}\"' > outfile
#### result_3
awk: syntax error at source line 1
 context is
	 >>> \ <<< "{count++} END {print count}\"
awk: bailing out at source line 1

### awk_4
./pipex infile "grep Hello" "awk \"'{count++} END {print count}'\"" outfile
< infile grep Hello | awk \"'{count++} END {print count}'\" > outfile
#### result_4
(none)

*/

### test awk

./pipex infile "grep Hello" "awk  -v -f '{count++} END {print count}' testfile testfile hello " outfile


./pipex infile "awk '{ print \$1, \$2}' ./file.txt" "cat -e" outfile

./pipex infile "awk '{max = 0; for (i=3; i<NF; i++) max = ($i > max) ? $i : max ; print max}' ./file.txt" "cat -e" outfile

./pipex infile "awk -v -f 'BEGIN{FS=","}{print $1,"FNR="FNR}' myfile myfile" "cat -e" outfile

./pipex infile "awk -v   -f  ' BEGIN{FS=\",\"}{print \$1,\"FNR=\"FNR}  '   myfile myfile " "cat -e" outfile

#### awk
awk '{ print }' infile

awk '{count++} END {print count}'

"awk -v -F '{count++} END {print count}' awkfile"



#### tester
Tester:
https://github.com/vfurmane/pipex-tester
https://github.com/mariadaan/PIPEXaminator

#### quote cmd test
./pipex infile "awk '{count++} END {print count}'" "cat -e" outfile

./pipex infile "sed -n -e ' 1p ' infile" "cat -e" outfile

./pipex infile "sed -n -e ' /H/p ' infile" "cat -e" outfile
