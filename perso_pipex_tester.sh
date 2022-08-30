# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    perso_pipex_tester.sh                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/30 01:57:01 by iamongeo          #+#    #+#              #
#    Updated: 2022/08/30 02:58:15 by iamongeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


if [ -f 'Pipex' ]; then
	echo "Pipex result :"
	CMD='Pipex '$1
	for (( i=2; i < $#; i++));
	do
		CMD=$CMD" \"${!i}\""
	done
	CMD=$CMD" ${@: -1}"

#	CMD="./Pipex $1 $2 $3 $4 $5 $6 $7 $8 $9 $10 $11 $12 $13 $14 $15 $16"
	echo 'Pipex cmd : '$CMD
	$( eval '$CMD' )
fi

CMD='< '$1
for (( i=2; i < $#; i++));
do
	CMD=$CMD" | ${!i}"
done
CMD=$CMD" > ${@: -1}"

echo 'cmd to exec : '$CMD
echo "VS desired result :"
$( eval '$CMD' )
