<!DOCTYPE html>

<html>
<head>
<title>Login</title>
<?php
    $username = $_POST["username"];
    $stream = $_POST["stream"];
    $command = "./runCSU" . $username . $Stream;
    exec($command,$output,$return);
?>

</head>

<body>
<form action="login.php" method="post">
    Username: <input type="text" name="username"><br><br>
    Stream: <input type="text" name="stream"><br><br>
    <input type="submit" name="login" value="Login"><br>
</form>
<?php if (!$return): ?>

<form method="post", action="test.html">
    <input type="hidden" name="username" value="$username">
    <input type="hidden" name="stream" value="$stream">
    <input type="submit">
</form>
<?php endif; ?>

</body>
</html>
