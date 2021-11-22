#!/bin/bash

http_code=200
mime=text/html

echo -e "HTTP/1.1 $http_code OK\r"
echo "Content-type: $mime"
echo "Set-Cookie: name=NTNU"
echo
