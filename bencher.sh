#!/bin/sh

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    bencher.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfielder <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/22 23:10:52 by gfielder          #+#    #+#              #
#    Updated: 2019/02/22 23:10:52 by gfielder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


new_diffs_entry() {
	echo "" >> diffs.txt
	echo "Test Set: $(date '+%d/%m/%Y %H:%M:%S')" >> diffs.txt
}

compare() {
	./test_mine tests/test_$TEST_NUM.txt > out1.txt
	./test_davhojt tests/test_$TEST_NUM.txt > out2.txt
	DIFF=`diff out1.txt out2.txt`
	NUMDIFF=${#DIFF}
	if [ $NUM_DIFFS -gt 0 ]
	then
		if [ $NUM_DIFFS -eq 0 ]
		then
			new_diffs_entry
		fi
		echo "Diff detected:" >> diffs.txt
		echo "Test information:" >> diffs.txt
		cat tests/test_$TEST_NUM.txt.info > diffs.txt
		echo "My output:" >> diffs.txt
		cat out1.txt >> diffs.txt
		echo "davhojt's output:" >> diffs.txt
		cat out2.txt >> diffs.txt
		echo "" >> diffs.txt
		echo "Test $TEST_NUM: Discrepancy logged. See diffs.txt for details."
		NUM_DIFFS=$(($NUM_DIFFS + 1))
	else
		echo "Test $TEST_NUM: ok"
	fi
}


MAX_TEST=100
MIN_TEST=0
NUM_DIFFS=0
NUM_ARGS=$#

# Get custom number of arguments for which tests to run
if [ $NUM_ARGS -eq 1 ]
then
	MAX_TEST=$1
	MIN_TEST=0
fi
if [ $NUM_ARGS -eq 2 ]
then
	MAX_TEST=$2
	MIN_TEST=$1
fi
TEST_NUM=$MIN_TEST

# Make executables
echo "Making executables..."
make mine > /dev/null
make dav > /dev/null 
make filegen > /dev/null

# Run tests
echo "Time is now $(date '+%d/%m/%Y %H:%M:%S')"
echo "Running tests..."
while [ $TEST_NUM -lt $MAX_TEST ]
do
	compare
	TEST_NUM=$(($TEST_NUM + 1))
done

# add some space in diffs for the next set of tests
if [ $NUM_DIFFS -gt 0 ]
then
	echo "" >> diffs.txt
	echo "" >> diffs.txt
	echo "" >> diffs.txt
	echo "" >> diffs.txt
fi

