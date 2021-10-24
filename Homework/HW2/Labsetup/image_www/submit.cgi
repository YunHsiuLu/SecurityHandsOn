#!/bin/bash

echo "Content-type: text/html"
echo ""
strings /proc/$$/environ
