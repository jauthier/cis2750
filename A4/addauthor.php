<!DOCTYPE html>
<!--
addauthor.php
-->
<html>
<head>

<?php 
    $username = $_POST["username"];

    $check = 0;
    if ($_SERVER["REQUEST_METHOD"] == "POST"){
        if (isset($_POST['btnAdd']) or isset($_POST['btnRemove'])){
            if (!empty($_POST["user"]) and !empty($_POST["stream"])){
                $user = $_POST["user"];
                $stream = $_POST["stream"];
                $check = 1;
                $cmd = "";
                if (isset($_POST['btnAdd'])){
                    $cmd = "./a2/addauthor ".$user." ".$stream;
                } elseif (isset($_POST['btnRemove'])) {
                    $cmd = "./a2/addauthor -r ".$user." ".$stream;
                }
                exec($cmd,$out,$return);
            }
        }
    }
?>

<title>\Add Author</title>
</head>

<body>

<h3>Welcome <?php echo $username; ?></h3>
<h2>Add or Remove a User</h2>

<?php if ($check == 1): ?>
    <form id="form" method="post" action="stream.php">
        <input type="hidden" name="username" value="<?php echo $username; ?>">
    </form>
    <script type="text/javascript">
        document.getElementById('form').submit();
    </script>
    <?php
        $command = "./a2/post ".$username." ".$stream." ".$text;
        exec($command, $output, $return);
        echo $output[0];
        echo $output[1];
        $currentPost = $output[2];
    ?>
<?php endif; ?>


<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
    Username: <input type="text" name="user"><br>
    Stream List: <input type="text" name="stream"><br>
    <input type="submit" name="add" value="Add" id="btnAdd">
    <input type="submit" name="remove" value="Remove" id="btnRemove">
</form>>

<form method="post" action="stream.php" name="newStream">
    <input type="hidden" name="file" value="readPost.wpml">
    <input type="hidden" name="username" value="<?php echo $username ?>">
    <input type="submit" name="newStream" value="Get New Stream">
</form>

<form method="post" action="post.php" name="post">
    <input type="hidden" name="file" value="readPost.wpml">
    <input type="hidden" name="username" value="<?php echo $username ?>">
    <input type="submit" name="post" value="Post">
</form>

<form action="login.php">
    <input type="submit" name="logut" value="Logout">
</form>

</body>
</html>
