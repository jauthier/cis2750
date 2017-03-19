<!DOCTYPE html>

<html>
<head>
<title>Login</title>
</head>

<body>
<h3>Login</h3>
<?php
    $check = 0;
    $username = "";
    if ($_SERVER["REQUEST_METHOD"] == "POST"){
        if (!empty($_POST["username"])){
            $username = $_POST["username"];
            $check = 1;
        }
    }
?>

<?php if ($check == 1): ?>
    <form id="form" method="post" action="stream.php">
        <input type="hidden" name="username" value="<?php echo $username; ?>">
    </form>
    <script type="text/javascript">
        document.getElementById('form').submit();
    </script>
<?php endif; ?>

<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
    Username: <input type="text" name="username"><br><br>
    <input type="submit" value="Login"><br>
</form>

</body>
</html>
