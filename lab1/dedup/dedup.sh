# TODO: Type your shell script here
read path
cd $path
master=""
fdupes . | while read file; do
    # echo "Current File: $file"
    # echo "Current Master: $master"
    if [ "x${master}" == "x" ]; then
        master=$file
        # echo "New Master: $master"
    elif cmp --silent -- "$master" "$file"; then
        # echo "Soft Link Generated from $file to $master"
        ln -sf "${master}" "${file}"
    else
        master=$file
    fi
done
