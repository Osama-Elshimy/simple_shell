#!/bin/bash

command=gcc
flags=("-Wall" "-Werror" "-Wextra" "-pedantic" "-std=gnu89" "-ggdb")
files=(./*.c)
out_dir="./build"
exec_name="shell"

if [ ! -d "$out_dir" ]; then
	mkdir "$out_dir"
fi

betty ./*.c
"$command" "${flags[@]}" "${files[@]}" -o "$out_dir"/"$exec_name"
