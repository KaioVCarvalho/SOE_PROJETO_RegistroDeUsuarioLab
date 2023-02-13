#!/bin/bash
python3 reconface.py
grep $(cat resultado.txt) info.txt | cut -d " " -f 2 > .token
./teste

