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
            $command = "./runCSU " . $username . " " . $stream;
            exec($command,$output,$return);
        }
    }
?>
<?php if ($output[0] == 1): ?>

<form id="form" method="post" action="test.php">
    <input type="hidden" name="username" value="<?php echo $username; ?>">
    <input type="hidden" name="stream" value="<?php echo $stream; ?>">
</form>
<script type="text/javascript">
  document.getElementById('form').submit();
</script
<?php endif; ?>

<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
    Username: <input type="text" name="username"><br><br>
    Stream: <input type="text" name="stream"><br><br>
    <input type="submit" value="Login"><br>
</form>

</body>
</html>
