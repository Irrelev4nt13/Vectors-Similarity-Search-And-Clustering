#!/bin/bash

# Clean and build the tests
make -s clean && make -s tests

# Define the directory and an array of executable names
dir=./bin/
exes=("lsh" "cube")
output_file_prefix="./tests/results"

# Define list of values for w and threshold
# w_values=("4" "10" "1000" "1500" "2000" "2500" "3000" "3500" "4500" "5000")
# t_values=("1.0" "1.1" "1.2" "1.3" "1.4" "1.5" "2.0")
w_values=("5000" "4")
t_values=("1.0")
# Iterate through the executable names and run the tests
for exe in "${exes[@]}"
do
    # Check if the file exists and remove it
    output_file="$output_file_prefix"_"$exe".txt
    if [ -e $output_file ]; then
        rm $output_file
    fi
    touch $output_file
    # Double loop to iterate over both lists
    if [ $exe == "lsh" ]; then
        # continue
        for w in "${w_values[@]}"
        do
            for t in "${t_values[@]}"
            do
                total_sum=0
                max_scale=0
                for i in {0..4}
                do
                    output=$("$dir$exe"_test -d datasets/train-images.idx3-ubyte -q datasets/t10k-images.idx3-ubyte -k 4 -L 5 -N 100 -w $w -t $t)
                    echo $output >> $output_file
                    # Determine the scale of the current output
                    scale=$(awk -v num="$output" 'BEGIN { scale = 0; split(num, parts, "."); if (length(parts[2]) > scale) scale = length(parts[2]); print scale }')     
                    # Convert the output to a floating-point number with the determined scale
                    output=$(bc <<< "scale=$scale; $output")
                    # Add the output to the total sum
                    total_sum=$(bc <<< "scale=$scale; $total_sum + $output")      
                    # Update the maximum scale if necessary
                    if ((scale > max_scale)); then
                        max_scale=$scale
                    fi
                done
                average=$(bc <<< "scale=$max_scale; $total_sum / 5")
                average=$(printf "%.${max_scale}f" "$average")
                echo "For args: w: $w, t: $t percentage: $average%" >> $output_file
            done
        done
    else
        echo "cube"
    fi
done

# Clean up
make -s clean