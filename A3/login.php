<!DOCTYPE html>

<html>
<head>
<title>Login</title>
</head>

<body>
<?php
    if ($_SERVER["REQUEST_METHOD"] == "POST"){
        echo "in if";
        $username = $_POST["username"];
        $stream = $_POST["stream"];
        echo "$username";
        $command = "./runCSU" . $username . $Stream;
        exec($command,$output,$return);
        echo $output[0];
    }
?>

<form action="login.php" method="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
    Username: <input type="text" name="username"><br><br>
    Stream: <input type="text" name="stream"><br><br>
    <input type="submit" value="Login"><br>
</form>




<?php if ($output == 1): ?>

<form method="post", action="test.php">
    <input type="hidden" name="username" value="$username">
    <input type="hidden" name="stream" value="$stream">
    <input type="submit">
</form>
<?php endif; ?>

</body>
</html>
