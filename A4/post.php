<!DOCTYPE html>
<!--
post.php
-->
<html>
<head>
<title>Post</title>
</head>

<body>
<?php 
    $username = $_POST["username"];
    $check = 0;
    if ($_SERVER["REQUEST_METHOD"] == "POST"){
        if (!empty($_POST["stream"]) and !empty($_POST["text"])){
            $stream = $_POST["stream"];
            $cmd = "./checkSU ".$username." ".$stream;
            exec($cmd, $output, $return);
            if ($output[0] == 1){
                $text = $_POST["text"];
                $check = 1;
            }
        }
    }
?>
<h3>Welcome <?php echo $username; ?></h3>

<?php if ($check == 1): ?>
    <?php
        $command = "./a2/post ".$username." ".$stream." ".$text;
        exec($command,$out,$return);
        $c = count($out) - 1;
        $currentPost = $out[$c];
    ?>
    <form id="form" method="post" action="stream.php">
        <input type="hidden" name="username" value="<?php echo $username; ?>">
    </form>
    <script type="text/javascript">
        document.getElementById('form').submit();
    </script>

<?php endif; ?>


<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
    <input type="hidden" name="username" value="<?php echo $username; ?>">
    Stream: <input type="text" name="stream"><br>
    Message:<br><textarea name="text" rows="5" cols="60"></textarea><br>
    <input type="submit" name="post" value="Post">
</form>>

<form method="post" action="stream.php" name="newStream">
    <input type="hidden" name="username" value="<?php echo $username; ?>">
    <input type="submit" name="newStream" value="Get New Stream">
</form>

<form method="post" action="addAuthor.php" name="addAuthor">
    <input type="hidden" name="username" value="<?php echo $username; ?>">
    <input type="submit" name="addAuthor" value="Add Author">
</form>

<form action="login.php">
    <input type="submit" name="logut" value="Logout">
</form>

</body>
</html>
