<!DOCTYPE html>

<html>
<head>
<title>Login</title>
</head>

<body>
<h3>Login</h3>
<?php
    $username = $Stream = "";
    if ($_SERVER["REQUEST_METHOD"] == "POST"){
        if (empty($_POST["username"]) or empty($_POST["stream"])){
            echo "empty";
        } else {
            $username = $_POST["username"];
            $stream = $_POST["stream"];
            echo "$username";
            $command = "./runCSU" . $username . $Stream;
            exec($command,$output,$return);
            echo "$output[0]";
        }
        
        
    }
?>
<?php if ($output[0] == 1): ?>

<form method="post", action="test.php">
    <input type="hidden" name="username" value="$username">
    <input type="hidden" name="stream" value="$stream">
    <input type="submit">
</form>
<?php endif; ?>

<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
    Username: <input type="text" name="username"><br><br>
    Stream: <input type="text" name="stream"><br><br>
    <input type="submit" value="Login"><br>
</form>

</body>
</html>
