for file in *.c; do
    mv -- "$file" "${file%.c}.backup"
done
