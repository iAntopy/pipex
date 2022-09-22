
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


echo "Testing official pipex vs 42 pipex :"
echo

echo "Official pipex :"
eval '<' $INFILE $CMD1 '|' $CMD2 '>' $OUTREAL
cat $OUTREAL

REAL_EXIT_CODE=$?
echo
echo "Official exit code : " $REAL_EXIT_CODE
