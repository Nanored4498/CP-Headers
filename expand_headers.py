#!/usr/bin/env python3

import sys

if len(sys.argv) != 3:
	print("Error: need exactly two arguments! (input and output files)")
	exit(1)

path = sys.argv[1]
i = len(path)-1
while i >= 0 and path[i] != '/': i -= 1
path = path[:i+1]
inf = open(sys.argv[1], "r")
ouf = open(sys.argv[2], "w")

lines = inf.readlines()
inf.close()

includes = []
usings = []
typedefs = set()
local = set()

i = 0
while i < len(lines):
	if i > 0 and lines[i] == '\n' and lines[i-1] == '\n':
		del lines[i]
	elif lines[i].startswith("#include <"):
		includes.append(' '.join(lines[i].split()) + '\n')
		del lines[i]
	elif lines[i].startswith("#include \""):
		name0 = lines[i].split()[1][1:-1]
		name = name0.split('/')[-1]
		if name in local:
			del lines[i]
		else:
			local.add(name)
			file = open(path + name0, "r")
			lines = lines[:i] + file.readlines() + lines[i+1:]
			file.close()
	elif lines[i].startswith("using "):
		u = ' '.join(lines[i].split()) + '\n'
		if u not in usings: usings.append(u)
		del lines[i]
	elif lines[i].startswith("typedef "):
		td = ' '.join(lines[i].split())
		if td in typedefs: del lines[i]
		else:
			typedefs.add(td)
			i += 1
	else: i += 1

file_header = list(set(includes))
if len(file_header) > 0: file_header.append("\n")
file_header += usings
# if len(file_header) > 0 and file_header[-1] != "\n": file_header.append("\n")
# file_header += list(set(typedefs))
if len(file_header) > 0 and file_header[-1] != "\n": file_header.append("\n")

if len(file_header) > 0 and file_header[-1] == "\n" and len(lines) > 0 and lines[0] == "\n": file_header = file_header[:-1]
lines = file_header + lines

ouf.writelines(lines)