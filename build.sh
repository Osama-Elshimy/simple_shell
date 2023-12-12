#!/bin/bash

command=gcc
flags=("-Wall" "-Werror" "-Wextra" "-pedantic" "-std=gnu89" "-ggdb")
files=(./*.c)
out_dir="./build"
exec_name="shell"

if [ ! -d "$out_dir" ]; then
	mkdir "$out_dir"
fi

betty_doc=$(betty-doc ./*.c)
if [ $? -ne 0 ]; then
	echo "$betty_doc"
fi

betty_style=$(betty-style -q --no-summary ./*.c)
if [ $? -ne 0 ]; then
	echo "$betty_style"
fi

"$command" "${flags[@]}" "${files[@]}" -o "$out_dir"/"$exec_name"
