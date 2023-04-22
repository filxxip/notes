#!/bin/bash

source env/bin/activate
./setToken.sh
python3 main.py
deactivate
