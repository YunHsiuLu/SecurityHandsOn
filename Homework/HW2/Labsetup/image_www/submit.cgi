#!/bin/bash

echo "Content-type: text/html"
echo ""

echo "<!DOCTYPE html>"
echo "<html><head>"

if [ "$REQUEST_METHOD" = "GET" ]; then

    Var1=$(echo "$QUERY_STRING" | sed 's/^.*var1=\([^&]*\).*$/\1/')
    Var1_Dec=$(echo -e $(echo "$Var1" | sed -e 's/+/ /g;s/%\(..\)/\\x\1/g;'))

    Var2=$(echo "$QUERY_STRING" | sed 's/^.*var2=\([^&]*\).*$/\1/')
    Var2_Dec=$(echo -e $(echo "$Var2" | sed -e 's/+/ /g;s/%\(..\)/\\x\1/g;'))

    echo "<title>Bash-CGI Example 1</title>"
    echo "</head><body>"
    echo "<h1>Bash-CGI Example 1</h1>"
    echo "<p>QUERY_STRING: ${QUERY_STRING}<br>var1=${Var1_Dec}<br>var2=${Var2_Dec}</p>"

else
    echo "<title>456 Wrong Request Method</title>"
    echo "</head><body>"
    echo "<h1>456</h1>"
    echo "<p>Requesting data went wrong.<br>The Request method has to be \"GET\" only!</p>"

fi

echo "<hr>"
echo "$SERVER_SIGNATURE"
echo "</body></html>"

exit 0
