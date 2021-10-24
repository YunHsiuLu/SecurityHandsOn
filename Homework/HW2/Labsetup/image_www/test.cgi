#!/bin/bash

echo "Content-type: text/html"
echo ""
cat <<EOT
<!DOCTYPE html>
<html>
<head>
        <title>Welcome to our application</title>
</head>
<body>
        <p>Hello! Please enter your name and e-mail address and press the submit button</p>
        <form action="submit.cgi" method="GET">
        	<input type="text" name="value1"><br />
		<input type="text" name="value2"><br />
		<input type="submit" value="Submit">
	</form>
</body>
</html>
EOT
