<!DOCTYPE html>
<!--
readPost.php
-->
<html>
<head>
<?php 
    $username = $_POST["username"];
    $stream = $_POST["stream"];
    $action = $_POST["action"];
    $sort = $_POST["sort"];
    $currentPost = $_POST["currentPost"];
    if ($currentPost == "-1"){
        $command = "./getCP ".$username." ".$stream." ".$sort;
        exec($command,$output,$return);
        $currentPost = $output[0];
    }

    $s = $cp = $a = "";
 ?>
<title><?php echo $stream; ?></title>
</head>

<body>

<h3>Welcome <?php echo $username; ?></h3>

<?php
    $command = "./a2/view.py ".$username." ".$stream." ".$action." ".$sort." ".$currentPost;
    exec($command, $output, $return);
    echo $output[0];
    echo $output[1];
    $currentPost = $output[2];
?>

<form method="post" action="create.php" name="next">
    <input type="hidden" name="file" value="readPost.wpml">
    <input type="hidden" name="username" value="<?php echo $username ?>">
    <input type="hidden" name="stream" value="<?php echo $stream ?>">
    <input type="hidden" name="action" value="-n">
    <input type="hidden" name="sort" value="<?php echo $sort ?>">
    <input type="hidden" name="currentPost" value="<?php echo $currentPost ?>">
    <input type="submit" name="next" value="Next">
</form>

<form method="post" action="create.php" name="previous">
    <input type="hidden" name="file" value="readPost.wpml">
    <input type="hidden" name="username" value="<?php echo $username ?>">
    <input type="hidden" name="stream" value="<?php echo $stream ?>">
    <input type="hidden" name="action" value="-p">
    <input type="hidden" name="sort" value="<?php echo $sort ?>">
    <input type="hidden" name="currentPost" value="<?php echo $currentPost ?>">
    <input type="submit" name="previous" value="Previous">
</form>

<form method="post" action="create.php" name="sortByAuthor">
    <input type="hidden" name="file" value="readPost.wpml">
    <input type="hidden" name="username" value="<?php echo $username ?>">
    <input type="hidden" name="stream" value="<?php echo $stream ?>">
    <?php 
        if ($sort == "-d")
            $s = "-r";
        else
            $s = "-d";
        if ($stream == "all"){
            $cp = $currentPost;
            $a = "-r";
        } else {
            $command = "./getCP ".$username." ".$stream." ".$s;
            exec($command,$output,$return);
            $cp = $output[0];
            $a = "-c";
        }
    ?>
    <input type="hidden" name="action" value="$a">
    <input type="hidden" name="sort" value="<?php echo $s ?>">
    <input type="hidden" name="currentPost" value="<?php echo $cp ?>">
    <input type="submit" name="sortByAuthor" value="Sort By Author">
</form>

<form method="post" action="create.php" name="getMostRecent">
    <input type="hidden" name="file" value="readPost.wpml">
    <input type="hidden" name="username" value="<?php echo $username ?>">
    <input type="hidden" name="stream" value="<?php echo $stream ?>">
    <input type="hidden" name="action" value="-r">
    <input type="hidden" name="sort" value="<?php echo $sort ?>">
    <input type="hidden" name="currentPost" value="<?php echo $currentPost ?>">
    <input type="submit" name="getMostRecent" value="Most Recent Post">
</form>


</body>
</html>
