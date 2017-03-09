<!DOCTYPE html>

<html>
<head>
<title>Login</title>
<?php
    $username = $_POST["username"];
    $stream = $_POST["stream"];
    $command = "./runCUS" . $username . $Stream;
    exec($command,$output,$return);
?>

</head>

<body>
<?php if (!$return): ?>

<form method="post", action="test.html">
    <input type="hidden" name="username" value="$username">
    <input type="hidden" name="stream" value="$stream">
    <input type="submit">
</form>
<?php endif; ?>

</body>
</html>
