pipex_mgo

/*
	Examples


	$> ./pipex infile "ls -l" "wc -l" outfile
	should be the same as “< infile ls -l | wc -l > outfile”

	$> ./pipex infile "grep a1" "wc -w" outfile
	should be the same as “< infile grep a1 | wc -w > outfile”

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
"< infile grep Hello | awk \"{count++} END {print count}\" > outfile"
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
