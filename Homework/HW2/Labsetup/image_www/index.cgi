#!/bin/bash

echo "Content-type: text/html"
echo ""
cat << EOT
<!DOCTYPE html>
<html>
<head>
        <title>Welcome to our application</title>
</head>
<body>
        <p>Hello! Please enter var1 and var2 and press the submit button</p>
        <form action="submit.cgi" method="GET">
                <label>Var1</label>
                <input type="text" name="var1" value="">
                <br>
                <label>Var2</label>
                <input type="text" name="var2" value="">
                <br>
                <button type="submit">Submit</button>
        </form>
</body>
</html>
EOT
