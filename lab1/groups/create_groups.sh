# lab_group.csv
# create group id for each group
# <roll1>_<roll2> if 2 else <roll1>

removeLine() {
	while read -r line; do
		sed -i "/$line/d" $2
	done <$1
}

notPresent() {
	while read -r line; do
		# echo ${#line}
		if [ $(grep -c "$line" $2) == 0 ]; then
			echo "$line"
		fi
	done <$1
}

inputcsv=$1

cut -d',' -f3,4 ${inputcsv} | sed 's/"//g' | sed 1d | sed 's/,/_/g' | awk -F'_' '{
	if ($2 < $1)
		if (!$2)
			print $1;
		else
			print $2"_"$1;
	else
		print $1"_"$2;
	}' | sort | uniq >groups.id

awk -F '_' '{ print $1; 
				if($2)
				print $2;}' groups.id | sort -n >response.roll

uniq -c response.roll | awk '{if($1 > 1) print $2;}' >duplicate.roll

notPresent response.roll students_list.csv >invalid.roll
notPresent students_list.csv response.roll >missing.roll

while read -r line; do
	grep "$line" groups.id >>invalidGroup.id
done <invalid.roll

removeLine duplicate.roll groups.id
removeLine invalid.roll groups.id
# removeLine missing.roll groups.id

echo "Valid Group IDs"
awk '{print $1}' groups.id

echo "Roll Numbers with more than 1 entry"
awk '{print $1}' duplicate.roll >&2

echo "Group IDs with invalid Roll No"
awk '{print $1}' invalidGroup.id

echo "Roll Nos which registered for course but didn't respond to the form"
awk '{print $1}' missing.roll

rm groups.id
rm response.roll
rm duplicate.roll
rm invalid.roll
rm missing.roll
rm invalidGroup.id
