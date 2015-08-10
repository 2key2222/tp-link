# This script demonstrates how to use Unicode file names
# in a PowerShell script.
# This script is in UTF-16 encoding.

$env:DOS2UNIX_DISPLAY_ENC = "unicode"

dos2unix -i uni_el_αρχείο.txt uni_zh_文件.txt


echo "test select-string:"

# The following is not working.
# When I redirect the output to a file I see a lot of null characters inserted.
dos2unix -i uni* | select-string -encoding unicode -pattern αρχ