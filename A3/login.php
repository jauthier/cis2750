<!DOCTYPE html>

<html>
<head>
<title>Login</title>
<?php
    $username = $_POST["username"];
    $stream = $_POST["stream"];
    $command = "./runCUS" . $username . $Stream;
    exec($command,$output,$return);
    if (!$return)
        header("Location:./test.html")
    else
        echo "not successful";

?>

</head>

<body>
<h3>Login</h3>
<form action="login.php" method="post">
    Username: <input type="text" name="username"><br><br>
    Stream: <input type="text" name="stream"><br><br>
    <input type="submit" name="login" value="Login"><br>
</form>
</body>
</html>