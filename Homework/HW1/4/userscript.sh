

echo "Starting script . . ."

<<com
echo "Command line parameters:"

for var in $@
    do
        echo "    $var"
    done

echo "Environment variables:"
echo "    SHELL=$SHELL"
echo "    USER=$USER"
echo "    TERM=$TERM"
echo "    Myname=$Myname"
com

echo "Show env:"
env
echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

echo "End of script"


