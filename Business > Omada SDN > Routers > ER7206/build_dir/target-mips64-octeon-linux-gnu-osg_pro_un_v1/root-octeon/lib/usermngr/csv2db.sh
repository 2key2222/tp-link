#!/bin/bash

sqlite3	<<EOF
.separator ','
.show
.open ${1}
.import ${2} ${3}