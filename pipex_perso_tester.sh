# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pipex_perso_tester.sh                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/10 02:46:45 by iamongeo          #+#    #+#              #
#    Updated: 2022/09/12 23:10:26 by iamongeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!bin/bash

INFILE=$1
CMD1=$2
CMD2=$3
OUTFILE=$4
OUTREAL="${OUTFILE}_real"
OUTFAKE="${OUTFILE}_fake"

GREEN='\033[1;32m'
RED='\033[1;31m'

echo INFILE $INFILE
echo CMD1 $CMD1
echo CMD2 $CMD2
echo OUTFILE $OUTFILE

if [ -f $OUTFILE ]; then
	cp $OUTFILE $OUTREAL
	cp $OUTFILE $OUTFAKE
fi

echo "Testing official pipex vs 42 pipex :"
echo

echo "Official pipex :"
eval '<' $INFILE $CMD1 '|' $CMD2 '>' $OUTREAL
REAL_EXIT_CODE=$?
echo
echo "Official exit code : " $REAL_EXIT_CODE

echo
echo "42 pipex : "

eval ./pipex $INFILE '"'${CMD1}'"' '"'${CMD2}'"' $OUTFAKE
FAKE_EXIT_CODE=$?
echo
echo "42 exit code : " $FAKE_EXIT_CODE

echo 'OFFICIAL OUTPUT :'
cat $OUTREAL
echo

echo '42 PIPEX OUTPUT :'
cat $OUTFAKE
echo
echo "<-------------------< VERDICT >-------------------->"
if cmp --silent -- "$OUTREAL" "$OUTFAKE"; then
	echo $GREEN "TEST SUCCESSFUL : Both outputs are the same !"
else
	echo $RED "TEST FAILURE : Both outputs differ !"
	diff $OUTREAL $OUTFAKE
fi

echo "<---------------< EXIT CODES DIFF >---------------->"
if [ $REAL_EXIT_CODE = $FAKE_EXIT_CODE ]; then
	echo $GREEN "TEST SUCCESSFUL : Both exit codes are the same !"
else
	echo $RED "TEST FAILURE : Exit codes differ !"
fi
echo "official : $REAL_EXIT_CODE, 42 pipex : $FAKE_EXIT_CODE"
